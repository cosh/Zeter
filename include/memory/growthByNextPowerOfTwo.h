/*
 * growthByNextPowerOfTwo.h
 *
 *  Created on: 17.05.2013
 *      Author: cosh
 *     Purpose: A growth implementation that returns the next power of two
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

#ifndef _growthByNextPowerOfTwo_h
#define _growthByNextPowerOfTwo_h

class GrowthByNextPowerOfTwo {

private:
	/**
	 * Determines of this is a power of two
	 * @param n The interesting number
	 * @return True or false
	 */
	bool IsPowerOf2(long long n);

public:

	/**
	 * Gets the next size to a given size
	 * @param size The given size
	 */
	long long GetNextSize(long long size);

	/**
	 * Gets the size of a given slot
	 * @param slotIntex The index of the slot
	 */
	long long GetSizeOfSlot(int slotIntex);

	/**
	 * Gives the slot for a size
	 * @param n The given size
	 * @return The slot
	 */
	int GetSlotForSize(long long n);
};

#endif
