#define pressed(b) (input.buttons[b].is_down)
#define draw_player(x, y) (draw_rect(x, y, x+size, y+size, 0xffffff))

#define str(x) std::to_string(x)

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

struct Input {
  Menu_Button_State buttons[BUTTON_COUNT];
};

Input input = {};

int playerX = 0;
int playerY = 0;
int size = buffer_height / 6;
float origSpeed = 1;
float speed = origSpeed;

float acceleration = 0.02;

int beachCoordinates = 0, wasteCoordinatesX = 0;

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
  int startX, startY, endX, endY, wasteCoords;
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

      if (name == "PlasticBottle") {
        endX = Sprites::getPlasticBottle()[0].size() + startX;
        endY = Sprites::getPlasticBottle().size() + startY;
      }
      if (name == "TrashBag") {
        endX = Sprites::getTrashBag()[0].size() + startX;
        endY = Sprites::getTrashBag().size() + startY;
      }
      if (name == "RustedBlockOfIron") {
        endX = Sprites::getRustedBlockOfIron()[0].size() + startX;
        endY = Sprites::getRustedBlockOfIron().size() + startY;
      }
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
          drawSprite(startX + wasteCoords, startY, 1, Sprites::getPlasticBottle());
        else
          drawSprite(startX + wasteCoords, startY, 1, Sprites::getPlasticBottleAlt());
        return 15;
      }

      if (spriteName == "TrashBag") {
        drawSprite(startX + wasteCoords, startY, 1, Sprites::getTrashBag());
        return 50;
      }

      if (spriteName == "RustedBlockOfIron") {
        drawSprite(startX + wasteCoords, startY, 1, Sprites::getRustedBlockOfIron());
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

bool isInContact1D(int start, int end, int val) {
  int tempEnd;
  if (start > end) {
    tempEnd = end;
    end = start;
    start = tempEnd;
  }

  return start <= val && val <= end;
}

bool isInContact2D(int startX, int startY, int endX, int endY, int objStartX, int objStartY, int objEndX,
                   int objEndY) {

  if (startX > objStartX && startX < objEndX && startY > objStartY &&
      startY < objEndY)
    return true;
  if (endX > objStartX && endX < objEndX && endY > objStartY &&
      endY < objEndY)
    return true;
  if (startX > objStartX && startX < objEndX && endY > objStartY &&
      endY < objEndY)
    return true;
  if (endX > objStartX && endX < objEndX && startY > objStartY &&
      startY < objEndY)
    return true;
  if (startX < objStartX && objStartX < objEndX && objEndX < endX)
    return true;

  if (isInContact1D(startX, endX, objStartX) &&
          isInContact1D(startY, endY, objStartY) ||
      isInContact1D(startX, endX, objEndX) &&
          isInContact1D(startY, endY, objEndY))
    return true;

  return false;
}

void washedUp(HWND& window, tstring appdata) {

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
               (buffer_width) / 200, Sprites::getBeach());

    if (!sprites.empty()) {
      for (auto i = 1; i <= sprites.size() * 2; i += 2)
        draw_rect(buffer_width / 20 * 19, buffer_height / 4 + i * 20,
                  buffer_width / 20 * 19 + 20,
                  buffer_height / 4 + 20 + i * 20, 0x0000ff);
    }

    if (pressed(BUTTON_LEFT)) playerX -= (speed += acceleration);
    if (pressed(BUTTON_RIGHT)) playerX += (speed += acceleration);
    if (pressed(BUTTON_DOWN)) playerY -= (speed += acceleration);
    if (pressed(BUTTON_UP)) playerY += (speed += acceleration);

    if (!pressed(BUTTON_LEFT) && !pressed(BUTTON_RIGHT) &&
        !pressed(BUTTON_UP) && !pressed(BUTTON_DOWN))
      speed = origSpeed;
    if (pressed(BUTTON_LEFT) && input.buttons[BUTTON_RIGHT].changed)
      speed = 0;
    if (pressed(BUTTON_DOWN) && input.buttons[BUTTON_UP].changed)
      speed = 0;

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
      sprites[i].setStartX(
          randomNumber(playerX - buffer_width / 4, playerX + buffer_width));
      sprites[i].setStartY(randomNumber(0, buffer_height / 5 * 3));
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
      sprites[i].wasteCoords = wasteCoordinatesX;
      auto pointsForPickup = sprites[i].draw();

      /*

      draw_text(hdc, "startX is " + str(playerX + buffer_width / 4), 100, 100, 3, 0,
                0xffffff);
      draw_text(hdc, "startY is " + str(playerY), 400, 100, 3, 0, 0xffffff);
      draw_text(hdc, "endX is " + str(playerX + buffer_width / 4 + size), 100, 80,
                3, 0, 0xffffff);
      draw_text(hdc, "endY is " + str(playerY + size), 400, 80, 3, 0, 0xffffff);
      draw_text(hdc, "objStartX is " + str(sprites[i].startX + wasteCoordinatesX), 100,
                140 * (i + 1), 3, 0, 0xffffff);
      draw_text(hdc, "objStartY is " + str(sprites[i].startY), 400, 140 * (i + 1), 3,
                0, 0xffffff);
      draw_text(hdc,
                "objEndX is " + str(sprites[i].endX + wasteCoordinatesX),
                100, 120 * (i + 1), 3, 0, 0xffffff);
      draw_text(hdc, "objEndY is " + str(sprites[i].endY), 400,
                120 * (i + 1), 3, 0, 0xffffff);

      // DBG hitbox of sprite
      draw_rect(sprites[i].startX + wasteCoordinatesX, sprites[i].endY,
                sprites[i].startX + wasteCoordinatesX + 10,
                sprites[i].endY + 10, 0x00ff00);
      draw_rect(sprites[i].endX + wasteCoordinatesX, sprites[i].endY,
                sprites[i].endX + wasteCoordinatesX + 10, sprites[i].endY + 10,
                0x00ff00);
      draw_rect(sprites[i].endX + wasteCoordinatesX, sprites[i].startY,
                sprites[i].endX + wasteCoordinatesX + 10,
                sprites[i].startY + 10, 0x00ff00);
      draw_rect(sprites[i].startX + wasteCoordinatesX, sprites[i].startY,
                sprites[i].startX + wasteCoordinatesX + 10,
                sprites[i].startY + 10, 0x00ff00);
      // DBGover

      // DBG hitbox of player
      draw_rect(playerX + buffer_width / 4, playerY + size,
                playerX + buffer_width / 4 + 10, playerY + size + 10,
                0x000000); // Top Left
      draw_rect(playerX + buffer_width / 4 + size, playerY + size,
                playerX + buffer_width / 4 + 10 + size, playerY + size + 10,
                0x000000); // Top Right
      draw_rect(playerX + buffer_width / 4, playerY,
                playerX + buffer_width / 4 + 10, playerY + 10,
                0x000000); // Bottom Left
      draw_rect(playerX + buffer_width / 4 + size, playerY,
                playerX + buffer_width / 4 + 10 + size, playerY + 10,
                0x000000); // Bottom Right
      // DBGOver
      */

      if (pressed(BUTTON_ENTER)) {
        if (isInContact2D(
                playerX + buffer_width / 4, playerY,
                playerX + buffer_width / 4 + size, playerY + size,
                sprites[i].startX + wasteCoordinatesX, sprites[i].startY,
                sprites[i].endX + wasteCoordinatesX, sprites[i].endY)) {

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

  std::fstream scoreboardDat;
  scoreboardDat.open((appdata + tstring(L"\\Washed Up\\scoreboard.dat")), std::ios_base::app | std::ios_base::in);
  scoreboardDat << score << " ";
  scoreboardDat.close();
}