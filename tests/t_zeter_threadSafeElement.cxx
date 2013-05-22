#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "zeter_tests.h"
#include <atomic>

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
	bool exchanged= atomicInt.compare_exchange_strong( tstVal, newVal );

	assert(exchanged == true);
	assert(atomicInt.load() == newVal);

	exchanged= atomicInt.compare_exchange_strong( tstVal, newVal );

	assert(exchanged == false);
	assert(atomicInt.load() == newVal);

	return 0;
}

int main() {
        int err = 0;

        test_zeter_atomc_basic();
        test_zeter_atomc_basic_compareExchange();

        return err ? -1 : 0;
}

