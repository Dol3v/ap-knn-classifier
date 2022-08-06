#include <fstream>
#include "csv.hpp"
#include "knn.hpp"


void train_model(KnnClassifier<std::vector<double>, std::string>& model, std::fstream &file) {
    while (file) {
        std::string line;
        std::getline(file, line);

        if (line.empty()) {
            break;
        }
        std::stringstream ss(line);

        auto values = csv::read_line<double, double, double, double, std::string>(ss);

        auto data_class = std::get<4>(values);
        auto data = utils::tup2vec4(values);

        model.load_data(data, data_class);
    }
}

void run_predictions(KnnClassifier<std::vector<double>, std::string>& classifier,
                     std::fstream &input_data,
                     const std::vector<Metric<std::vector<double>>> &metrics,
                     const std::vector<std::fstream> &fstreams) {
    if (metrics.size() != fstreams.size()) {
        throw std::logic_error("metric list and file list sizes don't match");
    }

}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "usage: a.out k" << std::endl;
        return 1;
    }
    int k = std::stoi(std::string(argv[1]));
    ChebyshevMetric chebyshev_metric;
    EuclideanMetric euclidean_metric;
    ManhattanMetric manhattan_metric;

    std::vector<Metric<std::vector<double>>*> metrics;
    metrics.push_back(&euclidean_metric);
    metrics.push_back(&chebyshev_metric);
    metrics.push_back(&manhattan_metric);

    KnnClassifier<std::vector<double>, std::string> classifier(k);

    std::fstream fio;
    fio.open("classified.csv");
    if (!fio) {
        std::cout << "Failed to open the training data" << std::endl;
        return 1;
    }
    train_model(classifier, fio);
    fio.close();
    fio.open("Unclassified.csv");
    if (!fio) {
        std::cout << "Failed to open the unclassified data" << std::endl;
        return 1;
    }

    std::fstream euclidean, chebyshev, manhattan;
    euclidean.open("euclidean_output.csv", std::fstream::out | std::fstream::trunc);
    chebyshev.open("chebyshev_output.csv", std::fstream::out | std::fstream::trunc);
    manhattan.open("manhattan_output.csv", std::fstream::out | std::fstream::trunc);
    if (!euclidean || !chebyshev || !manhattan) {
        std::cout << "Failed to create output files" << std::endl;
        return 1;
    }
    std::vector<std::fstream> files;
    files.push_back(std::move(euclidean));
    files.push_back(std::move(chebyshev));
    files.push_back(std::move(manhattan));

    while (fio) {
        // reading values from csv
        std::string line;
        std::getline(fio, line);
        if (line.empty()) {
            break;
        }
        std::stringstream ss(line);
        auto values = csv::read_line<double, double, double, double>(ss);
        auto data = utils::tup2vec4(values);

        // classifying using the different metrics and writing to matching files
        for (int i = 0; i < metrics.size(); ++i) {
            std::string data_class = classifier.predict(data, *metrics[i]);
            csv::write_line((std::ostream &) files[i], std::get<0>(values),
                            std::get<1>(values),
                            std::get<2>(values),
                            std::get<3>(values),
                            data_class);
        }
    }
    fio.close();
    for (auto &file : files) {
        file.close();
    }
}