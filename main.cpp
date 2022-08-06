#include <fstream>
#include "csv.hpp"
#include "knn.hpp"


void train_model(KnnClassifier<std::vector<double>, std::string> model, std::fstream& file) {
    while (file) {
        std::string line;
        std::getline(file, line);

        if (line.empty()) {
            break;
        }
        std::stringstream ss(line);

        auto values = csv::read_line<double, double, double, double, std::string>(ss);

        auto data_class = std::get<4>(values);
        std::vector<double> data;
        data.push_back(std::get<0>(values));
        data.push_back(std::get<1>(values));
        data.push_back(std::get<2>(values));
        data.push_back(std::get<3>(values));

        model.load_data(data, data_class);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "usage: a.out k" << std::endl;
        return 1;
    }
    int k = std::stoi(std::string(argv[1]));
    ChebyshevMetric chebyshev_metric;
    EuclideanMetric euclidean_metric;
    ManhattanMetric manhattan_metric;
    KnnClassifier<std::vector<double>, std::string> classifier(k);

    std::fstream fio;
    fio.open(R"(..\classified.csv)");
    if (!fio) {
        std::cout << "Failed to open the training data" << std::endl;
        return 1;
    }
    train_model(classifier, fio);
    fio.close();
    fio.open(R"(..\Unclassified.csv)");
    if (!fio) {
        std::cout << "Failed to open the unclassified data" << std::endl;
        return 1;
    }

    std::fstream euclidean, chebyshev, manhattan;
    euclidean.open("..\\euclidean_output.csv", std::fstream::out | std::fstream::trunc);
    chebyshev.open("..\\chebyshev_output.csv", std::fstream::out | std::fstream::trunc);
    manhattan.open("..\\manhattan_output.csv", std::fstream::out | std::fstream::trunc);
    if (!euclidean || !chebyshev || !manhattan) {
        std::cout << "Failed to create output files" << std::endl;
        return 1;
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

//        std::cout << classifier.predict(data) << std::endl;
    }

    fio.close();
}