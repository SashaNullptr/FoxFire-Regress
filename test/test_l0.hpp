#ifndef TEST_TEST_L0_HPP_
#define TEST_TEST_L0_HPP_


// C System-Headers
//
// C++ System headers
#include <limits>
#include <iomanip>
#include <iostream>
#include <type_traits>
#include <algorithm>
#include <memory>
// Eigen Headers
#include <eigen3/Eigen/Dense>
// gtest Headers
#include "gtest/gtest.h"
// Project Specific Headers
// Generic
#include "../Generic/generics.hpp"
#include "../Generic/debug.hpp"

#include "../L0_Regularized/L0_EM/l0_em.hpp"
#include "synthentic_data_gen.hpp"
#include "utils.hpp"

namespace foxfire {

namespace test {

template<typename T>
bool TestL0EM() {

	unsigned int N = rand() % 100 + 2;
	unsigned int P = rand() % 100 + 2;

	DEBUG_PRINT( "Test matrix size: " << N << " x " << P );

	const T lambda = 1.0;
	const T epsilon_0 = 1e-6;
	const T epsilon_1 = 1e-3;

	unsigned int num_active_vars = static_cast<unsigned int>(std::ceil(static_cast<T>(P) / 10.0));

	SyntheticDataGenerator<T> data_generator(N, P, num_active_vars, 0.3, 5.0);

	Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> X = data_generator.X();
	Eigen::Matrix<T, Eigen::Dynamic, 1> Y = data_generator.Y();


	Eigen::Matrix<T, Eigen::Dynamic, 1> true_beta = data_generator.Beta();
	Eigen::Matrix<T, Eigen::Dynamic, 1> theta = L0_EM( X, Y, lambda, epsilon_0, epsilon_1 );

	T delta_true_computed = ( theta - true_beta ).squaredNorm()/theta.size();

	return (delta_true_computed <= 0.5);

}

TEST(L0EM,Basic) {
	EXPECT_TRUE(TestL0EM<double>());
	EXPECT_TRUE(TestL0EM<float>());
}

}

}

#endif /* TEST_TEST_L0_HPP_ */
