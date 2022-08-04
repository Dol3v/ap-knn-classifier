#include "csv.h"
#include <sstream>
#include <tuple>

namespace csv {

//    template <typename... Values>
//    std::tuple<Values...> _read_line(std::stringstream&);
//

    template<typename T, typename... Values>
    typename std::enable_if<sizeof...(Values) != 0, std::tuple<T, Values...>>::type
    read_line(std::stringstream &sstream) {
        char junk;

        T value;
        sstream >> value;
        sstream >> junk;
        std::cout << value << std::endl;
        std::tuple<T> value_tuple = std::make_tuple(value);
        return std::tuple_cat(value_tuple, read_line<Values...>(sstream));
    }

    template<typename T>
    std::tuple<T> read_line(std::stringstream &sstream) {
        char junk;

        T value;
        sstream >> value;
        sstream >> junk;
        std::cout << value << std::endl;
        return std::make_tuple(value);
    }

    template<typename T, typename... Values>
    void write_line(std::ostream &os, const T &t, const Values &... values) {
        // base case
        if (sizeof...(values) == 0) {
            os << t << std::endl;
            return;
        }
        // "recursive" case
        os << t << ",";
        write_line(os, values...);
    }
}