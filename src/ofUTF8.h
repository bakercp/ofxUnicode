//
//  ofxUTF8CPP.h
//  ofxUTFCPPExample
//
//  Created by Christopher Baker on 5/23/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#pragma once

#include "ofUnicode.h"
#include "utf8.h"

enum ofTextEncoding {
    OF_TEXT_ENCODING_UTF8 = 0        , // variable width encoding (http://en.wikipedia.org/wiki/UTF-8) backward compatible  w/ ASCII
    OF_TEXT_ENCODING_UTF16           , // 16-bit multi-byte (http://en.wikipedia.org/wiki/UTF-16)
    OF_TEXT_ENCODING_ASCII           , // 7-bit ASCII text encoding (http://en.wikipedia.org/wiki/ASCII)
    OF_TEXT_ENCODING_LATIN_1         , // 8-bit single-byte - (http://en.wikipedia.org/wiki/ISO/IEC_8859-1)
    OF_TEXT_ENCODING_LATIN_9         , // 8-bit single-byte - (http://en.wikipedia.org/wiki/ISO/IEC_8859-15), western chars + €
    OF_TEXT_ENCODING_WINDOWS_1252      // Superset of Latin 1 (ISO 8859-1) http://en.wikipedia.org/wiki/Windows-1252
};

class ofUTF8 {
public:
    
    // custom iterator helper
    static ofUTF8Iter begin(const string& input);
    static ofUTF8Iter end(const string& input);
    
    // custom bi-directional iterator
    static ofUTF8Iterator iterator(const string& input);
    
    // convert from other encodings to UTF8
    static string   convertFrom(const string& input, ofTextEncoding inputEncoding = OF_TEXT_ENCODING_UTF8);
    
    // convert unicode to UTF8 string
    static string   toString(ofUniChar& unicode);
    static string   toString(ofUniChars& unichars);

    // convert UTF8 string to a unicode string
    static ofUniChars toUniChars(string txt);

    // append unicode char to UTF8 string
    static string   append(string txt, ofUniChar unicode);
    static string&  appendInPlace(string& txt, ofUniChar unicode);

    // check to see if a UTF8 string is valid
    static bool     isValid(string txt);
    static bool     isValid(ofUTF8Iter iter, ofUTF8Iter end);
    
    // check to see if a string starts with a UTF8 BOM (byte order mark)
    static bool     startsWithBOM(string txt);
    static bool     startsWithBOM(ofUTF8Iter iter, ofUTF8Iter end);
    
    // attempt to repair a broken UTF8 string
    static string   repair(string txt, ofUniChar replacement = -1);
    static string&  repairInPlace(string& txt, ofUniChar replacement = -1);
    
    // calculate the number of UTF8 chars (string.length() returns the number of bytes)
    static int      distance(string txt);
    static int      distance(ofUTF8Iter iter, ofUTF8Iter end);
    
    // case insensitive comparison of UTF8 strings
    static int      icompare(const string& utf8String0, const string& utf8String1);
    
    // unicode-based case conversion
	static string   toUpper(const string& str);
	static string&  toUpperInPlace(string& str);
	static string   toLower(const string& str);
	static string&  toLowerInPlace(string& str);
    
    // Checked Iterators - No need to check input 
    ////////////////////////////////////////////////////////////////////
    static ofUniChar   getNext(ofUTF8Iter& iter, ofUTF8Iter end);  // will increment iter and return value
    static ofUniChar   getPrior(ofUTF8Iter& iter, ofUTF8Iter end); // will increment iter and return value
    static ofUTF8Iter  advance(ofUTF8Iter& iter, ofUTF8Iter end, int numToSkip = 1); // skips N unicode chars
    //------------------------------------------------------------------
    //------------------------------------------------------------------
    static ofUniChar   get(ofUTF8Iter iter, ofUTF8Iter end);  // reads the unichar at the current iter position
    static ofUTF8Iter  next(ofUTF8Iter iter, ofUTF8Iter end); // moves the iterator to the next unicode start
    static ofUTF8Iter  prior(ofUTF8Iter iter, ofUTF8Iter end); // moves the iterator to the previous unicode start
    //------------------------------------------------------------------
    //------------------------------------------------------------------
    static ofUniChar   get(const string& input, ofUTF8Iter iter = NULL);  // reads the unichar at the current iter position
    static ofUTF8Iter  next(const string& input, ofUTF8Iter iter = NULL); // moves the iterator to the next unicode start
    static ofUTF8Iter  prior(const string& input, ofUTF8Iter iter = NULL); // moves the iterator to the previous unicode start
    static ofUTF8Iter  advance(const string& input, ofUTF8Iter iter = NULL, int numToSkip = 1); // skips N unicode chars
    
    // Unchecked Iterators - Should check input string for valid UTF8 first 
    ////////////////////////////////////////////////////////////////////
    static ofUniChar   get(ofUTF8Iter iter);  // reads the unichar at the current iter position
    static ofUTF8Iter  next(ofUTF8Iter iter); // moves the iterator to the next unicode start
    static ofUTF8Iter  prior(ofUTF8Iter iter); // moves the iterator to the previous unicode start
    static ofUTF8Iter  advance(ofUTF8Iter iter, int numToSkip = 1); // skips N unicode chars
    
    static ofUniChar   getNext(ofUTF8Iter& iter); // moves the iterator to the next unicode start and returns it
    static ofUniChar   getPrior(ofUTF8Iter& iter); // moves the iterator to the previous unicode start and returns it

private:
    // keep them around
    static Poco::UTF8Encoding        utf8_enc;
    static Poco::UTF16Encoding       utf16_enc;
    static Poco::ASCIIEncoding       ascii_enc;
    static Poco::Latin1Encoding      latin1_enc;
    static Poco::Latin9Encoding      latin9_enc;
    static Poco::Windows1252Encoding windows1252_enc;
    
};