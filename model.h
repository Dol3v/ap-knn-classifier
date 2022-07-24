#pragma once

/// Classifier model
template <typename T, typename S>
class Model {
public:
    virtual void load_data(const T&, const S&) = 0;
    virtual S predict(const T&) = 0;
};
