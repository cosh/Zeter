/*
 * arrayAllocator.h
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

#ifndef _arrayAllocatort_h
#define _arrayAllocator_h

#include "boost/pool/object_pool.hpp"

/**
 * TObject is the type of the object that is inside the arrays
 * TArraySizer is the type of the object that is responsible for sizing the arrays
 */
template <class TObject, class TArraySizer>
class ArrayAllocator {

private:

	const boost::object_pool<TObject>* _poolpool[];

public:

	TObject* const GetArray(const ulong size);
};

#endif
