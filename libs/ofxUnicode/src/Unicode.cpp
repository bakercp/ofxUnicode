// =============================================================================
//
// Copyright (c) 2012-2016 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#include "ofx/Unicode.h"
#include "ofUtils.h"
#include "ofLog.h"
#include "Poco/UTF8String.h"
#include "Poco/Unicode.h"


namespace ofx {


Linebreaker::Linebreaker(const std::string& language):
    _language(language)
{
}


Linebreaker::~Linebreaker()
{
}


const std::string& Linebreaker::language() const
{
    return _language;
}


std::vector<Linebreaker::BreakType> Linebreaker::findBreaks(const std::string& text) const
{
    return findBreaks(text, _language);
}


std::vector<Linebreaker::BreakType> Linebreaker::findBreaks(const std::u16string& text) const
{
    return findBreaks(text, _language);
}


std::vector<Linebreaker::BreakType> Linebreaker::findBreaks(const std::u32string& text) const
{
    return findBreaks(text, _language);
}


std::vector<Linebreaker::BreakType> Linebreaker::findBreaks(const std::string& text,
                                                            const std::string& language)
{
    std::vector<Linebreaker::BreakType> breaks(text.size());

    set_linebreaks_utf8(reinterpret_cast<const utf8_t*>(text.data()),
                        text.size(),
                        language.data(),
                        reinterpret_cast<char*>(breaks.data()));

    return breaks;
}


std::vector<Linebreaker::BreakType> Linebreaker::findBreaks(const std::u16string& text,
                                                            const std::string& language)
{
    std::vector<Linebreaker::BreakType> breaks(text.size());

    set_linebreaks_utf16(reinterpret_cast<const utf16_t*>(text.data()),
                        text.size(),
                        language.data(),
                        reinterpret_cast<char*>(breaks.data()));
    
    return breaks;
}


std::vector<Linebreaker::BreakType> Linebreaker::findBreaks(const std::u32string& text,
                                                            const std::string& language)
{
    std::vector<Linebreaker::BreakType> breaks(text.size());

    set_linebreaks_utf32(reinterpret_cast<const utf32_t*>(text.data()),
                        text.size(),
                        language.data(),
                        reinterpret_cast<char*>(breaks.data()));
    
    return breaks;
}


Wordbreaker::Wordbreaker(const std::string& language):
    _language(language)
{
}


Wordbreaker::~Wordbreaker()
{
}


const std::string& Wordbreaker::language() const
{
    return _language;
}


std::vector<Wordbreaker::BreakType> Wordbreaker::findBreaks(const std::string& text) const
{
    return findBreaks(text, _language);
}


std::vector<Wordbreaker::BreakType> Wordbreaker::findBreaks(const std::u16string& text) const
{
    return findBreaks(text, _language);
}


std::vector<Wordbreaker::BreakType> Wordbreaker::findBreaks(const std::u32string& text) const
{
    return findBreaks(text, _language);
}


std::vector<Wordbreaker::BreakType> Wordbreaker::findBreaks(const std::string& text,
                                                            const std::string& language)
{
    std::vector<Wordbreaker::BreakType> breaks(text.size());

    set_wordbreaks_utf8(reinterpret_cast<const utf8_t*>(text.data()),
                        text.size(),
                        language.data(),
                        reinterpret_cast<char*>(breaks.data()));

    return breaks;
}


std::vector<Wordbreaker::BreakType> Wordbreaker::findBreaks(const std::u16string& text,
                                                            const std::string& language)
{
    std::vector<Wordbreaker::BreakType> breaks(text.size());

    set_wordbreaks_utf16(reinterpret_cast<const utf16_t*>(text.data()),
                         text.size(),
                         language.data(),
                         reinterpret_cast<char*>(breaks.data()));

    return breaks;
}


std::vector<Wordbreaker::BreakType> Wordbreaker::findBreaks(const std::u32string& text,
                                                            const std::string& language)
{
    std::vector<Wordbreaker::BreakType> breaks(text.size());
    
    set_wordbreaks_utf32(reinterpret_cast<const utf32_t*>(text.data()),
                         text.size(),
                         language.data(),
                         reinterpret_cast<char*>(breaks.data()));
    
    return breaks;
}


bool UTF8::isValid(const std::string& txt)
{
    try
    {
        return utf8::is_valid(txt.begin(), txt.end());
    }
    catch(const utf8::exception& utfcpp_ex)
    {
        ofLogError("UTF8::isValid") << utfcpp_ex.what();
        return false;
    }
}


bool UTF8::startsWithBOM(const std::string& txt)
{
    return utf8::starts_with_bom(txt.begin(), txt.end());
}


std::string UTF8::repair(const std::string& txt, char32_t replacement)
{
    std::string temp;

    try
    {
        if (replacement == -1)
        {
            utf8::replace_invalid(txt.begin(), txt.end(), std::back_inserter(temp));
        }
        else
        {
            utf8::replace_invalid(txt.begin(), txt.end(), std::back_inserter(temp), replacement);
        }
    }
    catch (const utf8::exception& utfcpp_ex)
    {
        ofLogError("UTF8::repair") << utfcpp_ex.what();
    }

    return temp;
}


std::string& UTF8::repairInPlace(std::string& txt, char32_t replacement)
{
    txt = repair(txt, replacement);
    return txt;
}


std::size_t UTF8::distance(const std::string& txt)
{
    try
    {
        return utf8::distance(txt.begin(), txt.end());
    }
    catch (const utf8::exception& utfcpp_ex)
    {
        ofLog(OF_LOG_ERROR, "ofUTF8::distance : " + ofToString(utfcpp_ex.what()));
        return 0;
    }
}


int UTF8::icompare(const std::string& utf8String0,
                   const std::string& utf8String1)
{
    return Poco::UTF8::icompare(utf8String0, utf8String1);
}


std::string UTF8::toUpper(const std::string& str)
{
    return Poco::UTF8::toUpper(str);
}


std::string& UTF8::toUpperInPlace(std::string& str)
{
    return Poco::UTF8::toUpperInPlace(str);
}


std::string UTF8::toLower(const std::string& str)
{
    return Poco::UTF8::toLower(str);
}


std::string& UTF8::toLowerInPlace(std::string& str)
{
    return Poco::UTF8::toLowerInPlace(str);
}


bool UTF32::isValid(char32_t unichar)
{
    return !((unichar > 0x0010ffffu) || (unichar >= 0xd800u && unichar <= 0xdfffu));
}


bool UTF32::isPrintable(char32_t unichar)
{
    Poco::Unicode::CharacterProperties props;
	Poco::Unicode::properties(unichar, props);
    
    return props.type != Poco::Unicode::UCP_CONTROL;
}


bool UTF32::isCntrl(char32_t unichar)
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


bool UTF32::isTitle(char32_t unichar)
{
    Poco::Unicode::CharacterProperties props;
	Poco::Unicode::properties(unichar, props);
    
    return props.type == Poco::Unicode::UCP_TITLE_CASE_LETTER;
}


bool UTF32::isSpace(char32_t unichar)
{
    return Poco::Unicode::isSpace(unichar);
}


bool UTF32::isDigit(char32_t unichar)
{
    return Poco::Unicode::isDigit(unichar);
}


bool UTF32::isPunct(char32_t unichar)
{
    return Poco::Unicode::isPunct(unichar);
}


bool UTF32::isAlpha(char32_t unichar)
{
    return Poco::Unicode::isAlpha(unichar);
}


bool UTF32::isAlphaNumeric(char32_t unichar)
{
    return isAlpha(unichar) || isDigit(unichar);
}


bool UTF32::isLower(char32_t unichar)
{
    return Poco::Unicode::isLower(unichar);
}


bool UTF32::isUpper(char32_t unichar)
{
    return Poco::Unicode::isUpper(unichar);
}


char32_t UTF32::toLower(char32_t unichar)
{
    return Poco::Unicode::toLower(unichar);
}


char32_t UTF32::toUpper(char32_t unichar)
{
    return Poco::Unicode::toUpper(unichar);
}


char32_t& UTF32::toLowerInPlace(char32_t& unichar)
{
    unichar = toLower(unichar); 
    return unichar;
}


char32_t& UTF32::toUpperInPlace(char32_t& unichar)
{
    unichar = toUpper(unichar); 
    return unichar;
}


std::u32string UTF32::toLower(std::u32string& unichar)
{
    std::u32string out;
    std::u32string::iterator it = unichar.begin();
    while(it != unichar.end()) {out.push_back(toLower(*(it++)));}
    return out;
}


std::u32string UTF32::toUpper(std::u32string& unichar)
{
    std::u32string out;
    std::u32string::iterator it = unichar.begin();
    while(it != unichar.end()) {out.push_back(toUpper(*(it++)));}
    return out;
}


std::u32string& UTF32::toLowerInPlace(std::u32string& unichar)
{
    std::u32string::iterator it = unichar.begin();
    while(it != unichar.end()) {toUpperInPlace(*(it++));}
    return unichar;
}


std::u32string& UTF32::toUpperInPlace(std::u32string& unichar)
{
    std::u32string::iterator it = unichar.begin();
    while(it != unichar.end()) {toLowerInPlace(*(it++));}
    return unichar;
}




