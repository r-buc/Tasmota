/*
  xdrv_82_esp32_ethernet.ino - ESP32 (PoE) ethernet support for Tasmota

  Copyright (C) 2021  Theo Arends

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef ESP32
#include "sdkconfig.h"
#ifdef CONFIG_ETH_ENABLED
#ifdef USE_ETHERNET
/*********************************************************************************************\
 * Ethernet support for ESP32
 *
 * Dedicated fixed Phy pins (EMAC)
 * GPIO17 - EMAC_CLK_OUT_180
 * GPIO19 - EMAC_TXD0(RMII)
 * GPIO21 - EMAC_TX_EN(RMII)
 * GPIO22 - EMAC_TXD1(RMII)
 * GPIO25 - EMAC_RXD0(RMII)
 * GPIO26 - EMAC_RXD1(RMII)
 * GPIO27 - EMAC_RX_CRS_DV
 *
 * {"NAME":"Olimex ESP32-PoE","GPIO":[1,1,1,1,1,1,0,0,5536,1,1,1,1,0,5600,0,0,0,0,5568,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1],"FLAG":0,"BASE":1}
 * GPIO12 = ETH POWER
 * GPIO18 = ETH MDIO
 * GPIO23 = ETH MDC
 * #define ETH_TYPE          0                   // LAN8720
 * #define ETH_CLKMODE       ETH_CLOCK_GPIO17_OUT
 * #define ETH_ADDRESS       0
 *
 * {"NAME":"wESP32","GPIO":[0,0,1,0,1,1,0,0,1,1,1,1,5568,5600,1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1],"FLAG":0,"BASE":1}
 * GPIO16 = ETH MDC
 * GPIO17 = ETH MDIO
 * #define ETH_TYPE          0                   // LAN8720
 * #define ETH_CLKMODE       ETH_CLOCK_GPIO0_IN
 * #define ETH_ADDRESS       0
 *
 * {"NAME":"WT32-ETH01","GPIO":[1,1,1,1,1,1,0,0,1,0,1,1,3840,576,5600,0,0,0,0,5568,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,1],"FLAG":0,"BASE":1}
 * GPIO16 = Force Hi
 * GPIO18 = ETH MDIO
 * GPIO23 = ETH MDC
 * #define ETH_TYPE          0                   // LAN8720
 * #define ETH_CLKMODE       ETH_CLOCK_GPIO0_IN
 * #define ETH_ADDRESS       1
 *
 * Used SPI
 * SPI_MOSI
 * SPI_MISO
 * SPI_CLK
 * SPI_RST = Tasmota ETH_POWER
 * SPI_IRQ = Tasmota ETH_MDIO
 * SPI_CS  = Tasmota ETH_MDC
\*********************************************************************************************/

#define XDRV_82           82

/*
// Olimex ESP32-PoE
#define ETH_CLKMODE       ETH_CLOCK_GPIO17_OUT
#define ETH_POWER_PIN     12

//********************************************************************************************

#ifndef ETH_ADDRESS
#define ETH_ADDRESS       0                      // ETH.h uint8_t:          0 = PHY0 .. 31 = PHY31
#endif

#ifndef ETH_TYPE
#define ETH_TYPE          0                      // 0 = LAN8720, 1 = TLK110/IP101, 2 = RTL8201, 3 = DP83848, 4 = DM9051, 5 = KSZ8081, 6 = KSZ8041, 7 = JL1101, 8 = W5500, 9 = KSZ8851
#endif

#ifndef ETH_CLKMODE
#define ETH_CLKMODE       ETH_CLOCK_GPIO0_IN     // ETH.h eth_clock_mode_t: 0 = ETH_CLOCK_GPIO0_IN, 1 = ETH_CLOCK_GPIO0_OUT, 2 = ETH_CLOCK_GPIO16_OUT, 3 = ETH_CLOCK_GPIO17_OUT
#endif
*/

