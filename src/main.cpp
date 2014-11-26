#include <iostream>
#include <string>
#include <fstream>

#include "classifier.h"

int main(int argc, char* argv[])
{
	std::string inputFilename, outputFilename, exportType;	

	for (int i = 1; i < argc; ++i)
	{
		if (std::string(argv[i]) == "-i" && i + 1 < argc) {
			inputFilename = argv[++i];
		}
		else if (std::string(argv[i]) == "-o" && i + 1 < argc) {
			outputFilename = argv[++i];
		}
		else if (std::string(argv[i]) == "-e" && i + 1 < argc) {
			exportType = argv[++i];
		}
		else {
			std::cerr << "Usage: " << argv[0] << " -i [input file] -o [output file] -e [h/cpp]" << std::endl;
			return EXIT_FAILURE;
		}
	}

	if (inputFilename.empty() || outputFilename.empty()) {
		std::cerr << "Usage: " << argv[0] << " -i [input file] -o [output file] -e [h/cpp]" << std::endl;
		return EXIT_FAILURE;
	}

	TClassifier* c = load_classifier_XML(inputFilename.c_str());

	std::ofstream out;	
	out.open(outputFilename);
	if (exportType == "h") {
		export_classifier_header(c, out, outputFilename.c_str());
	}
	else if (exportType == "cpp") {
		export_classifier_source(c, out, outputFilename.c_str(), "detector");
	}
	else {
		out.close();
		return EXIT_FAILURE;
	}

	out.close();
	return EXIT_SUCCESS;
}
