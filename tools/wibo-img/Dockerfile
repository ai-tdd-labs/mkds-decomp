# Fast x86 compiler backend for mwccarm on non-x86 hosts.
# qemu-i386 emulates the 32-bit compiler; wibo provides the Win32 loader.
# Build:  docker build -t mkds-wibo-qemu tools/wibo-img
FROM debian:bookworm-slim
RUN apt-get update && apt-get install -y --no-install-recommends \
      qemu-user-static python3 ca-certificates curl \
    && curl -sL -o /usr/local/bin/wibo-i686 \
       https://github.com/decompals/wibo/releases/download/1.2.0/wibo-i686 \
    && chmod +x /usr/local/bin/wibo-i686 \
    && apt-get purge -y curl && apt-get autoremove -y \
    && rm -rf /var/lib/apt/lists/*
WORKDIR /work
