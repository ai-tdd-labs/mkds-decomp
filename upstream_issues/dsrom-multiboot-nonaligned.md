# Multiboot signature dropped on rebuild when it sits at a non-4-aligned offset (Mario Kart DS EUR)

## Summary

`ds-rom` fails to round-trip the **multiboot / Download-Play RSA signature** for Mario Kart DS (EUR). The original ROM stores the 136-byte signature block starting at `rom_size_ds = 0x1860B9E`, which is **not 4-byte aligned**. `Rom::multiboot_signature()` returns `Ok(None)` for a misaligned start (`RawMultibootSignatureError::Misaligned` is swallowed), so `dsd rom extract` writes `multiboot_signature: null` and the rebuild omits the block — 136 bytes short of the original tail, breaking a byte-exact rebuild.

## Environment

- **ds-rom version:** as bundled with dsd v0.11.0
- **ROM:** Mario Kart DS (EUR)
- **Baserom SHA-1:** `ce97d9b43f0d3ca0d48b781983e8a16f6393378f`

## Evidence

At `0x1860B9E` the original ROM has a valid multiboot signature (magic `0x00016361`):

```
1860b9e: 61 63 01 00  <128-byte RSA signature>  <4-byte key_seed>
```

`rom_size_ds` (header `0x80`) equals `0x1860B9E`, which `% 4 == 2`. In `raw/rom.rs`, `multiboot_signature()` maps `Misaligned` to `Ok(None)`:

```rust
Err(RawMultibootSignatureError::Misaligned { .. }) => Ok(None), // not aligned by 4
```

so extract records `null` and the block is lost on rebuild.

## Workaround

Manually reconstructing `multiboot_signature.yaml` from the original bytes and pointing the config at it restores a byte-exact rebuild:

```yaml
magic: 90977
rsa_signature: !!binary |
  <base64 of the 128 bytes at 0x1860ba2>
key_seed: <u32 at 0x1860c22>
```

## Suggested fix

The DS accepts the signature at `rom_size_ds` regardless of 4-alignment (this ROM ships and boots that way). `multiboot_signature()` should still parse and preserve the block when only the alignment check fails — the magic number is the real validity gate. At minimum, extract could warn and emit the raw bytes so the rebuild is not silently 136 bytes short.

## Why it matters

Without this, no byte-exact rebuild of Mario Kart DS EUR is possible; the tail is always short by the signature block. Likely affects other retail carts whose signature offset is not 4-aligned.
