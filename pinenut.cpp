#include <cstddef>
#include <cstdint>

#define RGFW_IMPLEMENTATION

#include "pinenut.h"
#include <chrono>
#include <thread>

static void upscale(space *space, int upscalefactor, int W, int H,
                    uint8_t *pixels) {
  int normj = 0;
  for (int j = 0; j < H; j = j + upscalefactor) {
    int normi = 0;
    for (int ii = 0; ii < W; ii = ii + upscalefactor) {
      int norm = normj * space->res.x + normi;
      for (int jjj = 0; jjj < upscalefactor; jjj++) {
        for (int iii = 0; iii < upscalefactor; iii++) {
          int i = ((j + jjj) * W + (ii + iii));
          pixels[i * 4 + 0] =
              (uint8_t)(space->finalrenderimg.buffer[norm].r * 255.0f);
          pixels[i * 4 + 1] =
              (uint8_t)(space->finalrenderimg.buffer[norm].g * 255.0f);
          pixels[i * 4 + 2] =
              (uint8_t)(space->finalrenderimg.buffer[norm].b * 255.0f);
          pixels[i * 4 + 3] =
              (uint8_t)(space->finalrenderimg.buffer[norm].a * 255.0f);
        }
      }
      normi++;
    }
    normj++;
  }
}

void pinenut::init(char *windowName, int H, int W, int upscaleFactor) {
  RGFW_init("PineNut", 0);

  newW = W * upscaleFactor;
  newH = H * upscaleFactor;
  UpSclaeFactor1 = upscaleFactor;

  win = RGFW_createWindow(windowName, 0, 0, newW, newH, RGFW_windowCenter);

  pixels = (u8 *)RGFW_ALLOC(newW * newH * 4);
  fb = RGFW_createSurface(pixels, newW, newH, RGFW_formatRGBA8);

  GraphicsApiMasterBuffer = new space({(int)W, (int)H});

  Xspace *frame1rawbuff = new Xspace(GraphicsApiMasterBuffer->res);
  frame1rawbuff->setCharacterDensityList();
  xframe *frame1 = new xframe(frame1rawbuff);
  GraphicsApiMasterBuffer->addlayer(frame1);
}

void pinenut::tick() {
  //RGFW_event event;
 // while (RGFW_window_checkEvent(win, &event)) {
    // handle discrete events if needed
  //}

  shouldPineNutclose = RGFW_window_shouldClose(win);

  auto start = std::chrono::steady_clock::now();

  /// RENDER
  GraphicsApiMasterBuffer->render();

  // Event Code

  upscale(GraphicsApiMasterBuffer, UpSclaeFactor1, newW, newH, pixels);

  auto end = std::chrono::steady_clock::now();
  delta = std::chrono::duration<double>(end - start).count();

  RGFW_window_blitSurface(win, fb);
};

void pinenut::PineGetMouse(i32 *x1, i32 *x2) {
  i32 x = (i32)((float)(*x1) * UpSclaeFactor1);
  i32 y = (i32)((float)(*x2) * UpSclaeFactor1);
  RGFW_window_getMouse(win, &x, &y);
  *x1 = x / UpSclaeFactor1;
  *x2 = y / UpSclaeFactor1;
};

bool pinenut::PineNut_window_checkEvent(RGFW_event *event) {
  return (bool)RGFW_window_checkEvent(win, event);
};

bool pinenut::isPineKeyDown(RGFW_key key) {
  //
  return RGFW_window_isKeyDown(win, key);
}

void pinenut::kill() {
  RGFW_surface_free(fb);
  RGFW_FREE(pixels);

  RGFW_window_close(win);
  RGFW_deinit();
}

pinenut::pinenut() {}
