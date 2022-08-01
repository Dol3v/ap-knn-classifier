#include "algos.h"
#include <vector>

template <typename Iter, typename Pred>
typename std::iterator_traits<Iter>::value_type
utils::max_element(Iter begin, Iter end, Pred pred) {
    if (begin == end) throw std::logic_error("Invalid parameter: end and begin are equal");
    auto max = *begin;
    begin++;
    while (++begin != end) {
        if (pred(*begin, max)) max = *begin;
    }
    return max;
}