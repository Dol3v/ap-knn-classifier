#pragma once
#include <iterator>

namespace utils {

    /// Runs quick-select on a random-access iterator. The algorithm modifies the iterable in-place.
    ///
    /// Types:
    /// RAIter - random access iterator
    /// Pred - comparison predicate for the iterator elements
    ///
    /// Arguments:
    /// begin, end - begin and end of the iterable
    /// comp - comparison predicate for the iterable's elements
    template <typename RAIter, typename Pred>
    void quick_select(RAIter begin, RAIter end, uint32_t k, Pred comp);

    /// Returns the max element of an iterator.
    template <typename Iter, typename Pred>
    typename std::iterator_traits<Iter>::value_type
    max_element(Iter begin, Iter end, Pred comp);
}