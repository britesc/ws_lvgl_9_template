#include "bsp_cst328.h"

bsp_cst328_info_t *g_cst328_info;
bsp_cst328_data_t g_cst328_data;

void bsp_cst328_reg_read_byte(uint16_t reg_addr, uint8_t *data, size_t len) {
  uint16_t read_index = 0;
  g_cst328_info->Wire->beginTransmission(CST328_DEVICE_ADDR);
  g_cst328_info->Wire->write((uint8_t)(reg_addr >> 8));
  g_cst328_info->Wire->write((uint8_t)(reg_addr & 0x00ff));
  if (g_cst328_info->Wire->endTransmission(false) != 0) {
    Serial.println("I2C write failed");
    return;
  }
  g_cst328_info->Wire->requestFrom(CST328_DEVICE_ADDR, len);
  while (g_cst328_info->Wire->available() && read_index < len) {
    data[read_index++] = g_cst328_info->Wire->read();
  }
}

void bsp_cst328_reg_write_byte(uint16_t reg_addr, uint8_t *data, size_t len) {
  g_cst328_info->Wire->beginTransmission(CST328_DEVICE_ADDR);
  g_cst328_info->Wire->write((uint8_t)(reg_addr >> 8));
  g_cst328_info->Wire->write((uint8_t)(reg_addr & 0x00ff));

  for (size_t i; i < len; i++) {
    g_cst328_info->Wire->write(data[i]);
  }
  g_cst328_info->Wire->endTransmission();
}

void bsp_cst328_reset(void) {
  digitalWrite(g_cst328_info->rst_pin, LOW);
  delay(10);
  digitalWrite(g_cst328_info->rst_pin, HIGH);
  delay(50);
}

void bsp_cst328_read(void) {
  uint8_t buf[28];
  uint8_t points = 0;
  uint8_t num = 0;
  if (!g_cst328_data.read_data_done){
    g_cst328_data.points = 0;
    return;
  }

  g_cst328_data.read_data_done = false;
  bsp_cst328_reg_read_byte(CST328_TOUCH_FLAG_AND_NUM, &buf[0], 1);
  if ((buf[0] & 0x0F) != 0x00) {
    points = buf[0] & 0x0F;
    bsp_cst328_reg_read_byte(CST328_1ST_TOUCH_ID, &buf[1], 27);

    if ((buf[1] & 0x0f) != 0x06) {
      g_cst328_data.points = 0;
      return;
    }

    if (points > CST328_LCD_TOUCH_MAX_POINTS)
      points = CST328_LCD_TOUCH_MAX_POINTS;
    g_cst328_data.points = (uint8_t)points;

    for (int i = 0; i < points; i++) {
      if (i > 0)
        num = 2;
      g_cst328_data.coords[i].x = (uint16_t)(((uint16_t)buf[(i * 5) + 2 + num] << 4) + ((buf[(i * 5) + 4 + num] & 0xF0) >> 4));
      g_cst328_data.coords[i].y = (uint16_t)(((uint16_t)buf[(i * 5) + 3 + num] << 4) + (buf[(i * 5) + 4 + num] & 0x0F));
      g_cst328_data.coords[i].pressure = ((uint16_t)buf[(i * 5) + 5 + num]);
    }
  }
}

bool bsp_cst328_get_touch_data(bsp_cst328_data_t *cst328_data) {

  cst328_data->points = g_cst328_data.points;

  if (cst328_data->points == 0)
    return false;
  
  for (int i = 0; i < cst328_data->points; i++) {
    cst328_data->coords[i].pressure = g_cst328_data.coords[i].pressure;
    switch (g_cst328_info->rotation) {
      case 1:
        cst328_data->coords[i].x = g_cst328_data.coords[i].y;
        cst328_data->coords[i].y = g_cst328_info->height - 1 - g_cst328_data.coords[i].x;
        break;
      case 2:
        cst328_data->coords[i].x = g_cst328_info->width - 1 - g_cst328_data.coords[i].x;
        cst328_data->coords[i].y = g_cst328_info->height - 1 - g_cst328_data.coords[i].y;
        break;
      case 3:
        cst328_data->coords[i].x = g_cst328_info->width - g_cst328_data.coords[i].y;
        cst328_data->coords[i].y = g_cst328_data.coords[i].x;
        break;
      default:
        cst328_data->coords[i].x = g_cst328_data.coords[i].x;
        cst328_data->coords[i].y = g_cst328_data.coords[i].y;
        // Serial.printf("point:%d x:%d, y:%d\r\n", i, g_cst328_data.coords[i].x, g_cst328_data.coords[i].y);
        break;
    }
  }

  // Serial.printf("x:%d, y:%d rotation:%d\r\n", cst328_data->coords[0].x, cst328_data->coords[0].y, g_cst328_info->rotation);
  // Serial.printf("g_cst328_info ->width:%d ->height:%d  rotation:%d \r\n", g_cst328_info->width, g_cst328_info->height, g_cst328_info->rotation);
  return true;
}

void bsp_cst328_set_rotation(uint16_t rotation) {
  uint16_t swap;
  g_cst328_info->rotation = rotation;
  if (rotation == 1 || rotation == 3) {
    if (g_cst328_info->width < g_cst328_info->height) {
      swap = g_cst328_info->width;
      g_cst328_info->width = g_cst328_info->height;
      g_cst328_info->height = swap;
    }
  } else {
    if (g_cst328_info->width > g_cst328_info->height) {
      swap = g_cst328_info->width;
      g_cst328_info->width = g_cst328_info->height;
      g_cst328_info->height = swap;
    }
  }
}


void bsp_cst328_init(bsp_cst328_info_t *cst328_info) {
  uint8_t buf[24] = { 0 };
  uint16_t check_code;

  g_cst328_info = cst328_info;

  pinMode(g_cst328_info->rst_pin, OUTPUT);
  bsp_cst328_reset();

  bsp_cst328_set_rotation(cst328_info->rotation);

  bsp_cst328_reg_write_byte(CST328_ENUM_MODE_DEBUG_INFO, NULL, 0);

  bsp_cst328_reg_read_byte(CST328_IC_INFO, buf, 24);
  // Serial.printf("D1F4:0x%02x,0x%02x,0x%02x,0x%02x\r\n", buf[0], buf[1], buf[2], buf[3]);
  // Serial.printf("D1F8:0x%02x,0x%02x,0x%02x,0x%02x\r\n", buf[4], buf[5], buf[6], buf[7]);
  // Serial.printf("D1FC:0x%02x,0x%02x,0x%02x,0x%02x\r\n", buf[8], buf[9], buf[10], buf[11]);
  // Serial.printf("D200:0x%02x,0x%02x,0x%02x,0x%02x\r\n", buf[12], buf[13], buf[14], buf[15]);
  // Serial.printf("D204:0x%02x,0x%02x,0x%02x,0x%02x\r\n", buf[16], buf[17], buf[18], buf[19]);
  // Serial.printf("D208:0x%02x,0x%02x,0x%02x,0x%02x\r\n", buf[20], buf[21], buf[22], buf[23]);
  check_code = (((uint16_t)buf[11] << 8) | buf[10]);

  bsp_cst328_reg_write_byte(CST328_ENUM_MODE_NORMAL, NULL, 0);
  if (check_code == 0xcaca)
    Serial.printf("Find CST328!\r\n");
  else
    Serial.printf("CST328 not found!\r\n");

  pinMode(g_cst328_info->int_pin, INPUT_PULLUP);
  attachInterrupt(
    digitalPinToInterrupt(g_cst328_info->int_pin), [] {
      g_cst328_data.read_data_done = true;
    },
    FALLING);
}
