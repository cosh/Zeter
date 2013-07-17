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
#include "synchronization/lockableElement.h"
#include "boost/lockfree/queue.hpp"

using boost::lockfree::queue;

TEST(test_zeter_lock_free_queue_basic) {
	//sth for later...

	//lock_free_queue<LockableElement*>* queueLe = new lock_free_queue<LockableElement*>();
	//LockableElement* le = new LockableElement();

	//queueLe->push(le);
	//std::unique_ptr<LockableElement> lePointer = queueLe->pop();

	//delete(queueLe);

	/*
	 lock_free_queue<int>* queueInt = new lock_free_queue<int>();
	 int value = 4;

	 queueInt->push(value);

	 std::unique_ptr<int> valueRef = queueInt->pop();

	 //assert(value == valueRef);

	 delete(queueInt);
	 */
	return 0;
}

TEST(test_zeter_boost_queue_basic) {

	LockableElement * le = new LockableElement();
	boost::lockfree::queue<LockableElement*>* q = new boost::lockfree::queue<
			LockableElement*>(1000000);

	for (int i = 0; i < 1000000; i++) {
		q->push(le);
	}

	for (int i = 0; i < 1000000; i++) {
		q->pop(le);
	}

	return 0;
}

int main() {
	int err = 0;

	test_zeter_lock_free_queue_basic();
	test_zeter_boost_queue_basic();

	return err ? -1 : 0;
}
