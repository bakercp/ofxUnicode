
#include "ofUnicode.h"

//------------------------------------------------------------------
bool ofUnicode::isValid(const ofUniChar& unicode) {
    return !((unicode > 0x0010ffffu) || (unicode >= 0xd800u && unicode <= 0xdfffu));
}

//------------------------------------------------------------------
bool ofUnicode::isSpace(const ofUniChar& unichar) {
    return Poco::Unicode::isSpace(unichar);
}

//------------------------------------------------------------------
bool ofUnicode::isDigit(const ofUniChar& unichar) {
    return Poco::Unicode::isDigit(unichar);
}

//------------------------------------------------------------------
bool ofUnicode::isPunct(const ofUniChar& unichar) {
    return Poco::Unicode::isPunct(unichar);
}

//------------------------------------------------------------------
bool ofUnicode::isAlpha(const ofUniChar& unichar) {
    return Poco::Unicode::isAlpha(unichar);
}

//------------------------------------------------------------------
bool ofUnicode::isLower(const ofUniChar& unichar) {
    return Poco::Unicode::isLower(unichar);
}

//------------------------------------------------------------------
bool ofUnicode::isUpper(const ofUniChar& unichar) {
    return Poco::Unicode::isUpper(unichar);
}

//------------------------------------------------------------------
ofUniChar ofUnicode::toLower(const ofUniChar& unichar) {
    return Poco::Unicode::toLower(unichar);
}

//------------------------------------------------------------------
ofUniChar ofUnicode::toUpper(const ofUniChar& unichar) {
    return Poco::Unicode::toUpper(unichar);
}

//------------------------------------------------------------------
ofUniChar& ofUnicode::toLowerInPlace(ofUniChar& unichar) { 
    unichar = toLower(unichar); 
    return unichar;
}
//------------------------------------------------------------------
ofUniChar& ofUnicode::toUpperInPlace(ofUniChar& unichar) { 
    unichar = toUpper(unichar); 
    return unichar;
}


