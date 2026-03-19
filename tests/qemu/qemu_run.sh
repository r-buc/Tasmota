#!/usr/bin/env bash
# tests/qemu/qemu_run.sh
#
# Boot a Tasmota ESP32 firmware image inside Espressif's QEMU fork.
#
# ---------------------------------------------------------------------------
# Prerequisites – install Espressif's QEMU fork
# ---------------------------------------------------------------------------
# Espressif maintains an official QEMU fork with ESP32 support at:
#   https://github.com/espressif/qemu
#
# Quick-install on Ubuntu/Debian:
#   sudo apt-get install -y git ninja-build libglib2.0-dev libpixman-1-dev \
#       libslirp-dev python3 python3-pip
#   git clone --depth 1 --branch esp-develop \
#       https://github.com/espressif/qemu.git /opt/qemu-esp32
#   cd /opt/qemu-esp32
#   ./configure --target-list=xtensa-softmmu \
#               --enable-slirp \
#               --disable-werror
#   make -j$(nproc)
#   # The resulting binary is: /opt/qemu-esp32/build/qemu-system-xtensa
#
# Alternatively you can use the pre-built binaries distributed as part of
# Espressif's IDF Docker image:
#   docker pull espressif/idf
#   # then run qemu-system-xtensa from within the container
# ---------------------------------------------------------------------------

set -euo pipefail

# Path to the merged raw flash image produced by the build_qemu_esp32 workflow.
# The image must be a flat binary starting at flash offset 0x0 (created with
# `esptool.py merge_bin --fill-flash-size 4MB ...`).
FLASH_IMAGE="${1:-tasmota32-qemu-flash.bin}"

# Path to the qemu-system-xtensa binary (override with the QEMU_BINARY env var).
QEMU_BINARY="${QEMU_BINARY:-qemu-system-xtensa}"

if [ ! -f "$FLASH_IMAGE" ]; then
  echo "ERROR: Flash image not found: $FLASH_IMAGE"
  echo "Usage: $0 <path-to-tasmota32-qemu-flash.bin>"
  exit 1
fi

echo "Booting Tasmota ESP32 in QEMU..."
echo "  Flash image : $FLASH_IMAGE"
echo "  QEMU binary : $QEMU_BINARY"
echo ""
echo "Serial output will appear below. Press Ctrl-A X to quit QEMU."
echo "--------------------------------------------------------------"

# -nographic     : disable graphical output; use the terminal for serial I/O
# -machine esp32 : select the ESP32 machine model (Xtensa LX6 dual-core)
# -drive ...     : attach the merged flash image as an MTD flash device
# -serial mon:stdio : route UART0 (console) to stdout and open the QEMU monitor
"${QEMU_BINARY}" \
  -nographic \
  -machine esp32 \
  -drive "file=${FLASH_IMAGE},if=mtd,format=raw" \
  -serial mon:stdio
