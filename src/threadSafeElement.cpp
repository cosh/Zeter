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
#include <chrono>
#include <thread>

bool ThreadSafeElement::ReadResource() {

	//	//>=0 indicates that the method is not in use.
	if (++_readerCount > 0)
	{
		return true;
	}

	std::chrono::milliseconds sleepDuration(1);

	//another thread writes something, so lets wait
	for (int i = 0; i < INT_MAX; ++i)
	{
		//readerCount was incremented in the if clause, so lets decrement it again
		--_readerCount;

		if (i%10000 == 9999)
		{
			std::this_thread::sleep_for(sleepDuration);
		}

		if (++_readerCount > 0)
		{
			return true;
		}
	}

	return false;
}

void ThreadSafeElement::FinishReadResource() {
	//Release the lock
	--_readerCount;
}

bool ThreadSafeElement::WriteResource() {

	int tstVal = 0;

	if(_readerCount.compare_exchange_strong( tstVal, -10000 ))
	{
		return true;
	}

	std::chrono::milliseconds sleepDuration(1);

	int newVal = -10000;

	for (int i = 0; i < INT_MAX; ++i)
	{

		if (i%10000 == 9999)
		{
			std::this_thread::sleep_for(sleepDuration);
		}

		if (_readerCount.compare_exchange_strong( tstVal, newVal ))
		{
			return true;
		}
	}

	return false;
}

void ThreadSafeElement::FinishWriteResource() {

	_readerCount.store(0);
}
