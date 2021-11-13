#pragma once

int randomNumber(int start, int end) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(start, end);
  return distr(gen);
}