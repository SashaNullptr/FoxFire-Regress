//Explicit Instantiation of ISTA for Python Wrappers

#include "ista.hpp"

template class foxfire::ISTA<float,foxfire::internal::Solver<float>>;
template class foxfire::ISTA<float,foxfire::internal::ScreeningSolver<float>>;

template class foxfire::ISTA<double,foxfire::internal::Solver<double>>;
template class foxfire::ISTA<double,foxfire::internal::ScreeningSolver<double>>;
