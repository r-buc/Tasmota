/*
 * qemu_openeth.c – OpenCores Ethernet MAC support for QEMU-based Tasmota builds.
 *
 * When building with FIRMWARE_TASMOTA32_QEMU this file does two things:
 *
 *  1. Compiles the OpenCores MAC driver (esp_eth_mac_openeth.c) inline.
 *     In production CI builds with CONFIG_ETH_USE_OPENETH=y the symbol already
 *     lives in the rebuilt libesp_eth.a; in that case the FIRMWARE_TASMOTA32_QEMU
 *     guard prevents a duplicate definition.
 *
 *  2. Defines __wrap_esp_eth_mac_new_esp32 so that the linker option
 *     -Wl,--wrap=esp_eth_mac_new_esp32 (added to build_flags for the QEMU env)
 *     redirects every call originating from the prebuilt Arduino ETH library to
 *     use the OpenCores MAC instead of the Synopsys GMAC.  Without this, the
 *     Synopsys driver accesses register offsets that QEMU does not map for its
 *     OpenCores model, causing a LoadStorePIFAddrError panic.
 *
 * SPDX-FileCopyrightText: 2024 Tasmota Contributors
 * SPDX-License-Identifier: GPL-3.0-only
 */

#ifdef FIRMWARE_TASMOTA32_QEMU

/*
 * Include the OpenCores MAC implementation directly.
 * The openeth_impl/ subdirectory only contains .impl and .h files, not .c files,
 * so PlatformIO does not compile it as a separate translation unit.
 */
#include "openeth_impl/openeth.h"
#include "openeth_impl/esp_openeth.h"

/* Include the actual implementation (renamed .impl so PlatformIO ignores it) */
#include "openeth_impl/esp_eth_mac_openeth.impl"

/*
 * Linker-wrap trampoline.
 *
 * -Wl,--wrap=esp_eth_mac_new_esp32 causes the linker to redirect every call to
 * esp_eth_mac_new_esp32 (including the one inside the prebuilt Ethernet library)
 * to __wrap_esp_eth_mac_new_esp32.
 *
 * We simply call esp_eth_mac_new_openeth with the generic eth_mac_config_t that
 * ETH.begin() already set up (the ESP32-specific esp32_config is irrelevant for
 * the OpenCores MAC).
 */
#include <esp_eth_mac.h>
#include <esp_eth_mac_openeth.h>

esp_eth_mac_t *__wrap_esp_eth_mac_new_esp32(
        const void *esp32_config, const eth_mac_config_t *config)
{
    return esp_eth_mac_new_openeth(config);
}

#endif  /* FIRMWARE_TASMOTA32_QEMU */
