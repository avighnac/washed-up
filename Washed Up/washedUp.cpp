#define pressed(b) (input.buttons[b].is_down)
#define draw_player(x, y) (draw_rect(x, y, x+size, y+size, 0xffffff))

#define str(x) std::to_string(x)

#include "Sprites/Beach.hpp"
#include "Sprites/PlasticBottle.hpp"
#include "Sprites/PlasticBottleAlt.hpp"
#include "Sprites/TrashBag.hpp"
#include "Sprites/RustedBlockOfIron.hpp"

void drawSprite(int startX, int startY, int size,
                std::vector<std::vector<unsigned int>> &spriteVec) {
  for (auto y = 0; y < spriteVec.size(); y++) {
    for (auto x = 0; x < spriteVec[y].size(); x++) {
      if (spriteVec[spriteVec.size() - y - 1][spriteVec[y].size() - x - 1] !=
          0xffffff)
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
  BUTTON_CONTROL,

  BUTTON_COUNT,
};

struct Input {
  Button_State buttons[BUTTON_COUNT];
};

Input input = {};

int playerX = 0;
int playerY = 0;
float size = buffer_height / 6;
float speed = 5;

int beachCoordinates = 0, wasteCoordinatesX = 0;

bool boostedSpeed = false;

#include <random>

int randomNumber(int start, int end) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(start, end);
  return distr(gen);
}

class Sprite {
private:

public:
  std::string spriteName;
  int startX, startY, wasteCoords;
  bool isSetX = 0, isSetY = 0, isSetName = 0;
  bool deleted = false;

  void setStartX(int startx) {
    if (!isSetX) {
      startX = startx;
      isSetX = true;
    }
  }

  void setStartY(int starty) {
    if (!isSetY) {
      startY = starty;
      isSetY = true;
    }
  }

  void setName(std::string name) {
    if (!isSetName) {
      spriteName = name;
      isSetName = true;
    }
  }

  void deleteSprite () { deleted = true; }

  bool spriteType = false;
  int randomSprite;

  int draw() {
    if (!deleted) {
      if (spriteName == "PlasticBottle") {
        if (!spriteType) {
          randomSprite = randomNumber(0, 1);
          spriteType = 1;
        }
        if (randomSprite == 1)
          drawSprite(startX + wasteCoords, startY, 1, PlasticBottle);
        else
          drawSprite(startX + wasteCoords, startY, 1, PlasticBottleAlt);
        return 15;
      }

      if (spriteName == "TrashBag") {
        drawSprite(startX + wasteCoords, startY, 1, TrashBag);
        return 50;
      }

      if (spriteName == "RustedBlockOfIron") {
        drawSprite(startX + wasteCoords, startY, 1, RustedBlockOfIron);
        return 10;
      }
    }
  }
};

static void erase_element_at_pos(std::vector<Sprite>& vec, size_t position) {
  std::vector<Sprite> answer;
  for (auto i = 0; i < vec.size(); i++) {
    if (i != position)
      answer.push_back(vec[i]);
  }
  vec = answer;
}

void washedUp(HWND& window) {

  HDC hdc = GetDC(window);
  
  size = buffer_height / 6;

  int trashPerRound = 5;
  std::vector<Sprite> sprites(trashPerRound);

  int score = 0;

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
    //Check whether all trash has been picked up, if so
    //spawn more.
    if (sprites.empty()) {
      for (auto i = 0; i < trashPerRound; i++) {
        Sprite spr;
        sprites.push_back(spr);
      }
    }

    if (beachCoordinates <= -750)
      beachCoordinates = speed;
    if (beachCoordinates >= 92)
      beachCoordinates = -700;
    //This drawSprite function draws the background (beach).
    drawSprite(beachCoordinates - speed,
               buffer_height - (100 * (buffer_width) / 200) -
                   (55 * (buffer_width - 38) / 1098),
               (buffer_width) / 200, Beach);

    if (!sprites.empty()) {
      for (auto i = 1; i <= sprites.size() * 2; i += 2)
        draw_rect(buffer_width / 20 * 19, buffer_height / 4 + i * 20,
                  buffer_width / 20 * 19 + 20,
                  buffer_height / 4 + 20 + i * 20, 0x0000ff);
    }

    if (pressed(BUTTON_LEFT)) playerX -= speed;
    if (pressed(BUTTON_RIGHT)) playerX += speed;
    if (pressed(BUTTON_DOWN)) playerY -= speed;
    if (pressed(BUTTON_UP)) playerY += speed;

    if (playerY < 0)
      playerY = 0;
    if (playerY > buffer_height - size)
      playerY = buffer_height - size;

    draw_player(playerX + buffer_width / 4, playerY);

    if (playerX <= -buffer_width / 8 && pressed(BUTTON_LEFT)) {
      playerX = -buffer_width / 8;
      beachCoordinates += speed;
      wasteCoordinatesX += speed;
    }
    if (playerX + speed >= 17 * buffer_width / 28 && pressed(BUTTON_RIGHT)) {
      playerX = 17 * buffer_width / 28 - speed;
      beachCoordinates -= speed;
      wasteCoordinatesX -= speed;
    }

    for (auto i = 0; i < sprites.size(); i++) {
      auto randNum = randomNumber(0, 2);
      switch (randNum) {
      case 0:
        sprites[i].setName("PlasticBottle");
        break;
      case 1:
        sprites[i].setName("TrashBag");
        break;
      case 2:
        sprites[i].setName("RustedBlockOfIron");
        break;
      }
      sprites[i].setStartX(randomNumber(playerX - buffer_width / 4, playerX + buffer_width));
      sprites[i].setStartY(randomNumber(0, buffer_height / 5 * 3));
      sprites[i].wasteCoords = wasteCoordinatesX;
      auto pointsForPickup = sprites[i].draw();

      /* draw_text(hdc, "PX is " + str(playerX + buffer_width / 4), 100, 100, 3,
                   0, 0xffffff);
      draw_text(hdc, "PY is " + str(playerY), 400, 100, 3, 0, 0xffffff);
      draw_text(hdc, "WX is " + str(sprites[i].startX + wasteCoordinatesX), 100,
                125 * (i+1), 3, 0, 0xffffff);
      draw_text(hdc, "WY is " + str(sprites[i].startY), 100,
                150 * (i+1), 3, 0, 0xffffff); */

      /* The <= 50 is a convience feature. It makes it so that 
         the item would still collect if you were +- 50 pixels away from its hitbox */
      if (abs((playerX + buffer_width / 4) - (sprites[i].startX + wasteCoordinatesX) <= 50) && abs(playerY - sprites[i].startY) <= 25) {
        if (pressed(BUTTON_ENTER)) {
          score += pointsForPickup;
          erase_element_at_pos(sprites, i);
          i--;
        }
      }
    }

    draw_text(hdc, str(score), buffer_width / 10 * 9,
              (buffer_height / 10 * 9), buffer_width / 300, 0,
              0xffffff);

    StretchDIBits(hdc, 0, 0, buffer_width, buffer_height, 0, 0, buffer_width,
                  buffer_height, buffer_memory, &buffer_bitmap_info,
                  DIB_RGB_COLORS, SRCCOPY);
  }
}