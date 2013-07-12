#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "zeter_tests.h"
#include <atomic>
#include <thread>
#include <chrono>
#include "collections/lock_free_queue.h"

TEST(test_zeter_lock_free_queue_basic) {

	return 0;
}

int main() {
	int err = 0;

	test_zeter_lock_free_queue_basic();

	return err ? -1 : 0;
}
