//Explicit Instantiation of CD for Python Wrappers

#include "coordinate_descent.hpp"

template class foxfire::LazyCoordinateDescent<float,foxfire::internal::Solver<float>>;
template class foxfire::LazyCoordinateDescent<float,foxfire::internal::ScreeningSolver<float>>;

template class foxfire::LazyCoordinateDescent<double,foxfire::internal::Solver<double>>;
template class foxfire::LazyCoordinateDescent<double,foxfire::internal::ScreeningSolver<double>>;
