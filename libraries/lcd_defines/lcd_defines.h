#ifndef __LCD_DEFINES_H__
	#define __LCD_DEFINES_H__

	#define LCD_Portrait      0
	#define LCD_Landscape     1
	#define LCD_Orientation   LCD_Landscape

	#define LCD_SPI_SPEED     (80 * 1000 * 1000)
	#define LCD_SPI_NUM       spi1
	#define LCD_DC_PIN        14
	#define LCD_CS_PIN        13
	#define LCD_SCK_PIN       10
	#define LCD_MOSI_PIN      11
	#define LCD_MISO_PIN      12
	#define LCD_RST_PIN       15
	#define LCD_BL_PIN        16	// Backlight

	#define GFX_BL LCD_BL_PIN // default backlight pin, you may replace DF_GFX_BL to actual backlight pin

#endif // __LCD_DEFINES_H__