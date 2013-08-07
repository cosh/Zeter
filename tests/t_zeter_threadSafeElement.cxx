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

std::atomic<bool> go(false);

TEST(test_zeter_atomc_basic) {

	std::atomic<int> atomicInt(0);

	int oldValue = atomicInt++;
	int newValue = atomicInt.load();

	assert(oldValue == 0);
	assert(newValue == 1);

	atomicInt--;

	assert(++atomicInt > 0);

	return 0;
}

TEST(test_zeter_atomc_basic_compareExchange) {

	std::atomic<int> atomicInt(0);

	int tstVal = 0;
	int newVal = -200000000;

	// tst_val != ai   ==>  tst_val is modified
	bool exchanged = atomicInt.compare_exchange_strong(tstVal, newVal);

	assert(exchanged == true);
	assert(atomicInt.load() == newVal);

	exchanged = atomicInt.compare_exchange_strong(tstVal, newVal);

	assert(exchanged == false);
	assert(atomicInt.load() == newVal);

	return 0;
}

void Read(int count, ThreadSafeElement* elemenet) {

	while(!go)
		{
			// do nothing
		}

	for (int i = 0; i < count; ++i) {
		if (elemenet->ReadResource()) {
			elemenet->FinishReadResource();
		} else {
			assert(false);
		}
	}
}

void Write(int count, ThreadSafeElement* elemenet) {

	while(!go)
		{
			// do nothing
		}

	for (int i = 0; i < count; ++i) {

		if (elemenet->WriteResource()) {
			elemenet->FinishWriteResource();
		} else {
			assert(false);
		}
	}
}

/*TEST(test_zeter_threadSafeElement_mixed) {

	int readCount = 3000000;
	int writeCount = 10;

	ThreadSafeElement *element = new ThreadSafeElement();

	std::thread a(Read, readCount, element);
	std::thread b(Read, readCount, element);
	std::thread c(Read, readCount, element);
	std::thread d(Write, writeCount, element);
	std::thread e(Write, writeCount, element);
	a.join();
	b.join();
	c.join();
	d.join();
	e.join();

	return 0;
}*/

TEST(test_zeter_threadSafeElement_read) {

	int readCount = 300000;

	ThreadSafeElement *element = new ThreadSafeElement();

	go = false;

	std::thread a(Read, readCount, element);
	std::thread b(Read, readCount, element);
	std::thread c(Read, readCount, element);

	go = true;

	a.join();
	b.join();
	c.join();

	assert(element->GetStatus() == 0);

	return 0;
}

TEST(test_zeter_threadSafeElement_write) {

	int writeCount = 300000;

	ThreadSafeElement *element = new ThreadSafeElement();

	go = false;

	std::thread d(Write, writeCount, element);
	std::thread e(Write, writeCount, element);
	std::thread f(Write, writeCount, element);
	std::thread g(Write, writeCount, element);

	go = true;

	d.join();
	e.join();
	f.join();
	g.join();

	assert(element->GetStatus() == 0);

	return 0;
}

int main() {
	int err = 0;

	test_zeter_atomc_basic();
	test_zeter_atomc_basic_compareExchange();
	//test_zeter_threadSafeElement_mixed();
	test_zeter_threadSafeElement_read();
	test_zeter_threadSafeElement_write();

	return err ? -1 : 0;
}
