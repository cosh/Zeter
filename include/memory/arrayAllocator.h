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

#ifndef _arrayAllocator_h
#define _arrayAllocator_h

#include "boost/pool/pool.hpp"
#include <array>
#include "arrayMetaData.h"

/**
 * TObject is the type of the object that is inside the arrays
 * TArraySizer is the type of the object that is responsible for sizing the arrays
 */
template<class TObject, class TArraySizer, std::size_t slots>
class ArrayAllocator {

private:
	const std::size_t _slots;
	TArraySizer* _sizer;
	std::array<boost::pool<>*, slots>* _poolArray;
	std::array<ArrayMetaData*, slots>* _arrayMetaData;

public:

	explicit ArrayAllocator() :
			_slots(slots)
			{

		_sizer = new TArraySizer();
		_poolArray = new std::array<boost::pool<>*, slots>();
		_arrayMetaData = new std::array<ArrayMetaData*, slots>();

		for (std::size_t i = 0; i < _slots; ++i) {
			size_t templateSize = 0;
			int sizeOfSlot = _sizer->GetSizeOfSlot(i);

			templateSize = sizeof(TObject*) * sizeOfSlot;

			_poolArray->at(i) = new boost::pool<>(templateSize);
			_arrayMetaData->at(i) = new ArrayMetaData(_poolArray->at(i), templateSize);
		}

	}

	~ArrayAllocator() {
		for (std::size_t i = 0; i < _slots; ++i) {
			delete(_poolArray->at(i));
		}

		delete(_poolArray);
		delete(_sizer);
	}

	TObject * const GetArray(const int size)
	{
		return static_cast<TObject *>(_poolArray->at(_sizer->GetSlotForSize(_sizer->GetNextSize(size)))->malloc());
	}
};

#endif
