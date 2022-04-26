void scoreboard(HWND &window, tstring appdata) {
  HDC hdc = GetDC(window);

  std::vector<long long> scores;
  std::fstream scoreboardDat;
  scoreboardDat.open((appdata + tstring(L"\\Washed Up\\scoreboard.dat")),
                     std::ios_base::in);
  std::string currentScore;
  while (scoreboardDat >> currentScore) {
    scores.push_back(std::stoll(currentScore));
  }

  std::sort(scores.begin(), scores.end());

  while (running) {
    MSG message;
    if (PeekMessage(&message, window, 0, 0, PM_REMOVE) > 0) {

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

    clear_screen(0xfffff0);
    draw_text(hdc, "Scoreboard", buffer_width / 2 - (buffer_width / 150 * 3 * 10),
              buffer_height - (buffer_height / 10), buffer_width / 150, 0,
              0x000000);

    for (auto i = 0; i < 10; i++) {
      draw_text(hdc, std::to_string(i + 1) + ": " + std::to_string(scores[scores.size() - i - 1]),
                buffer_width / 20,
                buffer_height - (buffer_height / 5 + (buffer_height / 20 * (i + 1))),
                buffer_width / 230, 0,
                0x000000);
    }

    StretchDIBits(hdc, 0, 0, buffer_width, buffer_height, 0, 0, buffer_width,
                  buffer_height, buffer_memory, &buffer_bitmap_info,
                  DIB_RGB_COLORS, SRCCOPY);
  }
  }
}