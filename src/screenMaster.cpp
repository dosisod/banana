#include "screenMaster.hpp"

ScreenMaster::ScreenMaster(std::shared_ptr<Terminal> t) {
	term=t;
}

void ScreenMaster::addBuffer(std::string s) {
	screens.emplace_back(
		std::make_shared<Screen>(term)
	);
	screens[screens.size()-1]->useBuffer(std::make_shared<File>(s));
}