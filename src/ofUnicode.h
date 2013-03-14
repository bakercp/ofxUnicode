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

#include "ofConstants.h"
#include "ofLog.h"
#include "ofUtils.h"

#include "unicode/utypes.h"
#include "unicode/unistr.h"
#include "unicode/stringpiece.h"
#include "unicode/utf8.h"
#include "unicode/uchar.h"

#include "Poco/String.h"
#include "Poco/UTF8String.h"
#include "Poco/Ascii.h"
#include "Poco/Unicode.h"
#include "Poco/UTF8Encoding.h"
#include "Poco/TextIterator.h"


// types
typedef char                 ofChar;      // a standard signed char
typedef const char*          ofCharPtr;
typedef unsigned char        ofUTF8Char;    // a UTF8 type (unsigned char)
typedef const unsigned char* ofUTF8Ptr;     // a pointer type used when traversing
                                        // a UTF8 encoded std::string.
                                        // the "beginning" of the string would be
                                        // ofUTF8Ptr b = input.c_str();
                                        // the "end" of the string would be
                                        // ofUTF8Ptr e = input.c_str() + input.length();
                                        // this is wierd.
typedef int                 ofUTF8Idx;

typedef UChar               ofUTF16Char;   // a UTF16 type - stay clear of wstring. it's 4 bytes on *NIX, and 2 on Win
typedef UChar32             ofUTF32Char;   // a UTF32 type
typedef ofUTF32Char         ofUniChar;     // a unicode character type for clarity

typedef const ofUTF16Char * ofUTF16Ptr;   // a pointer to wstring, like above 
typedef const ofUTF32Char * ofUTF32Ptr;  // a pointer to unicode character
typedef const ofUniChar *   ofUniCharPtr;  // a pointer to unicode character

typedef string                    ofUTF8String;  //
typedef UnicodeString             ofUTF16String; // std:wstring is a mess cross platform, let icu take care of it.
typedef basic_string<ofUTF32Char> ofUTF32String; // aka unicode string
typedef ofUTF32String             ofUniString; // this is a "unicode" string
                                        // each vector entry contains one 
                                        // unicode code point.  
                                        // It is NOT UTF8 encoded.

//class ofUnicode {
//public:
//    
//    static bool       isValid(const ofUniChar& unicode);     // is this a valid unicode character?
//    static bool       isPrintable(const ofUniChar& unicode); // is this a "printable" character?
//                                                             // True if the unicode category is not CONTROL
//                                                             // This does not guarantee that the character
//                                                             // has a visible "glyph".
//    
//    static bool       isCntrl(const ofUniChar& unichar);    // is this a "control" unicode character?
//                                                            // this is broadly defined to include unicode
//                                                            // CONTROL category, and other invisible glyphs
//                                                            // this is Not the opposite of isPrintable.
//    static bool       isTitle(const ofUniChar& unichar);    // is this a unicode "Titlecase" codepoint?
//    static bool       isSpace(const ofUniChar& unichar);
//    static bool       isDigit(const ofUniChar& unichar);    
//    static bool       isPunct(const ofUniChar& unichar);
//    static bool 	  isAlpha(const ofUniChar& unichar);
//    static bool 	  isAlphaNumeric(const ofUniChar& unichar); // isAlpha || isDigit
//    static bool       isLower(const ofUniChar& unichar);
//    static bool       isUpper(const ofUniChar& unichar);
//
//    // conversions
//    static ofUniChar  toLower(const ofUniChar& unichar);
//    static ofUniChar  toUpper(const ofUniChar& unichar);
//    static ofUniChar& toLowerInPlace(ofUniChar& unichar);
//    static ofUniChar& toUpperInPlace(ofUniChar& unichar);
//
//    // unicode string based conversions
//    static ofUniString  toLower(ofUniString& unichar);
//    static ofUniString  toUpper(ofUniString& unichar);
//    static ofUniString& toLowerInPlace(ofUniString& unichar);
//    static ofUniString& toUpperInPlace(ofUniString& unichar);
//
//private:
//    
//};
