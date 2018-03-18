#ifndef L0_REGULARIZED_L0_EM_L0_EM_HPP_
#define L0_REGULARIZED_L0_EM_L0_EM_HPP_

// C System-Headers
//
// C++ System headers
//
// Eigen Headers
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Core>

namespace foxfire {

template<typename T>
Eigen::Matrix<T, Eigen::Dynamic, 1> L0_EM(
		const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>& X,
		const Eigen::Matrix<T, Eigen::Dynamic, 1>& Y,
		const T Lambda,
		const T epsilon_0,
		const T epsilon_1 ) {

	unsigned int n = X.rows();
	Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> X_t = X.transpose();
	Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> eye = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>::Identity(n, n);

	Eigen::Matrix<T, Eigen::Dynamic, 1> theta = ( X_t * X + Lambda * eye).inverse() * X_t * Y;
	Eigen::Matrix< T, Eigen::Dynamic, T > eta = theta

	while ( ( theta - eta ).norm() >= epsilon_1 ) {

		eta = theta;
		Eigen::Matrix< T, 1, Eigen::Dynamic > X_eta_t = ( eta * eta ).cwiseProduct( X_t );
		theta = ( X_eta_t.transpose() * X + Lambda * eye).inverse() * X_eta_t.transpose() * Y;
	}

	for( auto& elem : theta ) {
		if( std::abs( elem ) < epsilon_0 ) {
			elem = 0.0;
		}
	}

	return theta;

}

}

#endif /* L0_REGULARIZED_L0_EM_L0_EM_HPP_ */
