#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "zeter_tests.h"
#include <atomic>
#include <thread>
#include <chrono>
#include "synchronization/threadSafeElement.h"
#include "synchronization/lockableElement.h"

bool go = false;

void LockSth(int count, LockableElement* elemenet) {

	while(!go)
	{
		// do nothing
	}

	for (int i = 0; i < count; ++i) {

		if (elemenet->tryLock()) {
			elemenet->unLock();
		} else {
			assert(false);
		}
	}
}

TEST(test_zeter_lockableElement) {

	int lockCount = 300000;

	LockableElement *element = new LockableElement();

	std::thread a(LockSth, lockCount, element);
	std::thread b(LockSth, lockCount, element);
	std::thread c(LockSth, lockCount, element);
	std::thread d(LockSth, lockCount, element);
	std::thread e(LockSth, lockCount, element);
	std::thread f(LockSth, lockCount, element);

	go = true;

	a.join();
	b.join();
	c.join();
	d.join();
	e.join();
	f.join();

	return 0;
}

int main() {
	int err = 0;

	test_zeter_lockableElement();

	return err ? -1 : 0;
}
