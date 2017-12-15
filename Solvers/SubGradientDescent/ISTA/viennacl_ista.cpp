#ifdef W_OPENCL

#include "viennacl_ista.hpp"

template class foxfire::CL_ISTA<float,foxfire::internal::CL_Solver<float>>;
template class foxfire::CL_ISTA<double,foxfire::internal::CL_Solver<double>>;

#endif
