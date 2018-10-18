#include <iostream>


#include <avm/AvmParser.hpp>
#include <regex>
#include <zconf.h>

int main(int argc, char **argv) {
	std::regex r(R"(-([s|v]{1}))");
	std::smatch match;
	std::ifstream file;
	int option = 0;

	for (int index = 1; index < argc; ++index) {
		std::string const s = argv[index];
		if (std::regex_search(s.begin(), s.end(), match, r)) {
			option |= match[1].compare("v") == 0 ? OPT_VISU : 0;
			option |= match[1].compare("s") == 0 ? OPT_SLOW : 0;
		} else {
			option |= OPT_FILE;
//			std::cout << s << std::endl;
			if (!file.is_open())
				file.open(s);
		}
	}
	std::cout << option << std::endl;
	AvmParser ap(option);
	if (option & OPT_FILE) ap.fromFile(file); else ap.fromStdin();
	return 0;
}
