inline int clamp(int min, int val, int max) {
  if (val < min)
    return min;
  if (val > max)
    return max;
  return val;
}

void draw_rect(int x0, int y0, int x1, int y1, unsigned int color) {

  x0 = clamp(0, x0, buffer_width);
  x1 = clamp(0, x1, buffer_width);
  y0 = clamp(0, y0, buffer_height);
  y1 = clamp(0, y1, buffer_height);

  for (int y = y0; y < y1; y++) {
    unsigned int *pixel = (unsigned int *)buffer_memory + x0 + y * buffer_width;
    for (int x = x0; x < x1; x++) {
      *pixel++ = color;
    }
  }
}

std::vector<std::vector<bool>> character(char alphabetChar) {
  switch (alphabetChar) {
  case 'a': {
    return {{0, 0, 0, 0, 0},
            {0, 1, 1, 1, 0},
            {0, 1, 0, 1, 0},
            {0, 1, 0, 1, 0},
            {0, 1, 1, 1, 1}};
    break;
  }
  case 'b': {
    return {{0, 1, 0, 0, 0},
            {0, 1, 0, 0, 0},
            {0, 1, 1, 1, 0},
            {0, 1, 0, 1, 0},
            {0, 1, 1, 1, 0}};
    break;
  }
  case 'c': {
    return {{0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 1, 1, 0},
            {0, 1, 0, 0, 0},
            {0, 1, 1, 1, 0}};
    break;
  }
  case 'd': {
    return {{0, 0, 0, 1, 0},
            {0, 0, 0, 1, 0},
            {0, 1, 1, 1, 0},
            {0, 1, 0, 1, 0},
            {0, 1, 1, 1, 0}};
    break;
  }
  case 'e': {
    return {{0, 1, 1, 1, 0},
            {0, 1, 0, 1, 0},
            {0, 1, 1, 1, 0},
            {0, 1, 0, 0, 0},
            {0, 1, 1, 1, 0}};
    break;
  }
  case 'f': {
    return {{0, 0, 1, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 1, 1, 1, 0}, 
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0}};
    break;
  }
  case 'g': {
    return {{0, 1, 1, 1, 0},
            {0, 1, 0, 1, 0},
            {0, 1, 1, 1, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 1, 1, 0}};
    break;
  }
  case 'h': {
    return {{0, 1, 0, 0, 0},
            {0, 1, 0, 0, 0},
            {0, 1, 1, 1, 0},
            {0, 1, 0, 1, 0},
            {0, 1, 0, 1, 0}};
    break;
  }
  case 'i': {
    return {{0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0}};
    break;
  }
  case 'k': {
    return {{0, 1, 0, 1, 0},
            {0, 1, 1, 0, 0},
            {0, 1, 0, 0, 0},
            {0, 1, 1, 0, 0},
            {0, 1, 0, 1, 0}};
    break;
  }
  case 'l': {
    return {{0, 1, 0, 0, 0},
            {0, 1, 0, 0, 0},
            {0, 1, 0, 0, 0},
            {0, 1, 0, 0, 0},
            {0, 0, 1, 1, 0}};
    break;
  }
  case 'm': {
    return {{0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 0, 1, 0},
            {1, 0, 1, 0, 1},
            {1, 0, 0, 0, 1}};
    break;
  }
  case 'n': {
    return {{0, 0, 0, 0, 0},
            {0, 0, 1, 1, 0},
            {0, 1, 0, 1, 0},
            {0, 1, 0, 1, 0},
            {0, 1, 0, 1, 0}};
    break;
  }
  case 'o': {
    return {{0, 0, 0, 0, 0},
            {0, 1, 1, 1, 0},
            {1, 0, 0, 0, 1},
            {1, 0, 0, 0, 1},
            {0, 1, 1, 1, 0}};
    break;
  }
  case 'p': {
    return {{0, 0, 0, 0, 0},
            {0, 1, 1, 1, 0},
            {0, 1, 0, 1, 0},
            {0, 1, 1, 1, 0},
            {0, 1, 0, 0, 0}};
    break;
  }
  case 'r': {
    return {{0, 0, 0, 0, 0},
            {1, 0, 1, 1, 0},
            {0, 1, 1, 0, 0},
            {0, 1, 0, 0, 0},
            {0, 1, 0, 0, 0}};
    break;
  }
  case 's': {
    return {{0, 0, 1, 1, 0},
            {0, 1, 0, 0, 0},
            {0, 1, 1, 0, 0},
            {0, 0, 0, 1, 0},
            {0, 1, 1, 1, 0}};
    break;
  }
  case 't': {
    return {{0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 1, 1, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 1, 0}};
    break;
  }
  case 'u': {
    return {{0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 0, 1, 0},
            {0, 1, 0, 1, 0},
            {0, 1, 1, 1, 0}};
    break;
  }
  case 'w': {
    return {{0, 0, 0, 0, 0},
            {1, 0, 0, 0, 1},
            {1, 0, 0, 0, 1},
            {1, 0, 1, 0, 1},
            {0, 1, 0, 1, 0}};
    break;
  }
  case 'y': {
    return {{0, 1, 0, 1, 0},
            {0, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 1, 0, 0, 0}};
    break;
  }

  case 'A': {
    return {{0, 1, 1, 1, 0},
            {1, 1, 0, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 0, 0, 0, 1},
            {1, 0, 0, 0, 1}};
    break;
  }
  case 'B': {
    return {{0, 1, 1, 1, 0},
            {0, 1, 0, 1, 1},
            {0, 1, 1, 1, 0},
            {0, 1, 0, 1, 1},
            {0, 1, 1, 1, 0}};
    break;
  }
  case 'C': {
    return {{0, 1, 1, 1, 1},
            {1, 0, 0, 0, 0},
            {1, 0, 0, 0, 0},
            {1, 0, 0, 0, 0},
            {0, 1, 1, 1, 1}};
    break;
  }
  case 'D': {
    return {{1, 1, 1, 1, 0},
            {1, 0, 0, 0, 1},
            {1, 0, 0, 0, 1},
            {1, 0, 0, 0, 1},
            {1, 1, 1, 1, 0}};
    break;
  }
  case 'E': {
    return {{1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0},
            {1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0},
            {1, 1, 1, 1, 1}};
    break;
  }
  case 'F': {
    return {{1, 1, 1, 0, 0},
            {1, 0, 0, 0, 0},
            {1, 1, 1, 0, 0},
            {1, 0, 0, 0, 0},
            {1, 0, 0, 0, 0}};
    break;
  }
  case 'G': {
    return {{1, 1, 1, 0, 0},
            {1, 0, 0, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 0, 1, 1, 0},
            {1, 1, 1, 0, 0}};
    break;
  }
  case 'H': {
    return {{1, 0, 0, 0, 1},
            {1, 0, 0, 0, 1},
            {1, 1, 1, 1, 1},
            {1, 0, 0, 0, 1},
            {1, 0, 0, 0, 1}};
  }
  case 'I': {
    return {{0, 1, 1, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 1, 1, 1, 0}};
    break;
  }
  case 'K': {
    return {{1, 0, 0, 1, 1},
            {1, 0, 1, 1, 0},
            {1, 1, 0, 0, 0},
            {1, 0, 1, 1, 0},
            {1, 0, 0, 1, 1}};
    break;
  }
  case 'L': {
    return {{1, 0, 0, 0, 0},
            {1, 0, 0, 0, 0},
            {1, 0, 0, 0, 0},
            {1, 0, 0, 0, 0},
            {1, 1, 1, 1, 1}};
    break;
  }
  case 'M': {
    return {{1, 0, 0, 0, 1},
            {1, 1, 0, 1, 1},
            {1, 0, 1, 0, 1},
            {1, 0, 0, 0, 1},
            {1, 0, 0, 0, 1}};
    break;
  }
  case 'N': {
    return {{1, 0, 0, 0, 1},
            {1, 1, 0, 0, 1},
            {1, 0, 1, 0, 1},
            {1, 0, 0, 1, 1},
            {1, 0, 0, 0, 1}};
    break;
  }
  case 'O': {
    return {{0, 1, 1, 1, 0},
            {1, 0, 0, 0, 1},
            {1, 0, 0, 0, 1},
            {1, 0, 0, 0, 1},
            {0, 1, 1, 1, 0}};
    break;
  }
  case 'P': {
    return {{1, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 1, 0, 0},
            {1, 0, 0, 0, 0},
            {1, 0, 0, 0, 0}};
    break;
  }
  case 'R': {
    return {{1, 1, 1, 0, 0},
            {1, 0, 0, 1, 0},
            {1, 1, 1, 0, 0},
            {1, 0, 1, 1, 0},
            {1, 0, 0, 0, 1}};
    break;
  }
  case 'S': {
    return {{0, 1, 1, 1, 0},
            {0, 1, 0, 0, 0},
            {0, 1, 1, 1, 0},
            {0, 0, 0, 1, 0},
            {0, 1, 1, 1, 0}};
    break;
  }
  case 'T': {
    return {{1, 1, 1, 1, 1},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0}};
    break;
  }
  case 'U': {
    return {{1, 0, 0, 0, 1},
            {1, 0, 0, 0, 1},
            {1, 0, 0, 0, 1},
            {1, 0, 0, 0, 1},
            {1, 1, 1, 1, 1}};
    break;
  }
  case 'V': {
    return {{1, 0, 0, 0, 1},
            {1, 1, 0, 1, 1},
            {0, 1, 0, 1, 0},
            {0, 1, 0, 1, 0},
            {0, 0, 1, 0, 0}};
    break;
  }
  case 'W': {
    return {{1, 0, 0, 0, 1},
            {1, 0, 0, 0, 1},
            {1, 0, 0, 0, 1},
            {1, 0, 1, 0, 1},
            {0, 1, 0, 1, 0}};
    break;
  }
  case 'X': {
    return {{1, 0, 0, 0, 1},
            {0, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 1, 0, 1, 0},
            {1, 0, 0, 0, 1}};
    break;
  }
  case 'Y': {
    return {{1, 0, 0, 0, 1},
            {0, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0}};
    break;
  }

  case ',': {
    return {{0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 1, 0, 0}};
    break;
  }
  case ':': {
    return {{0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
    break;
  }       
  case ' ': {
    return {{0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}};
    break;
  }
  case '\'': {
    return {{0, 1, 0, 0, 0},
            {0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}};
    break;
  }
  case '!': {
    return {{0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0}};
    break;
  }
  case '.': {
    return {{0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0}};
    break;
  }
  case '-': {
    return {{0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 1, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}};
    break;
  }
  case '+': {
    return {{0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {1, 1, 1, 1, 1},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0}};
    break;
  }

  case '1': {
    return {{0, 0, 1, 0, 0},
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 1, 1, 1, 0}};
    break;
  }
  case '2': {
    return {{0, 1, 1, 0, 0},
            {1, 0, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 1, 0, 0, 0},
            {1, 1, 1, 1, 1}};
    break;
  }
  case '3': {
    return {{0, 1, 1, 1, 0},
            {0, 0, 0, 1, 0},
            {0, 1, 1, 1, 0},
            {0, 0, 0, 1, 0},
            {0, 1, 1, 1, 0}};
    break;
  }
  case '4': {
    return {{0, 0, 1, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 1, 0, 1, 0},
            {1, 1, 1, 1, 0},
            {0, 0, 0, 1, 0}};
    break;
  }
  case '5': {
    return {{0, 1, 1, 1, 0},
            {0, 1, 0, 0, 0},
            {0, 1, 1, 1, 0},
            {0, 0, 0, 1, 1},
            {0, 1, 1, 1, 0}};
    break;
  }
  case '6': {
    return {{0, 1, 1, 1, 0},
            {0, 1, 0, 0, 0},
            {0, 1, 1, 1, 0},
            {0, 1, 0, 1, 0},
            {0, 1, 1, 1, 0}};
    break;
  }
  case '7': {
    return {{1, 1, 1, 1, 1},
            {0, 0, 0, 1, 0},
            {1, 1, 1, 1, 1},
            {0, 1, 0, 0, 0},
            {1, 0, 0, 0, 0}};
    break;
  }
  case '8': {
    return {{0, 1, 1, 1, 0},
            {0, 1, 0, 1, 0},
            {0, 1, 1, 1, 0},
            {0, 1, 0, 1, 0},
            {0, 0, 1, 1, 0}};
    break;
  }
  case '9': {
    return {{0, 1, 1, 1, 0},
            {0, 1, 0, 1, 0},
            {0, 1, 1, 1, 0},
            {0, 0, 0, 1, 0},
            {0, 1, 1, 1, 0}};
    break;
  }
  case '0': {
    return {{0, 1, 1, 1, 0},
            {0, 1, 0, 1, 0},
            {0, 1, 0, 1, 0},
            {0, 1, 0, 1, 0},
            {0, 1, 1, 1, 0}};
    break;
  }

  default: {
    return {{0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}};
    break;
  }
  }
}

