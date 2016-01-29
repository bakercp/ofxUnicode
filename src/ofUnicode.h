//
//  ofUnicode.h
//  ofxUTFCPPExample
//
//  Created by Christopher Baker on 5/23/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#pragma once

#include "ofConstants.h"
#include "ofLog.h"
#include "ofUtils.h"

#include "utf8.h"

#include "Poco/String.h"
#include "Poco/UTF8String.h"
#include "Poco/Ascii.h"
#include "Poco/Unicode.h"
#include "Poco/UTF8Encoding.h"
#include "Poco/TextIterator.h"
#include "Poco/TextConverter.h"

#include "Poco/UTF16Encoding.h"
#include "Poco/ASCIIEncoding.h"
#include "Poco/Latin1Encoding.h"
#include "Poco/Latin9Encoding.h"
#include "Poco/Windows1252Encoding.h"

// types
//typedef char             ofChar;      // a standard signed char
//typedef const char *     ofCharPtr;
//typedef unsigned char    ofUTF8Char;    // a UTF8 type (unsigned char)
//typedef ofCharPtr        const char*;     // a pointer type used when traversing
//                                        // a UTF8 encoded std::string.
//                                        // the "beginning" of the string would be
//                                        // const char* b = input.c_str();
//                                        // the "end" of the string would be
//                                        // const char* e = input.c_str() + input.length();
//                                        // this is wierd.

//typedef unsigned short   ofUTF16Char;   // a UTF16 type - stay clear of wstring. it's 4 bytes on *NIX, and 2 on Win
//typedef unsigned int     ofUTF32Char;   // a UTF32 type        
//typedef ofUTF32Char      char32_t;     // a unicode character type for clarity
//
//typedef const ofUTF16Char * ofUTF16Ptr;   // a pointer to wstring, like above 
//typedef const ofUTF32Char * ofUTF32Ptr;  // a pointer to unicode character
//typedef const char32_t *   char32_tPtr;  // a pointer to unicode character

//typedef std::string                    std::string;  //
//typedef basic_string<ofUTF16Char> std::u16string; // std:wstring is a mess cross platform
//typedef basic_string<ofUTF32Char> ofUTF32String; // aka unicode string
//typedef ofUTF32String             std::u32string; // this is a "unicode" string
//                                        // each vector entry contains one 
//                                        // unicode code point.  
//                                        // It is NOT UTF8 encoded.


//typedef utf8::iterator<const char*> ofxUTF8Iterator;  

// a bidirectional iterator for 
// to allow stl-iterator-like iteration
// through a UTF8 encoded std::string.
// Not exactly like an STL iterator.
// from the UTF8-CPP library.

class ofUnicode
{
public:
    
    static bool       isValid(char32_t unicode);     // is this a valid unicode character?
    static bool       isPrintable(char32_t unicode); // is this a "printable" character?
                                                             // True if the unicode category is not CONTROL
                                                             // This does not guarantee that the character
                                                             // has a visible "glyph".
    
    static bool       isCntrl(char32_t unichar);    // is this a "control" unicode character?
                                                            // this is broadly defined to include unicode
                                                            // CONTROL category, and other invisible glyphs
                                                            // this is Not the opposite of isPrintable.
    static bool       isTitle(char32_t unichar);    // is this a unicode "Titlecase" codepoint?
    static bool       isSpace(char32_t unichar);
    static bool       isDigit(char32_t unichar);
    static bool       isPunct(char32_t unichar);
    static bool 	  isAlpha(char32_t unichar);
    static bool 	  isAlphaNumeric(char32_t unichar); // isAlpha || isDigit
    static bool       isLower(char32_t unichar);
    static bool       isUpper(char32_t unichar);

    // conversions
    static char32_t  toLower(char32_t unichar);
    static char32_t  toUpper(char32_t unichar);
    static char32_t& toLowerInPlace(char32_t& unichar);
    static char32_t& toUpperInPlace(char32_t& unichar);

    // unicode string based conversions
    static std::u32string toLower(std::u32string& unichar);
    static std::u32string  toUpper(std::u32string& unichar);
    static std::u32string& toLowerInPlace(std::u32string& unichar);
    static std::u32string& toUpperInPlace(std::u32string& unichar);

private:
    
};
