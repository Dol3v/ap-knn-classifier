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

    template<typename T>
    T read_value(std::stringstream &);

    template<>
    std::string read_value(std::stringstream &);

    /// Writes a line in csv format to an output stream,
    /// assumes each value implemented the <<operator to be written.
    template<typename... Values>
    void write_line(std::ostream &, const Values &...);
}

template<typename T>
T csv::read_value(std::stringstream &sstream) {
    char junk;
    T return_value;
    sstream >> return_value;
    sstream >> junk; // remove comma delimiter
    return return_value;
}

template<typename T, typename... Values>
typename std::enable_if<sizeof...(Values) != 0, std::tuple<T, Values...>>::type
csv::read_line(std::stringstream &sstream) {
    T value = csv::read_value<T>(sstream);
    std::tuple<T> value_tuple = std::make_tuple(value);
    return std::tuple_cat(value_tuple, read_line<Values...>(sstream));
}

template<typename T>
std::tuple<T> csv::read_line(std::stringstream &sstream) {
    T value = csv::read_value<T>(sstream);
    std::cout << value << std::endl;
    return std::make_tuple(value);
}

template<typename T, typename... Values>
void csv::write_line(std::ostream &os, const T &t, const Values &... values) {
    // base case
    if (sizeof...(values) == 0) {
        os << t << std::endl;
        return;
    }
    // "recursive" case
    os << t << ",";
    csv::write_line(os, values...);
}
