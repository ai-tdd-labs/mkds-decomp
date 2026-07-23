#!/usr/bin/env bash
# wibo_up.sh — bring up the fast x86 compiler backend (qemu-i386 + wibo).
#
# mwccarm.exe is a 32-bit x86 Windows binary. On Apple Silicon, Rosetta cannot
# run 32-bit x86 under Linux and a full x86 QEMU VM is too slow. This runs the
# compiler under qemu-i386 user-mode + wibo inside a tiny Docker container that
# mounts the repo root at the SAME absolute path, so host paths resolve unchanged.
# Objects are BYTE-IDENTICAL to the wine backend, ~4x faster serial / ~9x parallel,
# with no wine fork-exhaustion.
#
# Usage:
#   tools/wibo_up.sh                       # start colima + the mkds-cc container
#   MKDS_CC=wibo tools/aimatch.py ...      # any tool that shells the oracle
#   MKDS_CC=wibo tools/permute.py ...      # the permuter, ~9x faster
#
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"   # ai-assisted-decomp
IMG=mkds-wibo-qemu
NAME="${MKDS_WIBO_CONTAINER:-mkds-cc}"

# 1) colima (free Docker runtime; arm64 VM, Rosetta unused for the compiler)
if ! docker ps >/dev/null 2>&1; then
  echo "colima starten..."
  colima start --cpu 4 --memory 6 --arch aarch64 --vm-type vz --vz-rosetta
fi

# 2) image must exist (built once by the setup; see tools/wibo-img/)
if ! docker image inspect "$IMG" >/dev/null 2>&1; then
  echo "!! image $IMG ontbreekt — bouw het eerst (tools/wibo-img/Dockerfile.qemu)"; exit 1
fi

# 3) persistent container, repo root mounted at the same absolute path
if [ "$(docker inspect -f '{{.State.Running}}' "$NAME" 2>/dev/null)" != "true" ]; then
  docker rm -f "$NAME" >/dev/null 2>&1 || true
  docker run -d --name "$NAME" -v "$ROOT":"$ROOT" -w "$ROOT" "$IMG" sleep infinity >/dev/null
  echo "container $NAME gestart (mount $ROOT op zelfde pad)"
else
  echo "container $NAME draait al"
fi

# smoke test
docker exec "$NAME" bash -c 'test -x /usr/local/bin/wibo-i686 && echo "wibo klaar"'
echo "OK — gebruik: MKDS_CC=wibo <tool>"
