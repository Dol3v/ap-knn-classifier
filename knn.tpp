#include "metric.h"
#include "algos.cpp"
#include <algorithm>
#include <tuple>
#include "model.h"
#include "metric.h"
#include <map>

template<class Data, class Class>
DataEntry<Data, Class>::DataEntry(Data data, Class class_) : data(data), data_class(class_) {
}

template<class Data, class Class>
KnnClassifier<Data, Class>::KnnClassifier(int k, const Metric<Data> &metric) : k(k), metric(metric) {
    this->data_set;
}

template<class Data, class Class>
void KnnClassifier<Data, Class>::load_data(const Data &t, const Class &s) {
    auto *data = new DataEntry<Data, Class>(t, s);
    data_set.push_back(data);
}

template<class Data, class Class>
Class KnnClassifier<Data, Class>::predict(const Data &t) {
    if (this->data_set.size() < k) {
        throw std::logic_error("insufficient data loaded to make a prediction");
    }
    // calculate distances
    std::vector<std::pair<double, Class>> distances;
    for (auto entry: data_set) {
        distances.push_back(std::pair<double, Class>(metric(t, entry->data), entry->data_class));
    }
    // order first k elements
    std::nth_element(distances.begin(), distances.begin() + k, distances.end(),
                     [](const std::pair<double, Class> &c1, const std::pair<double, Class> &c2) {
                         return c1.first < c2.first;
                     });

    // count occurrences per class
    std::map<Class, int> occurrences;
    for (auto it = distances.begin(); it != distances.begin() + k; ++it) {
        if (occurrences.find(it->second) == occurrences.end()) {
            occurrences.insert(std::pair<Class, double>(it->second, 0));
        }
        ++occurrences[it->second];
    }
    // return max element
    return utils::max_element(occurrences.begin(), occurrences.end(),
                            [](const std::pair<Class, int> &p1, const std::pair<Class, int> &p2) {
                                return p1.second < p2.second;
                            }).first;
}

template<class Data, class Class>
KnnClassifier<Data, Class>::~KnnClassifier() {
    for (auto entry: data_set) {
        delete entry;
    }
}
