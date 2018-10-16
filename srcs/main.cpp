#include <iostream>


#include <avm/AvmParser.hpp>
#include <list>

int main(int argc, char **argv) {
	AvmParser ap;
	if (argc == 2) {
		std::ifstream file(argv[1]);
		if (file.is_open())
			ap.fromFile(file);
		else
			std::cerr << "Error" << std::endl;
	} else
		ap.fromStdin();
	return 0;
}