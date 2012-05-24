#include "ofUTF8.h"

//------------------------------------------------------------------
ofUTF8Iter ofUTF8::begin(const string& input) {
    return input.c_str();
}
//------------------------------------------------------------------
ofUTF8Iter ofUTF8::end(const string& input) {
    return input.c_str() + input.length();
}
//------------------------------------------------------------------
ofUTF8Iterator ofUTF8::iterator(const string& input) {
    ofUTF8Iterator it(begin(input),begin(input),end(input));
    return it;
}

//------------------------------------------------------------------
string ofUTF8::convertFrom(const string& input, ofTextEncoding inputEncoding) {
    
    // pass through
    if(inputEncoding == OF_TEXT_ENCODING_UTF8) {
        return input;
    }
    
    // converts from various encoding using poco.
    string utf8String;
    
    if(inputEncoding == OF_TEXT_ENCODING_UTF16) {
        Poco::TextConverter converter(utf16_enc, utf8_enc);
        converter.convert(input, utf8String);
    } else if(inputEncoding == OF_TEXT_ENCODING_ASCII) {
        Poco::TextConverter converter(ascii_enc, utf8_enc);
        converter.convert(input, utf8String);
    } else if(inputEncoding == OF_TEXT_ENCODING_LATIN_1) {
        Poco::TextConverter converter(latin1_enc, utf8_enc);
        converter.convert(input, utf8String);
    } else if(inputEncoding == OF_TEXT_ENCODING_LATIN_9) {
        Poco::TextConverter converter(latin9_enc, utf8_enc);
        converter.convert(input, utf8String);
    } else if(inputEncoding == OF_TEXT_ENCODING_WINDOWS_1252) {
        Poco::TextConverter converter(windows1252_enc, utf8_enc);
        converter.convert(input, utf8String);
    } else {
        ofLog(OF_LOG_ERROR,"ofUTF8::convertFrom : unknown input encoding.");
        return input;
    }
    
    return utf8String;
}

//------------------------------------------------------------------
string ofUTF8::toString(ofUniChar& unicode) {
    string txt;
    return append(txt, unicode);
}

//------------------------------------------------------------------
string ofUTF8::toString(ofUniChars& unichars) {
    string txt;
    ofUniChars::iterator iter;// = unichars.begin();
    iter = unichars.begin();
    while(iter != unichars.end()) {
        appendInPlace(txt,*iter);
        iter++;
    }
}

//------------------------------------------------------------------
ofUniChars ofUTF8::toUniChars(string txt) {
    ofUniChars utf32result;
    try {
        utf8::utf8to32(begin(txt), end(txt), back_inserter(utf32result));
    } catch(const utf8::exception& utfcpp_ex) {
        string err = utfcpp_ex.what();
        ofLog(OF_LOG_ERROR, "ofUTF8::toUniChars : " + err);
    }
    return utf32result;
}

//------------------------------------------------------------------
string ofUTF8::append(string txt, ofUniChar unicode) {
    try {
        utf8::append(unicode, back_inserter(txt));
    } catch(const utf8::exception& utfcpp_ex) {
        string err = utfcpp_ex.what();
        ofLog(OF_LOG_ERROR, "ofUTF8::append : " + err);
    }
    return txt;
}

//------------------------------------------------------------------
string& ofUTF8::appendInPlace(string& txt, ofUniChar unicode) {
    txt = append(txt,unicode);
    return txt;
}

//------------------------------------------------------------------
bool ofUTF8::isValid(string txt) {
    try {
        string::iterator end_it = utf8::find_invalid(txt.begin(), txt.end());
        if(end_it != txt.end()) {
            string validPart(txt.begin(),end_it);
            ofLog(OF_LOG_ERROR,"ofUTF8::isValid - detected invalid UTF8 - valid part: " + validPart);
            return false;
        } else {
            return true;
        }
    } catch(const utf8::exception& utfcpp_ex) {
        string err = utfcpp_ex.what();
        ofLog(OF_LOG_ERROR, "ofUTF8::isValid : " + err);
        return false;
    }
}

//------------------------------------------------------------------
bool ofUTF8::isValid(ofUTF8Iter iter, ofUTF8Iter end) {
    try {
        bool isValid = utf8::is_valid(iter,end);
        if(!isValid) {
            ofLog(OF_LOG_ERROR,"ofUTF8::isValid - detected invalid UTF8");
            return false;
        } else {
            return true;
        }
    } catch(const utf8::exception& utfcpp_ex) {
        string err = utfcpp_ex.what();
        ofLog(OF_LOG_ERROR, "ofUTF8::isValid : " + err);
        return false;
    }

}

//------------------------------------------------------------------
bool ofUTF8::startsWithBOM(string txt) {
    return startsWithBOM(begin(txt),end(txt));
}

//------------------------------------------------------------------
bool ofUTF8::startsWithBOM(ofUTF8Iter iter, ofUTF8Iter end) {
    return utf8::starts_with_bom(iter,end);
}

//------------------------------------------------------------------
string repair(string txt, ofUniChar replacement) {
    string temp;
    try {
        if(replacement == -1) {
            utf8::replace_invalid(txt.begin(), txt.end(), back_inserter(temp));
        } else {
            utf8::replace_invalid(txt.begin(), txt.end(), back_inserter(temp), replacement);
        }
    } catch(const utf8::exception& utfcpp_ex) {
        string err = utfcpp_ex.what();
        ofLog(OF_LOG_ERROR, "ofUTF8::repair : " + err);
    }
    return temp;
}

