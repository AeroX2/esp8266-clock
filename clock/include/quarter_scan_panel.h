
/*
  Patch class for 32x16 RGB Matrix panels

  reimplement all functions which use x,y coordinates

*/

#ifndef ESP_HUB75_32x16MatrixPanel
#define ESP_HUB75_32x16MatrixPanel

#include "ESP32-VirtualMatrixPanel-I2S-DMA.h"

class QuarterScanMatrixPanel : public VirtualMatrixPanel {
  using VirtualMatrixPanel::VirtualMatrixPanel;

 public:
  inline void drawPixel(int16_t x, int16_t y, uint16_t color) {
    getCoords(x, y);

    uint8_t r, g, b;
    this->display->color565to888(color, r, g, b);
    pixelData[x][y] = (r << 16) + (g << 8) + b;
    this->display->drawPixelRGB888(coords.x, coords.y, r, g, b);
  }

  inline void drawPixelRGB888(int16_t x, int16_t y, uint8_t r, uint8_t g,
                              uint8_t b) {
    getCoords(x, y);
    pixelData[x][y] = (r << 16) + (g << 8) + b;
    this->display->drawPixelRGB888(coords.x, coords.y, r, g, b);
  }

  inline void fillScreen(uint16_t color) {
    for (int x = 0; x < 32; x++) {
      for (int y = 0; y < 16; y++) {
        pixelData[x][y] = 0;
      }
    }
  }

  uint16_t getPixel(int16_t x, int16_t y) { return pixelData[x][y]; }

 private:
  inline VirtualCoords getCoords(int16_t &x, int16_t &y) {
    coords.x = x + (x / 8) * 8 + (y % 8 / 4) * 8;
    coords.y = y % 4 + (y / 8) * 4;
    return coords;
  }

  uint32_t pixelData[32][16] = {0};
};

#endif
