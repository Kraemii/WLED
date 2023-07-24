#include "wled.h"
/*
 * This v1 usermod file allows you to add own functionality to WLED more easily
 * See: https://github.com/Aircoookie/WLED/wiki/Add-own-functionality
 * EEPROM bytes 2750+ are reserved for your custom use case. (if you extend #define EEPSIZE in const.h)
 * If you just need 8 bytes, use 2551-2559 (you do not need to increase EEPSIZE)
 * 
 * Consider the v2 usermod API if you need a more advanced feature set!
 */

//Use userVar0 and userVar1 (API calls &U0=,&U1=, uint16_t)

const int LIGHT_PIN = A0; // define analog pin

// variables
long readTime = 0;
float lightPercentage = 0;

//gets called once at boot. Do all initialization that doesn't depend on network here
void userSetup()
{
  pinMode(LIGHT_PIN, INPUT);
}

//gets called every time WiFi is (re-)connected. Initialize own network interfaces here
void userConnected()
{

}

//loop. You can use "if (WLED_CONNECTED)" to check for successful connection
void userLoop()
{
   // Read only every 500ms, otherwise it causes the board to hang
  if (millis() - readTime > 500)
  {
    readTime = millis();
    
    // Convert value to percentage
    int lightValue = analogRead(LIGHT_PIN);
    lightPercentage = float(analogRead(LIGHT_PIN)) / 4095;
    
  }
}
