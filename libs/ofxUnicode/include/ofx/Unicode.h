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


#pragma once


#include <string>
#include <vector>
#include "linebreak.h"
#include "linebreakdef.h"
#include "wordbreak.h"
#include "ofConstants.h"
#include "fribidi/fribidi-bidi.h"
#include "ucdn.h"

namespace ofx {


class Linebreaker
{
public:
    enum class BreakType: char
    {
        /// \brief Break is mandatory.
        MUST_BREAK = LINEBREAK_MUSTBREAK,
        /// \brief Break is allowed.
        ALLOW_BREAK = LINEBREAK_ALLOWBREAK,
        /// \brief No break is possible.
        NO_BREAK = LINEBREAK_NOBREAK,
        /// \brief A UTF-8/16 sequence is unfinished.
        INSIDE_CHAR = LINEBREAK_INSIDEACHAR
    };

    Linebreaker(const std::string& language = "en");

    ~Linebreaker();

    const std::string& language() const;

    std::vector<BreakType> findBreaks(const std::string& text) const;
    std::vector<BreakType> findBreaks(const std::u16string& text) const;
    std::vector<BreakType> findBreaks(const std::u32string& text) const;

    static std::vector<BreakType> findBreaks(const std::string& text,
                                             const std::string& language);

    static std::vector<BreakType> findBreaks(const std::u16string& text,
                                             const std::string& language);

    static std::vector<BreakType> findBreaks(const std::u32string& text,
                                             const std::string& language);

protected:
    std::string _language;
    
};


class Wordbreaker
{
public:
    enum class BreakType: char
    {
        /// \brief Break is allowed.
        ALLOW_BREAK = WORDBREAK_BREAK,
        /// \brief No break is allowed.
        NO_BREAK = WORDBREAK_NOBREAK,
        /// \brief A UTF-8/16 sequence is unfinished.
        INSIDE_CHAR = WORDBREAK_INSIDEACHAR
    };


    Wordbreaker(const std::string& language = "en");

    ~Wordbreaker();

    const std::string& language() const;

    std::vector<BreakType> findBreaks(const std::string& text) const;
    std::vector<BreakType> findBreaks(const std::u16string& text) const;
    std::vector<BreakType> findBreaks(const std::u32string& text) const;

    static std::vector<BreakType> findBreaks(const std::string& text,
                                             const std::string& language);

    static std::vector<BreakType> findBreaks(const std::u16string& text,
                                             const std::string& language);

    static std::vector<BreakType> findBreaks(const std::u32string& text,
                                             const std::string& language);

protected:
    std::string _language;
    
};


class UTF8
{
public:
    // check to see if a UTF8 string is valid
    static bool isValid(const std::string& txt);

    // check to see if a string starts with a UTF8 BOM (byte order mark)
    static bool startsWithBOM(const std::string& txt);

    // attempt to repair a broken UTF8 string
    static std::string repair(const std::string& txt, char32_t replacement = -1);

    static std::string& repairInPlace(std::string& txt, char32_t replacement = -1);

    // calculate the number of UTF8 chars (string.length() returns the number of bytes)
    static std::size_t distance(const std::string& txt);

    // case insensitive comparison of UTF8 strings
    static int icompare(const std::string& utf8String0, const std::string& utf8String1);

    // unicode-based case conversion
    static std::string toUpper(const std::string& str);
    static std::string& toUpperInPlace(std::string& str);
    static std::string toLower(const std::string& str);
    static std::string& toLowerInPlace(std::string& str);
    
};


class UTF32
{
public:
    /// \param utf32 A unicode character.
    /// \returns true iff is a valid unicode character.
    static bool isValid(char32_t utf32);

    static bool isPrintable(char32_t utf32); // is this a "printable" character?
                                                             // True if the unicode category is not CONTROL
                                                             // This does not guarantee that the character
                                                             // has a visible "glyph".
    
    // is this a "control" unicode character?
    // this is broadly defined to include unicode
    // CONTROL category, and other invisible glyphs
    // this is Not the opposite of isPrintable.
    static bool isControl(char32_t utf32);

