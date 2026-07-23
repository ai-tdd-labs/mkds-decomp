#!/bin/bash
# install_hooks.sh — koppel de pre-commit-poortwachter (na elke verse clone draaien)
cd "$(dirname "$0")/.."
ln -sf ../../tools/precommit_guard.sh .git/hooks/pre-commit
echo "pre-commit-poortwachter geïnstalleerd"