#include <ETH.h>

#define ETH_USES_SPI    0x80                    // Use the highest significant bit to mark SPI Ethernet

const uint8_t eth_type_xtable[] = {
#if CONFIG_ETH_USE_ESP32_EMAC
  ETH_PHY_LAN8720,      //  0 = LAN8720
  ETH_PHY_TLK110,       //  1 = TLK110/IP101
  ETH_PHY_RTL8201,      //  2 = RTL8201
  ETH_PHY_DP83848,      //  3 = DP83848

#if CONFIG_ETH_SPI_ETHERNET_DM9051
  ETH_PHY_DM9051  | ETH_USES_SPI, //  4 = 10 = DM9051
#else
  0,                    //  4 = 10 = DM9051
#endif

  ETH_PHY_KSZ8081,      //  5 = KSZ8081
  ETH_PHY_KSZ8041,      //  6 = KSZ8041
  ETH_PHY_JL1101,       //  7 = JL1101
#else
  0,                    //  0 = LAN8720
  0,                    //  1 = TLK110/IP101
  0,                    //  2 = RTL8201
  0,                    //  3 = DP83848
  
#if CONFIG_ETH_SPI_ETHERNET_DM9051
  ETH_PHY_DM9051  | ETH_USES_SPI, //  4 = 10 = DM9051
#else
  0,                    //  4 = 10 = DM9051
#endif

  0,                    //  5 = KSZ8081
  0,                    //  6 = KSZ8041
  0,                    //  7 = JL1101
#endif // CONFIG_ETH_USE_ESP32_EMAC

#if CONFIG_ETH_SPI_ETHERNET_W5500
  ETH_PHY_W5500   | ETH_USES_SPI,     //  8 = W5500
#else
  0,                    //  8 = W5500
#endif

#if CONFIG_ETH_SPI_ETHERNET_KSZ8851SNL
  ETH_PHY_KSZ8851 | ETH_USES_SPI,     //  9 = KSZ8851
#else
  0,                    //  9 = KSZ8851
#endif
};
char eth_hostname[sizeof(TasmotaGlobal.hostname)];
uint8_t eth_config_change;

/*********************************************************************************************\
 * OpenCores Ethernet MAC - QEMU builds only
 *
 * QEMU emulates an OpenCores Ethernet MAC at the same register base and
 * interrupt source as the real ESP32 EMAC.  The standard EMAC driver
 * (esp_eth_mac_new_esp32) targets the Synopsys GMAC register layout, which
 * differs from OpenCores and causes a LoadStorePIFAddrError panic.
 *
 * CONFIG_ETH_USE_OPENETH=y (set via custom_sdkconfig in the tasmota32-qemu
 * PlatformIO env) makes the IDF rebuild include esp_eth_mac_new_openeth() in
 * libesp_eth.a.  EthernetInitOpenCores() below calls it directly, bypassing
 * ETH.begin() which always uses esp_eth_mac_new_esp32().
\*********************************************************************************************/
#if defined(FIRMWARE_TASMOTA32_QEMU) && defined(CONFIG_ETH_USE_OPENETH)
#include <esp_eth_mac_openeth.h>
#include <esp_eth_netif_glue.h>

#define QEMU_OPENETH_RX_TASK_STACK  4096  // RX task stack size for OpenCores MAC
#define QEMU_OPENETH_PHY_ADDR       1     // DP83848C PHY address in Espressif QEMU

static esp_eth_handle_t qemu_eth_handle = nullptr;
static esp_netif_t     *qemu_eth_netif  = nullptr;

