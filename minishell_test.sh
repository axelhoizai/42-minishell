#!/bin/bash

# Chemin vers minishell
MINISHELL="./minishell test"
MINISHELL_VALGRIND="valgrind --leak-check=full --track-origins=yes ./minishell test"

# Répertoire pour les fichiers Valgrind
VALGRIND_DIR="valgrind_logs"

# Supprimer le dossier Valgrind s'il existe, puis le recréer
if [ -d "$VALGRIND_DIR" ]; then
    rm -rf "$VALGRIND_DIR"
fi
mkdir -p "$VALGRIND_DIR"

# Fichiers temporaires pour comparer les résultats
TMP_MINISHELL_OUTPUT="minishell_output.txt"
TMP_BASH_OUTPUT="bash_output.txt"
TMP_DIFF_OUTPUT="diff_output.txt"

# Fonction pour tester une commande
test_builtin() {
    local cmd="$1"
    local test_name=$(echo "$cmd" | tr ' ' '_' | tr -cd '[:alnum:]_') # Nom du fichier basé sur la commande
    local valgrind_log="$VALGRIND_DIR/${test_name}_valgrind.txt"
    
    echo "Testing: $cmd"

    # Exécuter la commande dans minishell (sans Valgrind) et afficher le résultat dans le terminal
    echo "$cmd" | $MINISHELL > $TMP_MINISHELL_OUTPUT 2>&1
    if [ $? -ne 0 ]; then
        echo "[ERROR] Minishell crashed on: $cmd"
        return
    fi

    # Exécuter la commande dans bash pour comparaison
    echo "$cmd" | bash --posix > $TMP_BASH_OUTPUT 2>&1

    # Comparer les résultats de sortie
    if diff $TMP_MINISHELL_OUTPUT $TMP_BASH_OUTPUT > $TMP_DIFF_OUTPUT; then
        echo "[OK] $cmd"
    else
        echo "[FAIL] $cmd"
        echo "Diff between minishell and bash output:"
        cat $TMP_DIFF_OUTPUT
    fi
    echo "$cmd" | $MINISHELL_VALGRIND 
    # Exécuter la commande dans minishell avec Valgrind pour capturer les informations sur la mémoire
    echo "$cmd" | valgrind --leak-check=full --log-file="$valgrind_log" $MINISHELL > /dev/null 2>&1
    echo "Valgrind log saved to $valgrind_log"
}

# Vérification des options
if [ $# -eq 0 ]; then
    # Aucun argument : tester toutes les commandes avec et sans Valgrind
    echo "Running all tests with and without Valgrind..."
    for test_file in commands/*.txt; do
        while read -r cmd; do
            test_builtin "$cmd"
        done < "$test_file"
    done
elif [ "$1" == "no" ]; then
    # Option "no" : tester toutes les commandes sans Valgrind
    echo "Running all tests without Valgrind..."
    for test_file in commands/*.txt; do
        while read -r cmd; do
            echo "Testing: $cmd"
            echo "$cmd" | $MINISHELL > $TMP_MINISHELL_OUTPUT 2>&1
            echo "$cmd" | bash --posix > $TMP_BASH_OUTPUT 2>&1
            if diff $TMP_MINISHELL_OUTPUT $TMP_BASH_OUTPUT > $TMP_DIFF_OUTPUT; then
                echo "[OK] $cmd"
            else
                echo "[FAIL] $cmd"
                cat $TMP_DIFF_OUTPUT
            fi
        done < "$test_file"
    done
else
    # Option spécifique : tester seulement les commandes d'un fichier
    test_file="commands/$1.txt"
    if [ -f "$test_file" ]; then
        echo "Running tests for commands in $test_file..."
        while read -r cmd; do
            test_builtin "$cmd"
        done < "$test_file"
    else
        echo "Test file $test_file not found."
        exit 1
    fi
fi

# Nettoyer les fichiers temporaires (mais garder les fichiers Valgrind)
rm -f $TMP_MINISHELL_OUTPUT $TMP_BASH_OUTPUT $TMP_DIFF_OUTPUT

echo "Tests finished. Valgrind logs are in the $VALGRIND_DIR directory."
