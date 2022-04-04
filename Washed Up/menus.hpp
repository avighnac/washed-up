#define menuPressed(b) (menuInput.buttons[b].is_down && menuInput.buttons[b].changed)

#define rect(a, b, c, d, e) (draw_rect(a, b, a+(c), b+(d), e))

#include "isInContact.hpp"

struct Menu_Button_State {
  bool is_down;
  bool changed;
};

struct Menu_Input {
  Menu_Button_State buttons[BUTTON_COUNT];
};

Menu_Input menuInput = {};

int mainMenuOption = 0;
bool prevMouseState = 0;

inline bool isInBetween(int start, int end, int num) {
  if (start > end) {
    int temp = start;
    start = end;
    end = temp;
  }

  return start <= num && num <= end;
}

int mainMenu(HWND &window) {
  std::vector<std::string> mainMenuOptions = {
    "Play", "Scoreboard", "Items"
  };

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

    int pos = buffer_width / 6;

    for (auto i = 0; i < mainMenuOptions.size(); i++) {
      if (i == mainMenuOption)
        draw_rect(
            pos - buffer_width / 35, buffer_height / 2 - buffer_width / 35,
            pos + (4 * 6 * mainMenuOptions[i].length()) + buffer_width / 35,
            buffer_height / 2 + (5 * 4) + buffer_width / 35,
            0x0ff0ff); // I really don't know why the * 6 is needed, it was
                       // trial and error TBH.
      else
        draw_rect(
            pos - buffer_width / 50, buffer_height / 2 - buffer_width / 50,
            pos + (4 * 6 * mainMenuOptions[i].length()) + buffer_width / 50,
            buffer_height / 2 + (5 * 4) + buffer_width / 50,
            0x696969); // Nice.

      draw_text(hdc, mainMenuOptions[i], pos, buffer_height / 2, 4, 0,
                0xffffff);
      pos += buffer_width / 5 * (i + 1);
    }

    pos = buffer_width / 6;
    
    if (GetKeyState(VK_LBUTTON) < 0 &&
        !prevMouseState) {
      prevMouseState = true;
      POINT pt;
      GetCursorPos(&pt);
      mouse_event(MOUSEEVENTF_LEFTUP, pt.x, pt.y, 0, 0);
      ScreenToClient(window, &pt);
      pt.y = buffer_height - pt.y;

      for (auto i = 0; i < mainMenuOptions[i].size(); i++) {
        if (isInContact2D(pt.x, pt.y, pt.x, pt.y, pos - buffer_width / 35,
                          buffer_height / 2 - buffer_width / 35,
                          pos + (4 * 6 * mainMenuOptions[i].length()) +
                              buffer_width / 35,
                          buffer_height / 2 + (5 * 4) + buffer_width / 35)) {
          if (mainMenuOption == i)
            return i;
          mainMenuOption = i;
        }

        pos += buffer_width / 5 * (i + 1);
      }
    } else
      prevMouseState = false;

    if (menuPressed(BUTTON_RIGHT)) {
      mainMenuOption++;
      if (mainMenuOption > mainMenuOptions.size() - 1)
        mainMenuOption = mainMenuOptions.size() - 1;
    }
    if (menuPressed(BUTTON_LEFT)) {
      mainMenuOption--;
      if (mainMenuOption < 0)
        mainMenuOption = 0;
    }

    if (menuPressed(BUTTON_ENTER))
      return mainMenuOption;

    StretchDIBits(hdc, 0, 0, buffer_width, buffer_height, 0, 0, buffer_width,
                  buffer_height, buffer_memory, &buffer_bitmap_info,
                  DIB_RGB_COLORS, SRCCOPY);
  }
}