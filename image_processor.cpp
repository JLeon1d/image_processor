#include <iostream>
#include "cli_parser.h"
#include "image.h"

int main(int argc, char** argv) {
    CLIParser params;
    try {
        params.ParseCLIParser(argc, argv);
    } catch (const std::invalid_argument& e) {
        std::cout << "Error : " << e.what() << std::endl;
        std::cout << params.GetHelpMessage();
        return 0;
    } catch (const std::exception& e) {
        throw e;
    }

    if (params.IsEmpty()) {
        std::cout << params.GetHelpMessage();
        return 0;
    }

    Image image;
    try {
        image.ReadBMP(params.GetInputFilePath());
    } catch (const std::invalid_argument& e) {
        std::cout << "Error : " << e.what() << std::endl;
        std::cout << params.GetHelpMessage();
        return 0;
    } catch (const std::exception& e) {
        throw e;
    }

    for (const auto& filter : (*params.GetFilters())) {
        filter->Apply(image);
    }

    try {
        image.WriteBMP(params.GetOutputFilePath());
    } catch (const std::exception& e) {
        throw e;
    }

    return 0;
}
