#include <string>
#include <stack>
#include <vector>
#include <map>
#include <bitset>
#include "MSMaths.h"
#include "Prism.h"

#pragma once
class LSystem
{
public:
	std::vector<Prism> GenLSystem(std::string currentString, std::bitset<7> b, std::vector<Prism> allPrisms = {});
};

