/*==============================================================================
 
 Copyright (c) 2010, 2011, 2012 Christopher Baker <http://christopherbaker.net>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

 ==============================================================================*/

#include "ofUTF32.h"

//------------------------------------------------------------------
ofUTF8String ofUTF32::toUTF8(const ofUniChar& input) {
    ofUTF8String utf8result;
    return ofUTF8::append(utf8result, input);
}

//------------------------------------------------------------------
ofUTF8String ofUTF32::toUTF8(const ofUniString& input) {
    ofUTF8String utf8result;
    return ofUTF8::append(utf8result, input);
}

//------------------------------------------------------------------
ofUTF16String ofUTF32::toUTF16(const ofUniString& input) {
    return UnicodeString::fromUTF32(input.c_str(),input.length());
}
