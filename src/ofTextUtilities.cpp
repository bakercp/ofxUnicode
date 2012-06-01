//
//  ofTextUtilities.cpp
//  ofxUnicodeExample
//
//  Created by Christopher Baker on 6/1/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#include "ofTextUtilities.h"

//------------------------------------------------------------------
vector<string> ofTextUtilities::listAvailableCharsets() {
    vector<string> charsets;
    UErrorCode status = U_ZERO_ERROR;
    for(int i = 0; i < ucnv_countAvailable(); i++) {
        charsets.push_back(ucnv_getAvailableName(i));
    }
    return charsets;
}

//------------------------------------------------------------------
bool ofTextUtilities::detectCharset(const string& buffer, string& name, string& lang, int& confidence) {
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
bool ofTextUtilities::convertCharset(string& buffer, const string& originCharset, const string& destCharset) {
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
bool ofTextUtilities::convertCharsetToUTF8(string& buffer, const string& originCharset) {
    return convertCharset(buffer,originCharset,"UTF-8");
}

