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

bool ThreadSafeElement::ReadResource() {




	return false;

//	//>=0 indicates that the method is not in use.
//	if (state_.)
//	{
//		//Code to access a resource that is not thread safe would go here.
//		return true;
//	}
//
//
//
//	            //another thread writes something, so lets wait
//
//
//				for (var i = 0; i < int.MaxValue; i++)
//	            {
//
//	                //usingResource was incremented in the if clause, so lets decrement it again
//
//	                Interlocked.Decrement(ref _usingResource);
//
//
//
//	                if (i%10000 == 9999)
//	                {
//	                    Thread.Sleep(1);
//	                }
//
//
//
//	                if (Interlocked.Increment(ref _usingResource) > 0)
//
//	                {
//
//	                    return true;
//
//	                }
//
//	            }
//
//
//
//	            return false;
}