    // Like any data, text on a computer is represented by bytes.
    // A byte is usually 8 bits and represents the smallest grouping
    // of bits that we generally work with.
    //
    // Text is representing in a computer by mapping glyphs (or other
    // (control characters), etc to a single integer >= 0.
    //
    // The mapping from glyphs to to numbers is called an encoding.
    // Many encodings have common mappings (such as ASCII and UNICODE).
    // While one encoding may map "ß" to one number, a differnt encoding
    // may represent the "ß" using a different number.
    //
    // Unicode is a character mapping that aims to be the standard mapping
    // between a glyph (or other control character) and an integer >= 0.
    //
    // For example:
    //  In Unicode, "ß" is represented by the the HEX number 0x00DF (or decimal
    //  number 223).
    //
    //  In Mac Roman Encoding, "ß" is represented by the the HEX number 0x00A7
    //  (or decimal number 167)
    //
    //  By contrast, Mac Roman Encoding represents "ﬂ" (a ligature) with
    //  the HEX number 0x00DF.  Further, Unicode represents "ﬂ" at HEX number
    //  0xFB02.
    //
    // The reason for these different encodings was because many of the older
    // systems wanted to ONLY use one byte to represent the most important
    // glyphs (and control characters) for their application.  On a modern
    // computer, it is no problem to use multiple bytes to represent large numbers,
    // but on limited hardware (think, thermal printers), the computational
    // overhead of interpreting multi-byte characters was/is more difficult
    // than simply agreeing on a common mapping up before reading or writing bytes.
    //
    // Thus, the first task is to make sure the character mapping between
    // a glyph (or other control character) is understood.  Generally,
    // the goal is to ultimately use a Unicode character map.
    //
    // In the following code, the "convert" function (backed by Poco::TextConverter)
    // is in charge of remapping one encoding to another.  But, not only
    // does it remap characters to new code points, it can also decide how the
    // bytes (groups of 8 bits) will be arranged in order to represent glyph
    // code points that are too big to fit inside a single byte.  For instance
    // the maximum number that can be represented by an unsigned (8-bit) byte is
    // 255.  The convert function is limited to storing each code point
    // as a series of unsigned chars (which is underneath the std::string object).
    //
    // Thus, even though UTF16 is usually represented using a _larger_ datatype
    // (i.e. wchar -- which can be similar to an unsigned short int), it
    // breaks up the UTF16 into a series of 8 bit bytes.
    //
    // UTF8, UTF16 and UTF32 are all ways to represent the numbers that represent
    // the unicode number for glyphs (and control characters).
    //
    // UTF8 uses variable length clusters of 8bit bytes to represent increasingly
    // larger unicode numbers.  The first byte in these clusters is either
    // interpreted directly (for code points betwen 0-127) or tells reveals
    // how many subsequent bytes will have to be read to get the full number.
    //
    // UTF16 uses varible length clusters of 16 bits units (2 bytes) to represent
    // increasingly larger unicode numbers.  Like UTF8, the first 16 bit unit
    // is used to reveal wheather a second 16 bit unit will have to be read
    // to get the full number.
    //
    // UTF16 is most easily represented by a std::wstring, which is backed by
    // an array of "wchar_t", which is a data type comprised of at least 2 bytes
    // and interpreted as a unit.  Alternatively, it can be represented in a
    // std::string as 2 or 4 unsigned chars (i.e. a bytes).  The convert function
    // below allows us to convert std::strings that use this encoding into
    // a more easily manipulated UTF8 4 byte format.
    //
    // Generally, it is easier to use the std::wstring to represent UTF16
    // sequences.
    //
    // UTF32 is a direct representation of a Unicode code point.  It is backed
    // by an unsigned int, which can represent very large values > 0.
    //
    // In this library, we attempt to differentiate between these different
    // schemes by explicitly creating aliases for different string types.
    // For instance, an std::string is simply an alias for std:string.  The
    // reason for this alias is simply to be clear what kind of encoding is
    // being used, since a string could have its bytes in any number of ways.
    //
    // An std::string is an alias for the std:wstring.
    //
    // An ofUTF32String is an alias for a basic_string<char32_t>, which is a
    // string string that is backed by an unsigned int.  Unlike UTF16, which
    // has its own dedicated string type (std::wstring), there is no
    // such 32bit Unicode String.  There will be in with c++0x.
    //
    // For more on that, check out this.
    // http://members.shaw.ca/akochoi/articles/unicode-processing-c++0x/index.html
    // in c++0x, the following is defined:
    // typedef string u8string;
    // typedef basic_string<unsigned int> u16string;
    // typedef basic_string<unsigned int> u32string;
    // since it isn't available (easily) yet, we'll just use our own
    // there will also be a coverter codecvt class th convert between these
    // rather than using POCO or UTF8CPP.  For now, we work around it.
    // POCO will support UTF32 functions soon too:
    // http://sourceforge.net/apps/trac/poco/milestone/Release%201.5.0
    //
    // Anyway, good luck!


