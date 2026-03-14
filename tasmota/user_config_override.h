/*
dBBBBBP     dBP     dBBBBb    dBBBBb     dBBBP      dBBBP     dBBBBb   dBBBBBb     dBP     dBBBBb     dBBBBb     dBBBP            dBBBBb  dBBBBb
                                  dBP                             dBP       dBP                dBP
   dBP     dBP     dBBBB      dBBBK'    dBBP       dBBP       dBBBK'    dBBBBK    dBP     dBP dBP    dBBBB      dBBP                dBBBP   dBBP
  dBP     dBP     dB' BB     dB' db    dBP        dBP        dB' db    dBP  BB   dBP     dBP dBP    dB' BB     dBP                   dBP   dBP__
 dBBBBP  dBP     dBBBBBB    dBBBBP'   dBBBBP     dBBBBP     dBBBBP'   dBP  dB'  dBP     dBBBBBP    dBBBBBB    dBBBBP             dBBBBP   dBBBBP
 */

#ifdef CUSTOM_CONFIG_ZIGBEE_BRIDGE32  // *******************************************************************

#undef CODE_IMAGE_STR
#define CODE_IMAGE_STR "zig_bridge32"

#define FALLBACK_MODULE WEMOS
#define USER_TEMPLATE "{\"NAME\":\"Zig_Bridge32\",\"GPIO\":[1,1,3552,1,3584,1,1,1,5793,5792,320,544,5536,1,5600,1,0,1,1,5568,0,1,1,1,0,0,0,0,608,640,32,1,1,0,0,1],\"FLAG\":0,\"BASE\":1}"
#undef MODULE
#define MODULE USER_MODULE
// {"NAME":"ZB-GW03-V1.2","GPIO":[1,1,3552,1,3584,1,1,1,5793,5792,320,544,5536,1,5600,1,0,1,1,5568,0,1,1,1,0,0,0,0,608,640,32,1,1,0,0,1],"FLAG":0,"BASE":1}

#undef OTA_URL
#define OTA_URL " "  // [OtaUrl]

#undef  SERIAL_LOG_LEVEL
#define SERIAL_LOG_LEVEL LOG_LEVEL_NONE

#define USE_ETHERNET
#undef  ETH_TYPE
#define ETH_TYPE 0 // ETH_PHY_LAN8720
#undef  ETH_CLKMODE
#define ETH_CLKMODE 3 // ETH_CLOCK_GPIO17_OUT
#undef  ETH_ADDRESS
#define ETH_ADDRESS 1 // PHY1

//#define USE_ARDUINO_OTA                          // Add optional support for Arduino OTA (+13k code)
//#define USE_HOME_ASSISTANT                       // Enable Home Assistant Discovery Support (+7k code)

//#define USE_MQTT_TLS                             // Use TLS for MQTT connection (+34.5k code, +7.0k mem and +4.8k additional during connection handshake)
//  #define USE_MQTT_TLS_CA_CERT                   // Force full CA validation instead of fingerprints, slower, but simpler to use (+2.2k code, +1.9k mem during connection handshake)
//  #define USE_MQTT_TLS_FORCE_EC_CIPHER           // Force Elliptic Curve cipher (higher security) required by some servers (automatically enabled with USE_MQTT_AWS_IOT) (+11.4k code, +0.4k mem)
//  #define USE_MQTT_AWS_IOT                       // Enable MQTT for AWS IoT - requires a private key (+11.9k code, +0.4k mem)

//#define USE_KNX                                  // Enable KNX IP Protocol Support (+9.4k code, +3k7 mem)
#define USE_WEBSERVER                            // Enable web server and Wifi Manager (+66k code, +8k mem)
  #define USE_JAVASCRIPT_ES6                     // Enable ECMAScript6 syntax using less JavaScript code bytes (fails on IE11)
#define USE_WEBSEND_RESPONSE                   // Enable command WebSend response message (+1k code)
//#define USE_EMULATION
//  #define USE_EMULATION_HUE                      // Enable Hue Bridge emulation for Alexa (+14k code, +2k mem)
//  #define USE_EMULATION_WEMO                     // Enable Belkin WeMo emulation for Alexa (+6k code, +2k mem)
//  #define USE_SENDMAIL

#define USE_TIMERS                               // Add support for up to 16 timers (+2k2 code)
  #define USE_TIMERS_WEB                         // Add timer webpage support (+4k5 code)
  #define USE_SUNRISE                            // Add support for Sunrise and sunset tools (+16k)

