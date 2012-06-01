#include "ofUTF8.h"


//------------------------------------------------------------------
ofUTF16String ofUTF8::toUTF16(const ofUTF8String& txt) {
    return UnicodeString::fromUTF8(txt);
}

//------------------------------------------------------------------
ofUniString ofUTF8::toUTF32(const ofUTF8String& txt) {
    return ofUTF16::toUTF32(toUTF16(txt)); // conversion through UTF16 ... not ideal.
}

//------------------------------------------------------------------
ofUTF8String ofUTF8::append(ofUTF8String txt, ofUniChar unicode) {
    ofUTF8Char buffer[U8_MAX_LENGTH];
    UBool error = false;
    uint32_t i = 0;
    U8_APPEND(buffer,i,U8_MAX_LENGTH,unicode,error);
    if(!error) {
        txt.append(toCharPtr(buffer),i);
    } else {
        ofLog(OF_LOG_ERROR,"ofUTF8::append - error converting unicode to UTF8.  Returning original.");
    }
    return txt;
}

//------------------------------------------------------------------
ofUTF8String ofUTF8::append(ofUTF8String txt, ofUniString unicode) {
    ofUTF8Char buffer[U8_MAX_LENGTH*unicode.length()];
    UBool error = false;
    uint32_t i = 0;
    for(int j = 0; j < unicode.length(); j++) {
        U8_APPEND(buffer,i,U8_MAX_LENGTH,unicode[j],error);
        if(error) break;
    }

    if(!error) {
        txt.append(toCharPtr(buffer),i);
    } else {
        ofLog(OF_LOG_ERROR,"ofUTF8::append - error converting unicode to UTF8.  Returning original.");
    }

    return txt;
    
}

//------------------------------------------------------------------
ofUTF8String& ofUTF8::appendInPlace(ofUTF8String& txt, ofUniChar unicode) {
    char buffer[U8_MAX_LENGTH];
    
}

//------------------------------------------------------------------
ofUTF8String ofUTF8::appendUnsafe(ofUTF8String txt, ofUniChar unicode) {
    char buffer[U8_MAX_LENGTH];
    
}

//------------------------------------------------------------------
ofUTF8String ofUTF8::appendUnsafe(ofUTF8String txt, ofUniString unicode) {
    char buffer[U8_MAX_LENGTH];
    
}

//------------------------------------------------------------------
ofUTF8String& ofUTF8::appendInPlaceUnsafe(ofUTF8String& txt, ofUniChar unicode) {
    char buffer[U8_MAX_LENGTH];
    
}

//------------------------------------------------------------------
bool ofUTF8::isValid(const ofUTF8String& txt) {
    return isValid(txt,0,txt.length());
}

//------------------------------------------------------------------
bool ofUTF8::isValid(const ofUTF8String& txt, ofCharPtr fromPtr) {
    return isValid(txt,(ofUTF8Idx)(fromPtr - txt.c_str()),(ofUTF8Idx)txt.length());
}

//------------------------------------------------------------------
bool ofUTF8::isValid(const ofUTF8String& txt, ofCharPtr fromPtr, ofCharPtr toPtr) {
    return isValid(txt,(ofUTF8Idx)(fromPtr - txt.c_str()),(ofUTF8Idx)(toPtr - txt.c_str()));
}

//------------------------------------------------------------------
bool ofUTF8::isValid(const ofUTF8String& txt, ofUTF8Idx fromIdx) {
    return isValid(txt,fromIdx,(ofUTF8Idx)txt.length());
}

//------------------------------------------------------------------
bool ofUTF8::isValid(const ofUTF8String& txt, ofUTF8Idx fromIdx, ofUTF8Idx toIdx) {
    return distance(txt,fromIdx,toIdx) > -1;
}

//------------------------------------------------------------------
int ofUTF8::distance(const ofUTF8String& txt) {
    return distance(txt,0,txt.length());
}

