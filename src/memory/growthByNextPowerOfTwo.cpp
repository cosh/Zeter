/*
 * growthByNextPowerOfTwo.cpp
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

#include "memory/growthByNextPowerOfTwo.h"
#include <math.h>

long long GrowthByNextPowerOfTwo::GetNextSize(long long size) {
	if(!IsPowerOf2(size))
	{
		--size;
	}

	size |= size >> 1;
	size |= size >> 2;
	size |= size >> 4;
	size |= size >> 8;
	size |= size >> 16;
	size |= size >> 16;
	size |= size >> 16;

	return size + 1;
}

bool GrowthByNextPowerOfTwo::IsPowerOf2(long long n)
{
	 return (n & (n - 1))==0;
}

long long GrowthByNextPowerOfTwo::GetSizeOfSlot(int slotIndex) {
	return pow (2, slotIndex);
}

int GrowthByNextPowerOfTwo::GetSlotForSize(long long n)
{
  if (n & 0x7FFFFFFF00000000) {
    if (n & 0x7FFF000000000000) {
      if (n & 0x7F00000000000000) {
        if (n & 0x7000000000000000) {
          if (n & 0x4000000000000000)
            return 63;
          else
            return (n & 0x2000000000000000) ? 62 : 61;
        } else {
          if (n & 0x0C00000000000000)
            return (n & 0x0800000000000000) ? 60 : 59;
          else
            return (n & 0x0200000000000000) ? 58 : 57;
        }
      } else {
        if (n & 0x00F0000000000000) {
          if (n & 0x00C0000000000000)
            return (n & 0x0080000000000000) ? 56 : 55;
          else
            return (n & 0x0020000000000000) ? 54 : 53;
        } else {
          if (n & 0x000C000000000000)
            return (n & 0x0008000000000000) ? 52 : 51;
          else
            return (n & 0x0002000000000000) ? 50 : 49;
        }
      }
    } else {
      if (n & 0x0000FF0000000000) {
        if (n & 0x0000F00000000000) {
          if (n & 0x0000C00000000000)
            return (n & 0x0000800000000000) ? 48 : 47;
          else
            return (n & 0x0000200000000000) ? 46 : 45;
        } else {
          if (n & 0x00000C0000000000)
            return (n & 0x0000080000000000) ? 44 : 43;
          else
            return (n & 0x0000020000000000) ? 42 : 41;
        }
      } else {
        if (n & 0x000000F000000000) {
          if (n & 0x000000C000000000)
            return (n & 0x0000008000000000) ? 40 : 39;
          else
            return (n & 0x0000002000000000) ? 38 : 37;
        } else {
          if (n & 0x0000000C00000000)
            return (n & 0x0000000800000000) ? 36 : 35;
          else
            return (n & 0x0000000200000000) ? 34 : 33;
        }
      }
    }
  } else {
    if (n & 0x00000000FFFF0000) {
      if (n & 0x00000000FF000000) {
        if (n & 0x00000000F0000000) {
          if (n & 0x00000000C0000000)
            return (n & 0x0000000080000000) ? 32 : 31;
          else
            return (n & 0x0000000020000000) ? 30 : 29;
        } else {
          if (n & 0x000000000C000000)
            return (n & 0x0000000008000000) ? 28 : 27;
          else
            return (n & 0x0000000002000000) ? 26 : 25;
        }
      } else {
        if (n & 0x0000000000F00000) {
          if (n & 0x0000000000C00000)
            return (n & 0x0000000000800000) ? 24 : 23;
          else
            return (n & 0x0000000000200000) ? 22 : 21;
        } else {
          if (n & 0x00000000000C0000)
            return (n & 0x0000000000080000) ? 20 : 19;
          else
            return (n & 0x0000000000020000) ? 18 : 17;
        }
      }
    } else {
      if (n & 0x000000000000FF00) {
        if (n & 0x000000000000F000) {
          if (n & 0x000000000000C000)
            return (n & 0x0000000000008000) ? 16 : 15;
          else
            return (n & 0x0000000000002000) ? 14 : 13;
        } else {
          if (n & 0x0000000000000C00)
            return (n & 0x0000000000000800) ? 12 : 11;
          else
            return (n & 0x0000000000000200) ? 10 : 9;
        }
      } else {
        if (n & 0x00000000000000F0) {
          if (n & 0x00000000000000C0)
            return (n & 0x0000000000000080) ? 8 : 7;
          else
            return (n & 0x0000000000000020) ? 6 : 5;
        } else {
          if (n & 0x000000000000000C)
            return (n & 0x0000000000000008) ? 4 : 3;
          else
            return (n & 0x0000000000000002) ? 2 : (n ? 1 : 0);
        }
      }
    }
  }
}