// -- Compression ---------------------------------
#define USE_UNISHOX_COMPRESSION                  // Add support for string compression in Rules or Scripts

#define USE_RULES                                // Add support for rules (+4k4 code)
//  #define USE_EXPRESSION                         // Add support for expression evaluation in rules (+3k2 code, +64 bytes mem)
//    #define SUPPORT_IF_STATEMENT                 // Add support for IF statement in rules (+4k2 code, -332 bytes mem)
//  #define SUPPORT_MQTT_EVENT                     // Support trigger event with MQTT subscriptions (+3k5 code)

//#define USE_SCRIPT                               // Add support for script
  #define USE_SCRIPT_FATFS 4                     // Add support for script storage on SD card (+12k code, +4k mem)

#ifdef ESP32
  #undef OTA_URL
  #define OTA_URL "https://github.com/tasmota/install/raw/main/firmware/unofficial/tasmota32-zigbeebridge.bin"
  #define USE_TLS
  #define USE_BERRY
  #define USE_WEBCLIENT
  #define USE_WEBCLIENT_HTTPS
#endif  // ESP32

// -- Optional modules ----------------------------
//#define ROTARY_V1                                // Add support for MI Desk Lamp
//#define USE_SONOFF_RF                            // Add support for Sonoff Rf Bridge
//  #define USE_RF_FLASH                           // Add support for flashing the EFM8BB1 chip on the Sonoff RF Bridge. C2CK must be connected to GPIO4, C2D to GPIO5 on the PCB (+3k code)
//#define USE_SONOFF_SC                            // Add support for Sonoff Sc (+1k1 code)
//#define USE_TUYA_MCU                             // Add support for Tuya Serial Dimmer
//#define USE_ARMTRONIX_DIMMERS                    // Add support for Armtronix Dimmers (+1k4 code)
//#define USE_PS_16_DZ                             // Add support for PS-16-DZ Dimmer and Sonoff L1 (+2k code)
//#define USE_SONOFF_IFAN                          // Add support for Sonoff iFan02 and iFan03 (+2k code)
//#define USE_BUZZER                               // Add support for a buzzer (+0k6 code)
//#define USE_ARILUX_RF                            // Add support for Arilux RF remote controller (+1k code, 252 iram (non 2.3.0))
//#define USE_SHUTTER                              // Add Shutter support for up to 4 shutter with different motortypes (+6k code)
//#define USE_DEEPSLEEP                            // Add support for deepsleep (+1k code)
//#define USE_EXS_DIMMER                           // Add support for ES-Store WiFi Dimmer (+2k6 code)
//#define USE_HOTPLUG                              // Add support for HotPlug
//#define USE_DEVICE_GROUPS                      // Add support for device groups (+4k code)
//#define USE_PWM_DIMMER                           // Add support for MJ-SD01/acenx/NTONPOWER PWM dimmers (+4k5 code)
//  #define USE_PWM_DIMMER_REMOTE                  // Add support for remote switches to PWM Dimmer, also adds device groups support (+0k7 code, also includes device groups)
//#define USE_KEELOQ                               // Add support for Jarolift rollers by Keeloq algorithm (+4k5 code)
//#define USE_SONOFF_D1                            // Add support for Sonoff D1 Dimmer

// -- Optional light modules ----------------------
//#define USE_LIGHT                                    // LIGHTS support

//#define USE_COUNTER                              // Enable counters
#define USE_ADC_VCC                              // Display Vcc in Power status. Disable for use as Analog input on selected devices

// #define USE_DS18x20                              // Add support for DS18x20 sensors with id sort, single scan and read retry (+2k6 code)
//  #define W1_PARASITE_POWER                      // Optimize for parasite powered sensors