    // is this a unicode "Titlecase" codepoint?
    static bool isTitle(char32_t utf32);
    static bool isSpace(char32_t utf32);
    static bool isDigit(char32_t utf32);
    static bool isPunct(char32_t utf32);
    static bool isAlpha(char32_t utf32);
    static bool isAlphaNumeric(char32_t utf32); // isAlpha || isDigit
    static bool isLower(char32_t utf32);
    static bool isUpper(char32_t utf32);

    // conversions
    static char32_t toLower(char32_t unichar);
    static char32_t toUpper(char32_t unichar);
    static char32_t& toLowerInPlace(char32_t& unichar);
    static char32_t& toUpperInPlace(char32_t& unichar);

    // unicode string based conversions
    static std::u32string toLower(std::u32string& unichar);
    static std::u32string toUpper(std::u32string& unichar);
    static std::u32string& toLowerInPlace(std::u32string& unichar);
    static std::u32string& toUpperInPlace(std::u32string& unichar);

};


class TextConverter
{
public:
    /// \brief Convert between character sets.
    /// \param input The input string corresponding to inputEncoding.
    /// \param output A string in which to write the output encoded with outputEncoding.
    /// \param inputEncoding The input encoding character set, e.g. ENCODING_ISO_8859_15.
    /// \param outputEncoding The output encoding character set, e.g. ENCODING_ISO_8859_15.
    /// \returns -1 if error.
    ///           0 if no error.
    ///          >0 For number of invalid byte sequences in source.
    static int convert(const std::string& input,
                       std::string& output,
                       const std::string& inputEncoding,
                       const std::string& outputEncoding);

    // to UTF8
    static std::string toUTF8(const std::u16string& input);
    static std::string toUTF8(char32_t input);
    static std::string toUTF8(const std::u32string& input);

    // to UTF16
    static std::u16string toUTF16(const std::string& input);
    static std::u16string toUTF16(char32_t input);
    static std::u16string toUTF16(const std::u32string& input);

    // to UTF32
    static std::u32string toUTF32(const std::string& input);
    static std::u32string toUTF32(const std::u16string& input);

    /// \brief 7-bit ASCII text encoding.
    /// \sa http://en.wikipedia.org/wiki/ASCII
    static const std::string ENCODING_ASCII;

    /// \brief Variable width encoding backward compatible w/ ASCII.
    /// \sa http://en.wikipedia.org/wiki/UTF-8
    static const std::string ENCODING_UTF8;

    /// \brief 16-bit multi-byte.
    /// \sa http://en.wikipedia.org/wiki/UTF-16
    static const std::string ENCODING_UTF16;

    /// \brief 32-bit multi-byte.
    /// \sa http://en.wikipedia.org/wiki/UTF-32
    static const std::string ENCODING_UTF32;

    /// \brief 8-bit single-byte.
    /// \sa  http://en.wikipedia.org/wiki/ISO/IEC_8859-1
    static const std::string ENCODING_ISO_8859_1;

    /// \brief 8-bit single-byte.
    /// \sa  http://en.wikipedia.org/wiki/ISO/IEC_8859-1
    static const std::string ENCODING_LATIN_1;

    /// \brief 8-bit single-byte.
    /// \sa https://en.wikipedia.org/wiki/ISO/IEC_8859-2
    static const std::string ENCODING_ISO_8859_2;

    /// \brief 8-bit single-byte.
    /// \sa https://en.wikipedia.org/wiki/ISO/IEC_8859-2
    static const std::string ENCODING_LATIN_2;

    /// \brief 8-bit single-byte. Western chars + €.
    /// \sa http://en.wikipedia.org/wiki/ISO/IEC_8859-15
    static const std::string ENCODING_ISO_8859_15;

    /// \brief 8-bit single-byte. Western chars + €.
    /// \sa http://en.wikipedia.org/wiki/ISO/IEC_8859-15
    static const std::string ENCODING_LATIN_9;

    /// \brief Windows Central and Eastern European.
    /// \sa http://en.wikipedia.org/wiki/Windows-1250
    static const std::string ENCODING_WINDOWS_1250;

    /// \brief Windows Cyrillic.
    /// \sa http://en.wikipedia.org/wiki/Windows-1251
    static const std::string ENCODING_WINDOWS_1251;

    /// \brief Superset of Latin 1 (ISO 8859-1)
    /// \sa http://en.wikipedia.org/wiki/Windows-1252
    static const std::string ENCODING_WINDOWS_1252;

};


} // namespace ofx

