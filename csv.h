#pragma once
#include <iostream>
#include <sstream>
#include <tuple>

namespace csv {

    /// Reads a collection of values from a csv file; assumes they're all
    /// primitives (i.e integers, chars, doubles) or strings.
    template<typename T, typename... Values>
    typename std::enable_if<sizeof...(Values) != 0, std::tuple<T, Values...>>::type
    read_line(std::stringstream &sstream);

    template<typename T>
    std::tuple<T> read_line(std::stringstream &sstream);

    /// Writes a line in csv format to an output stream,
    /// assumes each value implemented the <<operator to be written.
    template <typename... Values>
    void write_line(std::ostream&, const Values&...);
}