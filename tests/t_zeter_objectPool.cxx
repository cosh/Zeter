#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "zeter_tests.h"
#include "threadSafeElement.h"
#include <boost/pool/object_pool.hpp>
#include "memory/growthByNextPowerOfTwo.h"
#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <array>

TEST(test_zeter_objectPool_basic) {

	boost::object_pool<ThreadSafeElement> p;

	for (int i = 0; i < 10000; ++i) {
		ThreadSafeElement * const t = p.malloc();
	}

	return 0;
}

TEST(test_zeter_objectPool_growth) {

	GrowthByNextPowerOfTwo growth;

	int newValue = growth.GetNextSize(0);

	assert(newValue == 1);

	newValue = growth.GetNextSize(1);
	assert(newValue == 2);

	newValue = growth.GetNextSize(2);
	assert(newValue == 4);

	newValue = growth.GetNextSize(3);
	assert(newValue == 4);

	newValue = growth.GetNextSize(4);
	assert(newValue == 8);

	newValue = growth.GetNextSize(126);
	assert(newValue == 128);

	newValue = growth.GetNextSize(8388607);
	assert(newValue == 8388608);

	return 0;
}

int main() {
	int err = 0;

	test_zeter_objectPool_basic();
	test_zeter_objectPool_growth();

	return err ? -1 : 0;
}
