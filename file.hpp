#include <fstream>
#include <string>
#include <vector>

class File {
public:
	File(std::string fn);

private:
	std::string filename;
	std::fstream stream; //stream is here as it can be used when reading and writing
	std::vector<std::string> buffer; //contains the lines of the file
};