#define menuPressed(b) (menuInput.buttons[b].is_down && menuInput.buttons[b].changed)

struct Menu_Button_State {
  bool is_down;
  bool changed;
};

struct Menu_Input {
  Menu_Button_State buttons[BUTTON_COUNT];
};

Menu_Input menuInput = {};

bool mainMenuOption = 1;
bool prevMouseState = 0;

inline bool isInBetween(int start, int end, int num) {
  return start <= num && num <= end;
}

bool mainMenu(HWND &window) {
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
    menuInput.buttons[b].changed = is_down != menuInput.buttons[b].is_down;            \
    menuInput.buttons[b].is_down = is_down;                                        \
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

    clear_screen(0xfffff0);
    HDC hdc = GetDC(window);

    RECT rc;
    GetClientRect(window, &rc);
    ClientToScreen(window, reinterpret_cast<POINT *>(&rc.left));
    ClientToScreen(window, reinterpret_cast<POINT *>(&rc.right));

    if (mainMenuOption) {
      draw_rect(buffer_width / 8 - (buffer_width / 50), buffer_height / 2 - (buffer_width / 50),
                buffer_width / 4 + (buffer_width / 50),
                buffer_height / 4 * 3 + (buffer_width / 50), 0x808080);

      draw_rect(buffer_width / 8, buffer_height / 2, buffer_width / 4,
                buffer_height / 4 * 3, 0x00ff00);
      draw_text(hdc, "Play",
                (buffer_width / 8 + buffer_width / 4) / 2 -
                    (buffer_width / 300 * 3 * 4),
                (buffer_height / 2 + buffer_height / 4 * 3) / 2,
                buffer_width / 300, 0, 0xffffff);
      draw_rect(buffer_width / 8 * 6, buffer_height / 2, buffer_width / 8 * 7,
                buffer_height / 4 * 3, 0x00ff00);
      draw_text(hdc, "Scoreboard",
                (buffer_width / 8 * 6 + buffer_width / 8 * 7) / 2 -
                    buffer_width / 390 * 3 * 10,
                (buffer_height / 2 + buffer_height / 4 * 3) / 2,
                buffer_width / 390, 0, 0xffffff);
    } else {
      draw_rect(buffer_width / 8 * 6 - (buffer_width / 50),
                buffer_height / 2 - (buffer_width / 50),
                buffer_width / 8 * 7 + (buffer_width / 50),
                buffer_height / 4 * 3 + (buffer_width / 50), 0x808080);

      draw_rect(buffer_width / 8, buffer_height / 2, buffer_width / 4,
                buffer_height / 4 * 3, 0x00ff00);
      draw_text(hdc, "Play",
                (buffer_width / 8 + buffer_width / 4) / 2 -
                    (buffer_width / 300 * 3 * 4),
                (buffer_height / 2 + buffer_height / 4 * 3) / 2,
                buffer_width / 300, 0, 0xffffff);
      draw_rect(buffer_width / 8 * 6, buffer_height / 2, buffer_width / 8 * 7,
                buffer_height / 4 * 3, 0x00ff00);
      draw_text(hdc, "Scoreboard",
                (buffer_width / 8 * 6 + buffer_width / 8 * 7) / 2 -
                    buffer_width / 390 * 3 * 10,
                (buffer_height / 2 + buffer_height / 4 * 3) / 2,
                buffer_width / 390, 0, 0xffffff);
    }

    if (GetKeyState(VK_LBUTTON) < 0 && !prevMouseState) {
      prevMouseState = false;
      POINT pt;
      GetCursorPos(&pt);
      mouse_event(MOUSEEVENTF_LEFTUP, pt.x, pt.y, 0, 0);

      if (isInBetween(buffer_width / 8, buffer_width / 4, (pt.x - rc.left)) &&
          isInBetween(buffer_height - (buffer_height / 4 * 3), buffer_height / 2,
                      (pt.y - rc.top)))
        mainMenuOption = 1;
      else if (isInBetween(buffer_width / 8 * 6, buffer_width / 8 * 7, (pt.x - rc.left)) &&
               isInBetween(buffer_height - (buffer_height / 4 * 3), buffer_height / 2,
                      (pt.y - rc.top)))
        mainMenuOption = 0;
    }

    if (menuPressed(BUTTON_LEFT))
      mainMenuOption = !mainMenuOption;
    if (menuPressed(BUTTON_RIGHT))
      mainMenuOption = !mainMenuOption;

    if (menuPressed(BUTTON_ENTER)) {
      return mainMenuOption;
    }

    StretchDIBits(hdc, 0, 0, buffer_width, buffer_height, 0, 0, buffer_width,
                  buffer_height, buffer_memory, &buffer_bitmap_info,
                  DIB_RGB_COLORS, SRCCOPY);
  }
}