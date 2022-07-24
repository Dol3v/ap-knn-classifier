#include "knn.h"
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

template<class Data, class Class>
DataEntry<Data, Class>::DataEntry(Data data, Class class_) : data(data), data_class(class_) {
}

template<class Data, class Class>
KnnClassifier<Data, Class>::KnnClassifier(int k, const Metric<Data> &metric) : k(k), metric(metric) {
    this->data_set;
}

template<class Data, class Class>
void KnnClassifier<Data, Class>::load_data(const Data &t, const Class &s) {
    if (t.size() != k) {
        cout << "Invalid data point size" << endl;
        return;
    }
    auto *data = new DataEntry<Data, Class>(t, s);
    data_set.push_back(data);
}

template<class Data, class Class>
Class KnnClassifier<Data, Class>::predict(const Data &t) {
    auto *distances = new vector<double>;

    for (auto entry: data_set) {
        distances->push_back(metric(t, entry->data));
    }
    // order first k elements
    std::nth_element(distances, distances + k, distances + distances->size());
    // get class with most occurrences
    map<Class, unsigned int> occurrences;
    for (auto it = distances->begin(); it != distances->begin() + k; ++it) {
        cout << *it << endl;
        ++occurrences[*it];
    }
    return std::max_element(occurrences.begin(), occurrences.end());
}

template<class Data, class Class>
KnnClassifier<Data, Class>::~KnnClassifier() {
    for (auto entry: data_set) {
        delete entry;
    }
}

