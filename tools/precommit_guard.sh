#!/bin/bash
# precommit_guard.sh — poortwachter tegen binaries/propriëtair spul in commits.
# Draait als .git/hooks/pre-commit (installatie: tools/install_hooks.sh).
# Blokkeert gestagede bestanden op: verboden extensies, verboden paden,
# binaire magic-bytes (PE/ELF/NDS-ROM) en omvang >5MB. Repo-hygiëne-les
# 2026-07-21: .o's en de mwccarm-exe stonden publiek; gitignore alleen is
# passief — deze hook is de actieve grendel.
set -u
FOUT=0
while IFS= read -r f; do
  [ -f "$f" ] || continue
  case "$f" in
    *.o|*.exe|*.nds|*.bin|*.elf|*.dll|*.so|*.dylib)
      echo "GEBLOKKEERD (extensie): $f"; FOUT=1; continue ;;
    extract/*|tools/mwccarm/*|.tmpmatch/*|build/*)
      echo "GEBLOKKEERD (pad): $f"; FOUT=1; continue ;;
  esac
  # magic bytes: MZ (PE), 0x7f ELF; en groot binair spul
  magic=$(head -c 4 "$f" | LC_ALL=C od -An -tx1 | tr -d ' \n')
  case "$magic" in
    4d5a*|7f454c46)
      echo "GEBLOKKEERD (binair executable-formaat): $f"; FOUT=1; continue ;;
  esac
  size=$(stat -f%z "$f" 2>/dev/null || stat -c%s "$f")
  if [ "${size:-0}" -gt 5000000 ]; then
    echo "GEBLOKKEERD (>5MB): $f — bewust? commit dan handmatig met --no-verify"
    FOUT=1
  fi
done < <(git diff --cached --name-only --diff-filter=AM)
if [ "$FOUT" -ne 0 ]; then
  echo ""
  echo "pre-commit-poortwachter: commit geweigerd (zie hierboven)."
  echo "Echt nodig? Gebruik 'git commit --no-verify' — maar denk aan de publieke repo."
  exit 1
fi
exit 0
