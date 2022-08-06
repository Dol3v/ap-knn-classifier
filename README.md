# The Algorithm
We are given data points related to flowers, and need to classify them based off some set of training data.

To do that, the code uses the KNN algorithm, and a csv-file parser.
We use quickselect (the non-deterministic version) to get the k-closest points efficiently.

# Usage
```text
a.out k
```
where `k` is the argument for the KNN. The code expects the training file `classified.csv` and testing-data file `Unclassified.csv`
to be in the project's directory.
# How to Run
You can download the executable from the releases page and run it yourself:)
Otherwise, you can build it using CMake or using the command (after cloning the repository)
```text
g++ -o a.out -std=c11 main.cpp knn.hpp metric.hpp metric.cpp knn.tpp utils.hpp utils.tpp csv.hpp csv.cpp 
```

## OS Compatibility
Note that the path names used are compatible with Linux specifically. To run on Windows, re-build the program
using the path name `..\\x` instead of `x`.