static void QemuEthEventHandler(void *arg, esp_event_base_t event_base,
                                 int32_t event_id, void *event_data) {
  if (event_base == IP_EVENT && event_id == IP_EVENT_ETH_GOT_IP) {
    ip_event_got_ip_t *ev = (ip_event_got_ip_t *)event_data;
    Settings->eth_ipv4_address[1] = ev->ip_info.gw.addr;
    Settings->eth_ipv4_address[2] = ev->ip_info.netmask.addr;
    TasmotaGlobal.rules_flag.eth_connected = 1;
    TasmotaGlobal.global_state.eth_down = 0;
    WiFiHelper::scrubDNS();
    AddLog(LOG_LEVEL_DEBUG, PSTR("ETH: IPv4 %_I, mask %_I, gateway %_I"),
           ev->ip_info.ip.addr, ev->ip_info.netmask.addr, ev->ip_info.gw.addr);
  } else if (event_base == ETH_EVENT) {
    if (event_id == ETHERNET_EVENT_CONNECTED) {
      esp_eth_handle_t eth_handle = *(esp_eth_handle_t *)event_data;
      uint8_t mac_addr[6] = {0};
      esp_eth_ioctl(eth_handle, ETH_CMD_G_MAC_ADDR, mac_addr);
      AddLog(LOG_LEVEL_INFO, PSTR(D_LOG_ETH D_CONNECTED ", Mac %02X:%02X:%02X:%02X:%02X:%02X, Hostname %s"),
             mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5],
             eth_hostname);
    } else if (event_id == ETHERNET_EVENT_DISCONNECTED) {
      TasmotaGlobal.rules_flag.eth_disconnected = 1;
      TasmotaGlobal.global_state.eth_down = 1;
      AddLog(LOG_LEVEL_INFO, PSTR(D_LOG_ETH "Disconnected"));
    }
  }
}

static void EthernetInitOpenCores(void) {
  Network.begin();  // Initialise the Arduino/lwIP networking stack

  eth_mac_config_t mac_config = ETH_MAC_DEFAULT_CONFIG();
  mac_config.rx_task_stack_size = QEMU_OPENETH_RX_TASK_STACK;
  esp_eth_mac_t *mac = esp_eth_mac_new_openeth(&mac_config);
  if (!mac) {
    AddLog(LOG_LEVEL_ERROR, PSTR(D_LOG_ETH "openeth MAC init failed"));
    return;
  }

  eth_phy_config_t phy_config = ETH_PHY_DEFAULT_CONFIG();
  phy_config.phy_addr = QEMU_OPENETH_PHY_ADDR;  // DP83848C PHY address in Espressif QEMU
  phy_config.reset_gpio_num = -1;
  esp_eth_phy_t *phy = esp_eth_phy_new_dp83848(&phy_config);
  if (!phy) {
    AddLog(LOG_LEVEL_ERROR, PSTR(D_LOG_ETH "DP83848 PHY init failed"));
    return;
  }

  esp_eth_config_t eth_config = ETH_DEFAULT_CONFIG(mac, phy);
  if (esp_eth_driver_install(&eth_config, &qemu_eth_handle) != ESP_OK) {
    AddLog(LOG_LEVEL_ERROR, PSTR(D_LOG_ETH "driver install failed"));
    return;
  }

  esp_netif_config_t netif_cfg = ESP_NETIF_DEFAULT_ETH();
  qemu_eth_netif = esp_netif_new(&netif_cfg);
  esp_eth_netif_glue_handle_t glue = esp_eth_new_netif_glue(qemu_eth_handle);
  if (!glue) {
    AddLog(LOG_LEVEL_ERROR, PSTR(D_LOG_ETH "netif glue init failed"));
    return;
  }
  esp_netif_attach(qemu_eth_netif, glue);
  esp_netif_set_hostname(qemu_eth_netif, eth_hostname);

  esp_event_handler_instance_register(ETH_EVENT, ESP_EVENT_ANY_ID,
                                       &QemuEthEventHandler, nullptr, nullptr);
  esp_event_handler_instance_register(IP_EVENT, IP_EVENT_ETH_GOT_IP,
                                       &QemuEthEventHandler, nullptr, nullptr);

  if (esp_eth_start(qemu_eth_handle) != ESP_OK) {
    AddLog(LOG_LEVEL_ERROR, PSTR(D_LOG_ETH "start failed"));
  }
}
#endif  // FIRMWARE_TASMOTA32_QEMU && CONFIG_ETH_USE_OPENETH

