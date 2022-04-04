#include <vector>

#include "washedUpSprites.hpp"

#include "Sprites/Beach.hexImage"
#include "Sprites/PlasticBottle.hexImage"
#include "Sprites/PlasticBottleAlt.hexImage"
#include "Sprites/RustedBlockOfIron.hexImage"
#include "Sprites/TrashBag.hexImage"
#include "Sprites/Stickman_Left.hexImage"
#include "Sprites/Stickman_Right.hexImage"

std::vector<std::vector<unsigned int>> &sprites::getBeach() { return Beach; }
std::vector<std::vector<unsigned int>> &sprites::getPlasticBottle() { return PlasticBottle; }
std::vector<std::vector<unsigned int>> &sprites::getPlasticBottleAlt() { return PlasticBottleAlt; }
std::vector<std::vector<unsigned int>> &sprites::getRustedBlockOfIron() { return RustedBlockOfIron; }
std::vector<std::vector<unsigned int>> &sprites::getTrashBag() { return TrashBag; }
std::vector<std::vector<unsigned int>> &sprites::getStickman_Left() { return Stickman_Left; }
std::vector<std::vector<unsigned int>> &sprites::getStickman_Right() { return Stickman_Right; }