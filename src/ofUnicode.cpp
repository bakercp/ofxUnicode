#include "ofUnicode.h"


bool ofUnicode::isValid(char32_t unichar)
{
    return !((unichar > 0x0010ffffu) || (unichar >= 0xd800u && unichar <= 0xdfffu));
}


bool ofUnicode::isPrintable(char32_t unichar)
{
    Poco::Unicode::CharacterProperties props;
	Poco::Unicode::properties(unichar, props);
    
    return props.type != Poco::Unicode::UCP_CONTROL;
}


bool ofUnicode::isCntrl(char32_t unichar)
{
    // True if unichar is:
    //  - ISO 8-bit control character (U+0000..U+001f and U+007f..U+009f)
    //  - UCP_CONTROL
    //  - UCP_FORMAT (Cf)
    //  - UCP_LINE_SEPARATOR
    //  - UCP_PARAGRAPH_SEPARATOR
    // This definition shared with ICU's isCntrl function 
    // http://icu-project.org/apiref/icu4c/uchar_8h.html#a1295bd387a68fe6df79fedce367c18dd
    

    Poco::Unicode::CharacterProperties props;
	Poco::Unicode::properties(unichar, props);
    
    return props.type == Poco::Unicode::UCP_CONTROL
        || props.type == Poco::Unicode::UCP_FORMAT
        || props.type == Poco::Unicode::UCP_LINE_SEPARATOR
        || props.type == Poco::Unicode::UCP_PARAGRAPH_SEPARATOR;
    
}


bool ofUnicode::isTitle(char32_t unichar)
{
    Poco::Unicode::CharacterProperties props;
	Poco::Unicode::properties(unichar, props);
    
    return props.type == Poco::Unicode::UCP_TITLE_CASE_LETTER;
}


bool ofUnicode::isSpace(char32_t unichar)
{
    return Poco::Unicode::isSpace(unichar);
}


bool ofUnicode::isDigit(char32_t unichar)
{
    return Poco::Unicode::isDigit(unichar);
}


bool ofUnicode::isPunct(char32_t unichar)
{
    return Poco::Unicode::isPunct(unichar);
}


bool ofUnicode::isAlpha(char32_t unichar)
{
    return Poco::Unicode::isAlpha(unichar);
}


bool ofUnicode::isAlphaNumeric(char32_t unichar)
{
    return isAlpha(unichar) || isDigit(unichar);
}


bool ofUnicode::isLower(char32_t unichar)
{
    return Poco::Unicode::isLower(unichar);
}


bool ofUnicode::isUpper(char32_t unichar)
{
    return Poco::Unicode::isUpper(unichar);
}


char32_t ofUnicode::toLower(char32_t unichar)
{
    return Poco::Unicode::toLower(unichar);
}


char32_t ofUnicode::toUpper(char32_t unichar)
{
    return Poco::Unicode::toUpper(unichar);
}


char32_t& ofUnicode::toLowerInPlace(char32_t& unichar)
{
    unichar = toLower(unichar); 
    return unichar;
}


char32_t& ofUnicode::toUpperInPlace(char32_t& unichar)
{
    unichar = toUpper(unichar); 
    return unichar;
}


std::u32string ofUnicode::toLower(std::u32string& unichar)
{
    std::u32string out;
    std::u32string::iterator it = unichar.begin();
    while(it != unichar.end()) {out.push_back(toLower(*(it++)));}
    return out;
}


std::u32string ofUnicode::toUpper(std::u32string& unichar)
{
    std::u32string out;
    std::u32string::iterator it = unichar.begin();
    while(it != unichar.end()) {out.push_back(toUpper(*(it++)));}
    return out;
}


std::u32string& ofUnicode::toLowerInPlace(std::u32string& unichar) {
    std::u32string::iterator it = unichar.begin();
    while(it != unichar.end()) {toUpperInPlace(*(it++));}
    return unichar;
}


std::u32string& ofUnicode::toUpperInPlace(std::u32string& unichar)
{
    std::u32string::iterator it = unichar.begin();
    while(it != unichar.end()) {toLowerInPlace(*(it++));}
    return unichar;
}


