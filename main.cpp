#include <iostream>
#include "knn.h"
#include "algos.h"

bool compare(double a, double b) {
    return a < b;
}

int main() {
//    auto vec1 = new std::vector<double>();
//    vec1->push_back(0);
//    vec1->push_back(1);
//
    auto vec2 = new std::vector<double>();
    vec2->push_back(1);
    vec2->push_back(0);
//
//    const Metric<vector<double>>* metric = new EuclideanMetric();
//    auto* classifier = new KnnClassifier<vector<double>, std::string>(3, *metric);
//    classifier->load_data(*vec1, string("Iris"));
//    classifier->load_data(*vec2, string("Rose"));
//
//    auto vec3 = new vector<double>();
//    vec3->push_back(0);
//    vec3->push_back(0.75);
//    cout << classifier->predict(*vec3) << endl;
//    std::iterator_traits<vector<double>::iterator>::value_type val = 0.5;
//    double a = 3;
//    cout << (a == val) << endl
//  ;
    std::cout << utils::max_element<std::vector<double>::iterator, bool (*)(double, double)>(vec2->begin(), vec2->end(), compare) << std::endl;
    return 0;
}