// -- I2C sensors ---------------------------------
#define USE_I2C                                  // I2C using library wire (+10k code, 0k2 mem, 124 iram)
#ifdef USE_I2C
//  #define USE_SHT                                // Enable SHT1X sensor (+1k4 code)
//  #define USE_HTU                                // Enable HTU21/SI7013/SI7020/SI7021 sensor (I2C address 0x40) (+1k5 code)
//  #define USE_BMP                                // Enable BMP085/BMP180/BMP280/BME280 sensor (I2C address 0x76 or 0x77) (+4k code)
//  #define USE_BME680                             // Enable support for BME680 sensor using Bosch BME680 library (+4k code)
//  #define USE_BH1750                             // Enable BH1750 sensor (I2C address 0x23 or 0x5C) (+0k5 code)
//  #define USE_VEML6070                           // Enable VEML6070 sensor (I2C addresses 0x38 and 0x39) (+0k5 code)
//  #define USE_ADS1115                            // Enable ADS1115 16 bit A/D converter (I2C address 0x48, 0x49, 0x4A or 0x4B) based on Adafruit ADS1x15 library (no library needed) (+0k7 code)
//  #define USE_INA219                             // Enable INA219 (I2C address 0x40, 0x41 0x44 or 0x45) Low voltage and current sensor (+1k code)
//  #define USE_INA226                             // Enable INA226 (I2C address 0x40, 0x41 0x44 or 0x45) Low voltage and current sensor (+2k3 code)
//  #define USE_SHT3X                              // Enable SHT3x (I2C address 0x44 or 0x45) or SHTC3 (I2C address 0x70) sensor (+0k7 code)
//  #define USE_TSL2561                            // Enable TSL2561 sensor (I2C address 0x29, 0x39 or 0x49) using library Joba_Tsl2561 (+2k3 code)
//  #define USE_TSL2591                            // Enable TSL2591 sensor (I2C address 0x29, 0x39 or 0x49) using library Adafruit_TSL2591 (+2k3 code)
//  #define USE_MGS                                // Enable Xadow and Grove Mutichannel Gas sensor using library Multichannel_Gas_Sensor (+10k code)
    #define MGS_SENSOR_ADDR    0x04              // Default Mutichannel Gas sensor i2c address
//  #define USE_SGP30                              // Enable SGP30 sensor (I2C address 0x58) (+1k1 code)
//  #define USE_SI1145                             // Enable SI1145/46/47 sensor (I2C address 0x60) (+1k code)
//  #define USE_LM75AD                             // Enable LM75AD sensor (I2C addresses 0x48 - 0x4F) (+0k5 code)
//  #define USE_APDS9960                           // Enable APDS9960 Proximity Sensor (I2C address 0x39). Disables SHT and VEML6070 (+4k7 code)
//  #define USE_MCP230xx                           // Enable MCP23008/MCP23017 for GP INPUT ONLY (I2C addresses 0x20 - 0x27) providing command Sensor29 for configuration (+2k2 code)
//    #define USE_MCP230xx_ADDR 0x20               // Enable MCP23008/MCP23017 I2C Address to use (Must be within range 0x20 through 0x27 - set according to your wired setup)
//    #define USE_MCP230xx_OUTPUT                  // Enable MCP23008/MCP23017 OUTPUT support through sensor29 commands (+1k code)
//    #define USE_MCP230xx_DISPLAYOUTPUT           // Enable MCP23008/MCP23017 to display state of OUTPUT pins on Web UI (+0k2 code)
//  #define USE_PCA9685                            // Enable PCA9685 I2C HW PWM Driver - Must define I2C Address in #define USE_PCA9685_ADDR below - range 0x40 - 0x47 (+1k4 code)
//    #define USE_PCA9685_ADDR 0x40                // Enable PCA9685 I2C Address to use (Must be within range 0x40 through 0x47 - set according to your wired setup)
//    #define USE_PCA9685_FREQ 50                  // Define default PWM frequency in Hz to be used (must be within 24 to 1526) - If other value is used, it will rever to 50Hz
//  #define USE_MPR121                             // Enable MPR121 controller (I2C addresses 0x5A, 0x5B, 0x5C and 0x5D) in input mode for touch buttons (+1k3 code)
//  #define USE_CCS811                             // Enable CCS811 sensor (I2C address 0x5A) (+2k2 code)
//  #define USE_CCS811_V2                          // [I2cDriver24] Enable CCS811 sensor (I2C addresses 0x5A and 0x5B) (+2k8 code)
//  #define USE_MPU6050                            // Enable MPU6050 sensor (I2C address 0x68 AD0 low or 0x69 AD0 high) (+2k6 code)
//  #define USE_DS3231                             // Enable DS3231 external RTC in case no Wifi is avaliable. See docs in the source file (+1k2 code)
//    #define USE_RTC_ADDR  0x68                   // Default I2C address 0x68
//  #define USE_MGC3130                            // Enable MGC3130 Electric Field Effect Sensor (I2C address 0x42) (+2k7 code, 0k3 mem)
//  #define USE_MAX44009                           // Enable MAX44009 Ambient Light sensor (I2C addresses 0x4A and 0x4B) (+0k8 code)
//  #define USE_SCD30                              // Enable Sensiron SCd30 CO2 sensor (I2C address 0x61) (+3k3 code)
//  #define USE_SPS30                              // Enable Sensiron SPS30 particle sensor (I2C address 0x69) (+1.7 code)
//  #define USE_ADE7953                            // Enable ADE7953 Energy monitor as used on Shelly 2.5 (I2C address 0x38) (+1k5)
//  #define USE_VL53L0X                            // Enable VL53L0x time of flight sensor (I2C address 0x29) (+4k code)
//  #define USE_MLX90614                           // Enable MLX90614 ir temp sensor (I2C address 0x5a) (+0.6k code)
//  #define USE_CHIRP                              // Enable CHIRP soil moisture sensor (variable I2C address, default 0x20)
//  #define USE_PAJ7620                            // Enable PAJ7620 gesture sensor (I2C address 0x73) (+2.5k code)
//  #define USE_PCF8574                            // Enable PCF8574 I/O Expander (I2C addresses 0x20 - 0x27 and 0x38 - 0x3F) (+1k9 code)
//  #define USE_HIH6                               // Enable Honeywell HIH Humidity and Temperature sensor (I2C address 0x27) (+0k6)
//  #define USE_DHT12                              // [I2cDriver41] Enable DHT12 humidity and temperature sensor (I2C address 0x5C) (+0k7 code)
//  #define USE_DS1624                             // [I2cDriver42] Enable DS1624, DS1621 temperature sensor (I2C addresses 0x48 - 0x4F)
//  #define USE_AHT1x                              // [I2cDriver43] Enable AHT10/15 humidity and temperature sensor (I2C address 0x38) (+0k8 code)
//  #define USE_WEMOS_MOTOR_V1                     // [I2cDriver44] Enable Wemos motor driver V1 ()
//  #define USE_HDC1080                            // [I2cDriver45] Enable HDC1080 temperature/humidity sensor (I2C address 0x40) (+1k5 code)

