/*
   Arduino lvgl Template
*/

/*******************************************************************************
 * Start of Arduino_GFX setting
 ******************************************************************************/
#include <Arduino_GFX_Library.h>
#include <lcd_defines.h>
#include <i2c_defines.h>

Arduino_DataBus *bus = new Arduino_RPiPicoSPI(LCD_DC_PIN, LCD_CS_PIN, LCD_SCK_PIN, LCD_MOSI_PIN, LCD_MISO_PIN, LCD_SPI_NUM);

/* More display class: https://github.com/moononournation/Arduino_GFX/wiki/Display-Class */
Arduino_GFX *gfx = new Arduino_ST7789(
  bus, LCD_RST_PIN, LCD_Orientation /* rotation */, true /* IPS */);
/*******************************************************************************
 * End of Arduino_GFX setting
 ******************************************************************************/

/*******************************************************************************
 * Start of Wire setting
 ******************************************************************************/
#include <Wire.h>
/*******************************************************************************
 * End of Wire setting
 ******************************************************************************/

/*******************************************************************************
 * Start of lvgl setting
 ******************************************************************************/
#include <lvgl.h>
#include <bsp_cst328.h>
/*******************************************************************************
 * End of lvgl setting
 ******************************************************************************/

#define BACKGROUND RGB565_YELLOW
#define VERSION    "0.0.9"

void setup(void)
{
#ifdef DEV_DEVICE_INIT
  DEV_DEVICE_INIT();
#endif

  // Serial.begin(115200);
  // // Serial.setDebugOutput(true);
  // while(!Serial);
  // Serial.println("WS Pico 2350 Touchscreen Template");
  // Serial.println(VERSION);
  init_serial();

  // Init Display
  // if (!gfx->begin())
  // {
  //   Serial.println("gfx->begin() failed!");
  // }
  // gfx->fillScreen(BACKGROUND);
  init_display();

#ifdef GFX_BL
  pinMode(GFX_BL, OUTPUT);
  digitalWrite(GFX_BL, HIGH);
#endif
  Serial.flush();  

  init_wire();

}

void loop()
{
 
}

void init_serial()
{
  Serial.begin(115200);
  // Serial.setDebugOutput(true);
  while(!Serial);
  Serial.println("WS Pico 2350 Touchscreen Template");
  Serial.println(VERSION); 
}

void init_display()
{
  if (!gfx->begin())
  {
    Serial.println("gfx->begin() failed!");
  }
  gfx->fillScreen(BACKGROUND); 
}

void init_wire()
{
  Wire1.setSDA(I2C_SDA_PIN);
  Wire1.setSCL(I2C_SCL_PIN);
  Wire1.begin();
  Wire1.setClock(I2C_SPEED);
}  