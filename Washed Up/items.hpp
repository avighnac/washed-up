void items(HWND &window, tstring appdata) {
  HDC hdc = GetDC(window);

  long long bottle, trash_bag, iron;
  std::fstream bottleDat;
  bottleDat.open((appdata + tstring(L"\\Washed Up\\items\\bottle.dat")),
                     std::ios_base::in);
  std::fstream trash_bagDat;
  trash_bagDat.open((appdata + tstring(L"\\Washed Up\\items\\trash_bag.dat")),
                 std::ios_base::in);
  std::fstream ironDat;
  ironDat.open((appdata + tstring(L"\\Washed Up\\items\\iron.dat")),
                 std::ios_base::in);

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
        process_button(BUTTON_CONTROL, VK_CONTROL);
      }
    } break;

    default: {
      TranslateMessage(&message);
      DispatchMessage(&message);
    }
    }

    

    StretchDIBits(hdc, 0, 0, buffer_width, buffer_height, 0, 0, buffer_width,
                  buffer_height, buffer_memory, &buffer_bitmap_info,
                  DIB_RGB_COLORS, SRCCOPY);
  }
}