#include "Sprite.hpp"
#include "isInContact.hpp"
#include "randomNumber.hpp"

#include <washedUpSprites.hpp>

#define pressed(b) (input.buttons[b].is_down)
#define draw_player(x, y) (draw_rect(x, y, x + size, y + size, 0xffffff))

#define str(x) std::to_string(x)

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
float origSpeed = 1, speed = origSpeed;

float acceleration = 0.02;

int beachCoordinates = 0, wasteCoordinatesX = 0;

static void erase_element_at_pos(std::vector<Sprite> &vec, size_t position) {
  std::vector<Sprite> answer;
  for (auto i = 0; i < vec.size(); i++) {
    if (i != position)
      answer.push_back(vec[i]);
  }
  vec = answer;
}

void washedUp(HWND &window, tstring appdata) {

  HDC hdc = GetDC(window);

  size = buffer_height / 6;

  int trashPerRound = 5;
  std::vector<Sprite> sprites(trashPerRound);

  int score = 0;

  float deltaTime = 1 / 500.0;

  bool playerOrientedRight = true;

  while (running) {
    auto start = std::chrono::high_resolution_clock::now();
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

    // Limit the speed to not let player accelerate to crazy speeds.
    if (speed > 10) {
      speed = 10;
    }

    // Check whether all trash has been picked up, if so
    // spawn more.
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
    // This drawSprite function draws the background (beach).
    drawSprite(beachCoordinates - speed,
               buffer_height - (100 * (buffer_width) / 200) -
                   (55 * (buffer_width - 38) / 1098),
               (buffer_width) / 200, sprites::getBeach());

    if (!sprites.empty()) {
      for (auto i = 1; i <= sprites.size() * 2; i += 2)
        draw_rect(buffer_width / 20 * 19, buffer_height / 4 + i * 20,
                  buffer_width / 20 * 19 + 20, buffer_height / 4 + 20 + i * 20,
                  0x0000ff);
    }

    // 500FPS : 10 SPD ::1/deltaTimeFPS : 20SPD;
    // When the FPS is 500, this value is 1.
    auto frameSpeed = deltaTime * 500;
    auto currentAcceleration = acceleration * frameSpeed;
    auto currentSpeed = speed * frameSpeed;

    if (pressed(BUTTON_LEFT))
      playerX -= (speed += currentAcceleration) * frameSpeed;
    if (pressed(BUTTON_RIGHT))
      playerX += (speed += currentAcceleration) * frameSpeed;
    if (pressed(BUTTON_DOWN))
      playerY -= (speed += currentAcceleration) * frameSpeed;
    if (pressed(BUTTON_UP))
      playerY += (speed += currentAcceleration) * frameSpeed;

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

    // Left and right barriers.
    if (playerX <= -buffer_width / 8 && pressed(BUTTON_LEFT)) {
      playerX = -buffer_width / 8;
      auto moveAmount = speed * frameSpeed;
      beachCoordinates += moveAmount;
      wasteCoordinatesX += moveAmount;
    }
    if (playerX + speed >= 17 * buffer_width / 28 && pressed(BUTTON_RIGHT)) {
      playerX = 17 * buffer_width / 28 - speed;
      auto moveAmount = speed * frameSpeed;
      beachCoordinates -= moveAmount;
      wasteCoordinatesX -= moveAmount;
    }

    if (pressed(BUTTON_RIGHT))
      playerOrientedRight = true;
    else if (pressed(BUTTON_LEFT))
      playerOrientedRight = false;

    if (!playerOrientedRight) drawSprite(playerX + buffer_width / 4, playerY, 1,
               sprites::getStickman_Left());
    else
      drawSprite(playerX + buffer_width / 4, playerY, 1,
                 sprites::getStickman_Right());
    //draw_player(playerX + buffer_width / 4, playerY);

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

    draw_text(hdc, str(score), buffer_width / 10 * 9, (buffer_height / 10 * 9),
              buffer_width / 300, 0, 0xffffff);

    StretchDIBits(hdc, 0, 0, buffer_width, buffer_height, 0, 0, buffer_width,
                  buffer_height, buffer_memory, &buffer_bitmap_info,
                  DIB_RGB_COLORS, SRCCOPY);

    auto end = std::chrono::high_resolution_clock::now();
    deltaTime =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
            .count() /
        1000.0;
  }

  if (score >
      0) { // If score > 0, ie. if the player collected >1 piece of trash.
    std::fstream scoreboardDat;
    scoreboardDat.open((appdata + tstring(L"\\Washed Up\\scoreboard.dat")),
                       std::ios_base::app | std::ios_base::in);
    scoreboardDat << score << " ";
    scoreboardDat.close();
  }
}