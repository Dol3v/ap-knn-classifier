#pragma once
#include <iterator>

namespace utils {
    /// Returns the max element of an iterator.

    template <typename Iter, typename Pred>
    typename Iter::value_type
    max_element(Iter begin, Iter end, Pred pred);
}