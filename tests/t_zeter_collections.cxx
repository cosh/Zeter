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
#include <boost/thread.hpp>

boost::atomic_int producer_count(0);
boost::atomic_int consumer_count(0);

boost::lockfree::queue<LockableElement*> queue(10000);

const int iterations = 100000;
const int producer_thread_count = 4;
const int consumer_thread_count = 4;

void producer(void)
{
    for (int i = 0; i != iterations; ++i) {

    	LockableElement * le = new LockableElement();
    	++producer_count;

        while (!queue.push(le));
    }
}

boost::atomic<bool> done (false);
void consumer(void)
{
    LockableElement * value;
    while (!done) {
        while (queue.pop(value))
            ++consumer_count;
    }

    while (queue.pop(value))
        ++consumer_count;
}


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

	using namespace std;
	    cout << "boost::lockfree::queue is ";
	    if (!queue.is_lock_free())
	        cout << "not ";
	    cout << "lockfree" << endl;

	    boost::thread_group producer_threads, consumer_threads;

	    for (int i = 0; i != producer_thread_count; ++i)
	        producer_threads.create_thread(producer);

	    for (int i = 0; i != consumer_thread_count; ++i)
	        consumer_threads.create_thread(consumer);

	    producer_threads.join_all();
	    done = true;

	    consumer_threads.join_all();

	    cout << "produced " << producer_count << " objects.";
	    cout << "consumed " << consumer_count << " objects.";

	return 0;
}

int main() {
	int err = 0;

	test_zeter_lock_free_queue_basic();
	test_zeter_boost_queue_basic();

	return err ? -1 : 0;
}
