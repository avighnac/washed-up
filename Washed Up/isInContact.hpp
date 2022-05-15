#pragma once

bool isInContact1D(int start, int end, int val) {
  int tempEnd;
  if (start > end) {
    tempEnd = end;
    end = start;
    start = tempEnd;
  }

  return start <= val && val <= end;
}

bool isInContact2D(int startX, int startY, int endX, int endY, int objStartX,
                   int objStartY, int objEndX, int objEndY) {

  if (startX > objStartX && startX < objEndX && startY > objStartY &&
      startY < objEndY)
    return true;
  if (endX > objStartX && endX < objEndX && endY > objStartY && endY < objEndY)
    return true;
  if (startX > objStartX && startX < objEndX && endY > objStartY &&
      endY < objEndY)
    return true;
  if (endX > objStartX && endX < objEndX && startY > objStartY &&
      startY < objEndY)
    return true;
  if (startX < objStartX && objStartX < objEndX && objEndX < endX &&
      startY < objStartY && objStartY < objEndY && objEndY < endY)
    return true;

  if (isInContact1D(startX, endX, objStartX) &&
          isInContact1D(startY, endY, objStartY) ||
      isInContact1D(startX, endX, objEndX) &&
          isInContact1D(startY, endY, objEndY))
    return true;

  return false;
}