//   #define USE_DISPLAY                            // Add I2C Display Support (+2k code)
//     #define USE_DISPLAY_MODES1TO5                // Enable display mode 1 to 5 in addition to mode 0
//     #define USE_DISPLAY_LCD                      // [DisplayModel 1] Enable Lcd display (I2C addresses 0x27 and 0x3F) (+6k code)
//     #define USE_DISPLAY_SSD1306                  // [DisplayModel 2] Enable SSD1306 Oled 128x64 display (I2C addresses 0x3C and 0x3D) (+16k code)
//     #define USE_DISPLAY_MATRIX                   // [DisplayModel 3] Enable 8x8 Matrix display (I2C adresseses see below) (+11k code)
//       #define MTX_ADDRESS1     0x71              // [DisplayAddress1] I2C address of first 8x8 matrix module
//       #define MTX_ADDRESS2     0x74              // [DisplayAddress2] I2C address of second 8x8 matrix module
//       #define MTX_ADDRESS3     0x75              // [DisplayAddress3] I2C address of third 8x8 matrix module
//       #define MTX_ADDRESS4     0x72              // [DisplayAddress4] I2C address of fourth 8x8 matrix module
//       #define MTX_ADDRESS5     0x73              // [DisplayAddress5] I2C address of fifth 8x8 matrix module
//       #define MTX_ADDRESS6     0x76              // [DisplayAddress6] I2C address of sixth 8x8 matrix module
//       #define MTX_ADDRESS7     0x00              // [DisplayAddress7] I2C address of seventh 8x8 matrix module
//       #define MTX_ADDRESS8     0x00              // [DisplayAddress8] I2C address of eigth 8x8 matrix module
//     #define USE_DISPLAY_SH1106                   // [DisplayModel 7] Enable SH1106 Oled 128x64 display (I2C addresses 0x3C and 0x3D)
#endif  // USE_I2C

