#include "filter.h"

Filter::Filter(const std::vector<std::string>& params) : params_(params) {
}

Filter::~Filter() {
    params_.clear();
}
