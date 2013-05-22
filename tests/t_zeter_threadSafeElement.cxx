#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "zeter_tests.h"
#include <atomic>
#include <thread>
#include <chrono>
#include "threadSafeElement.h"

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
	for (int i = 0; i < count; ++i) {
		if(elemenet->ReadResource())
		{
			elemenet->FinishReadResource();
		}
	}
}

void Write(int count, int timeOut, ThreadSafeElement* elemenet) {
	std::chrono::milliseconds sleepDuration(10);

	for (int i = 0; i < count; ++i) {

		std::this_thread::sleep_for(sleepDuration);

		if(elemenet->WriteResource())
		{
			elemenet->FinishWriteResource();
		}
	}
}

TEST(test_zeter_threadSafeElement) {

	int readCount = 2000000;
	int writeCount = 100000;
	int timeout = 10;

	ThreadSafeElement *element = new ThreadSafeElement();

	std::thread a(Read, readCount, element);
	std::thread b(Read, readCount, element);
	std::thread c(Read, readCount, element);
	//std::thread d(Write, writeCount, timeout, element);
	a.join();
	b.join();
	c.join();
	//d.join();

	return 0;
}

int main() {
	int err = 0;

	test_zeter_atomc_basic();
	test_zeter_atomc_basic_compareExchange();
	test_zeter_threadSafeElement();

	return err ? -1 : 0;
}
