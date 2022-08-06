#include "csv.h"


int main() {
//    std::string line = "123,29.5,19";
    std::string s = "";
    std::ostringstream os(s);
    std::string str = "Iris";
    csv::write_line<int, std::string, double>(os, 5, str, 8.5);
//    std::istringstream iss(line);
//    csv::read_line<int, double, int>(iss);
//    std::cout << os.str() << std::endl;

    std::stringstream is(os.str());
    auto tup = csv::read_line<int, std::string, double>(is);
    std::cout << std::get<0>(tup) << " " << std::get<1>(tup) << " " << std::get<2>(tup) << std::endl;
}