extern esp_netif_t* get_esp_interface_netif(esp_interface_t interface);

void EthernetEvent(arduino_event_t *event);
void EthernetEvent(arduino_event_t *event) {
  switch (event->event_id) {
    case ARDUINO_EVENT_ETH_START:
      AddLog(LOG_LEVEL_DEBUG, PSTR(D_LOG_ETH D_ATTEMPTING_CONNECTION));
      ETH.setHostname(eth_hostname);
      break;

    case ARDUINO_EVENT_ETH_CONNECTED:
      AddLog(LOG_LEVEL_INFO, PSTR(D_LOG_ETH D_CONNECTED " at %dMbps%s, Mac %s, Hostname %s"),
        ETH.linkSpeed(), (ETH.fullDuplex()) ? " Full Duplex" : "",
        ETH.macAddress().c_str(), eth_hostname
        );
        
      // AddLog(LOG_LEVEL_DEBUG, D_LOG_ETH "ETH.enableIPV6() -> %i", ETH.enableIPV6());
      break;
      
    case ARDUINO_EVENT_ETH_GOT_IP:
      // AddLog(LOG_LEVEL_DEBUG, PSTR(D_LOG_ETH "Mac %s, IPAddress %_I, Hostname %s"),
      //   ETH.macAddress().c_str(), (uint32_t)ETH.localIP(), eth_hostname);
      Settings->eth_ipv4_address[1] = (uint32_t)ETH.gatewayIP();
      Settings->eth_ipv4_address[2] = (uint32_t)ETH.subnetMask();
      if (0 == Settings->eth_ipv4_address[0]) {  // At this point ETH.dnsIP() are NOT correct unless DHCP
        Settings->eth_ipv4_address[3] = (uint32_t)ETH.dnsIP();
        Settings->eth_ipv4_address[4] = (uint32_t)ETH.dnsIP(1);
      }
      TasmotaGlobal.rules_flag.eth_connected = 1;
      TasmotaGlobal.global_state.eth_down = 0;
#ifndef FIRMWARE_MINIMAL
      AddLog(LOG_LEVEL_DEBUG, PSTR("ETH: IPv4 %_I, mask %_I, gateway %_I"),
              event->event_info.got_ip.ip_info.ip.addr,
              event->event_info.got_ip.ip_info.netmask.addr,
              event->event_info.got_ip.ip_info.gw.addr);
#endif // FIRMWARE_MINIMAL
      WiFiHelper::scrubDNS();    // internal calls to reconnect can zero the DNS servers, save DNS for future use
      break;

#ifdef USE_IPV6
    case ARDUINO_EVENT_ETH_GOT_IP6:
    {
      ip_addr_t ip_addr6;
      ip_addr_copy_from_ip6(ip_addr6, event->event_info.got_ip6.ip6_info.ip);
      IPAddress addr(&ip_addr6);
#ifndef FIRMWARE_MINIMAL
      AddLog(LOG_LEVEL_DEBUG, PSTR("%s: IPv6 %s %s"),
             event->event_id == ARDUINO_EVENT_ETH_GOT_IP6 ? "ETH" : "WIF",
             IPv6isLocal(addr) ? PSTR("Local") : PSTR("Global"), addr.toString().c_str());
#endif // FIRMWARE_MINIMAL
      if (!IPv6isLocal(addr)) {    // declare network up on IPv6
        TasmotaGlobal.rules_flag.eth_connected = 1;
        TasmotaGlobal.global_state.eth_down = 0;
      }
      WiFiHelper::scrubDNS();    // internal calls to reconnect can zero the DNS servers, save DNS for future use
    }
    break;
#endif // USE_IPV6

    case ARDUINO_EVENT_ETH_DISCONNECTED:
      AddLog(LOG_LEVEL_INFO, PSTR(D_LOG_ETH "Disconnected"));
      TasmotaGlobal.rules_flag.eth_disconnected = 1;
      TasmotaGlobal.global_state.eth_down = 1;
      break;

    case ARDUINO_EVENT_ETH_STOP:
      AddLog(LOG_LEVEL_DEBUG, PSTR(D_LOG_ETH "Stopped"));
      TasmotaGlobal.global_state.eth_down = 1;
      break;

    default:
      break;
  }
}

