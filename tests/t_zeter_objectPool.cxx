#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "zeter_tests.h"
#include "threadSafeElement.h"
#include <boost/pool/object_pool.hpp>

TEST(test_zeter_objectPool_basic) {

	boost::object_pool<ThreadSafeElement> p;

	for (int i = 0; i < 10000; ++i) {
		ThreadSafeElement * const t = p.malloc();
	}

	return 0;
}

int main() {
	int err = 0;

	test_zeter_objectPool_basic();

	return err ? -1 : 0;
}
