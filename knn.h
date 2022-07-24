#pragma once
#include <string>
#include "model.h"
#include "metric.h"

/// data entry
template <class Data, class Class>
class DataEntry {
public:
    Data data;
    Class data_class;
    DataEntry(Data data, Class class_);
};



/// KNN classifier
template <class Data, class Class>
class KnnClassifier : public Model<Data, Class> {
private:
    int k;
    std::vector<DataEntry<Data, Class>*> data_set;
    const Metric<Data>& metric;
public:
    KnnClassifier(int k, const Metric<Data>& metric);
    virtual void load_data(const Data &t, const Class &s);
    virtual Class predict(const Data &t);
    ~KnnClassifier();
};