//------------------------------------------------------------------
int ofUTF8::distance(const ofUTF8String& txt, ofCharPtr fromPtr) {
    return distance(txt,(ofUTF8Idx)(fromPtr - txt.c_str()),(ofUTF8Idx)txt.length());
}

//------------------------------------------------------------------
int ofUTF8::distance(const ofUTF8String& txt, ofCharPtr fromPtr, ofCharPtr toPtr) {
    return distance(txt,(ofUTF8Idx)(fromPtr - txt.c_str()),(ofUTF8Idx)(toPtr - txt.c_str()));
}

//------------------------------------------------------------------
int ofUTF8::distance(const ofUTF8String& txt, ofUTF8Idx fromIdx) {
    return distance(txt,fromIdx,(ofUTF8Idx)txt.length());
}

//------------------------------------------------------------------
int ofUTF8::distance(const ofUTF8String& txt, ofUTF8Idx fromIdx, ofUTF8Idx toIdx) {
    ofUniChar c = -1;
    int count = 0;
    ofUTF8Ptr txtPtr = beginUTF8Ptr(txt);
    for(ofUTF8Idx i = fromIdx; i < toIdx;/*U8_NEXT increments*/) {
        U8_NEXT(txtPtr, i, txt.length(), c); // Use U8_NEXT, rather than U8_NEXT_UNSAFE to grab errors.
        if(c < 0) {
            return -1;   
        } else {
            count++;
        }
    }
    return count; // all returned cleanly
}

//------------------------------------------------------------------
int ofUTF8::icompare(const ofUTF8String& utf8String0, const ofUTF8String& utf8String1) {
    // can also be done w/ Collator::compareUTF8
    return Poco::UTF8::icompare(utf8String0,utf8String1);
}


//------------------------------------------------------------------
ofUTF8String ofUTF8::toUpper(const ofUTF8String& txt) {
    return Poco::UTF8::toUpper(txt);
}

//------------------------------------------------------------------
ofUTF8String& ofUTF8::toUpperInPlace(ofUTF8String& txt) {
    return Poco::UTF8::toUpperInPlace(txt);
}

//------------------------------------------------------------------
ofUTF8String ofUTF8::toLower(const ofUTF8String& txt) {
    return Poco::UTF8::toLower(txt);
}

//------------------------------------------------------------------
ofUTF8String& ofUTF8::toLowerInPlace(ofUTF8String& txt) {
    return Poco::UTF8::toLowerInPlace(txt);
}

//------------------------------------------------------------------
ofUTF8Ptr ofUTF8::toUTF8Ptr(const ofCharPtr ptr) {
    return reinterpret_cast<ofUTF8Ptr>(ptr);
}

//------------------------------------------------------------------
ofCharPtr ofUTF8::toCharPtr(const ofUTF8Ptr ptr) {
    return reinterpret_cast<ofCharPtr>(ptr);
}

//------------------------------------------------------------------
ofCharPtr ofUTF8::beginCharPtr(const ofUTF8String& input) {
    return input.c_str();
}

//------------------------------------------------------------------
ofCharPtr ofUTF8::endCharPtr(const ofUTF8String& input) {
    return input.c_str() + input.length();
}

//------------------------------------------------------------------
ofUTF8Ptr ofUTF8::beginUTF8Ptr(const ofUTF8String& txt) {
    return toUTF8Ptr(beginCharPtr(txt));
}
//------------------------------------------------------------------
ofUTF8Ptr ofUTF8::endUTF8Ptr(const ofUTF8String& txt) {
    return toUTF8Ptr(endCharPtr(txt));
}

////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------
ofUniChar ofUTF8::get(const ofUTF8String& txt, ofCharPtr iter) { 
    return getNext(txt,iter);
}
//------------------------------------------------------------------
ofCharPtr ofUTF8::next(const ofUTF8String& txt, ofCharPtr iter) {
    ofUTF8Ptr txtPtr = beginUTF8Ptr(txt);
    int i = toUTF8Ptr(iter) - txtPtr;
    U8_FWD_1(txtPtr,i,txt.length()); // i will go positive
    iter = beginCharPtr(txt) + i;
    return iter;
}

