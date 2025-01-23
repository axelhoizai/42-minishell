#!/bin/bash

# Chemin vers minishell
MINISHELL="./minishell"

# Fichier temporaire pour comparer les résultats
TMP_MINISHELL_OUTPUT="minishell_output.txt"
TMP_BASH_OUTPUT="bash_output.txt"

# Fonction pour tester une commande
test_builtin() {
    local cmd="$1"
    echo "Testing: $cmd"

    # Exécuter la commande dans minishell
    if ! echo "$cmd" | $MINISHELL > $TMP_MINISHELL_OUTPUT 2>&1; then
        echo "[ERROR] Minishell crashed on: $cmd"
        return
    fi

    # Exécuter la commande dans bash --posix
    echo "$cmd" | bash --posix > $TMP_BASH_OUTPUT 2>&1

    # Comparer les résultats
    if diff -q $TMP_MINISHELL_OUTPUT $TMP_BASH_OUTPUT > /dev/null; then
        echo "[OK] $cmd"
    else
        echo "[FAIL] $cmd"
        echo "minishell output:"
        cat $TMP_MINISHELL_OUTPUT
        echo "Expected output (bash):"
        cat $TMP_BASH_OUTPUT
    fi
}

# Tests pour les builtins
test_builtin "echo Hello, World!"
test_builtin "echo -n No new line"
test_builtin "cd /tmp && pwd"
test_builtin "cd /nonexistent && pwd"
test_builtin "pwd"
# test_builtin "export TEST_VAR=42 && env | grep TEST_VAR"
# test_builtin "unset TEST_VAR && env | grep TEST_VAR"
test_builtin "exit 42"
test_builtin "exit"

# Nettoyer les fichiers temporaires
rm -f $TMP_MINISHELL_OUTPUT $TMP_BASH_OUTPUT