void EthernetSetIp(void) {
  // Set static IP
  ETH.config(Settings->eth_ipv4_address[0],       // IPAddress local_ip
             Settings->eth_ipv4_address[1],       // IPAddress gateway
             Settings->eth_ipv4_address[2],       // IPAddress subnet
             Settings->eth_ipv4_address[3],       // IPAddress dns1
             Settings->eth_ipv4_address[4]);      // IPAddress dns2
}

void EthernetInit(void) {
  if (!Settings->flag4.network_ethernet) { return; }

  int32_t eth_type = (Settings->eth_type < sizeof(eth_type_xtable)) ? eth_type_xtable[Settings->eth_type] : 0;    // make sure we don't overflow
  bool eth_uses_spi = (eth_type & ETH_USES_SPI);
  eth_type = eth_type & 0x7F;     // remove SPI flag
#if CONFIG_ETH_USE_ESP32_EMAC
  if (WT32_ETH01 == TasmotaGlobal.module_type) {
    Settings->eth_address = 1;                    // EthAddress
    Settings->eth_type = ETH_PHY_LAN8720;         // EthType 0 = LAN8720
    Settings->eth_clk_mode = 0;                   // EthClockMode 0 = ETH_CLOCK_GPIO0_IN
  }
#endif  // CONFIG_ETH_USE_ESP32_EMAC

  if (eth_uses_spi) {
    // Uses SPI Ethernet and needs at least SPI CS being ETH MDC
    if (!PinUsed(GPIO_ETH_PHY_MDC, GPIO_ANY)) {
#ifndef FIRMWARE_MINIMAL
      AddLog(LOG_LEVEL_DEBUG_MORE, PSTR(D_LOG_ETH "No ETH MDC as SPI CS GPIO defined"));
#endif // FIRMWARE_MINIMAL
      return;
    }
  } else {
#ifndef FIRMWARE_TASMOTA32_QEMU
// In the QEMU build the GPIO template has no ETH pins configured, but QEMU
// emulates the full EMAC + MII management interface.  Skip the early return
// so the normal ETH.begin() path below can run with synthesised pin numbers.
    // Native ESP32
    if (!PinUsed(GPIO_ETH_PHY_MDC, GPIO_ANY) && !PinUsed(GPIO_ETH_PHY_MDIO)) {  // && should be || but keep for backward compatibility
#ifndef FIRMWARE_MINIMAL
      AddLog(LOG_LEVEL_DEBUG_MORE, PSTR(D_LOG_ETH "No ETH MDC and ETH MDIO GPIO defined"));
#endif // FIRMWARE_MINIMAL
      return;
    }
#endif  // FIRMWARE_TASMOTA32_QEMU
  }

  eth_config_change = 0;

  strlcpy(eth_hostname, TasmotaGlobal.hostname, sizeof(eth_hostname) -5);  // Make sure there is room for "-eth"
  strcat(eth_hostname, "-eth");

#if defined(FIRMWARE_TASMOTA32_QEMU) && defined(CONFIG_ETH_USE_OPENETH)
  // For QEMU builds, use the OpenCores MAC directly via the standard
  // esp_eth_mac_new_openeth() API instead of ETH.begin() (which always
  // calls esp_eth_mac_new_esp32 and crashes against the OpenCores registers).
  EthernetInitOpenCores();
  return;
#endif  // FIRMWARE_TASMOTA32_QEMU && CONFIG_ETH_USE_OPENETH

  WiFi.onEvent(EthernetEvent);

  int eth_mdc = Pin(GPIO_ETH_PHY_MDC, GPIO_ANY);  // Ethernet SPI CS (chip select)
  uint32_t spi_bus = GetPin(eth_mdc) - AGPIO(GPIO_ETH_PHY_MDC); // 0 or 1
  int eth_mdio = Pin(GPIO_ETH_PHY_MDIO);          // Ethernet SPI IRQ
  int eth_power = Pin(GPIO_ETH_PHY_POWER);        // Ethernet SPI RST

#ifdef USE_IPV6
  ETH.enableIPv6();   // enable Link-Local
#endif // USE_IPV6

  bool init_ok = false;
  if (!eth_uses_spi) {
#if CONFIG_ETH_USE_ESP32_EMAC
#ifndef FIRMWARE_MINIMAL
    AddLog(LOG_LEVEL_INFO, PSTR(D_LOG_ETH "Ethernet using RMII"));
#endif // FIRMWARE_MINIMAL
#ifdef CONFIG_IDF_TARGET_ESP32P4
    init_ok = (ETH.begin((eth_phy_type_t)eth_type, Settings->eth_address, eth_mdc, eth_mdio, eth_power, EMAC_CLK_EXT_IN));
#else
    init_ok = (ETH.begin((eth_phy_type_t)eth_type, Settings->eth_address, eth_mdc, eth_mdio, eth_power, (eth_clock_mode_t)Settings->eth_clk_mode));
#endif //CONFIG_IDF_TARGET_ESP32P4
#endif  // CONFIG_ETH_USE_ESP32_EMAC
  } else {
#if CONFIG_SOC_SPI_PERIPH_NUM > 2 
    if ((1 == spi_bus) && (SPI_MOSI_MISO != TasmotaGlobal.spi_enabled2)) {
#ifndef FIRMWARE_MINIMAL
      AddLog(LOG_LEVEL_DEBUG_MORE, PSTR(D_LOG_ETH "No SPI bus2 GPIO defined"));
#endif // FIRMWARE_MINIMAL
      return;
    } else
#endif  // CONFIG_SOC_SPI_PERIPH_NUM > 2
    if (SPI_MOSI_MISO != TasmotaGlobal.spi_enabled) {
#ifndef FIRMWARE_MINIMAL
      AddLog(LOG_LEVEL_DEBUG_MORE, PSTR(D_LOG_ETH "No SPI bus1 GPIO defined"));
#endif // FIRMWARE_MINIMAL
      return;
    }
#ifndef FIRMWARE_MINIMAL
    AddLog(LOG_LEVEL_INFO, PSTR(D_LOG_ETH "Ethernet using SPI (bus%d)"), spi_bus +1);
#endif // FIRMWARE_MINIMAL
    init_ok = (ETH.begin((eth_phy_type_t)eth_type, Settings->eth_address,
                         eth_mdc, eth_mdio, eth_power,
#if CONFIG_SOC_SPI_PERIPH_NUM > 2 
                         (1 == spi_bus) ? SPI3_HOST : SPI2_HOST,
#else
                         SPI2_HOST,
#endif
                         Pin(GPIO_SPI_CLK, spi_bus), Pin(GPIO_SPI_MISO, spi_bus), Pin(GPIO_SPI_MOSI, spi_bus)));
  }
  if (!init_ok) {
    AddLog(LOG_LEVEL_DEBUG, PSTR(D_LOG_ETH "Bad EthType %i or init error"),eth_type);
    return;
  };

  if (Settings->eth_ipv4_address[0]) {
    EthernetSetIp();                             // Set static IP
  }
}

