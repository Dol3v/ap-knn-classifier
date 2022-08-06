#include "csv.h"
#include <sstream>

namespace csv {

    template <>
    std::string read_value(std::stringstream &sstream) {
        std::string return_value;
        std::getline(sstream, return_value, ',');
        return return_value;
    }
}