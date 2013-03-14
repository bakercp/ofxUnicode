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


#pragma once

#include "ofMain.h"
#include "ofUnicode.h"
#include "ofUTF8.h"
#include "ofUTF16.h"
#include "ofUTF32.h"

#include "unicode/ucsdet.h" // charset detection
#include "unicode/ucnv.h"   // character set conversion

class ofCharsetUtils {
public:
    ofCharsetUtils();
    virtual ~ofCharsetUtils();
    
    static vector<string> listAvailableCharsets();
    static bool detectCharset(const string& buffer, string& name, string& lang, int& confidence);
    static bool convertCharset(string& buffer, const string& originCharset, const string& destCharset); 
    static bool convertCharsetToUTF8(string& buffer, const string& originCharset); 
    
};
