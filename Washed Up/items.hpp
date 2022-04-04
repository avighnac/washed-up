#include <map>
#include <washedUpSprites.hpp>

class coordinates {
public:
  int startX, startY, endX, endY;

  coordinates(int sx, int sy, int ex, int ey) {
    startX = sx;
    startY = sy;
    endX = ex;
    endY = ey;
  }
};

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

  ironDat >> iron;
  bottleDat >> bottle;
  trash_bagDat >> trash_bag;

  ironDat.close();
  bottleDat.close();
  trash_bagDat.close();

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

    clear_screen(0xab2b0c);

    draw_text(hdc, "Items", buffer_width / 2 - (buffer_width / 150 * 3 * 5),
              buffer_height - (buffer_height / 10), buffer_width / 150, 0,
              0x000000);

    drawSprite(buffer_width - buffer_width / 16,
               buffer_height - buffer_height / 10, 1,
               sprites::getRustedBlockOfIron());
    draw_text(hdc, str(iron) + "-",
              buffer_width - buffer_width / 16 - 5 * (str(iron).length() + 1) -
                  sprites::getRustedBlockOfIron()[0].size() * 1,
              buffer_height - buffer_height / 10, 5, 0, 0x000000);

    int boxAdjustment = 10;

    std::map<std::string, coordinates> coordinatesMap;
    coordinatesMap.insert(
        {"blankBox",
         coordinates(buffer_width / 200 * boxAdjustment,
                     buffer_height / 200 * 10 + 2 * buffer_height / 3,
                     buffer_width / 200 * (boxAdjustment + 20),
                     buffer_height / 200 * 10 +
                         abs(buffer_width / 200 * (boxAdjustment + 20) -
                             buffer_width / 200 * boxAdjustment) +
                         2 * buffer_height / 3)});
    boxAdjustment += 30;
    coordinatesMap.insert(
        {"stickman_skin_head",
         coordinates(buffer_width / 200 * boxAdjustment,
                     buffer_height / 200 * 10 + 2 * buffer_height / 3,
                     buffer_width / 200 * boxAdjustment +
                         std::ceil(buffer_width / 1136.0) *
                             sprites::getStickman_Skin_Head()[0].size(),
                     buffer_height / 200 * 10 + 2 * buffer_height / 3 +
                         std::ceil(buffer_width / 1136.0) *
                             sprites::getStickman_Skin_Head().size())});

    // Blank box
    auto x = coordinatesMap.find("blankBox");
    draw_rect(x->second.startX, x->second.startY, x->second.endX,
              x->second.endY, 0xffffff);
    // Blank box end

    // Stickman skin
    x = coordinatesMap.find("stickman_skin_head");
    drawSprite(x->second.startX,
               x->second.startY,
               std::ceil(buffer_width / 1136.0),
               sprites::getStickman_Skin_Head());
    // Stickman skin end

    boxAdjustment += 30;

    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(window, &pt);
    pt.y = buffer_height - pt.y;

    for (auto &i : coordinatesMap) {
      if (isInContact2D(pt.x, pt.y, pt.x, pt.y, i.second.startX,
                        i.second.startY, i.second.endX, i.second.endY)) {
        draw_rect(i.second.startX, i.second.startY - buffer_height / 20 - buffer_height / 100,
                  i.second.endX, i.second.startY - buffer_height / 100, 0x00ff00);
      }
    }

    StretchDIBits(hdc, 0, 0, buffer_width, buffer_height, 0, 0, buffer_width,
                  buffer_height, buffer_memory, &buffer_bitmap_info,
                  DIB_RGB_COLORS, SRCCOPY);
  }
}