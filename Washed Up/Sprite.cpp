#include "Sprite.hpp"

void Sprite::setStartX(int startx) {
  if (!isSetX) {
    startX = startx;
    isSetX = true;
  }
}