// // -- SPI sensors ---------------------------------
// #define USE_SPI                                  // Hardware SPI using GPIO12(MISO), GPIO13(MOSI) and GPIO14(CLK) in addition to two user selectable GPIOs(CS and DC)
// #ifdef USE_SPI
// //  #define USE_NRF24                              // Add SPI support for NRF24L01(+) (+2k6 code)
//   #ifdef USE_NRF24
//     #define USE_MIBLE                            // BLE-bridge for some Mijia-BLE-sensors (+4k7 code)
//   #else
//     #ifndef USE_DISPLAY
//       #define USE_DISPLAY                        // Add SPI Display support for 320x240 and 480x320 TFT
//     #endif
//       #define USE_DISPLAY_ILI9341                // [DisplayModel 4] Enable ILI9341 Tft 480x320 display (+19k code)
// //      #define USE_DISPLAY_EPAPER_29              // [DisplayModel 5] Enable e-paper 2.9 inch display (+19k code)
// //      #define USE_DISPLAY_EPAPER_42              // [DisplayModel 6] Enable e-paper 4.2 inch display
// //      #define USE_DISPLAY_ILI9488                // [DisplayModel 8] [I2cDriver38] (Touch)
// //      #define USE_DISPLAY_SSD1351                // [DisplayModel 9]
// //      #define USE_DISPLAY_RA8876                 // [DisplayModel 10] [I2cDriver39] (Touch)
//   #endif  // USE_NRF24
// #endif  // USE_SPI

// -- Serial sensors ------------------------------
//#define USE_MHZ19                                // Add support for MH-Z19 CO2 sensor (+2k code)
//#define USE_SENSEAIR                             // Add support for SenseAir K30, K70 and S8 CO2 sensor (+2k3 code)
//#define USE_PMS5003                              // Add support for PMS5003 and PMS7003 particle concentration sensor (+1k3 code)
//#define USE_NOVA_SDS                             // Add support for SDS011 and SDS021 particle concentration sensor (+0k7 code)
//#define USE_HPMA                                 // Add support for Honeywell HPMA115S0 particle concentration sensor (+1k4)
//#define USE_SERIAL_BRIDGE                        // Add support for software Serial Bridge (+1k1 code)
//#define USE_MP3_PLAYER                           // Use of the DFPlayer Mini MP3 Player RB-DFR-562 commands: play, volume and stop
//#define USE_AZ7798                               // Add support for AZ-Instrument 7798 CO2 datalogger (+1k6 code)
//#define USE_PN532_HSU                            // Add support for PN532 using HSU (Serial) interface (+1k8 code, 140 bytes mem)
//  #define USE_PN532_CAUSE_EVENTS                 // Cause event execution for PN532_UID= and PN532_DATA=[if defined] (+ 30 bytes code)
  #define USE_PN532_DATA_FUNCTION                // Add sensor40 command support for erase, setting data block content (+1k7 code, 388 bytes mem)
  #define USE_PN532_DATA_RAW                     // Allow DATA block to be used by non-alpha-numberic data (+ 80 bytes code, 48 bytes ram)
//#define USE_RDM6300                              // Add support for RDM6300 125kHz RFID Reader (+0k8)
//#define USE_IBEACON                              // Add support for bluetooth LE passive scan of ibeacon devices (uses HM17 module)
//#define USE_HM10                                 // Add support for HM-10 as a BLE-bridge for the LYWSD03 (+5k1 code)
//#define USE_HRXL                                 // Add support for MaxBotix HRXL-MaxSonar ultrasonic range finders (+0k7)

// Power monitoring sensors -----------------------
#undef USE_ENERGY_SENSOR                         // Disable energy sensors (-14k code)
// #define USE_ENERGY_MARGIN_DETECTION              // Add support for Energy Margin detection (+1k6 code)
// //  #define USE_ENERGY_POWER_LIMIT                 // Add additional support for Energy Power Limit detection (+1k2 code)
// #define USE_PZEM004T                             // Add support for PZEM004T Energy monitor (+2k code)
// #define USE_PZEM_AC                              // Add support for PZEM014,016 Modbus Energy monitor (+1k1 code)
// #define USE_PZEM_DC                              // Add support for PZEM003,017 Modbus Energy monitor (+1k1 code)
// #define USE_MCP39F501                            // Add support for MCP39F501 Energy monitor as used in Shelly 2 (+3k1 code)
//#define USE_SDM120                             // Add support for Eastron SDM120-Modbus energy monitor (+1k1 code)
//#define USE_SDM630                             // Add support for Eastron SDM630-Modbus energy monitor (+0k6 code)
//#define USE_DDS2382                              // Add support for Hiking DDS2382 Modbus energy monitor (+0k6 code)
//#define USE_DDSU666                              // Add support for Chint DDSU666 Modbus energy monitor (+0k6 code)
//#define USE_SOLAX_X1                             // Add support for Solax X1 series Modbus log info (+4k1 code)
//#define USE_LE01MR                               // Add support for F&F LE-01MR modbus energy meter

