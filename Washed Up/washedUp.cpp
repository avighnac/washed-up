#define pressed(b) (input.buttons[b].is_down && input.buttons[b].changed)
#define draw_player(x, y) (draw_rect(x, y, x+size, y+size, 0xffffff))

#define str(x) std::to_string(x)

#include "Sprites/Beach.hpp"
void drawSprite(int startX, int startY, int size,
                std::vector<std::vector<unsigned int>> &spriteVec) {
  for (auto y = 0; y < spriteVec.size(); y++) {
    for (auto x = 0; x < spriteVec[y].size(); x++) {
      draw_rect(
          startX + x * size, startY + y * size, startX + (x + 1) * size,
          startY + (y + 1) * size,
          spriteVec[spriteVec.size() - y - 1][spriteVec[y].size() - x - 1]);
    }
  }
}

struct Button_State {
  bool is_down;
  bool changed;
};

enum {
  BUTTON_UP,
  BUTTON_DOWN,
  BUTTON_W,
  BUTTON_S,
  BUTTON_LEFT,
  BUTTON_RIGHT,
  BUTTON_ENTER,

  BUTTON_COUNT,
};

struct Input {
  Button_State buttons[BUTTON_COUNT];
};

Input input = {};

float playerX = 0.0f;
float playerY = 0.0f;
float size = buffer_height / 6;
float speed = 50;

int beachLocation = 0;

void washedUp(HWND& window) {
  HDC hdc = GetDC(window);
  
  size = buffer_height / 6;

  while (running) {
    MSG message;
    PeekMessage(&message, window, 0, 0, PM_REMOVE);

    switch (message.message) {
    case WM_KEYUP:
    case WM_KEYDOWN: {
      unsigned int vk_code = (unsigned int)message.wParam;
      bool is_down = ((message.lParam & (1 << 31)) == 0);

#define process_button(b, vk)                                                  \
  case vk: {                                                                   \
    input.buttons[b].changed = is_down != input.buttons[b].is_down;            \
    input.buttons[b].is_down = is_down;                                        \
  } break;

      switch (vk_code) {
        process_button(BUTTON_UP, VK_UP);
        process_button(BUTTON_DOWN, VK_DOWN);
        process_button(BUTTON_LEFT, VK_LEFT);
        process_button(BUTTON_RIGHT, VK_RIGHT);
        process_button(BUTTON_ENTER, VK_RETURN);
      }
    } break;

    default: {
      TranslateMessage(&message);
      DispatchMessage(&message);
    }
    }
    clear_screen(0x0000ff);
    if (beachLocation <= -750)
      beachLocation = speed;
    if (beachLocation >= 92)
      beachLocation = -700;
    //This drawSprite function draws the background (beach).
    drawSprite(beachLocation - speed,
               buffer_height - (100 * (buffer_width) / 200) -
                   (55 * (buffer_width - 38) / 1098),
               (buffer_width) / 200, Beach);

    if (pressed(BUTTON_LEFT))
      playerX -= speed;
    if (pressed(BUTTON_RIGHT))
      playerX += speed;
    if (pressed(BUTTON_DOWN))
      playerY -= speed;
    if (pressed(BUTTON_UP))
      playerY += speed;

    draw_player(playerX + buffer_width / 4, playerY);

    if (playerX <= -buffer_width / 8 && pressed(BUTTON_LEFT)) {
      playerX = -buffer_width / 8;
      beachLocation += speed;
    }
    if (playerX + speed >= 17 * buffer_width / 28 && pressed(BUTTON_RIGHT)) {
      playerX = 17 * buffer_width / 28 - speed;
      beachLocation -= speed;
    }

    StretchDIBits(hdc, 0, 0, buffer_width, buffer_height, 0, 0, buffer_width,
                  buffer_height, buffer_memory, &buffer_bitmap_info,
                  DIB_RGB_COLORS, SRCCOPY);
  }
}