#pragma once
#include <vector>

/// Measures distance between two data points.
template <class T>
class Metric {
public:
    virtual double operator()(const T&, const T&) const;
};

/// The usual Euclidean metric.
class EuclideanMetric : public Metric<std::vector<double>> {
public:
    double operator()(const std::vector<double> &t, const std::vector<double> &t1) const override;
};

/// The Manhattan distance function.
class ManhattanDistance : public Metric<std::vector<double>> {
public:
    double operator()(const std::vector<double> &t, const std::vector<double> &t1) const override;
};

/// The Chebyshev distance function.
class ChebyshevMetric : public Metric<std::vector<double>> {
public:
    double operator()(const std::vector<double> &t, const std::vector<double> &t1) const override;
};