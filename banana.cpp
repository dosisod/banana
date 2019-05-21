#include <iostream>
#include <fstream>
#include <string>

int main (int argc, char *argv[]) {
	if (argc!=2) {
		std::cout << "banana takes exactly 1 parameter (for now)\n";
	}

	std::fstream file;
	file.open(argv[1]);

	if (file.is_open()) {
		std::string line="";
		while (std::getline(file,line)) {
			std::cout << line << "\n";
		}
		file.close();
	}
	
	return 0;
}