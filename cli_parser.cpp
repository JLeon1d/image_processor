#include "cli_parser.h"
#include "filters/edge_detection_filter.h"
#include "filters/blur_filter.h"

bool CLIParser::IsEmpty() const {
    return is_empty_;
}

[[maybe_unused]] std::string CLIParser::GetProgramName() const {
    return program_name_;
}

std::string CLIParser::GetInputFilePath() const {
    return input_file_path_;
}

std::string CLIParser::GetOutputFilePath() const {
    return output_file_path_;
}

std::vector<std::unique_ptr<Filter>>* CLIParser::GetFilters() {
    return &filters_;
}

std::string CLIParser::GetHelpMessage() const {
    return help_;
}

void CLIParser::ParseCLIParser(int params_size, char** params_arr) {
    auto params = utils::ParseIntoStrings(params_size, params_arr);
    if (params.size() == 1) {
        is_empty_ = true;
        return;
    } else {
        is_empty_ = false;
    }
    program_name_ = params[0];

    if (params.size() < 3) {
        throw std::invalid_argument("Input and output file paths are required");
    }
    input_file_path_ = params[1];
    output_file_path_ = params[2];

    for (size_t i = 3; i < static_cast<size_t>(params_size); ++i) {
        if (params[i] == "-crop") {
            if (i + 2 >= params.size() || !utils::IsUIntNumber(params[i + 1]) || !utils::IsUIntNumber(params[i + 2])) {
                throw std::invalid_argument("Wrong Crop parameters");
            } else if (std::stoi(params[i + 1]) == 0 || std::stoi(params[i + 2]) == 0) {
                std::invalid_argument("Wrong Crop parameters, height and width should be positive");
            }
            filters_.push_back(std::make_unique<CropFilter>(CropFilter({params[i + 1], params[i + 2]})));
            i += 2;
        } else if (params[i] == "-gs") {
            filters_.push_back(std::make_unique<GrayscaleFilter>(GrayscaleFilter({})));
        } else if (params[i] == "-neg") {
            filters_.push_back(std::make_unique<NegativeFilter>(NegativeFilter({})));
        } else if (params[i] == "-sharp") {
            filters_.push_back(std::make_unique<SharpFilter>(SharpFilter({})));
        } else if (params[i] == "-edge") {
            if (i + 1 >= params.size() || !utils::IsFloatNumber(params[i + 1])) {
                throw std::invalid_argument("Wrong Edge Detection parameter");
            }
            filters_.push_back(std::make_unique<EdgeDetectionFilter>(EdgeDetectionFilter({params[i + 1]})));
            i += 1;
        } else if (params[i] == "-blur") {
            if (i + 1 >= params.size() || !utils::IsFloatNumber(params[i + 1])) {
                throw std::invalid_argument("Wrong Gaussian Blur parameter");
            }
            filters_.push_back(std::make_unique<BlurFilter>(BlurFilter({params[i + 1]})));
            i += 1;
        } else {
            throw std::invalid_argument("Wrong filter name");
        }
    }
}
