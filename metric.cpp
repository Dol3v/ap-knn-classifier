#include <stdexcept>
#include <cmath>
#include "metric.h"

double EuclideanMetric::operator()(const std::vector<double> &t, const std::vector<double> &t1) {
    if (t.size() != t1.size()) {
        // TODO: change to more appropriate error
        throw std::runtime_error("operands' sizes don't match");
    }
    double diff = 0;
    for (int i = 0; i < t.size(); i++) {
        diff += std::pow(t.at(i) - t1.at(i), 2);
    }
    return std::pow(diff, 1. / (double)t.size());
}

double ManhattanDistance::operator()(const std::vector<double> &t, const std::vector<double> &t1) {
    if (t.size() != t1.size()) {
        throw std::runtime_error("operands' sizes don't match");
    }
    double distance = 0;
    for (int i = 0; i < t.size(); i++) {
        distance += std::abs(t.at(i) - t1.at(i));
    }
    return distance;
}

double ChebyshevMetric::operator()(const std::vector<double> &t, const std::vector<double> &t1) {
    if (t.size() != t1.size()) {
        throw std::runtime_error("operands' sizes don't match");
    }
    double distance = 0;
    for (int i = 0; i < t.size(); i++) {
        distance = std::max(distance, std::abs(t.at(i) - t1.at(i)));
    }
    return distance;
}