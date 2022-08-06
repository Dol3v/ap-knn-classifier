#include <fstream>
#include "csv.h"
#include "knn.h"

int main() {
    ChebyshevMetric metric;
    KnnClassifier<std::vector<double>, std::string> classifier(9, metric);

    std::fstream fio;

    fio.open(R"(C:\Users\dol12\CLionProjects\ap1-knn-classifier\classified.csv)");

    while (fio) {
        std::string line;
        std::getline(fio, line);

        if (line.empty()) {
            break;
        }
        std::stringstream ss(line);

        auto values = csv::read_line<double, double, double, double, std::string>(ss);
//        std::cout << "---" << std::endl;

        auto data_class = std::get<4>(values);
        std::vector<double> data;
        data.push_back(std::get<0>(values));
        data.push_back(std::get<1>(values));
        data.push_back(std::get<2>(values));
        data.push_back(std::get<3>(values));

        classifier.load_data(data, data_class);
    }

    fio.close();
    fio.open(R"(C:\Users\dol12\CLionProjects\ap1-knn-classifier\Unclassified.csv)");
//    std::fstream fout;
//    fout.open(R"(C:\Users\dol12\CLionProjects\ap1-knn-classifier\result.csv)", std::fstream::out | std::fstream::trunc);
    if (!fio) {
        std::cout << "Failed to open the necessary files" << std::endl;
        return -1;
    }

    while (fio) {
        std::string line;
        std::getline(fio, line);
        if (line.empty()) {
            break;
        }
        std::stringstream ss(line);
        auto values = csv::read_line<double, double, double, double>(ss);
        std::vector<double> data;
        data.push_back(std::get<0>(values));
        data.push_back(std::get<1>(values));
        data.push_back(std::get<2>(values));
        data.push_back(std::get<3>(values));

        std::cout << classifier.predict(data) << std::endl;
    }

    fio.close();
}