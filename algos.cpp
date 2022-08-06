#include "algos.h"
#include <vector>

namespace utils {

    template <typename Iter>
    void swap(Iter a, Iter b) {
        auto temp = *a;
        *a = *b;
        *b = temp;
    }

    // to do
    template <typename RAIter, typename Pred>
    RAIter partition(RAIter begin, RAIter end, RAIter pivot, Pred comp) {
        typedef typename std::iterator_traits<RAIter>::value_type value_type;
        auto pivot_value = *pivot;
        // moving pivot to the end
        utils::swap(end - 1, pivot);

        RAIter store = begin;
        value_type temp;
        for (auto i = begin; i != end - 1; i++) {
            if (comp(*i, pivot_value)) {
                // move smaller value to the left of the pivot index
                utils::swap(i, store);
                store++;
            }
        }
        // move the pivot to its calculated index
        utils::swap(store, end - 1);
        return store;
    }

    template <typename RAIter, typename Pred>
    void quick_select(RAIter begin, RAIter end, Pred comp) {
        // asserting that we have a random iterator
        static_assert(std::is_base_of<std::random_access_iterator_tag,
                              typename std::iterator_traits<RAIter>::iterator_category>::value,
                      "Iterator must be a random-access iterator");

    }

    template <typename Iter, typename Pred>
    typename std::iterator_traits<Iter>::value_type
    max_element(Iter begin, Iter end, Pred comp) {
        if (begin == end) throw std::logic_error("Invalid parameter: end and begin are equal");
        auto max = begin;
        while (++begin != end) {
            if (comp(*max, *begin)) max = begin;
        }
        return *max;
    }
};

template std::vector<double>::iterator utils::partition(std::vector<double>::iterator begin, std::vector<double>::iterator end, std::vector<double>::iterator pivot, bool (*comp)(double, double));