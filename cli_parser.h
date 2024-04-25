#ifndef PROCESSOR_PARAMS_H
#define PROCESSOR_PARAMS_H

#include <unordered_map>
#include <vector>
#include <memory>
#include "filters/filter.h"
#include "utils.h"
#include "filters/crop_filter.h"
#include "filters/grayscale_filter.h"
#include "filters/negative_filter.h"
#include "filters/sharp_filter.h"

class CLIParser {
public:
    CLIParser() = default;

    ~CLIParser() = default;

    bool IsEmpty() const;

    [[maybe_unused]] std::string GetProgramName() const;

    std::string GetInputFilePath() const;

    std::string GetOutputFilePath() const;

    std::vector<std::unique_ptr<Filter>>* GetFilters();

    std::string GetHelpMessage() const;

    void ParseCLIParser(int params_size, char** params);

private:
    bool is_empty_;

    std::string program_name_;
    std::string input_file_path_;
    std::string output_file_path_;

    std::vector<std::unique_ptr<Filter>> filters_;

    const std::string help_ =
        "How to use this application:\n"
        "Format : {program path} {input file path} {output file path} [-{filter name} [filter parameters]] "
        "[-{filter name} [filter parameters]] ...\n"
        "List of filters :\n"
        "Name           | Command to use     | Description\n"
        "Crop           | -crop height width | Crop image to a given height and width\n"
        "Grayscale      | -gs                | Turns image into grayscale\n"
        "Negative       | -neg               | Turns image into negative\n"
        "Sharpening     | -sharp             | Makes image sharper\n"
        "Edge Detection | -edge threshold    | Turns image into black and white, pixels values less than threshold "
        "become black\n"
        "Gaussian Blur  | -blur sigma        | Blurs image with Gaussian blur, greater sigma = greater blur\n";
};

#endif  // PROCESSOR_PARAMS_H