IPAddress EthernetLocalIP(void) {
#if defined(FIRMWARE_TASMOTA32_QEMU) && defined(CONFIG_ETH_USE_OPENETH)
  if (qemu_eth_netif) {
    esp_netif_ip_info_t ip_info;
    if (esp_netif_get_ip_info(qemu_eth_netif, &ip_info) == ESP_OK) {
      return IPAddress(ip_info.ip.addr);
    }
  }
  return IPAddress();
#else
  return ETH.localIP();
#endif
}

// Check to see if we have any routable IP address
// IPv4 has always priority
// Copy the value of the IP if pointer provided (optional)
bool EthernetGetIP(IPAddress *ip) {
#if defined(FIRMWARE_TASMOTA32_QEMU) && defined(CONFIG_ETH_USE_OPENETH)
  if (qemu_eth_netif) {
    esp_netif_ip_info_t ip_info;
    if (esp_netif_get_ip_info(qemu_eth_netif, &ip_info) == ESP_OK && ip_info.ip.addr != 0) {
      if (ip != nullptr) { *ip = IPAddress(ip_info.ip.addr); }
      return true;
    }
  }
  if (ip != nullptr) { *ip = IPAddress(); }
  return false;
#else
#ifdef USE_IPV6
  if ((uint32_t)ETH.localIP() != 0) {
    if (ip != nullptr) { *ip = ETH.localIP(); }
    return true;
  }
  IPAddress lip;
  if (EthernetGetIPv6(&lip)) {
    if (ip != nullptr) { *ip = lip; }
    return true;
  }
  if (ip != nullptr) { *ip = IPAddress(); }
  return false;
#else
  // IPv4 only
  if (ip != nullptr) { *ip = ETH.localIP(); }
  return (uint32_t)ETH.localIP() != 0;
#endif // USE_IPV6
#endif // FIRMWARE_TASMOTA32_QEMU && CONFIG_ETH_USE_OPENETH
}
bool EthernetHasIP(void) {
  return EthernetGetIP(nullptr);
}
String EthernetGetIPStr(void) {
  IPAddress ip;
  if (EthernetGetIP(&ip)) {
    return ip.toString();
  } else {
    return String();
  }
}

