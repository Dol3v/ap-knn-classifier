#include <iostream>
#include "knn.h"

using namespace std;

int main() {
//    auto* metric = new ChebyshevMetric;
    auto vec1 = new std::vector<double>();
    vec1->push_back(0);
    vec1->push_back(1);

    auto vec2 = new std::vector<double>();
    vec2->push_back(1);
    vec2->push_back(0);
//    std::cout << (*metric)(*vec1, *vec2) << std::endl;

    const Metric<vector<double>>* metric = new EuclideanMetric();
    auto* classifier = new KnnClassifier<vector<double>, std::string>(1, *metric);
    classifier->load_data(*vec1, string("Iris"));
    classifier->load_data(*vec2, string("Rose"));

    auto vec3 = new vector<double>();
    vec3->push_back(0);
    vec3->push_back(0.75);
    cout << classifier->predict(*vec3) << endl;
    return 0;
}