//------------------------------------------------------------------
string& ofUTF8::repairInPlace(string& txt, ofUniChar replacement) {
    txt = repair(txt,replacement);
    return txt;
}
//------------------------------------------------------------------
int ofUTF8::distance(string txt) {
    try {
        return utf8::distance(txt.begin(), txt.end());
    } catch(const utf8::exception& utfcpp_ex) {
        string err = utfcpp_ex.what();
        ofLog(OF_LOG_ERROR, "ofUTF8::distance : " + err);
    }
}

//------------------------------------------------------------------
int ofUTF8::distance(ofUTF8Iter iter, ofUTF8Iter end) {
    try {
        return utf8::distance(iter, end);
    } catch(const utf8::exception& utfcpp_ex) {
        string err = utfcpp_ex.what();
        ofLog(OF_LOG_ERROR, "ofUTF8::distance : " + err);
    }
}

//------------------------------------------------------------------
int ofUTF8::icompare(const string& utf8String0, const string& utf8String1) {
    return Poco::UTF8::icompare(utf8String0,utf8String1);
}

//------------------------------------------------------------------
string ofUTF8::toUpper(const string& str) {
    return Poco::UTF8::toUpper(str);
}

//------------------------------------------------------------------
string& ofUTF8::toUpperInPlace(string& str) {
    return Poco::UTF8::toUpperInPlace(str);
}

//------------------------------------------------------------------
string ofUTF8::toLower(const string& str) {
    return Poco::UTF8::toLower(str);
}

//------------------------------------------------------------------
string& ofUTF8::toLowerInPlace(string& str) {
    return Poco::UTF8::toLowerInPlace(str);
}

//------------------------------------------------------------------
ofUniChar ofUTF8::getNext(ofUTF8Iter& iter, ofUTF8Iter end) {
    try {
        return utf8::next(iter,end);
    } catch(const utf8::exception& utfcpp_ex) {
        string err = utfcpp_ex.what();
        ofLog(OF_LOG_ERROR, "ofUTF8::getNext : " + err);
        return -1;
    }
}

//------------------------------------------------------------------
ofUniChar ofUTF8::getPrior(ofUTF8Iter& iter, ofUTF8Iter end) {
    try {
        return utf8::prior(iter,end);
    } catch(const utf8::exception& utfcpp_ex) {
        string err = utfcpp_ex.what();
        ofLog(OF_LOG_ERROR, "ofUTF8::getPrior : " + err);
        return -1;
    }
}

//------------------------------------------------------------------
ofUTF8Iter ofUTF8::advance(ofUTF8Iter& iter, ofUTF8Iter end, int numToSkip) {
    try {
        utf8::advance(iter,numToSkip,end);
        return iter;
    } catch(const utf8::exception& utfcpp_ex) {
        string err = utfcpp_ex.what();
        ofLog(OF_LOG_ERROR, "ofUTF8::advance : " + err);
        return NULL;
    }
}

//------------------------------------------------------------------
//------------------------------------------------------------------
ofUniChar ofUTF8::get(ofUTF8Iter iter, ofUTF8Iter end) {
    return getNext(iter,end);
}

//------------------------------------------------------------------
ofUTF8Iter ofUTF8::next(ofUTF8Iter iter, ofUTF8Iter end) {
    getNext(iter, end); return iter;
}

//------------------------------------------------------------------
ofUTF8Iter ofUTF8::prior(ofUTF8Iter iter, ofUTF8Iter end) {
    getPrior(iter, end); return iter;
}


//------------------------------------------------------------------
//------------------------------------------------------------------
ofUniChar ofUTF8::get(const string& input, ofUTF8Iter iter) {
    return getNext(iter, end(input));
}

//------------------------------------------------------------------
ofUTF8Iter ofUTF8::next(const string& input, ofUTF8Iter iter) {
    next(iter, end(input));
    return iter;
}

//------------------------------------------------------------------
ofUTF8Iter ofUTF8::prior(const string& input, ofUTF8Iter iter) {
    prior(iter, end(input));
    return iter;
}

//------------------------------------------------------------------
ofUTF8Iter ofUTF8::advance(const string& input, ofUTF8Iter iter, const int numToSkip) {
    return advance(iter, end(input));
}

////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------
ofUniChar ofUTF8::get(ofUTF8Iter iter) { 
    return utf8::unchecked::next(iter); // same as peek
}
//------------------------------------------------------------------
ofUTF8Iter ofUTF8::next(ofUTF8Iter iter) {
    utf8::unchecked::next(iter); // we don't return the unicode, just advance
    return iter; // iter is advanced
}

//------------------------------------------------------------------
ofUTF8Iter ofUTF8::prior(ofUTF8Iter iter) {
    utf8::unchecked::prior(iter); // we don't return the unicode, just move back
    return iter; // iter is advanced
}

//------------------------------------------------------------------
ofUTF8Iter ofUTF8::advance(ofUTF8Iter iter, const int numToSkip) {
    utf8::unchecked::advance(iter,numToSkip); // we don't return the unicode, just advance
    return iter; // iter is advanced
}

//------------------------------------------------------------------
ofUniChar ofUTF8::getNext(ofUTF8Iter& iter) {
    return utf8::unchecked::next(iter); // increment iter and return value
}

//------------------------------------------------------------------
ofUniChar ofUTF8::getPrior(ofUTF8Iter& iter) {
    return utf8::unchecked::prior(iter); // increment iter and return value
}

//------------------------------------------------------------------