    ////------------------------------------------------------------------
    //string TextConverter::convert(const ofBuffer& buffer, ofTextEncoding inputEncoding, ofTextEncoding outputEncoding) {
    //    return convert(buffer.getBinaryBuffer(), buffer.size(), inputEncoding, outputEncoding);
    //}
    //
    ////------------------------------------------------------------------
    //string TextConverter::convert(const void* source, int length,  ofTextEncoding inputEncoding, ofTextEncoding outputEncoding) {
    //    string output;
    //    Poco::TextEncoding& ie = getTextEncoding(inputEncoding);
    //    Poco::TextEncoding& oe = getTextEncoding(outputEncoding);
    //    Poco::TextConverter converter(ie,oe);
    //    converter.convert(source, length, output);
    //    return output;
    //}
    //
    ////------------------------------------------------------------------
    //string TextConverter::convert(const string& input, ofTextEncoding inputEncoding, ofTextEncoding outputEncoding) {
    //    // this returns a std::string -- which is just a sequence of bytes.
    //    // the way those bytes is interpreted is up to the user.
    //
    //    // pass through
    //    if(inputEncoding == outputEncoding) return input;
    //
    //    string output;
    //    Poco::TextEncoding& ie = getTextEncoding(inputEncoding);
    //    Poco::TextEncoding& oe = getTextEncoding(outputEncoding);
    //    Poco::TextConverter converter(ie,oe);
    //    converter.convert(input, output);
    //    return output;
    //}


