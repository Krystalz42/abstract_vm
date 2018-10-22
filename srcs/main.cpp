
#include <iostream>
#include <avm/AvmParser.hpp>
#include <regex>

void usage(char const *error) {
	char const *usage = "\t./avm [-v -s] file";
	std::cerr << "usage : " << error << std::endl << usage << std::endl;
	sleep(2);
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {

	std::regex r(R"(-([s|v]{1}))");
	std::smatch match;
	std::ifstream file;
	int option = 0;

	for (int index = 1; index < argc; ++index) {
		std::string const s = argv[index];
		if (std::regex_search(s.begin(), s.end(), match, r)) {
			if (match[1].compare("v") == 0) option |= OPT_VISU;
			else if (match[1].compare("s") == 0) option |= OPT_SLOW;
			else usage("bad option");
		} else {
			option |= OPT_FILE;
			if (!file.is_open())
				file.open(s);
		}
	}
	if (!file.is_open() && option & OPT_FILE) {
		usage("invalid file");
	}
	AvmParser ap(option);
	if (option & OPT_FILE)
		ap.fromFile(file);
	else
		ap.fromStdin();
	sleep(4);
	return 1;
}
