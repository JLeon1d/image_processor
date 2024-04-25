#ifndef FILTER_H
#define FILTER_H

#include "../image.h"
#include <cstdint>
#include <string>
#include <vector>

class Filter {
public:
    explicit Filter(const std::vector<std::string>& params);

    virtual ~Filter();

    virtual void Apply(Image& image) = 0;

protected:
    std::vector<std::string> params_;
};

#endif  // FILTER_H