    // to UTF8
    //------------------------------------------------------------------
    std::string TextConverter::toUTF8(const std::u16string& input)
    {
        std::string utf8result;

        try
        {
            utf8::utf16to8(input.begin(),input.end(), std::back_inserter(utf8result));
        }
        catch (const utf8::exception& utfcpp_ex)
        {
            ofLog(OF_LOG_ERROR, "TextConverter::toUTF8 : " + ofToString(utfcpp_ex.what()));
        }

        return utf8result;
    }


    std::string TextConverter::toUTF8(char32_t input)
    {
        std::string txt;

        try
        {
            utf8::append(input, std::back_inserter(txt));
        }
        catch (const utf8::exception& utfcpp_ex)
        {
            ofLog(OF_LOG_ERROR, "TextConverter::toUTF8 : " + ofToString(utfcpp_ex.what()));
        }
        return txt;
    }


    std::string TextConverter::toUTF8(const std::u32string& input)
    {
        std::string utf8result;

        try
        {
            utf8::utf32to8(input.begin(), input.end(), std::back_inserter(utf8result));
        }
        catch (const utf8::exception& utfcpp_ex)
        {
            ofLog(OF_LOG_ERROR, "TextConverter::toUTF8 : " + ofToString(utfcpp_ex.what()));
        }

        return utf8result;
    }


