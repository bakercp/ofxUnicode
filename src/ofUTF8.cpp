#include "ofUTF8.h"


bool ofUTF8::isValid(const std::string& txt)
{
    try
    {
        auto end_it = utf8::find_invalid(txt.begin(), txt.end());

        if (end_it != txt.end())
        {
            std::string validPart(txt.begin(), end_it);
            ofLog(OF_LOG_ERROR,"ofUTF8::isValid - detected invalid UTF8 - valid part: " + validPart);
            return false;
        }
        else
        {
            return true;
        }
    }
    catch (const utf8::exception& utfcpp_ex)
    {
        string err = utfcpp_ex.what();
        ofLog(OF_LOG_ERROR, "ofUTF8::isValid : " + err);
        return false;
    }
}


bool ofUTF8::isValid(const char* iter, const char* end)
{
    try
    {
        bool isValid = utf8::is_valid(iter, end);

        if (!isValid)
        {
            ofLog(OF_LOG_ERROR,"ofUTF8::isValid - detected invalid UTF8");
            return false;
        }
        else
        {
            return true;
        }
    }
    catch(const utf8::exception& utfcpp_ex)
    {
        ofLog(OF_LOG_ERROR, "ofUTF8::isValid : " + ofToString(utfcpp_ex.what()));
        return false;
    }

}


bool ofUTF8::startsWithBOM(const std::string& txt)
{
    return startsWithBOM(beginPtr(txt), endPtr(txt));
}


bool ofUTF8::startsWithBOM(const char* iter, const char* end)
{
    return utf8::starts_with_bom(iter,end);
}


std::string ofUTF8::repair(const std::string& txt, char32_t replacement)
{
    std::string temp;

    try
    {
        if (replacement == -1)
        {
            utf8::replace_invalid(txt.begin(), txt.end(), back_inserter(temp));
        }
        else
        {
            utf8::replace_invalid(txt.begin(), txt.end(), back_inserter(temp), replacement);
        }
    }
    catch (const utf8::exception& utfcpp_ex)
    {
        ofLog(OF_LOG_ERROR, "ofUTF8::repair : " + ofToString(utfcpp_ex.what()));
    }

    return temp;
}


std::string& ofUTF8::repairInPlace(std::string& txt, char32_t replacement)
{
    txt = repair(txt,replacement);
    return txt;
}


std::size_t ofUTF8::distance(const std::string& txt)
{
    try
    {
        return utf8::distance(txt.begin(), txt.end());
    }
    catch (const utf8::exception& utfcpp_ex)
    {
        ofLog(OF_LOG_ERROR, "ofUTF8::distance : " + ofToString(utfcpp_ex.what()));
    }
}


std::size_t ofUTF8::distance(const char* iter, const char* end)
{
    try
    {
        return utf8::distance(iter, end);
    }
    catch(const utf8::exception& utfcpp_ex)
    {
        ofLog(OF_LOG_ERROR, "ofUTF8::distance : " + ofToString(utfcpp_ex.what()));
    }
}


int ofUTF8::icompare(const std::string& utf8String0,
                     const std::string& utf8String1)
{
    return Poco::UTF8::icompare(utf8String0,utf8String1);
}


std::string ofUTF8::toUpper(const std::string& str)
{
    return Poco::UTF8::toUpper(str);
}


std::string& ofUTF8::toUpperInPlace(std::string& str)
{
    return Poco::UTF8::toUpperInPlace(str);
}


std::string ofUTF8::toLower(const std::string& str)
{
    return Poco::UTF8::toLower(str);
}


std::string& ofUTF8::toLowerInPlace(std::string& str)
{
    return Poco::UTF8::toLowerInPlace(str);
}


const char* ofUTF8::beginPtr(const std::string& input)
{
    return input.c_str();
}


const char* ofUTF8::endPtr(const std::string& input)
{
    return input.c_str() + input.length();
}


utf8::iterator<const char*> ofUTF8::iterator(const std::string& input)
{
    return utf8::iterator<const char*>(beginPtr(input), beginPtr(input), endPtr(input));
}



utf8::iterator<const char*> ofUTF8::begin(const std::string& input)
{
    return iterator(input);
}


utf8::iterator<const char*> ofUTF8::end(const std::string& input)
{
    return utf8::iterator<const char*>(endPtr(input), beginPtr(input), endPtr(input));
}



char32_t ofUTF8::getNext(const char* iter, const char* end)
{
    try
    {
        return utf8::next(iter,end);
    }
    catch (const utf8::exception& utfcpp_ex)
    {
        ofLog(OF_LOG_ERROR, "ofUTF8::getNext : " + ofToString(utfcpp_ex.what()));
        return -1;
    }
}


char32_t ofUTF8::getPrior(const char* iter, const char* end)
{
    try
    {
        return utf8::prior(iter,end);
    }
    catch (const utf8::exception& utfcpp_ex)
    {
        ofLog(OF_LOG_ERROR, "ofUTF8::getPrior : " + ofToString(utfcpp_ex.what()));
        return -1;
    }
}


const char* ofUTF8::advance(const char* iter, const char* end, std::size_t numToSkip)
{
    try
    {
        utf8::advance(iter, numToSkip, end);
        return iter;
    }
    catch (const utf8::exception& utfcpp_ex)
    {
        ofLog(OF_LOG_ERROR, "ofUTF8::advance : " + ofToString(utfcpp_ex.what()));
        return nullptr;
    }
}


char32_t ofUTF8::get(const char* iter, const char* end)
{
    return getNext(iter,end);
}


const char* ofUTF8::next(const char* iter, const char* end)
{
    getNext(iter, end); return iter;
}


const char* ofUTF8::prior(const char* iter, const char* end)
{
    getPrior(iter, end); return iter;
}



char32_t ofUTF8::get(const std::string& input, const char* iter)
{
    return getNext(iter, endPtr(input));
}


const char* ofUTF8::next(const std::string& input, const char* iter)
{
    next(iter, endPtr(input));
    return iter;
}


const char* ofUTF8::prior(const std::string& input, const char* iter)
{
    prior(iter, endPtr(input));
    return iter;
}


const char* ofUTF8::advance(const std::string& input,
                          const char* iter,
                          std::size_t numToSkip)
{
    return advance(iter, endPtr(input));
}



char32_t ofUTF8::get(const char* iter)
{
    return utf8::unchecked::next(iter); // same as peek
}


const char* ofUTF8::next(const char* iter)
{
    utf8::unchecked::next(iter); // we don't return the unicode, just advance
    return iter; // iter is advanced
}


const char* ofUTF8::prior(const char* iter)
{
    utf8::unchecked::prior(iter); // we don't return the unicode, just move back
    return iter; // iter is advanced
}


const char* ofUTF8::advance(const char* iter, std::size_t numToSkip)
{
    utf8::unchecked::advance(iter,numToSkip); // we don't return the unicode, just advance
    return iter; // iter is advanced
}


char32_t ofUTF8::getNext(const char* iter)
{
    return utf8::unchecked::next(iter); // increment iter and return value
}


char32_t ofUTF8::getPrior(const char* iter)
{
    return utf8::unchecked::prior(iter); // increment iter and return value
}