//------------------------------------------------------------------
ofCharPtr ofUTF8::prior(const ofUTF8String& txt, ofCharPtr iter) {
    ofUTF8Ptr txtPtr = beginUTF8Ptr(txt);
    int i = toUTF8Ptr(iter) - txtPtr;
    U8_BACK_1(txtPtr,0,i); // i will go negative
    iter = beginCharPtr(txt) + i;
    return iter;
}

//------------------------------------------------------------------
ofCharPtr ofUTF8::advance(const ofUTF8String& txt, ofCharPtr iter, const int numToSkip) {
    ofUTF8Ptr txtPtr = beginUTF8Ptr(txt);
    int i = toUTF8Ptr(iter) - txtPtr;
    U8_FWD_N(txtPtr,i,txt.length(),numToSkip);
    iter = beginCharPtr(txt) + i;
    return iter;
}

//------------------------------------------------------------------
ofUniChar ofUTF8::getNext(const ofUTF8String& txt, ofCharPtr& iter) {
    ofUniChar c;
    ofUTF8Ptr txtPtr = beginUTF8Ptr(txt);
    int i = toUTF8Ptr(iter) - txtPtr;
    U8_NEXT(txtPtr, i, txt.length(), c);
    iter = beginCharPtr(txt) + i;
    return c;
}

//------------------------------------------------------------------
ofUniChar ofUTF8::getPrior(const ofUTF8String& txt, ofCharPtr& iter) {
    ofUniChar c;
    ofUTF8Ptr txtPtr = beginUTF8Ptr(txt);
    int i = toUTF8Ptr(iter) - txtPtr;
    U8_BACK_1(txtPtr,0,i); // i will go positive
    iter = beginCharPtr(txt) + i;
    U8_GET(txtPtr,0,i,txt.length(),c);
    return c;

}






//------------------------------------------------------------------
ofUniChar ofUTF8::get(const ofUTF8String& txt, ofUTF8Idx idx) { 
    return getNext(txt,idx);
}
//------------------------------------------------------------------
ofUTF8Idx ofUTF8::next(const ofUTF8String& txt, ofUTF8Idx idx) {
    //U8_FWD_1,idx); // i will go positive
    return idx;
}

//------------------------------------------------------------------
ofUTF8Idx ofUTF8::prior(const ofUTF8String& txt, ofUTF8Idx idx) {
    U8_BACK_1(beginUTF8Ptr(txt),0,idx); // i will go negative
    return idx;
}

//------------------------------------------------------------------
ofUTF8Idx ofUTF8::advance(const ofUTF8String& txt, ofUTF8Idx idx, const int numToSkip) {
    U8_FWD_N(beginUTF8Ptr(txt),idx,txt.length(),numToSkip);
    return idx;
}

//------------------------------------------------------------------
ofUniChar ofUTF8::getNext(const ofUTF8String& txt, ofUTF8Idx& idx) {
    ofUniChar c;
    U8_NEXT(beginUTF8Ptr(txt), idx,txt.length(), c);
    return c;
}

//------------------------------------------------------------------
ofUniChar ofUTF8::getPrior(const ofUTF8String& txt, ofUTF8Idx& idx) {
    ofUniChar c;
    U8_PREV(beginUTF8Ptr(txt),0,idx,c);
    return c;
}

//------------------------------------------------------------------

