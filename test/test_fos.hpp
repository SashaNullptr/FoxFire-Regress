#ifndef TEST_FOS_HPP
#define TEST_FOS_HPP

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
#include "../FOS/fos.hpp"
#include "synthentic_data_gen.hpp"
#include "utils.hpp"

namespace foxfire {

namespace test {

template<typename T>
class FOSTester {
public:
	FOSTester() {
	}
	bool operator()(unsigned int N, unsigned int P, SolverType s_type);

private:
	bool KKTApproximate(
			const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>& X,
			const Eigen::Matrix<T, Eigen::Dynamic, 1>& Y,
			const Eigen::Matrix<T, Eigen::Dynamic, 1>& Beta_Lambda,
			const T Lambda, const T b, const T C_comp, const T gamma);

	FOS<T> fos;

	const T C_comp = 0.75;
	const T gamma = 1.0;
	const T b = 2.0;
};

template<typename T>
bool FOSTester<T>::KKTApproximate(
		const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>& X,
		const Eigen::Matrix<T, Eigen::Dynamic, 1>& Y,
		const Eigen::Matrix<T, Eigen::Dynamic, 1>& Beta_Lambda, const T Lambda,
		const T b, const T C_comp, const T gamma) {

	unsigned int n = X.rows();
	unsigned int p = X.cols();

	T LHS = (1.0 + 2.0 / b * (p * C_comp / (std::sqrt(gamma) * n * n)))
			* Lambda;
	Eigen::Matrix<T, Eigen::Dynamic, 1> RHS_fragment = 2.0 / b * X.transpose()
			* (Y - X * Beta_Lambda);
	T RHS = RHS_fragment.template lpNorm<Eigen::Infinity>();

	return (LHS <= RHS);

}

template<typename T>
bool FOSTester<T>::operator()(unsigned int N, unsigned int P,
		SolverType s_type) {

	unsigned int num_active_vars = static_cast<unsigned int>(std::ceil(
			static_cast<T>(P) / 10.0));

	SyntheticDataGenerator<T> data_generator(N, P, num_active_vars, 0.3, 5.0);

	Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> X = data_generator.X();
	Eigen::Matrix<T, Eigen::Dynamic, 1> Y = data_generator.Y();

	fos(X, Y, s_type);

	Eigen::Matrix<T, Eigen::Dynamic, 1> Beta_Lambda = fos.ReturnCoefficients();
	Eigen::Matrix<int, Eigen::Dynamic, 1> support = fos.ReturnSupport();

	// Filter out significant coefficients
	for (unsigned int i = 0; i < support.size(); i++) {
		if (support[i] == 0) {
			Beta_Lambda[i] = 0.0;
		}
	}
	T Lambda = fos.ReturnLambda();

	return (KKTApproximate(X, Y, Beta_Lambda, Lambda, b, C_comp, gamma));

}

template<typename T>
bool TestFOS(SolverType s_type) {

	DEBUG_PRINT( "Using DEBUG configuration" );

	FOSTester<T> tester;

	unsigned int N = rand() % 500 + 2;
	unsigned int P = rand() % 500 + 2;

	DEBUG_PRINT( "Test matrix size: " << N << " x " << P );

	return tester(N, P, s_type);
}

TEST(FOS, ISTA) {
	EXPECT_TRUE(TestFOS<double>(foxfire::SolverType::ista));
	EXPECT_TRUE(TestFOS<double>(foxfire::SolverType::screen_ista));
//	EXPECT_TRUE(TestFOS<float>(foxfire::SolverType::ista));
//	EXPECT_TRUE(TestFOS<float>(foxfire::SolverType::screen_ista));
}

TEST(FOS, FISTA) {
	EXPECT_TRUE(TestFOS<double>(foxfire::SolverType::fista));
	EXPECT_TRUE(TestFOS<double>(foxfire::SolverType::screen_fista));
//	EXPECT_TRUE(TestFOS<float>(foxfire::SolverType::fista));
//	EXPECT_TRUE(TestFOS<float>(foxfire::SolverType::screen_fista));
}

TEST(FOS, CoordinateDescent) {
	EXPECT_TRUE(TestFOS<double>(foxfire::SolverType::cd));
	EXPECT_TRUE(TestFOS<double>(foxfire::SolverType::screen_cd));
//	EXPECT_TRUE(TestFOS<float>(foxfire::SolverType::cd));
//	EXPECT_TRUE(TestFOS<float>(foxfire::SolverType::screen_cd));
}

#ifdef W_OPENCL
TEST(FOS, OpenCL) {
	EXPECT_TRUE(TestFOS<double>(foxfire::SolverType::cl_ista));
	EXPECT_TRUE(TestFOS<double>(foxfire::SolverType::cl_fista));
	EXPECT_TRUE(TestFOS<float>(foxfire::SolverType::cl_ista));
	EXPECT_TRUE(TestFOS<float>(foxfire::SolverType::cl_fista));
}
#endif

}

}

#endif // TEST_FOS_HPP
