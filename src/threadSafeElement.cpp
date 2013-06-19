/*
 * threadSafeElement.cpp
 *
 *  Created on: 17.05.2013
 *      Author: cosh
 *     Purpose:
 * 
 * Copyright (c) 2013 Henning Rauch
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of 
 * this software and associated documentation files (the "Software"), to deal in the 
 * Software without restriction, including without limitation the rights to use, copy, 
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, subject to the 
 * following conditions:
 * The above copyright notice and this permission notice shall be included in all 
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 */

#include "threadSafeElement.h"
#include <climits>
#include <thread>

bool ThreadSafeElement::ReadResource() {

	//	//>=0 indicates that the method is not in use.
	if (++_readerCount > 0) {
		return true;
	}

	//another thread writes something, so lets wait
	for (int i = 0; i < INT_MAX; ++i) {
		//readerCount was incremented in the if clause, so lets decrement it again
		--_readerCount;

		if (++_readerCount > 0) {
			return true;
		} else {
			std::this_thread::yield(); // other threads can push work to the queue now
		}
	}

	return false;
}

void ThreadSafeElement::FinishReadResource() {
	//Release the lock
	--_readerCount;
}

bool ThreadSafeElement::WriteResource() {
	int  tst_val= 0;
	int  new_val= -10000;

	if (_readerCount.compare_exchange_strong(tst_val, new_val)) {
		return true;
	}

	for (int i = 0; i < INT_MAX; ++i) {
		if (_readerCount.compare_exchange_strong(tst_val, new_val)) {
			return true;
		} else {
			std::this_thread::yield(); // other threads can push work to the queue now
		}
	}

	return false;
}

void ThreadSafeElement::FinishWriteResource() {
	_readerCount.store(0);
}

int ThreadSafeElement::GetStatus() {
	return _readerCount.load();
}
