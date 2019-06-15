#include "screenMaster.hpp"

void ScreenMaster::addBuffer(std::string s) {
	screens.emplace_back(
		std::make_shared<Screen>()
	);
}