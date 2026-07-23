#!/usr/bin/env python3
"""register_matches.py — verifieer elke handmatige/ombouw-match opnieuw met het
orakel en schrijf de bevestigde naar ai/matched.jsonl (canoniek register).
Alleen wat NU nog RESULT match=True geeft komt erin (geen blind vertrouwen)."""
import json
import pathlib
import re
import subprocess

MKDS = pathlib.Path(__file__).resolve().parent.parent
PY = str(MKDS.parent / "st/.venv/bin/python")
AIMATCH = MKDS / "tools/aimatch.py"

# (scratch, func, module, addr, size, bron)
ENTRIES = [
    ("m1_thread_getprio.c", "Os_Thread_GetPriority", "arm9", "0x0200dcd8", "0x8", "handmatig"),
    ("m2_isemulator.c", "Os_IsEmulator", "arm9", "0x0200e8fc", "0x8", "handmatig"),
    ("m3_lock_owner.c", "Os_Lock_GetOwnerId", "arm9", "0x0200cdc0", "0x8", "handmatig"),
    ("m4_thread_isterm.c", "Os_Thread_IsTerminated", "arm9", "0x0200e070", "0x14", "handmatig"),
    ("m5_cardowner.c", "SetCardOwnerArm9", "arm9", "0x0200cde0", "0x18", "handmatig"),
    ("m6_memregion.c", "Os_SetMemoryRegionStartAddress", "arm9", "0x0200ef24", "0x14", "handmatig"),
    ("m7_binsize.c", "Fs_OverlayInfo_GetBinarySize", "arm9", "0x02005880", "0x1c", "handmatig"),
    ("t1_memset32.c", "Crt0_MemorySet32", "arm9", "0x02000920", "0x14", "handmatig-nearmiss"),
    ("t2_fileinit.c", "Fs_File_Initialize", "arm9", "0x02004d80", "0x30", "handmatig"),
    ("t3_extrahandler.c", "Fs_Archive_SetExtraFileOperationHandler", "arm9", "0x02003c60", "0x20", "handmatig"),
    ("s1_wavedata.c", "SND_GetWaveDataAddress", "arm9", "0x02021968", "0x48", "ombouw:pokediamond"),
    ("x1_memchr.c", "memchr", "arm9", "0x02134db0", "0x30", "ombouw:st"),
    ("n1.c", "GX_VRAMCNT_SetLCDC_", "arm9", None, None, "ombouw:pokediamond"),
    ("n2.c", "Card_WriteRomOperation", "arm9", None, None, "ombouw:pokediamond"),
    ("n3.c", "Gfx_InitializeState", "arm9", None, None, "ombouw:pokediamond"),
    ("n4.c", "Fs_Archive_LoadFromFatFnt", "arm9", None, None, "ombouw:pokediamond"),
    ("n5.c", "VecFx32_Norm", "arm9", None, None, "ombouw:pokediamond"),
    ("n6.c", "Math_CountPopulation", "arm9", None, None, "ombouw:pokediamond"),
    ("ob_02133e50.c", "func_02133e50", "arm9", "0x02133e50", "0x134", "ombouw:st(__exit)"),
    ("ob_020218f4.c", "func_020218f4", "arm9", "0x020218f4", "0x74", "ombouw:pokediamond(SND_CalcChannelVolume)"),
    ("ob_01ff8058.c", "func_01ff8058", "itcm", "0x01ff8058", "0x15c", "ombouw:pokediamond(OS_IrqHandler_ThreadSwitch,asm)"),
    ("ob_0200e4e4.c", "Os_PopThread", "arm9", "0x0200e4e4", "0x48", "ombouw:pokediamond"),
    ("ob_02147dec.c", "FX_InvAsync", "arm9", "0x02147dec", "0x3c", "ombouw:pokediamond"),
    ("ob_02147e28.c", "FX_GetDivResult", "arm9", "0x02147e28", "0x3c", "ombouw:pokediamond"),
    ("ob_02147d88.c", "FX_DivAsync", "arm9", "0x02147d88", "0x38", "ombouw:pokediamond"),
    ("ob_0200cae4.c", "Os_EnableIrqHandler", "arm9", "0x0200cae4", "0x38", "ombouw:pokediamond"),
    ("cg_02134ae8.c", "func_02134ae8", "arm9", "0x02134ae8", "0x30", "coddog:st(scalbn)"),
    ("cg_02016694.c", "TEQSub_Fn33", "arm9", "0x02016694", "0x30", "coddog:st"),
    ("cg_020166c4.c", "TEQSub_Fn32", "arm9", "0x020166c4", "0x30", "coddog:familie"),
    ("cg_0201679c.c", "TEQSub_Fn17", "arm9", "0x0201679c", "0x30", "coddog:familie"),
    ("cg_020167cc.c", "TEQSub_Fn16", "arm9", "0x020167cc", "0x30", "coddog:familie"),
    ("cg_0201688c.c", "TEQSub_Fn3", "arm9", "0x0201688c", "0x30", "coddog:familie"),
    ("cg_020168bc.c", "TEQSub_Fn2", "arm9", "0x020168bc", "0x30", "coddog:familie"),
    ("cg_020168ec.c", "TEQSub_Fn1", "arm9", "0x020168ec", "0x30", "coddog:familie"),
    ("cg_0201691c.c", "TEQSub_Fn0", "arm9", "0x0201691c", "0x30", "coddog:familie"),
]


def verify(entry):
    scratch, func, module, addr, size, bron = entry
    src = MKDS / "ai/scratch" / scratch
    if not src.is_file():
        return None, "bestand mist"
    cmd = [PY, str(AIMATCH), "--src", str(src), "--func", func, "--quiet"]
    if module:
        cmd += ["--module", module]
    if addr:
        cmd += ["--addr", addr]
    if size:
        cmd += ["--size", size]
    try:
        r = subprocess.run(cmd, capture_output=True, text=True, cwd=MKDS, timeout=180)
    except subprocess.TimeoutExpired:
        return None, "wine timeout"
    if "match=True" in r.stdout:
        return True, "OK"
    m = re.search(r"mismatches=(\d+)/", r.stdout)
    return False, f"div {m.group(1)}" if m else "geen match"


def main():
    out = MKDS / "ai/matched.jsonl"
    rows = []
    for e in ENTRIES:
        ok, msg = verify(e)
        scratch, func, module, addr, size, bron = e
        tag = "MATCH" if ok else ("NEARMISS" if ok is False else "FOUT")
        print(f"  [{tag}] {func:<40} {msg}")
        if ok:
            rows.append({"func": func, "naam": func, "module": module,
                         "addr": addr or "?", "size": size or "?",
                         "bron": bron, "scratch": scratch})
    with out.open("w") as f:
        for r in rows:
            f.write(json.dumps(r) + "\n")
    print(f"\n{len(rows)} bevestigde matches geschreven naar ai/matched.jsonl")


if __name__ == "__main__":
    main()
