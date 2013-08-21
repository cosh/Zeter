/*
 * arrayAllocator.h
 *
 *  Created on: 17.05.2013
 *      Author: cosh
 *     Purpose: An array allocator that uses pools
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
#include "boost/pool/object_pool.hpp"
#include <array>
#include "arrayMetaData.h"
#include "arrayObject.h"

/**
 * TObject is the type of the object that is inside the arrays
 * TArraySizer is the type of the object that is responsible for sizing the arrays
 */
template<class TObject, class TArraySizer, std::size_t slots>
class ArrayAllocator {

private:
	/**
	 * The number of object pools
	 */
	const std::size_t _slots;

	/**
	 * The object that is responsible for sizing the pools
	 */
	TArraySizer* _sizer;

	/**
	 * The array of pools
	 */
	std::array<boost::pool<>*, slots>* _poolArray;

	/**
	 * The array of meta data
	 */
	std::array<ArrayMetaData*, slots>* _arrayMetaData;

	/**
	 * The pool of array objects
	 */
	boost::object_pool<ArrayObject<TObject>>* _arrayObjectPool;

public:

	/**
	 * Constructor
	 */
	explicit ArrayAllocator() :
			_slots(slots) {

		_sizer = new TArraySizer();
		_poolArray = new std::array<boost::pool<>*, slots>();
		_arrayMetaData = new std::array<ArrayMetaData*, slots>();

		const size_t next_size_base = 1000000;
		const size_t next_size_default = 32;

		const size_t max_size = 0;

		for (std::size_t i = 0; i < _slots; ++i) {
			size_t templateSize = 0;
			int sizeOfSlot = _sizer->GetSizeOfSlot(i);

			templateSize = sizeof(TObject*) * sizeOfSlot;

			//The value of this parameter is passed to the underlying Pool when it is created and
			//specifies the number of chunks to allocate in the first allocation request (defaults to 32).
			size_t next_size = next_size_base / sizeOfSlot;
			if (next_size < next_size_default) {
				next_size = next_size_default;
			}

			_poolArray->at(i) = new boost::pool<>(templateSize, next_size,
					max_size);
			_arrayMetaData->at(i) = new ArrayMetaData(_poolArray->at(i),
					sizeOfSlot);
		}

		_arrayObjectPool = new boost::object_pool<ArrayObject<TObject>>();
		_arrayObjectPool->set_next_size(next_size_base);

	}

	/**
	 * Destructor
	 */
	~ArrayAllocator() {
		for (std::size_t i = 0; i < _slots; ++i) {
			delete (_poolArray->at(i));
		}

		delete (_poolArray);
		delete (_sizer);
		delete (_arrayMetaData);
		delete (_arrayObjectPool);
	}

	/**
	 * Gets an array for a given size (or bigger, depending on the sizer)
	 * @param size The minimum size
	 * @return An array object that contains the desired array and the corresponding meta data
	 */
	ArrayObject<TObject> * const GetArray(const int size) {
		int index = _sizer->GetSlotForSize(_sizer->GetNextSize(size));
		TObject * const firstElement = static_cast<TObject *>(_poolArray->at(
				index)->ordered_malloc());
		ArrayMetaData * const metaData = _arrayMetaData->at(index);

		return _arrayObjectPool->construct(firstElement, metaData);
	}

	/**
	 * Frees the memory of the array
	 * @param toBeFreed The array object that should be freed
	 */
	void Free(ArrayObject<TObject> * const toBeFreed) {
		toBeFreed->GetArrayMetaData()->GetCorrespondingPool()->ordered_free(
				toBeFreed->GetFirstElement());
		_arrayObjectPool->destroy(toBeFreed);
	}
};

#endif
