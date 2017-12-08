//Explicit Instantiation of FISTA for Python Wrappers

#include "fista.hpp"

template class foxfire::FISTA<float,foxfire::internal::Solver<float>>;
template class foxfire::FISTA<float,foxfire::internal::ScreeningSolver<float>>;

template class foxfire::FISTA<double,foxfire::internal::Solver<double>>;
template class foxfire::FISTA<double,foxfire::internal::ScreeningSolver<double>>;
