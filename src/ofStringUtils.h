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

#include "ofMain.h"
#include "Poco/String.h"
#include "Poco/UTF8String.h"
#include <set>

//#include "alphanum.hpp"

// todo integrate with ofxunicode make all default to UTF8 based 

int ofStringCharAt(const string& s0, unsigned int pos);

//ofxUnicode ofxCharCodeAt(const string& s0, unsigned int pos);

int ofStringCompareAlphaNum(const string& s0, const string& s1);

int ofStringLexographicCompare(const string& s0, const string& s1, bool ignoreCase = false);

int ofStringCompare(const string& s0, const string& s1, bool ignoreCase = false);

int ofStringCompareIgnoreCase(const string& s0, const string& s1);

bool ofStringEquals(const string& s0, const string& s1, bool ignoreCase = false);
bool ofStringEqualsIgnoreCase(const string& s0, const string& s1);
//
//bool ofStringEndsWith(const string& input, const string& endsWith, bool ignoreCase = false);
//bool ofStringEndsWithIgnoreCase(const string& input, const string& endsWith);
//
//bool ofStringEndsWithAny(const string& input, const vector<string>& endsWith, bool ignoreCase = false);
//bool ofStringEndsWithAnyIgnoreCase(const string& input, const vector<string>& endsWith);
//
//bool ofStringStartsWith(const string& input, const string& endsWith, bool ignoreCase = false);
//bool ofStringStartsWithIgnoreCase(const string& input, const string& endsWith);
//
//bool ofStringStartsWithAny(const string& input, const vector<string>& endsWith, bool ignoreCase = false);
//bool ofStringStartsWithAnyIgnoreCase(const string& input, const vector<string>& endsWith);
//
//
//bool ofStringContains(const string& haystack, const string& needle);
//
//int ofStringIndexOf(const string& input, unsigned char utf8Char, int fromIndex, bool ignoreCase = false);
//int ofStringIndexOfIgnoreCase(const string& input, unsigned char utf8Char, int fromIndex);
//
//int ofStringLastIndexOf(unsigned char utf8Char, int fromIndex, bool ignoreCase = false);
//int ofStringLastIndexOfIgnoreCase(unsigned char utf8Char, int fromIndex);
//
//int ofStringIndexOfExcept(const string& input, unsigned char utf8Char, int fromIndex, bool ignoreCase = false);
//int ofStringIndexOfExceptIgnoreCase(const string& input, unsigned char utf8Char, int fromIndex);
//
//int ofStringLastIndexOfExcept(const string& input, unsigned char utf8Char, int fromIndex, bool ignoreCase = false);
//int ofStringLastIndexOfExceptIgnoreCase(const string& input, unsigned char utf8Char, int fromIndex);
//
//string ofStringPadLeft(const string& input, int numToPad, const string& padValue = "");
//string ofStringPadLeftInPlace(string& input, int numToPad, const string& padValue = "");
//
//string ofStringPadRight(const string& input, int numToPad, const string& padValue = "");
//string ofStringPadRightInPlace(string& input, int numToPad, const string& padValue = "");
//
//string ofStringPad(const string& input, int numToPad, const string& padValue = "");
//string ofStringPadInPlace(string& input, int numToPad, const string& padValue = "");
//
//string ofStringCenter(const string& input, int maxChars, const string& padValue = "");
//string ofStringCenterInPlace(string& input, int maxChars, const string& padValue = "");
//
//string ofStringRepeat(const string& valueToRepeat, int numTimes, const string& separator = "" );
//
//string ofStringChop(const string& input);
//string ofStringChopInPlace(string& input);
//
//string ofStringChomp(const string& input);
//string ofStringChompInPlace(string& input);
//
//string ofStringChomp(const string& input, const string& delimiter);
//string ofStringChompInPlace(string& input, const string& delimiter);
//
//string ofStringOverlay(const string& input, const string& overlayString, int start, int stop);
//string ofStringOverlayInPlace(const string& input, const string& overlayString, int start, int stop);
//
//
//int ofStringCountMatches(const string& input, const string& regex);
//
////bool isAlpha
////bool isNumeric
////bool isWhitespace
////bool isAsciiPrintable
//
////http://commons.apache.org/lang/api-2.5/org/apache/commons/lang/StringUtils.html
//bool isStringEmpty(const string& input);
//bool isStringBlank(const string& input);
//
//string ofStringJoin(const vector<string>& strings, const string& delimiter);
//string ofStringJoin(const set<string>& strings, const string& delimiter);
//
//string ofStringRemoveWhitespace(const string& input);
//string ofStringRemoveWhitespaceInPlace(string& input);
//
//string ofStringRemove(const string& input, const string& regex, const string& replacement);
//string ofStringRemoveInPlace(string& input, string& regex, const string& replacement);
//
//string ofStringRemove(const string& input, const string& regex, const string& replacement);
//string ofStringRemoveInPlace(string& input, string& regex, const string& replacement);
//
//string ofStringRemoveStartNth(const string& input, const string& regex, const string& replacement);
//string ofStringRemoveStartNthInPlace(string& input, string& regex, const string& replacement);
//
//string ofStringRemoveStartIgnoreCase(const string& input, const string& regex, const string& replacement);
//string ofStringRemoveStartIgnoreCaseInPlace(string& input, string& regex, const string& replacement);
//
//string ofStringRemoveEnd(const string& input, const string& regex, const string& replacement);
//string ofStringRemoveEndInPlace(string& input, string& regex, const string& replacement);
//
//string ofStringRemoveEndIgnoreCase(const string& input, const string& regex, const string& replacement);
//string ofStringRemoveEndIgnoreCaseInPlace(string& input, string& regex, const string& replacement);
//
//
//string ofStringReplace(const string& input, const string& regex, const string& replacement);
//string ofStringReplaceInPlace(string& input, string& regex, const string& replacement);
//
//string ofStringReplaceOnce(const string& input, const string& regex, const string& replacement);
//string ofStringReplaceOnceInPlace(string& input, string& regex, const string& replacement);
//
//string ofStringReplaceAll(const string& input, const string& regex, const string& replacement);
//string ofStringReplaceAllInPlace(string& input, const string& regex, const string& replacement);
//string ofStringReplaceFirst(const string& input, const string& regex, const string& replacement);
//string ofStringReplaceFirstInPlace(string& input, const string& regex, const string& replacement);
//
//string ofStringReplaceEach(const string& input, const vector<string>& searchList, const vector<string>& replacementList );
//string ofStringReplaceEachInPlace(string& input, const vector<string>& searchList, const vector<string>& replacementList );
//
//string ofStringReplaceRepeatedly(const string& input, const vector<string>& searchList, const vector<string>& replacementList );
//string ofStringReplaceRepeatedlyInPlace(string& input, const vector<string>& searchList, const vector<string>& replacementList );
//
//
//string ofxSubstring(const string& input, int beginIndex);
//string ofxSubstring(const string& input, int beginIndex, int endIndex);
//
//string ofxSubstringBefore(const string& input, const string& seperator);
//string ofxSubstringAfter(const string& input, const string& seperator);
//
//string ofxSubstringBeforeLast(const string& input, const string& seperator);
//string ofxSubstringAfterLast(const string& input, const string& seperator);
//
//string ofxSubstringBetween(const string& input, const string& seperator);
//string ofxSubstringBetween(const string& input, const string& open, const string& close);
//vector<string> ofxSubstringsBetween(const string& input, const string& open, const string& close);
//
//
//
//bool ofStringIsAllUpperCase(const string& input);
//bool ofStringIsAllLowerCase(const string& input);
//
//// TODO: add support for locales with ofxLocale
//string ofStringToUpperCase(const string& input);
//string ofStringToUpperCaseInPlace(string& input);
//
////http://commons.apache.org/lang/api-3.0/org/apache/commons/lang3/text/WordUtils.html#capitalize(java.lang.String)
//
//string ofxCapitalize(const string& input, const string& delimiters = "");
//string ofxCapitalizeInPlace(string& input, const string& delimiters = "");
//string ofxCapitalizeFully(const string& input, const string& delimiters = "");
//string ofxCapitalizeFullyInPlace(string& input, const string& delimiters = "");
//string ofxUncapitalize(const string& input, const string& delimiters = "");
//string ofxUncapitalizeInPlace(string& input, const string& delimiters = "");
//string ofxUncapitalizeFully(const string& input, const string& delimiters = "");
//string ofxUncapitalizeFullyInPlace(string& input, const string& delimiters = "");
//
//string ofStringSwapCase(const string& input);
//string ofStringSwapCaseInPlace(string& input);
//
//string ofStringInitials(const string& input);
//string ofStringInitialsInPlace(string& input);
//
//string ofStringTrimLeft(const string& input);
//string ofStringTrimLeftInPlace(string& input);
//
//string ofStringTrimRight(const string& input);
//string ofStringTrimRightInPlace(string& input);
//
//string ofStringTrim(const string& input);
//string ofStringTrimInPlace(string& input);
//
//string ofStringReverse(const string& input);
//string ofStringReverseInPlace(string& input);
//
////http://commons.apache.org/lang/api-2.5/org/apache/commons/lang/StringUtils.html#reverseDelimited(java.lang.String, char)
//string ofStringReverseDelimited(const string& input, const string& delimiter);
//string ofStringReverseDelimitedInPlace(string& input, const string& delimiter);
//
//string ofStringDefaultIfEmpty(const string& input, const string& defaultString);
//
//string ofStringAbbreviate(const string& input, int maxChars);
//string ofStringAbbreviateInPlace(string& input, int maxChars);
//
//string ofStringAbbreviate(const string& input, int offset, int maxChars);
//string ofStringAbbreviateInPlace(string& input, int offset, int maxChars);
//
////http://commons.apache.org/lang/api-2.5/org/apache/commons/lang/StringUtils.html#reverseDelimited(java.lang.String, char)string ofStringAbbreviateMiddle(const string& input, const string& middleString, int maxChars);
//string ofStringAbbreviateMiddleInPlace(string& input, const string& middleString, int maxChars);
//
//string ofStringDifference(const string& s0, const string& s1);
//int ofStringIndexOfDifference(const string& s0, const string& s1);
//int ofStringIndexOfDifference(const vector<string>& strings);
//
//string ofStringGetCommonPrefix(const vector<string>& strings);
//
//int ofStringGetLevenshteinDistance(const string& s0, const string& s1);
//
//vector<string> ofStringSplit(const string& regex, int limit = -1);
//
//vector<string> ofStringSplitByCharacterType(const string& input);
//vector<string> ofStringSplitByCharacterCamelCase(const string& input);
//
//vector<string> ofStringSplitPreserveAllTokens(const string& input, const string& regexSeperator, int max = -1);
//vector<string> ofStringSplitByWholeSeperator(const string& input, const string& regexSeperator, int max = -1);
//vector<string> ofStringSplitByWholeSeperatorPreserveAllTokens(const string& input, const string& regexSeperator, int max = -1);
//
//string ofStringWrap(const string& input, int nCharsWidth);
//
//string ofxEscapeString(const string& input);
//string ofxEscapeStringInPlace(string& input);
//
//string ofxUnescapeString(const string& input);
//string ofxUnescapeStringInPlace(string& input);
//
//string ofxURLEncodeString(const string& input);
//string ofxURLEncodeStringInPlace(string& input);
//
//string ofxURLUnencodeString(const string& input);
//string ofxURLUnecodeStringInPlace(string& input);


