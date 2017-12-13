#ifndef TEST_SYNTHENTIC_DATA_GEN_HPP_
#define TEST_SYNTHENTIC_DATA_GEN_HPP_

// C System-Headers
#include <fcntl.h>    /* For O_RDWR */
#include <unistd.h>   /* For open(), create() */
// C++ System headers
#include <vector>
#include <unordered_set>
// Eigen Headers
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Core>

namespace foxfire {

namespace test {

template<typename T>
using Vect = Eigen::Matrix<T, Eigen::Dynamic, 1>;

template<typename T>
using Mat = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>;

template<typename T>
class normal_random_variable {

public:
	normal_random_variable(Mat<T> const& covar) :
			normal_random_variable(Vect<T>::Zero(covar.rows()), covar) {

//		gen = std::mt19937 { std::random_device { }() };

	}

	normal_random_variable(Vect<T> const& mean, Mat<T> const& covar) :
			mean(mean) {
		Eigen::SelfAdjointEigenSolver<Mat<T>> eigenSolver(covar);
		transform = eigenSolver.eigenvectors()
				* eigenSolver.eigenvalues().cwiseSqrt().asDiagonal();

//		gen = std::mt19937 { std::random_device { }() };
	}

	Mat<T> operator()(unsigned int num_obs) const {
		std::mt19937 gen { std::random_device { }() };
		std::normal_distribution<T> dist;

//		return mean
//				+ transform
//						* Mat<T> { mean.rows(), num_obs }.unaryExpr(
//								[&](auto x) {return dist(gen);});

		return (transform
				* Mat<T> { mean.rows(), num_obs }.unaryExpr(
						[&](T x) {return dist(gen);})).transpose();
	}

private:
	Vect<T> mean;
	Mat<T> transform;

//	std::mt19937 gen;
//	std::normal_distribution<T> dist;
};

template<typename T>
Vect<T> binomial_vect(unsigned int n) {
	std::mt19937 gen { std::random_device { }() };
	std::binomial_distribution<T> dist(1, 0.5);

	return Vect<T> { n }.unaryExpr([&](T x) {return dist(gen);});
}

template<typename T>
Vect<T> randn_vect(unsigned int n) {
	std::mt19937 gen { std::random_device { }() };
	std::normal_distribution<T> dist;

	return Vect<T> { n }.unaryExpr([&](T x) {return dist(gen);});
}

template<typename T>
class SyntheticDataGenerator {
public:
	SyntheticDataGenerator(const unsigned int num_observations,
			const unsigned int num_vars, const unsigned int num_active,
			const T correlation, const T SNR);

	Mat<T> X();
	Vect<T> Y();
	Vect<T> Beta();

private:

	unsigned int GenerateRandSeed();

	void BuildSyntheticData(const unsigned int num_observations,
			const unsigned int num_vars, const unsigned int num_active,
			const T correlation, const T SNR);

	std::vector<int> choice_vect(unsigned int max_range,
			unsigned int subset_size);

	Vect<T> BuildBeta(const Mat<T>& X, const unsigned int num_observations,
			const unsigned int num_vars, const unsigned int num_active,
			const T correlation, const T SNR);

	Mat<T> __X;
	Vect<T> __Y;
	Vect<T> __Beta;
};

template<typename T>
Mat<T> SyntheticDataGenerator<T>::X() {
	return __X;
}

template<typename T>
Vect<T> SyntheticDataGenerator<T>::Y() {
	return __Y;
}

template<typename T>
Vect<T> SyntheticDataGenerator<T>::Beta() {
	return __Beta;
}

template<typename T>
SyntheticDataGenerator<T>::SyntheticDataGenerator(
		const unsigned int num_observations, const unsigned int num_vars,
		const unsigned int num_active, const T correlation, const T SNR) {
	srand(GenerateRandSeed());
//	BuildSyntheticData(num_observations, num_vars, num_active, correlation,
//			SNR);
	Mat<T> sigma_X = (1.0 - correlation) * Mat<T>::Identity(num_vars, num_vars)
			+ correlation * Mat<T>::Ones(num_vars, num_vars);

	Vect<T> mu_X = Vect<T>::Zero(num_vars);
	normal_random_variable<T> X_fragment(sigma_X);

	__X = X_fragment(num_observations);
	__X = std::sqrt(static_cast<T>(num_observations)) / __X.norm() * __X;

	__Beta = BuildBeta(__X, num_observations, num_vars, num_active, correlation,
			SNR);
	Vect<T> noise = randn_vect<T>(num_observations);

	__Y = __X * __Beta + noise;
}

template<typename T>
unsigned int SyntheticDataGenerator<T>::GenerateRandSeed() {
	int urandom = open("/dev/urandom", O_RDONLY);
	char data_buffer[1024];

	ssize_t result = read(urandom, data_buffer, sizeof(data_buffer));

	if (result < 0) {
		std::string err_mesg = __func__;
		err_mesg += "Unable to read from /dev/urandom.";
		throw std::runtime_error(err_mesg);
	}

	//close needs to be preceeded with double colons to avoid namespace conflict with Qt::close().
	::close(urandom);

	int seed = 0;

	for (const auto& token : data_buffer) {
		seed += static_cast<int>(token);
	}

	return abs(seed);
}

template<typename T>
std::vector<int> SyntheticDataGenerator<T>::choice_vect(unsigned int max_range,
		unsigned int subset_size) {
	std::vector<int> random_subset(max_range);
	std::iota(random_subset.begin(), random_subset.end(), 0);

	static std::mt19937 gen { std::random_device { }() };

	std::shuffle(std::begin(random_subset), std::end(random_subset), gen);
	return std::vector<int>(&random_subset[0], &random_subset[subset_size]);
}

template<typename T>
Vect<T> SyntheticDataGenerator<T>::BuildBeta(const Mat<T>& X,
		const unsigned int num_observations, const unsigned int num_vars,
		const unsigned int num_active, const T correlation, const T SNR) {

	Vect<T> Beta = Vect<T>::Zero(num_vars);

	std::vector<int> random_subset = choice_vect(num_vars, num_active);

	for (const auto& elem : random_subset) {
		Beta[elem] = (std::rand() % 2) ? (1.0) : (-1.0);
	}

	Beta = std::sqrt(
			SNR * static_cast<T>(num_observations) / (X * Beta).squaredNorm())
			* Beta;

	return Beta;
}

template<typename T>
void SyntheticDataGenerator<T>::BuildSyntheticData(
		const unsigned int num_observations, const unsigned int num_vars,
		const unsigned int num_active, const T correlation, const T SNR) {

	Mat<T> sigma_X = (1.0 - correlation) * Mat<T>::Identity(num_vars, num_vars)
			+ correlation * Mat<T>::Ones(num_vars, num_vars);

	Vect<T> mu_X = Vect<T>::Zero(num_vars);
	normal_random_variable<T> X_fragment(sigma_X);

	__X = X_fragment(num_observations);
	__X = std::sqrt(static_cast<T>(num_observations)) / __X.norm() * __X;

	__Beta = BuildBeta(__X, num_observations, num_vars, num_active, correlation,
			SNR);
	Vect<T> noise = randn_vect<T>(num_observations);

	__Y = __X * __Beta + noise;

}

}

}
#endif /* TEST_SYNTHENTIC_DATA_GEN_HPP_ */
