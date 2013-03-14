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


#include "ofCharsetUtils.h"

//------------------------------------------------------------------
vector<string> ofCharsetUtils::listAvailableCharsets() {
    vector<string> charsets;
//    UErrorCode status = U_ZERO_ERROR;
    for(int i = 0; i < ucnv_countAvailable(); i++) {
        charsets.push_back(ucnv_getAvailableName(i));
    }
    return charsets;
}

//------------------------------------------------------------------
bool ofCharsetUtils::detectCharset(const string& buffer, string& name, string& lang, int& confidence) {
    UCharsetDetector* csd;
    UErrorCode status = U_ZERO_ERROR;
    csd = ucsdet_open(&status);
    ucsdet_setText(csd, buffer.c_str(), buffer.length(), &status);
    const UCharsetMatch* csm;
    csm = ucsdet_detect(csd, &status);
    name = ucsdet_getName(csm, &status);
    lang = ucsdet_getLanguage(csm, &status);
    confidence = ucsdet_getConfidence(csm, &status);
    ucsdet_close(csd);
    return U_SUCCESS(status);
}

//------------------------------------------------------------------
bool ofCharsetUtils::convertCharset(string& buffer, const string& originCharset, const string& destCharset) {
    UErrorCode status = U_ZERO_ERROR;
    
    int destCap = buffer.length() * 2;
    char dest[destCap];
    int len = ucnv_convert(destCharset.c_str(), 
                           originCharset.c_str(), 
                           dest, 
                           destCap, 
                           buffer.c_str(), 
                           buffer.length(),
                           &status);
    
    buffer.clear();
    buffer.append(dest,len); // put it back in the string
    
    return U_SUCCESS(status);
}

//------------------------------------------------------------------
bool ofCharsetUtils::convertCharsetToUTF8(string& buffer, const string& originCharset) {
    return convertCharset(buffer,originCharset,"UTF-8");
}