void draw_vector(const std::vector<std::vector<bool>> &vec, int startX,
                 int startY, int size, unsigned int color) {
  for (auto y = (((long long)(vec.size())) - 1); y > -1; y--)
    for (auto x = 0; x < vec.size(); x++)
      if (vec[vec.size() - y - 1][x])
        draw_rect(startX + x * size, startY + y * size, startX + (x + 1) * size,
                  startY + (y + 1) * size, color);
}

void clear_screen(unsigned int color) {
  unsigned int *pixel = (unsigned int *)buffer_memory;
  for (auto y = 0; y < buffer_height; y++) {
    for (auto x = 0; x < buffer_width; x++) {
      *pixel++ = color;
    }
  }
}

void draw_text(HDC &hdc, std::string text, int startX, int startY, int size,
               int spacing, unsigned int color) {
  for (auto i = 0; i < text.size(); i++) {
    draw_vector(character(text[i]), startX + i * (size * 6 + spacing), startY,
                size, color);
  }
}

void draw_animated_text(HDC &hdc, std::string text, int startX, int startY,
                        int size, int spacing, unsigned int color, int msTime) {
  for (auto i = 0; i < text.size(); i++) {
    draw_vector(character(text[i]), startX + i * (size * 6 + spacing), startY,
                size, color);
    StretchDIBits(hdc, 0, 0, buffer_width, buffer_height, 0, 0, buffer_width,
                  buffer_height, buffer_memory, &buffer_bitmap_info,
                  DIB_RGB_COLORS, SRCCOPY);
    Sleep(msTime);
  }
}