////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------
ofUniChar ofUTF8::getUnsafe(const ofUTF8String& txt, ofCharPtr iter) { 
   return getNextUnsafe(txt,iter);
}
//------------------------------------------------------------------
ofCharPtr ofUTF8::nextUnsafe(const ofUTF8String& txt, ofCharPtr iter) {
    ofUTF8Ptr txtPtr = beginUTF8Ptr(txt);
    int i = toUTF8Ptr(iter) - txtPtr;
    U8_FWD_1_UNSAFE(txtPtr,i); // i will go positive
    iter = beginCharPtr(txt) + i;
    return iter;
}

//------------------------------------------------------------------
ofCharPtr ofUTF8::priorUnsafe(const ofUTF8String& txt, ofCharPtr iter) {
    ofUTF8Ptr txtPtr = beginUTF8Ptr(txt);
    int i = toUTF8Ptr(iter) - txtPtr;
    U8_BACK_1_UNSAFE(txtPtr,i); // i will go negative
    iter = beginCharPtr(txt) + i;
    return iter;
}

//------------------------------------------------------------------
ofCharPtr ofUTF8::advanceUnsafe(const ofUTF8String& txt, ofCharPtr iter, const int numToSkip) {
    ofUTF8Ptr txtPtr = beginUTF8Ptr(txt);
    int i = toUTF8Ptr(iter) - txtPtr;
    U8_FWD_N_UNSAFE(txtPtr,i,numToSkip);
    iter = beginCharPtr(txt) + i;
    return iter;
}

//------------------------------------------------------------------
ofUniChar ofUTF8::getNextUnsafe(const ofUTF8String& txt, ofCharPtr& iter) {
    ofUniChar c;
    ofUTF8Ptr txtPtr = beginUTF8Ptr(txt);
    int i = toUTF8Ptr(iter) - txtPtr;
    U8_NEXT_UNSAFE(txtPtr, i, c);
    iter = beginCharPtr(txt) + i;
    return c;
}

//------------------------------------------------------------------
ofUniChar ofUTF8::getPriorUnsafe(const ofUTF8String& txt, ofCharPtr& iter) {
    ofUniChar c;
    ofUTF8Ptr txtPtr = beginUTF8Ptr(txt);
    int i = toUTF8Ptr(iter) - txtPtr;
    U8_BACK_1_UNSAFE(txtPtr,i); // i will go positive
    iter = beginCharPtr(txt) + i;
    U8_GET_UNSAFE(txtPtr,i,c);
    return c;
}

//------------------------------------------------------------------
ofUniChar ofUTF8::getUnsafe(const ofUTF8String& txt, ofUTF8Idx idx) { 
   return getNextUnsafe(txt,idx);
}
//------------------------------------------------------------------
ofUTF8Idx ofUTF8::nextUnsafe(const ofUTF8String& txt, ofUTF8Idx idx) {
    U8_FWD_1_UNSAFE(beginUTF8Ptr(txt),idx); // i will go positive
    return idx;
}

//------------------------------------------------------------------
ofUTF8Idx ofUTF8::priorUnsafe(const ofUTF8String& txt, ofUTF8Idx idx) {
    U8_BACK_1_UNSAFE(beginUTF8Ptr(txt),idx); // i will go negative
    return idx;
}

//------------------------------------------------------------------
ofUTF8Idx ofUTF8::advanceUnsafe(const ofUTF8String& txt, ofUTF8Idx idx, const int numToSkip) {
    U8_FWD_N_UNSAFE(beginUTF8Ptr(txt),idx,numToSkip);
    return idx;
}

//------------------------------------------------------------------
ofUniChar ofUTF8::getNextUnsafe(const ofUTF8String& txt, ofUTF8Idx& idx) {
    ofUniChar c;
    U8_NEXT_UNSAFE(beginUTF8Ptr(txt), idx, c);
    return c;
}

//------------------------------------------------------------------
ofUniChar ofUTF8::getPriorUnsafe(const ofUTF8String& txt, ofUTF8Idx& idx) {
    ofUniChar c;
    U8_PREV_UNSAFE(beginUTF8Ptr(txt),idx,c)
    return c;
}

//------------------------------------------------------------------