    std::u16string TextConverter::toUTF16(const std::string& input)
    {
        std::u16string utf16result;

        try
        {
            utf8::utf8to16(input.begin(),
                           input.end(),
                           std::back_inserter(utf16result));

        }
        catch (const utf8::exception& utfcpp_ex)
        {
            ofLog(OF_LOG_ERROR, "TextConverter::toUTF16 : " + ofToString(utfcpp_ex.what()));
        }

        return utf16result;
    }


    std::u16string TextConverter::toUTF16(char32_t input)
    {
        return toUTF16(toUTF8(input));
    }


    std::u16string TextConverter::toUTF16(const std::u32string& input)
    {
        return toUTF16(toUTF8(input));
    }


    std::u32string TextConverter::toUTF32(const std::string& input)
    {
        std::u32string utf32result;

        try
        {
            utf8::utf8to32(input.begin(),
                           input.end(),
                           std::back_inserter(utf32result));
        }
        catch(const utf8::exception& utfcpp_ex)
        {
            ofLog(OF_LOG_ERROR, "TextConverter::toUTF32 : " + ofToString(utfcpp_ex.what()));
        }

        return utf32result;
    }


    std::u32string TextConverter::toUTF32(const std::u16string& input)
    {
        return toUTF32(toUTF8(input));
    }


    //
    ////------------------------------------------------------------------
    //Poco::TextEncoding& TextConverter::getTextEncoding(ofTextEncoding enc) {
    //    if(enc == OF_TEXT_ENCODING_UTF8) {
    //        static Poco::UTF8Encoding utf8_enc;
    //        return utf8_enc;
    //    } else if(enc == OF_TEXT_ENCODING_UTF16) {
    //        static Poco::UTF16Encoding utf16_enc;
    //        return utf16_enc;
    //    } else if(enc == OF_TEXT_ENCODING_ASCII) {
    //        static Poco::ASCIIEncoding ascii_enc;
    //        return ascii_enc;
    //    } else if(enc == OF_TEXT_ENCODING_LATIN_1) {
    //        static Poco::Latin1Encoding latin1_enc;
    //        return latin1_enc;
    //    } else if(enc == OF_TEXT_ENCODING_LATIN_9) {
    //        static Poco::Latin9Encoding latin9_enc;
    //        return latin9_enc;
    //    } else if(enc == OF_TEXT_ENCODING_WINDOWS_1252) {
    //        static Poco::Windows1252Encoding windows1252_enc;
    //        return windows1252_enc;
    //    } else {
    //        ofLog(OF_LOG_WARNING, "TextConverter::getEncoding - unknown encoding, returning utf8.");
    //        static Poco::UTF8Encoding utf8_enc;
    //        return utf8_enc;
    //    }
    //}
    
    


} // namespace ofx
