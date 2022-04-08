while (GetKeyState(VK_ESCAPE) >= 0 && running) {
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

  clear_screen(0xab2b0c);

  if (unlocked.find("stickman_skin_head")->second) {
    draw_text(hdc, "Selected!", buffer_width / 2 - (buffer_width / 150 * 3 * 9),
              buffer_height / 2, buffer_width / 150, 0, 0x000000);
    draw_text(hdc, "Press ESC to return.", buffer_width / 2 - (4 * 3 * 20),
              3 * buffer_height / 8, 4, 0, 0x000000);
  } else {
    draw_text(hdc, "Would you like to buy this item for 50 iron?",
              buffer_width / 2 - ((buffer_width + buffer_height) / 400 * 3 * 44),
              buffer_height / 2, (buffer_width + buffer_height) / 400, 0, 0x000000);
    
    draw_rect(buffer_width / 4, buffer_height / 4,
              buffer_width / 4 + buffer_width / 10,
              buffer_height / 4 + buffer_height / 10, 0x00ff00);
    draw_rect(5 * buffer_width / 8, buffer_height / 4,
              5 * buffer_width / 8 + buffer_width / 10,
              buffer_height / 4 + buffer_height / 10, 0xff0000);

    GetCursorPos(&pt);
    ScreenToClient(window, &pt);
    pt.y = buffer_height - pt.y;

    if (isInContact2D(pt.x, pt.y, pt.x, pt.y, buffer_width / 4,
                      buffer_height / 4, buffer_width / 4 + buffer_width / 10,
                      buffer_height / 4 + buffer_height / 10) && GetKeyState(VK_LBUTTON) < 0) {
      if (iron >= 50) {
        iron -= 50;
        unlocked.find("stickman_skin_head")->second = true;
      }
    }
  }
  stretchdibits;
}