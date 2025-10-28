/*
   Arduino lvgl Template
*/
#define VERSION "0.0.100"
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
 * Start of ui settings
 ******************************************************************************/
#include <ui.h>
#include <vars.h>
/*******************************************************************************
 * End of lvgl settings
 ******************************************************************************/

/*******************************************************************************
 * Start of eeprom settings
 ******************************************************************************/
#include <PicoFlashEeprom.h>
PicoFlashEeprom PFE((uint8_t)512);
/*******************************************************************************
 * End of eeprom settings
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
#define BACKGROUND RGB565_BLACK

/*******************************************************************************
 * End of sketch settings
 ******************************************************************************/

/*******************************************************************************
 * Start of Core 0
 ******************************************************************************/

void setup(void) {
#ifdef DEV_DEVICE_INIT
  DEV_DEVICE_INIT();
#endif

  // #if LV_FONT_MONTSERRAT_18
  //   #error "ENABLED!"
  // #endif

  /* Initialise Serial Output*/
  init_serial();
  /* Initialise Display */
  init_display();

#ifdef GFX_BL
  pinMode(GFX_BL, OUTPUT);
  digitalWrite(GFX_BL, HIGH);
#endif
  Serial.flush();

  /* Initialise Wire Library */
  init_wire();
  /* Initialise the System */
  init_system();
  /* Initialise LVGL */
  lv_init();

  /*Set a tick source so that LVGL will know how much time elapsed. */
  lv_tick_set_cb(millis_cb);

  /* register print function for debugging */
#if LV_USE_LOG != 0
  lv_log_register_print_cb(my_print);
#endif
  /* Initialise DIsplay BUffer */
  init_buffer();
  /* Initialise Touch Input*/
  init_touch();
  /* Initialise UI */
  ui_init();

  Serial.println("Setup done");
}

void loop() {
  lv_task_handler(); /* let the GUI do its work */
  //delay(5);
  ui_tick();
}

/*******************************************************************************
 * End of Core 0
 ******************************************************************************/

/*******************************************************************************
 * Start of Core 1
 ******************************************************************************/

void setup1() {
  // TODO
  init_serial();
  
  PFE.begin();
  if(!PFE.isEepromValid()) 
  {
    PFE.initializeEeprom();
  }
  if(PFE.isZapNumberValid(PFE.getZapNumber()))
  {
    // set to true for testing
    set_var_has_valid_zap_number(true);
    Serial.print("Zap NOT Valid");
  }
  else {
     
    set_var_has_valid_zap_number(true);
  }      
  Serial.println(PFE.getZapNumber());
}

void loop1() {
  // TODO
  if(PFE.isZapNumberValid(PFE.getZapNumber()))
  {
    Serial.print("Zap NOT Valid");
  }      
  Serial.println(PFE.getZapNumber());  
  delay(5000);
}


/*******************************************************************************
 * End of Core 1
 ******************************************************************************/

/*******************************************************************************
 * Start of Core Functions
 ******************************************************************************/

void init_serial() {
  int x = 0;
  Serial.begin(115200);
  // Serial.setDebugOutput(true);
  while (x < 500) {
    x++;
    if (Serial.available()) {
      x = 501;
    }
  }
  output_info();
}

void output_info() {
  Serial.println("WS Pico 2350 Touchscreen Template");
  String String_Out = String("  Version ") + VERSION;
  Serial.println(String_Out);
  String_Out = String("  GNU C++ Version ") + __cplusplus;
  Serial.println(String_Out);
  String_Out = String("  Compiled ") + __DATE__ + " " + __TIME__;
  Serial.println(String_Out);
  String_Out = String("  LVGL Version ") + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
  Serial.println(String_Out);
}

void init_display() {
  if (!gfx->begin()) {
    Serial.println("gfx->begin() failed!");
  }
  gfx->fillScreen(BACKGROUND);

#ifdef GFX_BL
  pinMode(GFX_BL, OUTPUT);
  digitalWrite(GFX_BL, HIGH);
#endif
}

void init_wire() {
  Wire1.setSDA(I2C_SDA_PIN);
  Wire1.setSCL(I2C_SCL_PIN);
  Wire1.begin();
  Wire1.setClock(I2C_SPEED);
}

void init_system() {
  screenWidth = gfx->width();
  screenHeight = gfx->height();
  screenRotation = gfx->getRotation();
  static bsp_cst328_info_t cst328_info;
  cst328_info.width = screenWidth;
  cst328_info.height = screenHeight;
  cst328_info.rotation = screenRotation;
  cst328_info.Wire = &Wire1;
  cst328_info.rst_pin = TP_RST_PIN;
  cst328_info.int_pin = TP_INT_PIN;
  bsp_cst328_init(&cst328_info);
}

void init_buffer() {
#ifdef DIRECT_RENDER_MODE
  bufSize = screenWidth * screenHeight;
#else
  bufSize = screenWidth * 120;
#endif

  Serial.println("LVGL disp_draw_buf heap_caps_malloc failed! malloc again...");
  disp_draw_buf1 = (lv_color_t *)malloc(bufSize * 2);
  disp_draw_buf2 = (lv_color_t *)malloc(bufSize * 2);

  if (!disp_draw_buf1 && !disp_draw_buf2) {
    Serial.println("LVGL disp_draw_buf allocate failed!");
  } else {
    disp = lv_display_create(screenWidth, screenHeight);
    lv_display_set_flush_cb(disp, my_disp_flush);
#ifdef DIRECT_RENDER_MODE
    lv_display_set_buffers(disp, disp_draw_buf1, disp_draw_buf2, bufSize * 2, LV_DISPLAY_RENDER_MODE_DIRECT);
#else
    lv_display_set_buffers(disp, disp_draw_buf1, disp_draw_buf2, bufSize * 2, LV_DISPLAY_RENDER_MODE_PARTIAL);
#endif
  }
}

void init_touch() {
  /*Initialize the (dummy) input device driver*/
  lv_indev_t *indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER); /*Touchpad should have POINTER type*/
  lv_indev_set_read_cb(indev, my_touchpad_read);
}

#if LV_USE_LOG != 0
void my_print(lv_log_level_t level, const char *buf) {
  LV_UNUSED(level);
  Serial.println(buf);
  Serial.flush();
}
#endif

uint32_t millis_cb(void) {
  return millis();
}

/* LVGL calls it when a rendered image needs to copied to the display*/
void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) {
  uint32_t w = lv_area_get_width(area);
  uint32_t h = lv_area_get_height(area);

  gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)px_map, w, h);
  /*Call it to tell LVGL you are ready*/
  lv_disp_flush_ready(disp);
}

/*Read the touchpad*/
void my_touchpad_read(lv_indev_t *indev, lv_indev_data_t *data) {
  bsp_cst328_data_t cst328_data;
  bsp_cst328_read();
  if (bsp_cst328_get_touch_data(&cst328_data)) {
    data->state = LV_INDEV_STATE_PR;

    /*Set the coordinates*/
    data->point.x = cst328_data.coords[0].x;
    data->point.y = cst328_data.coords[0].y;
  } else {
    data->state = LV_INDEV_STATE_REL;
  }
}

/*******************************************************************************
 * End of Core Functions
 ******************************************************************************/

/*******************************************************************************
 * Start of Zap Number Functions
 ******************************************************************************/




/*******************************************************************************
 * End of Zap Number Functions
 ******************************************************************************/


/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */
