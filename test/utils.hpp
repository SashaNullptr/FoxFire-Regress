#ifndef TEST_UTILS_HPP_
#define TEST_UTILS_HPP_

// C System-Headers
#include <fcntl.h>    /* For O_RDWR */
#include <unistd.h>   /* For open(), create() */
// C++ System headers
#include <limits>
#include <cmath>
// Eigen Headers
//
// gtest Headers
//
// Project Specific Headers
//

namespace foxfire {

namespace test {

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

class random_uint_generator {

public:
	random_uint_generator(unsigned int max_val) :
			max_uint(max_val) {
	}

	unsigned int get_next() {
		return (unsigned int) (xorshf96() % max_uint);
	}

private:
	unsigned long x = 123456789, y = 362436069, z = 521288629;
	unsigned int max_uint;

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

};

}

}

#endif /* TEST_UTILS_HPP_ */