// -- Low level interface devices -----------------
//#define USE_DHT                                   // Disable support for DHT11, AM2301 (DHT21, DHT22, AM2302, AM2321) and SI7021 Temperature and Humidity sensor

//#define USE_MAX31855                              // Disable MAX31855 K-Type thermocouple sensor using softSPI

// -- IR Remote features --------------------------
//#define USE_IR_REMOTE                            // Send IR remote commands using library IRremoteESP8266 and ArduinoJson (+4k3 code, 0k3 mem, 48 iram)
  #define USE_IR_SEND_NEC                        // Support IRsend NEC protocol
  #define USE_IR_SEND_RC5                        // Support IRsend Philips RC5 protocol
  #define USE_IR_SEND_RC6                        // Support IRsend Philips RC6 protocol

// #define USE_IR_RECEIVE                         // Support for IR receiver (+7k2 code, 264 iram)
    #define IR_RCV_BUFFER_SIZE      100          // Max number of packets allowed in capture buffer (default 100 (*2 bytes ram))
    #define IR_RCV_TIMEOUT          15           // Number of milli-Seconds of no-more-data before we consider a message ended (default 15)
    #define IR_RCV_MIN_UNKNOWN_SIZE 6            // Set the smallest sized "UNKNOWN" message packets we actually care about (default 6, max 255)

// -- Zigbee interface ----------------------------
#define USE_ZIGBEE                                // Enable serial communication with Zigbee CC2530 flashed with ZNP (+49k code, +3k mem)
  #undef  USE_ZIGBEE_ZNP
  #define USE_ZIGBEE_EZSP
  #define USE_ZIGBEE_EEPROM                      // T24C512A
  #define USE_TCP_BRIDGE
  #undef  USE_ZIGBEE_CHANNEL
  #define USE_ZIGBEE_CHANNEL 11                  // Zigbee Channel (11-26)
  #define USE_ZIGBEE_TXRADIO_DBM  20             // Tx Radio power in dBm (only for EZSP, EFR32 can go up to 20 dBm)
  #define USE_ZIGBEE_COALESCE_ATTR_TIMER 350     // timer to coalesce attribute values (in ms)
  #define USE_ZIGBEE_MODELID      "Tasmota Z2T"  // reported "ModelId"      (cluster 0000 / attribute 0005)
  #define USE_ZIGBEE_MANUFACTURER "Tasmota"      // reported "Manufacturer" (cluster 0000 / attribute 0004)

//#define USE_CCLOADER

//#define USE_SR04                                 // Add support for HC-SR04 ultrasonic devices (+1k code)

//#define USE_TM1638                               // Add support for TM1638 switches copying Switch1 .. Switch8 (+1k code)
//#define USE_HX711                                // Add support for HX711 load cell (+1k5 code)
  #define USE_HX711_GUI                          // Add optional web GUI to HX711 as scale (+1k8 code)

//#define USE_TX20_WIND_SENSOR                     // Add support for La Crosse TX20 anemometer (+2k6/0k8 code)
//#define USE_TX23_WIND_SENSOR                     // Add support for La Crosse TX23 anemometer (+2k7/1k code)

//#define USE_RC_SWITCH                            // Add support for RF transceiver using library RcSwitch (+2k7 code, 460 iram)

//#define USE_RF_SENSOR                            // Add support for RF sensor receiver (434MHz or 868MHz) (+0k8 code)
//  #define USE_THEO_V2                            // Add support for decoding Theo V2 sensors as documented on https://sidweb.nl using 434MHz RF sensor receiver (+1k4 code)
//  #define USE_ALECTO_V2                          // Add support for decoding Alecto V2 sensors like ACH2010, WS3000 and DKW2012 using 868MHz RF sensor receiver (+1k7 code)

//#define USE_HRE                                  // Add support for Badger HR-E Water Meter (+1k4 code)
//#define USE_A4988_STEPPER                        // Add support for A4988 stepper-motor-driver-circuit (+10k5 code)

//#define USE_TASMOTA_CLIENT                       // Add support for Arduino Uno/Pro Mini via serial interface including flashing (+2k3 code, 44 mem)

#endif  // CUSTOM_CONFIG_ZIGBEE_BRIDGE32 ******************************************************************


