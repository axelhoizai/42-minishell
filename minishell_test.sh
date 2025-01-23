#!/bin/bash

# Chemin vers minishell
MINISHELL="./minishell"

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

    # Exécuter la commande dans minishell avec Valgrind pour capturer les informations sur la mémoire
    echo "$cmd" | valgrind --leak-check=full --log-file="$valgrind_log" $MINISHELL > /dev/null 2>&1
    echo "Valgrind log saved to $valgrind_log"
}

# Liste des commandes à tester
test_builtin "echo Hello, World!"
test_builtin "echo -n No new line"
test_builtin "cd /tmp && pwd"
test_builtin "cd /nonexistent && pwd"
test_builtin "pwd"
# test_builtin "export TEST_VAR=42 && env | grep TEST_VAR"
# test_builtin "unset TEST_VAR && env | grep TEST_VAR"
test_builtin "exit 42"
test_builtin "exit"

# Nettoyer les fichiers temporaires (mais garder les fichiers Valgrind)
rm -f $TMP_MINISHELL_OUTPUT $TMP_BASH_OUTPUT $TMP_DIFF_OUTPUT

echo "Tests finished. Valgrind logs are in the $VALGRIND_DIR directory"
