#!/usr/bin/env bash
# tests/qemu/qemu_run.sh
#
# Boot a Tasmota ESP32 firmware image inside Espressif's QEMU fork.
#
# Use the QEMU-compatible firmware variant built with the tasmota32-qemu
# PlatformIO environment (-DFIRMWARE_TASMOTA32_QEMU).  This variant disables
# WiFi initialisation at startup because the Espressif QEMU ESP32 machine does
# not emulate the ESP32 WiFi hardware.
#
# The merged flash image (tasmota32-qemu-flash.bin) is produced by the
# build_qemu_esp32.yml GitHub Actions workflow and uploaded as the
# tasmota-qemu-esp32-image artifact.
#
# ---------------------------------------------------------------------------
# Prerequisites – install Espressif's QEMU fork
# ---------------------------------------------------------------------------
# Espressif maintains an official QEMU fork with ESP32 support at:
#   https://github.com/espressif/qemu
#
# Quick-install from a pre-built release binary (Ubuntu/Debian, x86-64):
#   sudo apt-get install -y libglib2.0-0 libpixman-1-0 libsdl2-2.0-0 libslirp0
#   RELEASE=esp-develop-9.2.2-20250228
#   VERSION=esp_develop_9.2.2_20250228
#   curl -L -o /tmp/qemu-esp32.tar.xz \
#     "https://github.com/espressif/qemu/releases/download/${RELEASE}/qemu-xtensa-softmmu-${VERSION}-x86_64-linux-gnu.tar.xz"
#   tar -xf /tmp/qemu-esp32.tar.xz -C /opt
#   export PATH="/opt/qemu/bin:$PATH"
#
# Build from source (if a pre-built binary is not available for your platform):
#   sudo apt-get install -y git ninja-build libglib2.0-dev libpixman-1-dev \
#       libslirp-dev python3 python3-pip
#   git clone --depth 1 --branch esp-develop \
#       https://github.com/espressif/qemu.git /opt/qemu-src
#   cd /opt/qemu-src
#   ./configure --target-list=xtensa-softmmu \
#               --enable-slirp \
#               --disable-werror
#   make -j$(nproc)
#   # The resulting binary is: /opt/qemu-src/build/qemu-system-xtensa
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
echo "The tasmota32-qemu firmware uses the ESP32 built-in EMAC for networking."
echo "QEMU's open_eth model emulates this MAC and routes it through SLIRP"
echo "(user-mode networking).  Add networking with:"
echo "  -nic user,model=open_eth,hostfwd=tcp::18080-:80"
echo "then query Tasmota via HTTP:"
echo "  curl http://localhost:18080/cm?cmnd=Status%200"
echo ""
echo "Serial output will appear below. Press Ctrl-A X to quit QEMU."
echo "--------------------------------------------------------------"

# -nographic     : disable graphical output; use the terminal for serial I/O
# -machine esp32 : select the ESP32 machine model (Xtensa LX6 dual-core)
# -drive ...     : attach the merged flash image as an MTD flash device
# -nic user,...  : SLIRP user-mode networking via OpenCores Ethernet (open_eth);
#                  host port 18080 is forwarded to guest port 80 (Tasmota web UI)
# -serial mon:stdio : route UART0 (console) to stdout and open the QEMU monitor
"${QEMU_BINARY}" \
  -nographic \
  -machine esp32 \
  -drive "file=${FLASH_IMAGE},if=mtd,format=raw" \
  -nic user,model=open_eth,hostfwd=tcp::18080-:80 \
  -serial mon:stdio

