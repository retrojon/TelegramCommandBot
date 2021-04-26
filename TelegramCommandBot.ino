/*******************************************************************
 A telegram bot for ESP32 that responds to preset commands.

 Using various Arduino libraries, most notably UniveralTelegramBot
    
 Modified by Retrojon
    
/***************************************************
 *  Version information
 ***************************************************/
int majorVersion = 0;
int minorVersion = 90;

/***************************************************
 *  Include files
 ***************************************************/
#include <SimpleTimer.h>            // timer lib
#include <Wire.h> 
#include "variables.h"              // credentials
#include <esp_task_wdt.h>           // watchdog timer
#include <IRremote.h>               // infrared mod
#include <WiFi.h>         
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <ESP32Ping.h>              // wifi Ping
#include <esp_wifi.h>               // wifi psave
#include <soc/rtc.h>                // 80mhz cpu
#include <UniversalTelegramBot.h>   // telegram client
#include "WiFiClientSecure.h"
#include <Time.h>                   // time () ctime ()
#include "handleNewMessages.h"      // telegram processing
#include <WebServer.h>              // ota http server
#include <Update.h>                 // ota 
#include "setup.h"
#include "handleWiFiReconnect.h"    // recon to wifi
#include "handleTelegramPoll.h"     // check new msgs
#include "handleFirstTimer.h"       // main timer
#include "handleSecondTimer.h"      // keep alive 

/***************************************************
 *  Name:        loop
 *  Returns:     Nothing.
 *  Parameters:  None.
 *  Description: Main application loop.
 *
 ***************************************************/

void loop() {

  /* WiFi Reconnect */
  
    handleWiFiReconnect();
 
  /* Poll new Telegram messages */

    handleTelegramPoll(); 

  /* Sleep/Power saving */
   
    handleFirstTimer();   

    handleSecondTimer(); }
 
   