char* EthernetHostname(void) {
  return eth_hostname;
}

String EthernetMacAddress(void) {
#if defined(FIRMWARE_TASMOTA32_QEMU) && defined(CONFIG_ETH_USE_OPENETH)
  if (qemu_eth_handle) {
    uint8_t mac[6] = {0};
    if (esp_eth_ioctl(qemu_eth_handle, ETH_CMD_G_MAC_ADDR, mac) == ESP_OK) {
      char buf[18];
      snprintf(buf, sizeof(buf), "%02X:%02X:%02X:%02X:%02X:%02X",
               mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
      return String(buf);
    }
  }
  return String();
#else
  return ETH.macAddress();
#endif
}

void EthernetConfigChange(void) {
  if (eth_config_change) {
    eth_config_change--;
    if (!eth_config_change) {
      EthernetSetIp();
    }
  }
}

/*********************************************************************************************\
 * Commands
\*********************************************************************************************/

#define D_CMND_ETHADDRESS   "Address"
#define D_CMND_ETHTYPE      "Type"
#define D_CMND_ETHCLOCKMODE "ClockMode"
#define D_CMND_ETHIPADDRESS D_CMND_IPADDRESS
#define D_CMND_ETHGATEWAY   D_JSON_GATEWAY
#define D_CMND_ETHNETMASK   D_JSON_SUBNETMASK
#define D_CMND_ETHDNS       D_JSON_DNSSERVER

const char kEthernetCommands[] PROGMEM = "Eth|"  // Prefix
  "ernet|" D_CMND_ETHADDRESS "|" D_CMND_ETHTYPE "|" D_CMND_ETHCLOCKMODE "|"
  D_CMND_ETHIPADDRESS "|" D_CMND_ETHGATEWAY "|" D_CMND_ETHNETMASK "|" D_CMND_ETHDNS ;

void (* const EthernetCommand[])(void) PROGMEM = {
  &CmndEthernet, &CmndEthAddress, &CmndEthType, &CmndEthClockMode,
  &CmndEthSetIpConfig, &CmndEthSetIpConfig, &CmndEthSetIpConfig, &CmndEthSetIpConfig };

#define ETH_PARAM_OFFSET 4                       // Offset of command index in above table of first CmndEthIpConfig

void CmndEthernet(void) {
  if ((XdrvMailbox.payload >= 0) && (XdrvMailbox.payload <= 1)) {
    Settings->flag4.network_ethernet = XdrvMailbox.payload;
    TasmotaGlobal.restart_flag = 2;
  }
  ResponseCmndStateText(Settings->flag4.network_ethernet);
}

void CmndEthAddress(void) {
  if ((XdrvMailbox.payload >= -1) && (XdrvMailbox.payload <= 31)) {
    Settings->eth_address = XdrvMailbox.payload;
    TasmotaGlobal.restart_flag = 2;
  }
  ResponseCmndNumber(Settings->eth_address);
}

void CmndEthType(void) {
  if ((XdrvMailbox.payload >= 0) && (XdrvMailbox.payload < sizeof(eth_type_xtable))) {
    Settings->eth_type = XdrvMailbox.payload;
    TasmotaGlobal.restart_flag = 2;
  }
  ResponseCmndNumber(Settings->eth_type);
}

void CmndEthClockMode(void) {
  if ((XdrvMailbox.payload >= 0) && (XdrvMailbox.payload <= 3)) {
    Settings->eth_clk_mode = XdrvMailbox.payload;
    TasmotaGlobal.restart_flag = 2;
  }
  ResponseCmndNumber(Settings->eth_clk_mode);
}

void CmndEthSetIpConfig(void) {
  uint32_t param_id = XdrvMailbox.command_code -ETH_PARAM_OFFSET;

  char cmnd_idx[2] = { 0 };
  if (3 == param_id) {                           // EthDnsServer
    if ((XdrvMailbox.index < 1) || (XdrvMailbox.index > 2)) {
      XdrvMailbox.index = 1;
    }
    cmnd_idx[0] = '0' + XdrvMailbox.index;
    param_id += XdrvMailbox.index -1;            // EthDnsServer2
  }

  if (XdrvMailbox.data_len) {
    uint32_t ipv4_address;
    if (ParseIPv4(&ipv4_address, XdrvMailbox.data)) {
      Settings->eth_ipv4_address[param_id] = ipv4_address;
      eth_config_change = 2;
    }
  }

  char network_address[22] = { 0 };
  if (0 == param_id) {
    if (!Settings->eth_ipv4_address[0]) {
      ext_snprintf_P(network_address, sizeof(network_address), PSTR(" (%_I)"), (uint32_t)ETH.localIP());
    }
  }
  Response_P(PSTR("{\"%s%s\":\"%_I%s\"}"), XdrvMailbox.command, cmnd_idx, Settings->eth_ipv4_address[param_id], network_address);
}

/*********************************************************************************************\
 * Interface
\*********************************************************************************************/

bool Xdrv82(uint32_t function) {
  bool result = false;

  switch (function) {
    case FUNC_EVERY_SECOND:
      EthernetConfigChange();
      break;
    case FUNC_COMMAND:
      result = DecodeCommand(kEthernetCommands, EthernetCommand);
      break;
    case FUNC_INIT:
      EthernetInit();
      break;
    case FUNC_ACTIVE:
      result = true;
      break;
  }
  return result;
}

#endif  // USE_ETHERNET
#endif  // CONFIG_IDF_TARGET_ESP32C2
#endif  // ESP32
