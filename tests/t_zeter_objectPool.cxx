#include <assert.h>
#include "zeter_tests.h"
#include <boost/pool/object_pool.hpp>
#include "memory/growthByNextPowerOfTwo.h"
#include "memory/arrayAllocator.h"
#include "synchronization/lockableElement.h"

TEST(test_zeter_arrayAllocator_basic) {

	const std::size_t size = 10;
	ArrayAllocator<LockableElement, GrowthByNextPowerOfTwo, size>* allocator =
			new ArrayAllocator<LockableElement, GrowthByNextPowerOfTwo, size>();

	ArrayObject<LockableElement>* const firstElementOfArray_0 = allocator->GetArray(0);
	firstElementOfArray_0->GetFirstElement()->tryLock();
	firstElementOfArray_0->GetFirstElement()->unLock();

	ArrayObject<LockableElement>* const firstElementOfArray_1 = allocator->GetArray(1);
	firstElementOfArray_1->GetFirstElement()->tryLock();
	firstElementOfArray_1->GetFirstElement()->unLock();

	ArrayObject<LockableElement>* const firstElementOfArray_2 = allocator->GetArray(2);
	firstElementOfArray_2->GetFirstElement()->tryLock();
	firstElementOfArray_2->GetFirstElement()->unLock();

	ArrayObject<LockableElement>* const firstElementOfArray_3 = allocator->GetArray(4);
	firstElementOfArray_3->GetFirstElement()->tryLock();
	firstElementOfArray_3->GetFirstElement()->unLock();

	ArrayObject<LockableElement>* const firstElementOfArray_4 = allocator->GetArray(126);
	firstElementOfArray_4->GetFirstElement()->tryLock();
	firstElementOfArray_4->GetFirstElement()->unLock();

	delete (allocator);

	return 0;
}

TEST(test_zeter_arrayAllocator_mass) {

	const std::size_t size = 10;
	ArrayAllocator<LockableElement, GrowthByNextPowerOfTwo, size>* allocator =
			new ArrayAllocator<LockableElement, GrowthByNextPowerOfTwo, size>();

	const int numberOfIterations = 10000;

	ArrayObject<LockableElement>* array[numberOfIterations];

	for (int i = 0; i < numberOfIterations; ++i) {
		ArrayObject<LockableElement>* const firstElementOfArray_4 = allocator->GetArray(126);
		firstElementOfArray_4->GetFirstElement()->tryLock();
		firstElementOfArray_4->GetFirstElement()->unLock();

		array[i] = firstElementOfArray_4;
	}

	for(int i = 0; i < numberOfIterations; ++i)
	{
		allocator->Free(array[i]);
	}

	return 0;
}

TEST(test_zeter_objectPool_basic) {

	boost::object_pool<LockableElement> p;

	for (int i = 0; i < 10000; ++i) {
		LockableElement * const t = p.malloc();
		t->tryLock();
		t->unLock();
	}

	return 0;
}

TEST(test_zeter_growth_GetNextSize) {

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

TEST(test_zeter_growth_GetSlotForSize) {

	GrowthByNextPowerOfTwo growth;

	int newValue = growth.GetSlotForSize(0);

	assert(newValue == 0);

	newValue = growth.GetSlotForSize(1);
	assert(newValue == 0);

	newValue = growth.GetSlotForSize(2);
	assert(newValue == 1);

	newValue = growth.GetSlotForSize(3);
	assert(newValue == 1);

	newValue = growth.GetSlotForSize(4);
	assert(newValue == 2);

	newValue = growth.GetSlotForSize(4294967296);
	assert(newValue == 32);

	return 0;
}

int main() {
	int err = 0;

	test_zeter_objectPool_basic();
	test_zeter_growth_GetNextSize();
	test_zeter_growth_GetSlotForSize();
	test_zeter_arrayAllocator_basic();
	test_zeter_arrayAllocator_mass();

	return err ? -1 : 0;
}
