#include <pybind11/pybind11.h>
#include "../src/filter.cpp"

namespace py = pybind11;

PYBIND11_MODULE(BloomFilter, m) {
    m.doc() = "Python bindings for BloomFilter";
    py::class_<BloomFilter>(m, "BloomFilter")
        .def(py::init<std::string, uint64_t, double>())  // Constructor
        .def("Add", &BloomFilter::Add)
        .def("Contains", &BloomFilter::Contains)
        .def("Size", &BloomFilter::Size)
        .def("Count", &BloomFilter::Count)
        .def("Clear", &BloomFilter::Clear);
}