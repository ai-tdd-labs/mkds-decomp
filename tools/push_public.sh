#!/bin/bash
# push_public.sh — publiceer de HUIDIGE boom als snapshot-commit op de schone
# publieke lijn (mkds-decomp-clean). Nooit `git push public main` doen: main's
# oude history bevat de opgeruimde binaries; deze route kan dat niet lekken.
set -eu
cd "$(dirname "$0")/.."
MSG="${1:-Sync from main}"
git fetch -q public main
TIP=$(git rev-parse public/main)
TREE=$(git rev-parse HEAD^{tree})
NEW=$(git commit-tree "$TREE" -p "$TIP" -m "$MSG

Co-Authored-By: Claude Fable 5 <noreply@anthropic.com>")
git push -q public "$NEW:refs/heads/main"
echo "publiek gepusht: $NEW"
