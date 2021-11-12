#pragma once
#include <vector>
#include <windows.h>
#include <string>
#include <random>
#include <shlobj.h>
#include <sstream>
#include <filesystem>
#include <fstream>

namespace Sprites {
std::vector<std::vector<unsigned int>> &getBeach();
std::vector<std::vector<unsigned int>> &getPlasticBottle();
std::vector<std::vector<unsigned int>> &getPlasticBottleAlt();
std::vector<std::vector<unsigned int>> &getRustedBlockOfIron();
std::vector<std::vector<unsigned int>> &getTrashBag();
}; // namespace Sprites