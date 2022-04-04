#pragma once

#include "randomNumber.hpp"
#include <washedUpSprites.hpp>

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

class Sprite {
private:
public:
  std::string spriteName;
  int startX, startY, endX, endY, wasteCoords;
  bool isSetX = 0, isSetY = 0, isSetName = 0;
  bool deleted = false;

  void setStartX(int startx);
  void setStartY(int starty);

  void setName(std::string name);

  void deleteSprite() { deleted = true; }

  bool spriteType = false;
  int randomSprite;

  int draw();
};


void Sprite::setStartX(int startx) {
  if (!isSetX) {
    startX = startx;
    isSetX = true;
  }
}

void Sprite::setStartY(int starty) {
  if (!isSetY) {
    startY = starty;
    isSetY = true;
  }
}

void Sprite::setName(std::string name) {
  if (!isSetName) {
    spriteName = name;
    isSetName = true;

    if (name == "PlasticBottle") {
      endX = sprites::getPlasticBottle()[0].size() + startX;
      endY = sprites::getPlasticBottle().size() + startY;
    }
    if (name == "TrashBag") {
      endX = sprites::getTrashBag()[0].size() + startX;
      endY = sprites::getTrashBag().size() + startY;
    }
    if (name == "RustedBlockOfIron") {
      endX = sprites::getRustedBlockOfIron()[0].size() + startX;
      endY = sprites::getRustedBlockOfIron().size() + startY;
    }
  }
}

int Sprite::draw() {
  if (!deleted) {
    if (spriteName == "PlasticBottle") {
      if (!spriteType) {
        randomSprite = randomNumber(0, 1);
        spriteType = 1;
      }
      if (randomSprite == 1)
        drawSprite(startX + wasteCoords, startY, 1,
                   sprites::getPlasticBottle());
      else
        drawSprite(startX + wasteCoords, startY, 1,
                   sprites::getPlasticBottleAlt());
      return 15;
    }

    if (spriteName == "TrashBag") {
      drawSprite(startX + wasteCoords, startY, 1, sprites::getTrashBag());
      return 50;
    }

    if (spriteName == "RustedBlockOfIron") {
      drawSprite(startX + wasteCoords, startY, 1,
                 sprites::getRustedBlockOfIron());
      return 10;
    }
  }
}