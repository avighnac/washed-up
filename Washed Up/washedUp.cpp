#define pressed(b) (input.buttons[b].is_down && input.buttons[b].changed)
#define draw_player(x, y) (draw_rect(x, y, x+speed, y+speed, 0xffffff))

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
float speed;

void washedUp(HWND& window) {
  HDC hdc = GetDC(window);

  speed = buffer_height / 6;

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

    if (pressed(BUTTON_LEFT))
      playerX -= speed;
    if (pressed(BUTTON_RIGHT))
      playerX += speed;
    if (pressed(BUTTON_DOWN))
      playerY -= speed;
    if (pressed(BUTTON_UP))
      playerY += speed;

    draw_player(playerX, playerY);
    draw_rect(buffer_width / 8 - 1, 0, buffer_width / 8, buffer_height,
              0x000000);
    draw_rect(6 * buffer_width / 7 - 1, 0,
              6 * buffer_width / 7,
              buffer_height,
              0x000000);

    if (playerX <= buffer_width / 8)
      playerX = buffer_width / 8;
    if (playerX + speed >= 6 * buffer_width / 7)
      playerX = 6 * buffer_width / 7 - speed;

    StretchDIBits(hdc, 0, 0, buffer_width, buffer_height, 0, 0, buffer_width,
                  buffer_height, buffer_memory, &buffer_bitmap_info,
                  DIB_RGB_COLORS, SRCCOPY);
  }
}