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

class random_uint_generator {

public:
	random_uint_generator( unsigned int max_val ):max_uint( max_val ) {
		srand( GenerateRandSeed() );
	}

	unsigned int get_next() {
		return (unsigned int)( rand()%max_uint );
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

unsigned int GenerateRandSeed() {
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

};

unsigned int urandUint(unsigned int max_val) {
	return (unsigned int) rand() % max_val;
}

}

}

#endif /* TEST_UTILS_HPP_ */
