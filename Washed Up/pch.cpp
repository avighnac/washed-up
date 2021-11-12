#include "pch.hpp"

#include "Sprites/Beach.hexImage"
#include "Sprites/PlasticBottle.hexImage"
#include "Sprites/PlasticBottleAlt.hexImage"
#include "Sprites/RustedBlockOfIron.hexImage"
#include "Sprites/TrashBag.hexImage"

std::vector<std::vector<unsigned int>> &Sprites::getBeach() { return Beach; }
std::vector<std::vector<unsigned int>> &Sprites::getPlasticBottle() { return PlasticBottle; }
std::vector<std::vector<unsigned int>> &Sprites::getPlasticBottleAlt() { return PlasticBottleAlt; }
std::vector<std::vector<unsigned int>> &Sprites::getRustedBlockOfIron() { return RustedBlockOfIron; }
std::vector<std::vector<unsigned int>> &Sprites::getTrashBag() { return TrashBag; }
