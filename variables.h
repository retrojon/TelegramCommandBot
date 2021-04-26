
  
  /* bATTERY BOOST TEST */ 
  
 #define MODEM_RST             5
#define MODEM_PWRKEY          4
#define MODEM_POWER_ON       23
#define MODEM_TX             27
#define MODEM_RX             26

#define I2C_SDA              21
#define I2C_SCL              22
#define LED_GPIO             13
#define LED_ON               HIGH
#define LED_OFF              LOW


// ================ Power IC IP5306 ===================
#define IP5306_ADDR (117) // 0x75
#define IP5306_REG_SYS_CTL0 (0x00)
#define IP5306_REG_SYS_CTL1 (0x01)
#define IP5306_REG_SYS_CTL2 (0x02)
#define IP5306_REG_READ0 (0x70)
#define IP5306_REG_READ1 (0x71)
#define IP5306_REG_READ3 (0x78)
#define IP5306_REG_CHG_CTL0 (0x20)
#define IP5306_REG_CHG_CTL1 (0x21)
#define IP5306_REG_CHG_DIG  (0x24)

//- REG_CTL0
#define BOOST_ENABLE_BIT (0x20)
#define CHARGE_OUT_BIT (0x10)
#define BOOT_ON_LOAD_BIT (0x04)
#define BOOST_OUT_BIT (0x02)
#define BOOST_BUTTON_EN_BIT (0x01)

//- REG_CTL1
#define BOOST_SET_BIT (0x80)
#define WLED_SET_BIT (0x40)
#define SHORT_BOOST_BIT (0x20)
#define VIN_ENABLE_BIT (0x04)

//- REG_CTL2
#define SHUTDOWNTIME_MASK (0x0c)
#define SHUTDOWNTIME_64S (0x0c)
#define SHUTDOWNTIME_32S (0x04)
#define SHUTDOWNTIME_16S (0x08)
#define SHUTDOWNTIME_8S  (0x00)

//- REG_READ0
#define CHARGE_ENABLE_BIT (0x08)

//- REG_READ1
#define CHARGE_FULL_BIT (0x08)

//- REG_READ2
#define LIGHT_LOAD_BIT (0x20)
#define LOWPOWER_SHUTDOWN_BIT (0x01)

//- CHG
#define CURRENT_100MA  (0x01 << 0)
#define CURRENT_200MA  (0x01 << 1)
#define CURRENT_400MA  (0x01 << 2)
#define CURRENT_800MA  (0x01 << 3)
#define CURRENT_1600MA  (0x01 << 4)

#define BAT_4_2V      (0x00)
#define BAT_4_3V      (0x01)
#define BAT_4_3_5V    (0x02)
#define BAT_4_4V      (0x03)

#define CHG_CC_BIT    (0x20)
  
  /* Watchdog Timer */ 

    #define WDT_TIMEOUT 10800 // 3 hour reboot 

  /* Infrared */ 

    #define NUMBER_OF_REPEATS 3U 
	
  /* WiFi Credentials  */

    #define WIFI_SSID "WIFI" 
    #define WIFI_PASSWORD "PASS"

  /* Telegram Bot  */ 

    #define BOT_TOKEN "xxxxxxxxx:xxxxxxxxxxxxxxxxxxxxxxxxxx" // BOT Token 
    const unsigned long BOT_MTBS = 5000; // 5s poll messages 
    unsigned long bot_lasttime; // last time messages' scan has been done

  /* Globals */ 

 

    bool OTAon = false; // OTA upgrade enable flag
    IPAddress ip (192, 168, 1, 100); // The remote ip to ping 

    time_t now;  // epoch
    tm tm;       // time

    SimpleTimer firstTimer(75000); // awake periodically for 75 secs ;75000
    SimpleTimer secondTimer(1200000); // or until kept awake for longer

  /* Sleep */ 

    bool flagy1 = true; // Flag for main timer; default  bool flagy1 = false;
    bool flagy2 = true;  // Flag for override; default bool flagy2 = true;

    #define uS_TO_S_FACTOR 1000000  // Conversion factor for micro seconds to seconds 
    #define TIME_TO_SLEEP  10      // Time ESP32 will go to sleep (in seconds) 
