//Explicit Instantiation of VCL FISTA for Python Wrappers
#ifdef W_OPENCL
#include "viennacl_fista.hpp"

template class foxfire::CL_FISTA<float,foxfire::internal::CL_Solver<float>>;
template class foxfire::CL_FISTA<double,foxfire::internal::CL_Solver<double>>;

#endif
