#ifndef TEST_UTILS_HPP_
#define TEST_UTILS_HPP_

// C System-Headers
//
// C++ System headers
#include <limits>
#include <cmath>
// Eigen Headers
//
// gtest Headers
//
// Project Specific Headers
//

template<typename T>
bool ApproximatelyEqual(const T& a, const T& b) {
	return std::abs(a - b)
			<= ((std::abs(a) < std::abs(b) ? std::abs(b) : std::abs(a))
					* std::numeric_limits<T>::epsilon());
}

template<typename Container>
bool ApproximatelyEqualContainer(const Container& a, const Container& b) {

	for (unsigned int i = 0; i < a.size(); i++) {
		if (!approximatelyEqual(a[i], b[i])) {
			return false;
		}
	}

	return true;
}

static unsigned long x = 123456789, y = 362436069, z = 521288629;

unsigned long xorshf96(void) { //period 2^96-1
	unsigned long t;
	x ^= x << 16;
	x ^= x >> 5;
	x ^= x << 1;

	t = x;
	x = y;
	y = z;
	z = t ^ x ^ y;

	return z;
}

unsigned int urandUint(unsigned int max_val) {
	return (unsigned int)rand() % max_val;
}

#endif /* TEST_UTILS_HPP_ */
