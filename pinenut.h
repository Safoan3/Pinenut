#include "../graphicsapi/graphicsapi.h" //path to graphics api

#include "RGFW.h"
#include <cstddef>
#include <cstdint>

struct pinenut {
  RGFW_window *win;
  u8 *pixels;
  RGFW_surface *fb;
  bool shouldPineNutclose = false;

  double delta;
  int newW = 1;
  int newH = 1;
  int UpSclaeFactor1 = 1;

  void init(char *windowName, int H, int W, int upscale);
  void tick();
  void kill();
  bool isPineKeyDown(RGFW_key key);
  void PineGetMouse(i32 *x1, i32 *x2);
  bool PineNut_window_checkEvent(RGFW_event *event);

  space *GraphicsApiMasterBuffer;
  pinenut();
};
