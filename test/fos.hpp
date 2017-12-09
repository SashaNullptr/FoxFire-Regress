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

namespace foxfire {

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
	Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> X = Eigen::Matrix<T,
			Eigen::Dynamic, Eigen::Dynamic>::Random(N, P);
	Eigen::Matrix<T, Eigen::Dynamic, 1> Y =
			Eigen::Matrix<T, Eigen::Dynamic, 1>::Random(N, 1);

	fos(X, Y, s_type);

	Eigen::Matrix<T, Eigen::Dynamic, 1> Beta_Lambda = fos.ReturnCoefficients();
	T Lambda = fos.ReturnLambda();

	return (KKTApproximate(X, Y, Beta_Lambda, Lambda, b, C_comp, gamma));

}

template<typename T>
bool TestFOS(unsigned int N, unsigned int P, SolverType s_type) {

	FOSTester<T> tester;
	return tester( N, P, s_type );
}

TEST(FOS, PlainSolvers) {
    ASSERT_TRUE( TestFOS<double>( 20, 50, foxfire::SolverType::ista ) );
    ASSERT_TRUE( TestFOS<double>( 20, 50, foxfire::SolverType::fista ) );
    ASSERT_TRUE( TestFOS<double>( 20, 50, foxfire::SolverType::cd ) );
}

TEST(FOS, ScreeningSolvers) {
    ASSERT_TRUE( TestFOS<double>( 20, 50, foxfire::SolverType::screen_ista ) );
    ASSERT_TRUE( TestFOS<double>( 20, 50, foxfire::SolverType::screen_fista ) );
    ASSERT_TRUE( TestFOS<double>( 20, 50, foxfire::SolverType::screen_cd ) );
}

TEST(FOS, DoublePrecision) {
    ASSERT_TRUE( TestFOS<double>( 20, 50, foxfire::SolverType::fista ) );
}

TEST(FOS, SinglePrecision) {
    ASSERT_TRUE( TestFOS<float>( 20, 50, foxfire::SolverType::fista ) );
}

}

#endif // TEST_FOS_HPP
