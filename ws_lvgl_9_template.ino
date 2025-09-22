/*
   Arduino lvgl Template
*/

/*******************************************************************************
 * Start of Arduino_GFX settings
 ******************************************************************************/
#include <Arduino_GFX_Library.h>
#include <lcd_defines.h>
#include <i2c_defines.h>

Arduino_DataBus *bus = new Arduino_RPiPicoSPI(LCD_DC_PIN, LCD_CS_PIN, LCD_SCK_PIN, LCD_MOSI_PIN, LCD_MISO_PIN, LCD_SPI_NUM);

/* More display class: https://github.com/moononournation/Arduino_GFX/wiki/Display-Class */
Arduino_GFX *gfx = new Arduino_ST7789(
  bus, LCD_RST_PIN, LCD_Orientation /* rotation */, true /* IPS */);
/*******************************************************************************
 * End of Arduino_GFX settings
 ******************************************************************************/

/*******************************************************************************
 * Start of Wire settings
 ******************************************************************************/
#include <Wire.h>
/*******************************************************************************
 * End of Wire settings
 ******************************************************************************/

/*******************************************************************************
 * Start of lvgl settings
 ******************************************************************************/
#include <lvgl.h>
#include <bsp_cst328.h>
/*******************************************************************************
 * End of lvgl settings
 ******************************************************************************/

/*******************************************************************************
 * Start of sketch settings
 ******************************************************************************/
uint32_t screenRotation;
uint32_t screenWidth;
uint32_t screenHeight;
uint32_t bufSize;
lv_display_t *disp;
lv_color_t *disp_draw_buf1;
lv_color_t *disp_draw_buf2;
#define BACKGROUND RGB565_PINK
#define VERSION    "0.0.11"
/*******************************************************************************
 * End of sketch settings
 ******************************************************************************/

void setup(void)
{
#ifdef DEV_DEVICE_INIT
  DEV_DEVICE_INIT();
#endif

  init_serial();

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

#if LV_USE_LOG != 0
void my_print(lv_log_level_t level, const char *buf)
{
  LV_UNUSED(level);
  Serial.println(buf);
  Serial.flush();
}
#endif

uint32_t millis_cb(void)
{
  return millis();
}

/* LVGL calls it when a rendered image needs to copied to the display*/
void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
  uint32_t w = lv_area_get_width(area);
  uint32_t h = lv_area_get_height(area);

  gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)px_map, w, h);
  /*Call it to tell LVGL you are ready*/
  lv_disp_flush_ready(disp);
}

/*Read the touchpad*/
void my_touchpad_read(lv_indev_t *indev, lv_indev_data_t *data)
{
  bsp_cst328_data_t cst328_data;
  bsp_cst328_read();
  if (bsp_cst328_get_touch_data(&cst328_data))
  {
    data->state = LV_INDEV_STATE_PR;

    /*Set the coordinates*/
    data->point.x = cst328_data.coords[0].x;
    data->point.y = cst328_data.coords[0].y;
  }
  else
  {
    data->state = LV_INDEV_STATE_REL;
  }
}

/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */