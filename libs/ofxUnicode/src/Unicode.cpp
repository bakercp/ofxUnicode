//
// Copyright (c) 2012 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/Unicode.h"
#include "ofUtils.h"
#include "ofLog.h"
#include "utf8proc.h"


namespace ofx {


//  http://unicode.org/Public/MAPPINGS/VENDORS/MICSFT/WINDOWS/CP1250.TXT // win
//  http://unicode.org/Public/MAPPINGS/VENDORS/APPLE/ROMAN.TXT           // mac
//  http://unicode.org/Public/MAPPINGS/ISO8859/8859-1.TXT                // linux


const std::u32string Unicode::STANDARD_CHARSET({
    0x0080, 0x0081, 0x0082, 0x0083, 0x0084, 0x0085, 0x0086, 0x0087,
    0x0088, 0x0089, 0x008A, 0x008B, 0x008C, 0x008D, 0x008E, 0x008F,
    0x0090, 0x0091, 0x0092, 0x0093, 0x0094, 0x0095, 0x0096, 0x0097,
    0x0098, 0x0099, 0x009A, 0x009B, 0x009C, 0x009D, 0x009E, 0x009F,
    0x00A0, 0x00A1, 0x00A2, 0x00A3, 0x00A4, 0x00A5, 0x00A6, 0x00A7,
    0x00A8, 0x00A9, 0x00AA, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x00AF,
    0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x00B4, 0x00B5, 0x00B6, 0x00B7,
    0x00B8, 0x00B9, 0x00BA, 0x00BB, 0x00BC, 0x00BD, 0x00BE, 0x00BF,
    0x00C0, 0x00C1, 0x00C2, 0x00C3, 0x00C4, 0x00C5, 0x00C6, 0x00C7,
    0x00C8, 0x00C9, 0x00CA, 0x00CB, 0x00CC, 0x00CD, 0x00CE, 0x00CF,
    0x00D0, 0x00D1, 0x00D2, 0x00D3, 0x00D4, 0x00D5, 0x00D6, 0x00D7,
    0x00D8, 0x00D9, 0x00DA, 0x00DB, 0x00DC, 0x00DD, 0x00DE, 0x00DF,
    0x00E0, 0x00E1, 0x00E2, 0x00E3, 0x00E4, 0x00E5, 0x00E6, 0x00E7,
    0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00EC, 0x00ED, 0x00EE, 0x00EF,
    0x00F0, 0x00F1, 0x00F2, 0x00F3, 0x00F4, 0x00F5, 0x00F6, 0x00F7,
    0x00F8, 0x00F9, 0x00FA, 0x00FB, 0x00FC, 0x00FD, 0x00FE, 0x00FF,
    0x0102, 0x0103, 0x0104, 0x0105, 0x0106, 0x0107, 0x010C, 0x010D,
    0x010E, 0x010F, 0x0110, 0x0111, 0x0118, 0x0119, 0x011A, 0x011B,
    0x0131, 0x0139, 0x013A, 0x013D, 0x013E, 0x0141, 0x0142, 0x0143,
    0x0144, 0x0147, 0x0148, 0x0150, 0x0151, 0x0152, 0x0153, 0x0154,
    0x0155, 0x0158, 0x0159, 0x015A, 0x015B, 0x015E, 0x015F, 0x0160,
    0x0161, 0x0162, 0x0163, 0x0164, 0x0165, 0x016E, 0x016F, 0x0170,
    0x0171, 0x0178, 0x0179, 0x017A, 0x017B, 0x017C, 0x017D, 0x017E,
    0x0192, 0x02C6, 0x02C7, 0x02D8, 0x02D9, 0x02DA, 0x02DB, 0x02DC,
    0x02DD, 0x03A9, 0x03C0, 0x2013, 0x2014, 0x2018, 0x2019, 0x201A,
    0x201C, 0x201D, 0x201E, 0x2020, 0x2021, 0x2022, 0x2026, 0x2030,
    0x2039, 0x203A, 0x2044, 0x20AC, 0x2122, 0x2202, 0x2206, 0x220F,
    0x2211, 0x221A, 0x221E, 0x222B, 0x2248, 0x2260, 0x2264, 0x2265,
    0x25CA, 0xF8FF, 0xFB01, 0xFB02
});



std::size_t Unicode::Block::size() const
{
    return end - begin + 1;
}


std::u32string Unicode::Block::charset() const
{
    std::u32string s(size(), 0);
    std::iota(s.begin(), s.end(), begin);
    return s;
}


const Unicode::Block Unicode::BASIC_LATIN {0x0000, 0x007F, "BASIC_LATIN"};
const Unicode::Block Unicode::LATIN_1_SUPPLEMENT {0x0080, 0x00FF, "LATIN_1_SUPPLEMENT"};
const Unicode::Block Unicode::LATIN_EXTENDED_A {0x0100, 0x017F, "LATIN_EXTENDED_A"};
const Unicode::Block Unicode::LATIN_EXTENDED_B {0x0180, 0x024F, "LATIN_EXTENDED_B"};
const Unicode::Block Unicode::IPA_EXTENSIONS {0x0250, 0x02AF, "IPA_EXTENSIONS"};
const Unicode::Block Unicode::SPACING_MODIFIER_LETTERS {0x02B0, 0x02FF, "SPACING_MODIFIER_LETTERS"};
const Unicode::Block Unicode::COMBINING_DIACRITICAL_MARKS {0x0300, 0x036F, "COMBINING_DIACRITICAL_MARKS"};
const Unicode::Block Unicode::GREEK_AND_COPTIC {0x0370, 0x03FF, "GREEK_AND_COPTIC"};
const Unicode::Block Unicode::CYRILLIC {0x0400, 0x04FF, "CYRILLIC"};
const Unicode::Block Unicode::CYRILLIC_SUPPLEMENT {0x0500, 0x052F, "CYRILLIC_SUPPLEMENT"};
const Unicode::Block Unicode::ARMENIAN {0x0530, 0x058F, "ARMENIAN"};
const Unicode::Block Unicode::HEBREW {0x0590, 0x05FF, "HEBREW"};
const Unicode::Block Unicode::ARABIC {0x0600, 0x06FF, "ARABIC"};
const Unicode::Block Unicode::SYRIAC {0x0700, 0x074F, "SYRIAC"};
const Unicode::Block Unicode::ARABIC_SUPPLEMENT {0x0750, 0x077F, "ARABIC_SUPPLEMENT"};
const Unicode::Block Unicode::THAANA {0x0780, 0x07BF, "THAANA"};
const Unicode::Block Unicode::NKO {0x07C0, 0x07FF, "NKO"};
const Unicode::Block Unicode::SAMARITAN {0x0800, 0x083F, "SAMARITAN"};
const Unicode::Block Unicode::MANDAIC {0x0840, 0x085F, "MANDAIC"};
const Unicode::Block Unicode::SYRIAC_SUPPLEMENT {0x0860, 0x086F, "SYRIAC_SUPPLEMENT"};
const Unicode::Block Unicode::ARABIC_EXTENDED_A {0x08A0, 0x08FF, "ARABIC_EXTENDED_A"};
const Unicode::Block Unicode::DEVANAGARI {0x0900, 0x097F, "DEVANAGARI"};
const Unicode::Block Unicode::BENGALI {0x0980, 0x09FF, "BENGALI"};
const Unicode::Block Unicode::GURMUKHI {0x0A00, 0x0A7F, "GURMUKHI"};
const Unicode::Block Unicode::GUJARATI {0x0A80, 0x0AFF, "GUJARATI"};
const Unicode::Block Unicode::ORIYA {0x0B00, 0x0B7F, "ORIYA"};
const Unicode::Block Unicode::TAMIL {0x0B80, 0x0BFF, "TAMIL"};
const Unicode::Block Unicode::TELUGU {0x0C00, 0x0C7F, "TELUGU"};
const Unicode::Block Unicode::KANNADA {0x0C80, 0x0CFF, "KANNADA"};
const Unicode::Block Unicode::MALAYALAM {0x0D00, 0x0D7F, "MALAYALAM"};
const Unicode::Block Unicode::SINHALA {0x0D80, 0x0DFF, "SINHALA"};
const Unicode::Block Unicode::THAI {0x0E00, 0x0E7F, "THAI"};
const Unicode::Block Unicode::LAO {0x0E80, 0x0EFF, "LAO"};
const Unicode::Block Unicode::TIBETAN {0x0F00, 0x0FFF, "TIBETAN"};
const Unicode::Block Unicode::MYANMAR {0x1000, 0x109F, "MYANMAR"};
const Unicode::Block Unicode::GEORGIAN {0x10A0, 0x10FF, "GEORGIAN"};
const Unicode::Block Unicode::HANGUL_JAMO {0x1100, 0x11FF, "HANGUL_JAMO"};
const Unicode::Block Unicode::ETHIOPIC {0x1200, 0x137F, "ETHIOPIC"};
const Unicode::Block Unicode::ETHIOPIC_SUPPLEMENT {0x1380, 0x139F, "ETHIOPIC_SUPPLEMENT"};
const Unicode::Block Unicode::CHEROKEE {0x13A0, 0x13FF, "CHEROKEE"};
const Unicode::Block Unicode::UNIFIED_CANADIAN_ABORIGINAL_SYLLABICS {0x1400, 0x167F, "UNIFIED_CANADIAN_ABORIGINAL_SYLLABICS"};
const Unicode::Block Unicode::OGHAM {0x1680, 0x169F, "OGHAM"};
const Unicode::Block Unicode::RUNIC {0x16A0, 0x16FF, "RUNIC"};
const Unicode::Block Unicode::TAGALOG {0x1700, 0x171F, "TAGALOG"};
const Unicode::Block Unicode::HANUNOO {0x1720, 0x173F, "HANUNOO"};
const Unicode::Block Unicode::BUHID {0x1740, 0x175F, "BUHID"};
const Unicode::Block Unicode::TAGBANWA {0x1760, 0x177F, "TAGBANWA"};
const Unicode::Block Unicode::KHMER {0x1780, 0x17FF, "KHMER"};
const Unicode::Block Unicode::MONGOLIAN {0x1800, 0x18AF, "MONGOLIAN"};
const Unicode::Block Unicode::UNIFIED_CANADIAN_ABORIGINAL_SYLLABICS_EXTENDED {0x18B0, 0x18FF, "UNIFIED_CANADIAN_ABORIGINAL_SYLLABICS_EXTENDED"};
const Unicode::Block Unicode::LIMBU {0x1900, 0x194F, "LIMBU"};
const Unicode::Block Unicode::TAI_LE {0x1950, 0x197F, "TAI_LE"};
const Unicode::Block Unicode::NEW_TAI_LUE {0x1980, 0x19DF, "NEW_TAI_LUE"};
const Unicode::Block Unicode::KHMER_SYMBOLS {0x19E0, 0x19FF, "KHMER_SYMBOLS"};
const Unicode::Block Unicode::BUGINESE {0x1A00, 0x1A1F, "BUGINESE"};
const Unicode::Block Unicode::TAI_THAM {0x1A20, 0x1AAF, "TAI_THAM"};
const Unicode::Block Unicode::COMBINING_DIACRITICAL_MARKS_EXTENDED {0x1AB0, 0x1AFF, "COMBINING_DIACRITICAL_MARKS_EXTENDED"};
const Unicode::Block Unicode::BALINESE {0x1B00, 0x1B7F, "BALINESE"};
const Unicode::Block Unicode::SUNDANESE {0x1B80, 0x1BBF, "SUNDANESE"};
const Unicode::Block Unicode::BATAK {0x1BC0, 0x1BFF, "BATAK"};
const Unicode::Block Unicode::LEPCHA {0x1C00, 0x1C4F, "LEPCHA"};
const Unicode::Block Unicode::OL_CHIKI {0x1C50, 0x1C7F, "OL_CHIKI"};
const Unicode::Block Unicode::CYRILLIC_EXTENDED_C {0x1C80, 0x1C8F, "CYRILLIC_EXTENDED_C"};
const Unicode::Block Unicode::GEORGIAN_EXTENDED {0x1C90, 0x1CBF, "GEORGIAN_EXTENDED"};
const Unicode::Block Unicode::SUNDANESE_SUPPLEMENT {0x1CC0, 0x1CCF, "SUNDANESE_SUPPLEMENT"};
const Unicode::Block Unicode::VEDIC_EXTENSIONS {0x1CD0, 0x1CFF, "VEDIC_EXTENSIONS"};
const Unicode::Block Unicode::PHONETIC_EXTENSIONS {0x1D00, 0x1D7F, "PHONETIC_EXTENSIONS"};
const Unicode::Block Unicode::PHONETIC_EXTENSIONS_SUPPLEMENT {0x1D80, 0x1DBF, "PHONETIC_EXTENSIONS_SUPPLEMENT"};
const Unicode::Block Unicode::COMBINING_DIACRITICAL_MARKS_SUPPLEMENT {0x1DC0, 0x1DFF, "COMBINING_DIACRITICAL_MARKS_SUPPLEMENT"};
const Unicode::Block Unicode::LATIN_EXTENDED_ADDITIONAL {0x1E00, 0x1EFF, "LATIN_EXTENDED_ADDITIONAL"};
const Unicode::Block Unicode::GREEK_EXTENDED {0x1F00, 0x1FFF, "GREEK_EXTENDED"};
const Unicode::Block Unicode::GENERAL_PUNCTUATION {0x2000, 0x206F, "GENERAL_PUNCTUATION"};
const Unicode::Block Unicode::SUPERSCRIPTS_AND_SUBSCRIPTS {0x2070, 0x209F, "SUPERSCRIPTS_AND_SUBSCRIPTS"};
const Unicode::Block Unicode::CURRENCY_SYMBOLS {0x20A0, 0x20CF, "CURRENCY_SYMBOLS"};
const Unicode::Block Unicode::COMBINING_DIACRITICAL_MARKS_FOR_SYMBOLS {0x20D0, 0x20FF, "COMBINING_DIACRITICAL_MARKS_FOR_SYMBOLS"};
const Unicode::Block Unicode::LETTERLIKE_SYMBOLS {0x2100, 0x214F, "LETTERLIKE_SYMBOLS"};
const Unicode::Block Unicode::NUMBER_FORMS {0x2150, 0x218F, "NUMBER_FORMS"};
const Unicode::Block Unicode::ARROWS {0x2190, 0x21FF, "ARROWS"};
const Unicode::Block Unicode::MATHEMATICAL_OPERATORS {0x2200, 0x22FF, "MATHEMATICAL_OPERATORS"};
const Unicode::Block Unicode::MISCELLANEOUS_TECHNICAL {0x2300, 0x23FF, "MISCELLANEOUS_TECHNICAL"};
const Unicode::Block Unicode::CONTROL_PICTURES {0x2400, 0x243F, "CONTROL_PICTURES"};
const Unicode::Block Unicode::OPTICAL_CHARACTER_RECOGNITION {0x2440, 0x245F, "OPTICAL_CHARACTER_RECOGNITION"};
const Unicode::Block Unicode::ENCLOSED_ALPHANUMERICS {0x2460, 0x24FF, "ENCLOSED_ALPHANUMERICS"};
const Unicode::Block Unicode::BOX_DRAWING {0x2500, 0x257F, "BOX_DRAWING"};
const Unicode::Block Unicode::BLOCK_ELEMENTS {0x2580, 0x259F, "BLOCK_ELEMENTS"};
const Unicode::Block Unicode::GEOMETRIC_SHAPES {0x25A0, 0x25FF, "GEOMETRIC_SHAPES"};
const Unicode::Block Unicode::MISCELLANEOUS_SYMBOLS {0x2600, 0x26FF, "MISCELLANEOUS_SYMBOLS"};
const Unicode::Block Unicode::DINGBATS {0x2700, 0x27BF, "DINGBATS"};
const Unicode::Block Unicode::MISCELLANEOUS_MATHEMATICAL_SYMBOLS_A {0x27C0, 0x27EF, "MISCELLANEOUS_MATHEMATICAL_SYMBOLS_A"};
const Unicode::Block Unicode::SUPPLEMENTAL_ARROWS_A {0x27F0, 0x27FF, "SUPPLEMENTAL_ARROWS_A"};
const Unicode::Block Unicode::BRAILLE_PATTERNS {0x2800, 0x28FF, "BRAILLE_PATTERNS"};
const Unicode::Block Unicode::SUPPLEMENTAL_ARROWS_B {0x2900, 0x297F, "SUPPLEMENTAL_ARROWS_B"};
const Unicode::Block Unicode::MISCELLANEOUS_MATHEMATICAL_SYMBOLS_B {0x2980, 0x29FF, "MISCELLANEOUS_MATHEMATICAL_SYMBOLS_B"};
const Unicode::Block Unicode::SUPPLEMENTAL_MATHEMATICAL_OPERATORS {0x2A00, 0x2AFF, "SUPPLEMENTAL_MATHEMATICAL_OPERATORS"};
const Unicode::Block Unicode::MISCELLANEOUS_SYMBOLS_AND_ARROWS {0x2B00, 0x2BFF, "MISCELLANEOUS_SYMBOLS_AND_ARROWS"};
const Unicode::Block Unicode::GLAGOLITIC {0x2C00, 0x2C5F, "GLAGOLITIC"};
const Unicode::Block Unicode::LATIN_EXTENDED_C {0x2C60, 0x2C7F, "LATIN_EXTENDED_C"};
const Unicode::Block Unicode::COPTIC {0x2C80, 0x2CFF, "COPTIC"};
const Unicode::Block Unicode::GEORGIAN_SUPPLEMENT {0x2D00, 0x2D2F, "GEORGIAN_SUPPLEMENT"};
const Unicode::Block Unicode::TIFINAGH {0x2D30, 0x2D7F, "TIFINAGH"};
const Unicode::Block Unicode::ETHIOPIC_EXTENDED {0x2D80, 0x2DDF, "ETHIOPIC_EXTENDED"};
const Unicode::Block Unicode::CYRILLIC_EXTENDED_A {0x2DE0, 0x2DFF, "CYRILLIC_EXTENDED_A"};
const Unicode::Block Unicode::SUPPLEMENTAL_PUNCTUATION {0x2E00, 0x2E7F, "SUPPLEMENTAL_PUNCTUATION"};
const Unicode::Block Unicode::CJK_RADICALS_SUPPLEMENT {0x2E80, 0x2EFF, "CJK_RADICALS_SUPPLEMENT"};
const Unicode::Block Unicode::KANGXI_RADICALS {0x2F00, 0x2FDF, "KANGXI_RADICALS"};
const Unicode::Block Unicode::IDEOGRAPHIC_DESCRIPTION_CHARACTERS {0x2FF0, 0x2FFF, "IDEOGRAPHIC_DESCRIPTION_CHARACTERS"};
const Unicode::Block Unicode::CJK_SYMBOLS_AND_PUNCTUATION {0x3000, 0x303F, "CJK_SYMBOLS_AND_PUNCTUATION"};
const Unicode::Block Unicode::HIRAGANA {0x3040, 0x309F, "HIRAGANA"};
const Unicode::Block Unicode::KATAKANA {0x30A0, 0x30FF, "KATAKANA"};
const Unicode::Block Unicode::BOPOMOFO {0x3100, 0x312F, "BOPOMOFO"};
const Unicode::Block Unicode::HANGUL_COMPATIBILITY_JAMO {0x3130, 0x318F, "HANGUL_COMPATIBILITY_JAMO"};
const Unicode::Block Unicode::KANBUN {0x3190, 0x319F, "KANBUN"};
const Unicode::Block Unicode::BOPOMOFO_EXTENDED {0x31A0, 0x31BF, "BOPOMOFO_EXTENDED"};
const Unicode::Block Unicode::CJK_STROKES {0x31C0, 0x31EF, "CJK_STROKES"};
const Unicode::Block Unicode::KATAKANA_PHONETIC_EXTENSIONS {0x31F0, 0x31FF, "KATAKANA_PHONETIC_EXTENSIONS"};
const Unicode::Block Unicode::ENCLOSED_CJK_LETTERS_AND_MONTHS {0x3200, 0x32FF, "ENCLOSED_CJK_LETTERS_AND_MONTHS"};
const Unicode::Block Unicode::CJK_COMPATIBILITY {0x3300, 0x33FF, "CJK_COMPATIBILITY"};
const Unicode::Block Unicode::CJK_UNIFIED_IDEOGRAPHS_EXTENSION_A {0x3400, 0x4DBF, "CJK_UNIFIED_IDEOGRAPHS_EXTENSION_A"};
const Unicode::Block Unicode::YIJING_HEXAGRAM_SYMBOLS {0x4DC0, 0x4DFF, "YIJING_HEXAGRAM_SYMBOLS"};
const Unicode::Block Unicode::CJK_UNIFIED_IDEOGRAPHS {0x4E00, 0x9FFF, "CJK_UNIFIED_IDEOGRAPHS"};
const Unicode::Block Unicode::YI_SYLLABLES {0xA000, 0xA48F, "YI_SYLLABLES"};
const Unicode::Block Unicode::YI_RADICALS {0xA490, 0xA4CF, "YI_RADICALS"};
const Unicode::Block Unicode::LISU {0xA4D0, 0xA4FF, "LISU"};
const Unicode::Block Unicode::VAI {0xA500, 0xA63F, "VAI"};
const Unicode::Block Unicode::CYRILLIC_EXTENDED_B {0xA640, 0xA69F, "CYRILLIC_EXTENDED_B"};
const Unicode::Block Unicode::BAMUM {0xA6A0, 0xA6FF, "BAMUM"};
const Unicode::Block Unicode::MODIFIER_TONE_LETTERS {0xA700, 0xA71F, "MODIFIER_TONE_LETTERS"};
const Unicode::Block Unicode::LATIN_EXTENDED_D {0xA720, 0xA7FF, "LATIN_EXTENDED_D"};
const Unicode::Block Unicode::SYLOTI_NAGRI {0xA800, 0xA82F, "SYLOTI_NAGRI"};
const Unicode::Block Unicode::COMMON_INDIC_NUMBER_FORMS {0xA830, 0xA83F, "COMMON_INDIC_NUMBER_FORMS"};
const Unicode::Block Unicode::PHAGS_PA {0xA840, 0xA87F, "PHAGS_PA"};
const Unicode::Block Unicode::SAURASHTRA {0xA880, 0xA8DF, "SAURASHTRA"};
const Unicode::Block Unicode::DEVANAGARI_EXTENDED {0xA8E0, 0xA8FF, "DEVANAGARI_EXTENDED"};
const Unicode::Block Unicode::KAYAH_LI {0xA900, 0xA92F, "KAYAH_LI"};
const Unicode::Block Unicode::REJANG {0xA930, 0xA95F, "REJANG"};
const Unicode::Block Unicode::HANGUL_JAMO_EXTENDED_A {0xA960, 0xA97F, "HANGUL_JAMO_EXTENDED_A"};
const Unicode::Block Unicode::JAVANESE {0xA980, 0xA9DF, "JAVANESE"};
const Unicode::Block Unicode::MYANMAR_EXTENDED_B {0xA9E0, 0xA9FF, "MYANMAR_EXTENDED_B"};
const Unicode::Block Unicode::CHAM {0xAA00, 0xAA5F, "CHAM"};
const Unicode::Block Unicode::MYANMAR_EXTENDED_A {0xAA60, 0xAA7F, "MYANMAR_EXTENDED_A"};
const Unicode::Block Unicode::TAI_VIET {0xAA80, 0xAADF, "TAI_VIET"};
const Unicode::Block Unicode::MEETEI_MAYEK_EXTENSIONS {0xAAE0, 0xAAFF, "MEETEI_MAYEK_EXTENSIONS"};
const Unicode::Block Unicode::ETHIOPIC_EXTENDED_A {0xAB00, 0xAB2F, "ETHIOPIC_EXTENDED_A"};
const Unicode::Block Unicode::LATIN_EXTENDED_E {0xAB30, 0xAB6F, "LATIN_EXTENDED_E"};
const Unicode::Block Unicode::CHEROKEE_SUPPLEMENT {0xAB70, 0xABBF, "CHEROKEE_SUPPLEMENT"};
const Unicode::Block Unicode::MEETEI_MAYEK {0xABC0, 0xABFF, "MEETEI_MAYEK"};
const Unicode::Block Unicode::HANGUL_SYLLABLES {0xAC00, 0xD7AF, "HANGUL_SYLLABLES"};
const Unicode::Block Unicode::HANGUL_JAMO_EXTENDED_B {0xD7B0, 0xD7FF, "HANGUL_JAMO_EXTENDED_B"};
const Unicode::Block Unicode::HIGH_SURROGATES {0xD800, 0xDB7F, "HIGH_SURROGATES"};
const Unicode::Block Unicode::HIGH_PRIVATE_USE_SURROGATES {0xDB80, 0xDBFF, "HIGH_PRIVATE_USE_SURROGATES"};
const Unicode::Block Unicode::LOW_SURROGATES {0xDC00, 0xDFFF, "LOW_SURROGATES"};
const Unicode::Block Unicode::PRIVATE_USE_AREA {0xE000, 0xF8FF, "PRIVATE_USE_AREA"};
const Unicode::Block Unicode::CJK_COMPATIBILITY_IDEOGRAPHS {0xF900, 0xFAFF, "CJK_COMPATIBILITY_IDEOGRAPHS"};
const Unicode::Block Unicode::ALPHABETIC_PRESENTATION_FORMS {0xFB00, 0xFB4F, "ALPHABETIC_PRESENTATION_FORMS"};
const Unicode::Block Unicode::ARABIC_PRESENTATION_FORMS_A {0xFB50, 0xFDFF, "ARABIC_PRESENTATION_FORMS_A"};
const Unicode::Block Unicode::VARIATION_SELECTORS {0xFE00, 0xFE0F, "VARIATION_SELECTORS"};
const Unicode::Block Unicode::VERTICAL_FORMS {0xFE10, 0xFE1F, "VERTICAL_FORMS"};
const Unicode::Block Unicode::COMBINING_HALF_MARKS {0xFE20, 0xFE2F, "COMBINING_HALF_MARKS"};
const Unicode::Block Unicode::CJK_COMPATIBILITY_FORMS {0xFE30, 0xFE4F, "CJK_COMPATIBILITY_FORMS"};
const Unicode::Block Unicode::SMALL_FORM_VARIANTS {0xFE50, 0xFE6F, "SMALL_FORM_VARIANTS"};
const Unicode::Block Unicode::ARABIC_PRESENTATION_FORMS_B {0xFE70, 0xFEFF, "ARABIC_PRESENTATION_FORMS_B"};
const Unicode::Block Unicode::HALFWIDTH_AND_FULLWIDTH_FORMS {0xFF00, 0xFFEF, "HALFWIDTH_AND_FULLWIDTH_FORMS"};
const Unicode::Block Unicode::SPECIALS {0xFFF0, 0xFFFF, "SPECIALS"};
const Unicode::Block Unicode::LINEAR_B_SYLLABARY {0x10000, 0x1007F, "LINEAR_B_SYLLABARY"};
const Unicode::Block Unicode::LINEAR_B_IDEOGRAMS {0x10080, 0x100FF, "LINEAR_B_IDEOGRAMS"};
const Unicode::Block Unicode::AEGEAN_NUMBERS {0x10100, 0x1013F, "AEGEAN_NUMBERS"};
const Unicode::Block Unicode::ANCIENT_GREEK_NUMBERS {0x10140, 0x1018F, "ANCIENT_GREEK_NUMBERS"};
const Unicode::Block Unicode::ANCIENT_SYMBOLS {0x10190, 0x101CF, "ANCIENT_SYMBOLS"};
const Unicode::Block Unicode::PHAISTOS_DISC {0x101D0, 0x101FF, "PHAISTOS_DISC"};
const Unicode::Block Unicode::LYCIAN {0x10280, 0x1029F, "LYCIAN"};
const Unicode::Block Unicode::CARIAN {0x102A0, 0x102DF, "CARIAN"};
const Unicode::Block Unicode::COPTIC_EPACT_NUMBERS {0x102E0, 0x102FF, "COPTIC_EPACT_NUMBERS"};
const Unicode::Block Unicode::OLD_ITALIC {0x10300, 0x1032F, "OLD_ITALIC"};
const Unicode::Block Unicode::GOTHIC {0x10330, 0x1034F, "GOTHIC"};
const Unicode::Block Unicode::OLD_PERMIC {0x10350, 0x1037F, "OLD_PERMIC"};
const Unicode::Block Unicode::UGARITIC {0x10380, 0x1039F, "UGARITIC"};
const Unicode::Block Unicode::OLD_PERSIAN {0x103A0, 0x103DF, "OLD_PERSIAN"};
const Unicode::Block Unicode::DESERET {0x10400, 0x1044F, "DESERET"};
const Unicode::Block Unicode::SHAVIAN {0x10450, 0x1047F, "SHAVIAN"};
const Unicode::Block Unicode::OSMANYA {0x10480, 0x104AF, "OSMANYA"};
const Unicode::Block Unicode::OSAGE {0x104B0, 0x104FF, "OSAGE"};
const Unicode::Block Unicode::ELBASAN {0x10500, 0x1052F, "ELBASAN"};
const Unicode::Block Unicode::CAUCASIAN_ALBANIAN {0x10530, 0x1056F, "CAUCASIAN_ALBANIAN"};
const Unicode::Block Unicode::LINEAR_A {0x10600, 0x1077F, "LINEAR_A"};
const Unicode::Block Unicode::CYPRIOT_SYLLABARY {0x10800, 0x1083F, "CYPRIOT_SYLLABARY"};
const Unicode::Block Unicode::IMPERIAL_ARAMAIC {0x10840, 0x1085F, "IMPERIAL_ARAMAIC"};
const Unicode::Block Unicode::PALMYRENE {0x10860, 0x1087F, "PALMYRENE"};
const Unicode::Block Unicode::NABATAEAN {0x10880, 0x108AF, "NABATAEAN"};
const Unicode::Block Unicode::HATRAN {0x108E0, 0x108FF, "HATRAN"};
const Unicode::Block Unicode::PHOENICIAN {0x10900, 0x1091F, "PHOENICIAN"};
const Unicode::Block Unicode::LYDIAN {0x10920, 0x1093F, "LYDIAN"};
const Unicode::Block Unicode::MEROITIC_HIEROGLYPHS {0x10980, 0x1099F, "MEROITIC_HIEROGLYPHS"};
const Unicode::Block Unicode::MEROITIC_CURSIVE {0x109A0, 0x109FF, "MEROITIC_CURSIVE"};
const Unicode::Block Unicode::KHAROSHTHI {0x10A00, 0x10A5F, "KHAROSHTHI"};
const Unicode::Block Unicode::OLD_SOUTH_ARABIAN {0x10A60, 0x10A7F, "OLD_SOUTH_ARABIAN"};
const Unicode::Block Unicode::OLD_NORTH_ARABIAN {0x10A80, 0x10A9F, "OLD_NORTH_ARABIAN"};
const Unicode::Block Unicode::MANICHAEAN {0x10AC0, 0x10AFF, "MANICHAEAN"};
const Unicode::Block Unicode::AVESTAN {0x10B00, 0x10B3F, "AVESTAN"};
const Unicode::Block Unicode::INSCRIPTIONAL_PARTHIAN {0x10B40, 0x10B5F, "INSCRIPTIONAL_PARTHIAN"};
const Unicode::Block Unicode::INSCRIPTIONAL_PAHLAVI {0x10B60, 0x10B7F, "INSCRIPTIONAL_PAHLAVI"};
const Unicode::Block Unicode::PSALTER_PAHLAVI {0x10B80, 0x10BAF, "PSALTER_PAHLAVI"};
const Unicode::Block Unicode::OLD_TURKIC {0x10C00, 0x10C4F, "OLD_TURKIC"};
const Unicode::Block Unicode::OLD_HUNGARIAN {0x10C80, 0x10CFF, "OLD_HUNGARIAN"};
const Unicode::Block Unicode::HANIFI_ROHINGYA {0x10D00, 0x10D3F, "HANIFI_ROHINGYA"};
const Unicode::Block Unicode::RUMI_NUMERAL_SYMBOLS {0x10E60, 0x10E7F, "RUMI_NUMERAL_SYMBOLS"};
const Unicode::Block Unicode::OLD_SOGDIAN {0x10F00, 0x10F2F, "OLD_SOGDIAN"};
const Unicode::Block Unicode::SOGDIAN {0x10F30, 0x10F6F, "SOGDIAN"};
const Unicode::Block Unicode::ELYMAIC {0x10FE0, 0x10FFF, "ELYMAIC"};
const Unicode::Block Unicode::BRAHMI {0x11000, 0x1107F, "BRAHMI"};
const Unicode::Block Unicode::KAITHI {0x11080, 0x110CF, "KAITHI"};
const Unicode::Block Unicode::SORA_SOMPENG {0x110D0, 0x110FF, "SORA_SOMPENG"};
const Unicode::Block Unicode::CHAKMA {0x11100, 0x1114F, "CHAKMA"};
const Unicode::Block Unicode::MAHAJANI {0x11150, 0x1117F, "MAHAJANI"};
const Unicode::Block Unicode::SHARADA {0x11180, 0x111DF, "SHARADA"};
const Unicode::Block Unicode::SINHALA_ARCHAIC_NUMBERS {0x111E0, 0x111FF, "SINHALA_ARCHAIC_NUMBERS"};
const Unicode::Block Unicode::KHOJKI {0x11200, 0x1124F, "KHOJKI"};
const Unicode::Block Unicode::MULTANI {0x11280, 0x112AF, "MULTANI"};
const Unicode::Block Unicode::KHUDAWADI {0x112B0, 0x112FF, "KHUDAWADI"};
const Unicode::Block Unicode::GRANTHA {0x11300, 0x1137F, "GRANTHA"};
const Unicode::Block Unicode::NEWA {0x11400, 0x1147F, "NEWA"};
const Unicode::Block Unicode::TIRHUTA {0x11480, 0x114DF, "TIRHUTA"};
const Unicode::Block Unicode::SIDDHAM {0x11580, 0x115FF, "SIDDHAM"};
const Unicode::Block Unicode::MODI {0x11600, 0x1165F, "MODI"};
const Unicode::Block Unicode::MONGOLIAN_SUPPLEMENT {0x11660, 0x1167F, "MONGOLIAN_SUPPLEMENT"};
const Unicode::Block Unicode::TAKRI {0x11680, 0x116CF, "TAKRI"};
const Unicode::Block Unicode::AHOM {0x11700, 0x1173F, "AHOM"};
const Unicode::Block Unicode::DOGRA {0x11800, 0x1184F, "DOGRA"};
const Unicode::Block Unicode::WARANG_CITI {0x118A0, 0x118FF, "WARANG_CITI"};
const Unicode::Block Unicode::NANDINAGARI {0x119A0, 0x119FF, "NANDINAGARI"};
const Unicode::Block Unicode::ZANABAZAR_SQUARE {0x11A00, 0x11A4F, "ZANABAZAR_SQUARE"};
const Unicode::Block Unicode::SOYOMBO {0x11A50, 0x11AAF, "SOYOMBO"};
const Unicode::Block Unicode::PAU_CIN_HAU {0x11AC0, 0x11AFF, "PAU_CIN_HAU"};
const Unicode::Block Unicode::BHAIKSUKI {0x11C00, 0x11C6F, "BHAIKSUKI"};
const Unicode::Block Unicode::MARCHEN {0x11C70, 0x11CBF, "MARCHEN"};
const Unicode::Block Unicode::MASARAM_GONDI {0x11D00, 0x11D5F, "MASARAM_GONDI"};
const Unicode::Block Unicode::GUNJALA_GONDI {0x11D60, 0x11DAF, "GUNJALA_GONDI"};
const Unicode::Block Unicode::MAKASAR {0x11EE0, 0x11EFF, "MAKASAR"};
const Unicode::Block Unicode::TAMIL_SUPPLEMENT {0x11FC0, 0x11FFF, "TAMIL_SUPPLEMENT"};
const Unicode::Block Unicode::CUNEIFORM {0x12000, 0x123FF, "CUNEIFORM"};
const Unicode::Block Unicode::CUNEIFORM_NUMBERS_AND_PUNCTUATION {0x12400, 0x1247F, "CUNEIFORM_NUMBERS_AND_PUNCTUATION"};
const Unicode::Block Unicode::EARLY_DYNASTIC_CUNEIFORM {0x12480, 0x1254F, "EARLY_DYNASTIC_CUNEIFORM"};
const Unicode::Block Unicode::EGYPTIAN_HIEROGLYPHS {0x13000, 0x1342F, "EGYPTIAN_HIEROGLYPHS"};
const Unicode::Block Unicode::EGYPTIAN_HIEROGLYPH_FORMAT_CONTROLS {0x13430, 0x1343F, "EGYPTIAN_HIEROGLYPH_FORMAT_CONTROLS"};
const Unicode::Block Unicode::ANATOLIAN_HIEROGLYPHS {0x14400, 0x1467F, "ANATOLIAN_HIEROGLYPHS"};
const Unicode::Block Unicode::BAMUM_SUPPLEMENT {0x16800, 0x16A3F, "BAMUM_SUPPLEMENT"};
const Unicode::Block Unicode::MRO {0x16A40, 0x16A6F, "MRO"};
const Unicode::Block Unicode::BASSA_VAH {0x16AD0, 0x16AFF, "BASSA_VAH"};
const Unicode::Block Unicode::PAHAWH_HMONG {0x16B00, 0x16B8F, "PAHAWH_HMONG"};
const Unicode::Block Unicode::MEDEFAIDRIN {0x16E40, 0x16E9F, "MEDEFAIDRIN"};
const Unicode::Block Unicode::MIAO {0x16F00, 0x16F9F, "MIAO"};
const Unicode::Block Unicode::IDEOGRAPHIC_SYMBOLS_AND_PUNCTUATION {0x16FE0, 0x16FFF, "IDEOGRAPHIC_SYMBOLS_AND_PUNCTUATION"};
const Unicode::Block Unicode::TANGUT {0x17000, 0x187FF, "TANGUT"};
const Unicode::Block Unicode::TANGUT_COMPONENTS {0x18800, 0x18AFF, "TANGUT_COMPONENTS"};
const Unicode::Block Unicode::KANA_SUPPLEMENT {0x1B000, 0x1B0FF, "KANA_SUPPLEMENT"};
const Unicode::Block Unicode::KANA_EXTENDED_A {0x1B100, 0x1B12F, "KANA_EXTENDED_A"};
const Unicode::Block Unicode::SMALL_KANA_EXTENSION {0x1B130, 0x1B16F, "SMALL_KANA_EXTENSION"};
const Unicode::Block Unicode::NUSHU {0x1B170, 0x1B2FF, "NUSHU"};
const Unicode::Block Unicode::DUPLOYAN {0x1BC00, 0x1BC9F, "DUPLOYAN"};
const Unicode::Block Unicode::SHORTHAND_FORMAT_CONTROLS {0x1BCA0, 0x1BCAF, "SHORTHAND_FORMAT_CONTROLS"};
const Unicode::Block Unicode::BYZANTINE_MUSICAL_SYMBOLS {0x1D000, 0x1D0FF, "BYZANTINE_MUSICAL_SYMBOLS"};
const Unicode::Block Unicode::MUSICAL_SYMBOLS {0x1D100, 0x1D1FF, "MUSICAL_SYMBOLS"};
const Unicode::Block Unicode::ANCIENT_GREEK_MUSICAL_NOTATION {0x1D200, 0x1D24F, "ANCIENT_GREEK_MUSICAL_NOTATION"};
const Unicode::Block Unicode::MAYAN_NUMERALS {0x1D2E0, 0x1D2FF, "MAYAN_NUMERALS"};
const Unicode::Block Unicode::TAI_XUAN_JING_SYMBOLS {0x1D300, 0x1D35F, "TAI_XUAN_JING_SYMBOLS"};
const Unicode::Block Unicode::COUNTING_ROD_NUMERALS {0x1D360, 0x1D37F, "COUNTING_ROD_NUMERALS"};
const Unicode::Block Unicode::MATHEMATICAL_ALPHANUMERIC_SYMBOLS {0x1D400, 0x1D7FF, "MATHEMATICAL_ALPHANUMERIC_SYMBOLS"};
const Unicode::Block Unicode::SUTTON_SIGNWRITING {0x1D800, 0x1DAAF, "SUTTON_SIGNWRITING"};
const Unicode::Block Unicode::GLAGOLITIC_SUPPLEMENT {0x1E000, 0x1E02F, "GLAGOLITIC_SUPPLEMENT"};
const Unicode::Block Unicode::NYIAKENG_PUACHUE_HMONG {0x1E100, 0x1E14F, "NYIAKENG_PUACHUE_HMONG"};
const Unicode::Block Unicode::WANCHO {0x1E2C0, 0x1E2FF, "WANCHO"};
const Unicode::Block Unicode::MENDE_KIKAKUI {0x1E800, 0x1E8DF, "MENDE_KIKAKUI"};
const Unicode::Block Unicode::ADLAM {0x1E900, 0x1E95F, "ADLAM"};
const Unicode::Block Unicode::INDIC_SIYAQ_NUMBERS {0x1EC70, 0x1ECBF, "INDIC_SIYAQ_NUMBERS"};
const Unicode::Block Unicode::OTTOMAN_SIYAQ_NUMBERS {0x1ED00, 0x1ED4F, "OTTOMAN_SIYAQ_NUMBERS"};
const Unicode::Block Unicode::ARABIC_MATHEMATICAL_ALPHABETIC_SYMBOLS {0x1EE00, 0x1EEFF, "ARABIC_MATHEMATICAL_ALPHABETIC_SYMBOLS"};
const Unicode::Block Unicode::MAHJONG_TILES {0x1F000, 0x1F02F, "MAHJONG_TILES"};
const Unicode::Block Unicode::DOMINO_TILES {0x1F030, 0x1F09F, "DOMINO_TILES"};
const Unicode::Block Unicode::PLAYING_CARDS {0x1F0A0, 0x1F0FF, "PLAYING_CARDS"};
const Unicode::Block Unicode::ENCLOSED_ALPHANUMERIC_SUPPLEMENT {0x1F100, 0x1F1FF, "ENCLOSED_ALPHANUMERIC_SUPPLEMENT"};
const Unicode::Block Unicode::ENCLOSED_IDEOGRAPHIC_SUPPLEMENT {0x1F200, 0x1F2FF, "ENCLOSED_IDEOGRAPHIC_SUPPLEMENT"};
const Unicode::Block Unicode::MISCELLANEOUS_SYMBOLS_AND_PICTOGRAPHS {0x1F300, 0x1F5FF, "MISCELLANEOUS_SYMBOLS_AND_PICTOGRAPHS"};
const Unicode::Block Unicode::EMOTICONS {0x1F600, 0x1F64F, "EMOTICONS"};
const Unicode::Block Unicode::ORNAMENTAL_DINGBATS {0x1F650, 0x1F67F, "ORNAMENTAL_DINGBATS"};
const Unicode::Block Unicode::TRANSPORT_AND_MAP_SYMBOLS {0x1F680, 0x1F6FF, "TRANSPORT_AND_MAP_SYMBOLS"};
const Unicode::Block Unicode::ALCHEMICAL_SYMBOLS {0x1F700, 0x1F77F, "ALCHEMICAL_SYMBOLS"};
const Unicode::Block Unicode::GEOMETRIC_SHAPES_EXTENDED {0x1F780, 0x1F7FF, "GEOMETRIC_SHAPES_EXTENDED"};
const Unicode::Block Unicode::SUPPLEMENTAL_ARROWS_C {0x1F800, 0x1F8FF, "SUPPLEMENTAL_ARROWS_C"};
const Unicode::Block Unicode::SUPPLEMENTAL_SYMBOLS_AND_PICTOGRAPHS {0x1F900, 0x1F9FF, "SUPPLEMENTAL_SYMBOLS_AND_PICTOGRAPHS"};
const Unicode::Block Unicode::CHESS_SYMBOLS {0x1FA00, 0x1FA6F, "CHESS_SYMBOLS"};
const Unicode::Block Unicode::SYMBOLS_AND_PICTOGRAPHS_EXTENDED_A {0x1FA70, 0x1FAFF, "SYMBOLS_AND_PICTOGRAPHS_EXTENDED_A"};
const Unicode::Block Unicode::CJK_UNIFIED_IDEOGRAPHS_EXTENSION_B {0x20000, 0x2A6DF, "CJK_UNIFIED_IDEOGRAPHS_EXTENSION_B"};
const Unicode::Block Unicode::CJK_UNIFIED_IDEOGRAPHS_EXTENSION_C {0x2A700, 0x2B73F, "CJK_UNIFIED_IDEOGRAPHS_EXTENSION_C"};
const Unicode::Block Unicode::CJK_UNIFIED_IDEOGRAPHS_EXTENSION_D {0x2B740, 0x2B81F, "CJK_UNIFIED_IDEOGRAPHS_EXTENSION_D"};
const Unicode::Block Unicode::CJK_UNIFIED_IDEOGRAPHS_EXTENSION_E {0x2B820, 0x2CEAF, "CJK_UNIFIED_IDEOGRAPHS_EXTENSION_E"};
const Unicode::Block Unicode::CJK_UNIFIED_IDEOGRAPHS_EXTENSION_F {0x2CEB0, 0x2EBEF, "CJK_UNIFIED_IDEOGRAPHS_EXTENSION_F"};
const Unicode::Block Unicode::CJK_COMPATIBILITY_IDEOGRAPHS_SUPPLEMENT {0x2F800, 0x2FA1F, "CJK_COMPATIBILITY_IDEOGRAPHS_SUPPLEMENT"};
const Unicode::Block Unicode::TAGS {0xE0000, 0xE007F, "TAGS"};
const Unicode::Block Unicode::VARIATION_SELECTORS_SUPPLEMENT {0xE0100, 0xE01EF, "VARIATION_SELECTORS_SUPPLEMENT"};
const Unicode::Block Unicode::SUPPLEMENTARY_PRIVATE_USE_AREA_A {0xF0000, 0xFFFFF, "SUPPLEMENTARY_PRIVATE_USE_AREA_A"};
const Unicode::Block Unicode::SUPPLEMENTARY_PRIVATE_USE_AREA_B {0x100000, 0x10FFFF, "SUPPLEMENTARY_PRIVATE_USE_AREA_B"};


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


std::string UTF8::normalize(const std::string& utf8,
                            Unicode::NormalizationForm form)
{
    utf8proc_uint8_t* retval = nullptr;

    switch (form)
    {
        case Unicode::NormalizationForm::NFC:
            retval = utf8proc_NFC(reinterpret_cast<const utf8proc_uint8_t*>(utf8.data()));
            break;
        case Unicode::NormalizationForm::NFD:
            retval = utf8proc_NFD(reinterpret_cast<const utf8proc_uint8_t*>(utf8.data()));
            break;
        case Unicode::NormalizationForm::NFKC:
            retval = utf8proc_NFKC(reinterpret_cast<const utf8proc_uint8_t*>(utf8.data()));
            break;
        case Unicode::NormalizationForm::NFKD:
            retval = utf8proc_NFKD(reinterpret_cast<const utf8proc_uint8_t*>(utf8.data()));
            break;
    }

    if (retval)
    {
        std::string out(reinterpret_cast<char*>(retval));
        free(retval);
        return out;
    }

    ofLogError("UTF8::normalize") << "Unable to normalize: " << utf8;
    return utf8;
}


std::string UTF8::casefold(const std::string& utf8)
{
    utf8proc_uint8_t* retval = nullptr;
    
    utf8proc_ssize_t result = utf8proc_map(reinterpret_cast<const utf8proc_uint8_t*>(utf8.data()),
                                           0,
                                           &retval,
                                           static_cast<utf8proc_option_t>(UTF8PROC_NULLTERM | UTF8PROC_STABLE | UTF8PROC_CASEFOLD));

    if (result > 0)
    {
        std::string out(reinterpret_cast<char*>(retval), result);
        free(retval);
        return out;
    }

    ofLogError("UTF8::casefold") << "Unable to casefold: " << utf8;
    return utf8;
}


bool UTF8::isValid(const std::string& txt)
{
    try
    {
        return utf8::is_valid(txt.begin(), txt.end());
    }
    catch (const utf8::exception& utfcpp_ex)
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
        ofLogError("ofUTF8::distance") << utfcpp_ex.what();
        return 0;
    }
}


int UTF8::icompare(const std::string& utf8String0,
                   const std::string& utf8String1)
{
    // Get correct pointers.
    const utf8proc_uint8_t* s0 = reinterpret_cast<const utf8proc_uint8_t*>(utf8String0.data());
    const utf8proc_uint8_t* s1 = reinterpret_cast<const utf8proc_uint8_t*>(utf8String1.data());

    // Normalize and casefold.
    utf8proc_option_t flags = static_cast<utf8proc_option_t>(UTF8PROC_NULLTERM | UTF8PROC_STABLE | UTF8PROC_CASEFOLD | UTF8PROC_COMPOSE);
    utf8proc_uint8_t* _s0 = nullptr;
    utf8proc_uint8_t* _s1 = nullptr;

    utf8proc_map(s0, 0, &_s0, flags);
    utf8proc_map(s1, 0, &_s1, flags);

    int result = 0;
    bool success = false;

    if (_s0 && _s1)
    {
        result = std::strcmp(reinterpret_cast<const char*>(_s0),
                             reinterpret_cast<const char*>(_s1));
        success = true;
    }

    free(_s0);
    free(_s1);

    if (!success)
    {
        ofLogError("UTF8::icompare") << "Unable to compare: " << utf8String0 << " and " << utf8String1;
    }

    return result;
}


std::string UTF8::toUpper(const std::string& str)
{
    return UTF32::toUTF8(UTF32::toUpper(toUTF32(str)));
}


std::string& UTF8::toUpperInPlace(std::string& str)
{
    str = toUpper(str);
    return str;
}


std::string UTF8::toLower(const std::string& str)
{
    return UTF32::toUTF8(UTF32::toLower(toUTF32(str)));
}


std::string& UTF8::toLowerInPlace(std::string& str)
{
    str = toLower(str);
    return str;
}


std::u16string UTF8::toUTF16(const std::string& input)
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
        ofLogError("TextConverter::toUTF16") << utfcpp_ex.what();
    }

    return utf16result;
}



std::u32string UTF8::toUTF32(const std::string& input)
{
    std::u32string utf32result;

    try
    {
        utf8::utf8to32(input.begin(),
                       input.end(),
                       std::back_inserter(utf32result));
    }
    catch (const utf8::exception& utfcpp_ex)
    {
        ofLogError("TextConverter::toUTF32") << utfcpp_ex.what();
    }

    return utf32result;
}


std::string UTF16::toUTF8(const std::u16string& input)
{
    std::string utf8result;

    try
    {
        utf8::utf16to8(input.begin(), input.end(), std::back_inserter(utf8result));
    }
    catch (const utf8::exception& utfcpp_ex)
    {
        ofLogError("TextConverter::toUTF8") << utfcpp_ex.what();
    }

    return utf8result;
}


    
std::u32string UTF16::toUTF32(const std::u16string& input)
{
    return UTF8::toUTF32(toUTF8(input));
}


bool UTF32::isValid(char32_t unichar)
{
    return !((unichar > 0x0010ffffu) || (unichar >= 0xd800u && unichar <= 0xdfffu));
}


bool UTF32::isPrintable(char32_t unichar)
{
    // aka is graphic.
    int category = ucdn_get_general_category(unichar);

    return category != UCDN_GENERAL_CATEGORY_CC
        && category != UCDN_GENERAL_CATEGORY_CF
        && category != UCDN_GENERAL_CATEGORY_CN
        && category != UCDN_GENERAL_CATEGORY_CO
        && category != UCDN_GENERAL_CATEGORY_CS
        && category != UCDN_GENERAL_CATEGORY_ZL
        && category != UCDN_GENERAL_CATEGORY_ZP;
}


bool UTF32::isControl(char32_t unichar)
{
    // True if unichar is:
    //    ISO 8-bit control character (U+0000..U+001f and U+007f..U+009f)
    //    U_CONTROL_CHAR (Cc)
    //    U_FORMAT_CHAR (Cf)
    //    U_LINE_SEPARATOR (Zl)
    //    U_PARAGRAPH_SEPARATOR (Zp)
    // This definition shared with ICU's isCntrl function
    // https://ssl.icu-project.org/apiref/icu4c/uchar_8h.html

    if ((unichar <= 0x001F) || (unichar >= 0x007F && unichar <= 0x009F))
    {
        return true;
    }
    else
    {
        int category = ucdn_get_general_category(unichar);

        return category == UCDN_GENERAL_CATEGORY_CC
            || category == UCDN_GENERAL_CATEGORY_CF
            || category == UCDN_GENERAL_CATEGORY_ZL
            || category == UCDN_GENERAL_CATEGORY_ZP;
    }
}


bool UTF32::isTitle(char32_t unichar)
{
    return ucdn_get_general_category(unichar) == UCDN_GENERAL_CATEGORY_LT;
}


bool UTF32::isSpace(char32_t unichar)
{
    int category = ucdn_get_general_category(unichar);

    return category == UCDN_GENERAL_CATEGORY_ZS
        || category == UCDN_GENERAL_CATEGORY_ZL
        || category == UCDN_GENERAL_CATEGORY_ZP;
}


bool UTF32::isDigit(char32_t unichar)
{
    return ucdn_get_general_category(unichar) == UCDN_GENERAL_CATEGORY_ND;
}


bool UTF32::isPunct(char32_t unichar)
{
    int category = ucdn_get_general_category(unichar);

    return category == UCDN_GENERAL_CATEGORY_PC
        || category == UCDN_GENERAL_CATEGORY_PD
        || category == UCDN_GENERAL_CATEGORY_PE
        || category == UCDN_GENERAL_CATEGORY_PF
        || category == UCDN_GENERAL_CATEGORY_PI
        || category == UCDN_GENERAL_CATEGORY_PO
        || category == UCDN_GENERAL_CATEGORY_PS;
}


bool UTF32::isAlpha(char32_t unichar)
{
    int category = ucdn_get_general_category(unichar);

    return category == UCDN_GENERAL_CATEGORY_LL
        || category == UCDN_GENERAL_CATEGORY_LM
        || category == UCDN_GENERAL_CATEGORY_LO
        || category == UCDN_GENERAL_CATEGORY_LT
        || category == UCDN_GENERAL_CATEGORY_LU;
}


bool UTF32::isAlphaNumeric(char32_t unichar)
{
    int category = ucdn_get_general_category(unichar);

    return category == UCDN_GENERAL_CATEGORY_ND // digit
        || category == UCDN_GENERAL_CATEGORY_LL
        || category == UCDN_GENERAL_CATEGORY_LM
        || category == UCDN_GENERAL_CATEGORY_LO
        || category == UCDN_GENERAL_CATEGORY_LT
        || category == UCDN_GENERAL_CATEGORY_LU;
}


bool UTF32::isLower(char32_t unichar)
{
    return ucdn_get_general_category(unichar) == UCDN_GENERAL_CATEGORY_LL;
}


bool UTF32::isUpper(char32_t unichar)
{
    return ucdn_get_general_category(unichar) == UCDN_GENERAL_CATEGORY_LU;
}


char32_t UTF32::toLower(char32_t unichar)
{
    return utf8proc_tolower(unichar);
}


char32_t UTF32::toUpper(char32_t unichar)
{
    return utf8proc_toupper(unichar);
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


std::u32string UTF32::toLower(const std::u32string& unichar)
{
    std::u32string out;
    auto it = unichar.cbegin();
    while (it != unichar.end()) {out.push_back(toLower(*(it++)));}
    return out;
}


std::u32string UTF32::toUpper(const std::u32string& unichar)
{
    std::u32string out;
    auto it = unichar.cbegin();
    while (it != unichar.end()) {out.push_back(toUpper(*(it++)));}
    return out;
}


std::u32string& UTF32::toLowerInPlace(std::u32string& unichar)
{
    auto it = unichar.begin();
    while (it != unichar.end()) {toUpperInPlace(*(it++));}
    return unichar;
}


std::u32string& UTF32::toUpperInPlace(std::u32string& unichar)
{
    auto it = unichar.begin();
    while (it != unichar.end()) {toLowerInPlace(*(it++));}
    return unichar;
}


std::string UTF32::toUTF8(char32_t input)
{
    std::string txt;

    try
    {
        utf8::append(input, std::back_inserter(txt));
    }
    catch (const utf8::exception& utfcpp_ex)
    {
        ofLogError("TextConverter::toUTF8") << utfcpp_ex.what();
    }
    return txt;
}


std::string UTF32::toUTF8(const std::u32string& input)
{
    std::string utf8result;

    try
    {
        utf8::utf32to8(input.begin(), input.end(), std::back_inserter(utf8result));
    }
    catch (const utf8::exception& utfcpp_ex)
    {
        ofLogError("TextConverter::toUTF8") << utfcpp_ex.what();
    }

    return utf8result;
}


std::u16string UTF32::toUTF16(char32_t input)
{
    return UTF8::toUTF16(toUTF8(input));
}


std::u16string UTF32::toUTF16(const std::u32string& input)
{
    return UTF8::toUTF16(toUTF8(input));
}


#include <iconv.h>


const iconv_t INVALID_CD = (iconv_t) - 1;
const std::size_t INVALID_CONVERSION = (std::size_t) - 1;


const std::string TextConverter::ENCODING_ASCII = "ASCII";
const std::string TextConverter::ENCODING_UTF8 = "UTF-8";
const std::string TextConverter::ENCODING_UTF16 = "UTF-16";
const std::string TextConverter::ENCODING_UTF32 = "UTF-32";
const std::string TextConverter::ENCODING_ISO_8859_1 = "ISO-8859-1";
const std::string TextConverter::ENCODING_LATIN_1 = ENCODING_ISO_8859_1;
const std::string TextConverter::ENCODING_ISO_8859_2 = "ISO-8859-2";
const std::string TextConverter::ENCODING_LATIN_2 = ENCODING_ISO_8859_2;
const std::string TextConverter::ENCODING_ISO_8859_15 = "ISO-8859-15";
const std::string TextConverter::ENCODING_LATIN_9 = ENCODING_ISO_8859_15;
const std::string TextConverter::ENCODING_WINDOWS_1250 = "windows-1250";
const std::string TextConverter::ENCODING_WINDOWS_1251 = "windows-1251";
const std::string TextConverter::ENCODING_WINDOWS_1252 = "windows-1252";


TextConverter::TextConverter()
{
}


TextConverter::TextConverter(const std::string& inputEncoding,
                             const std::string& outputEncoding)
{
    Settings settings;
    settings.inputEncoding = inputEncoding;
    settings.outputEncoding = outputEncoding;
    setup(settings);
}


TextConverter::TextConverter(const Settings& settings)
{
    setup(settings);
}


TextConverter::~TextConverter()
{
}


bool TextConverter::setup(const std::string& outputEncoding)
{
    Settings settings;
    settings.inputEncoding = "UTF-8";
    settings.outputEncoding = outputEncoding;
    return setup(settings);
}


bool TextConverter::setup(const Settings& settings)
{
    _cd.reset();

    // Input and output encoding are backwards in the iconv api.
    // This allocates a conversion descriptor.

    std::string outputEncoding = settings.outputEncoding;

    if (settings.transliterate)
        outputEncoding += "//TRANSLIT";

    iconv_t cd = iconv_open(outputEncoding.data(),
                            settings.inputEncoding.data());

    if (cd == INVALID_CD)
    {
        if (errno == EINVAL)
            ofLogError("TextConverter::convert") << settings.inputEncoding << " to " << settings.outputEncoding << " is not supported.";
        else
            ofLogError("TextConverter::convert") << "Unknown error.";
    }
    else
    {
        // Wrap in std::shared_ptr.
        _cd = std::shared_ptr<void>(cd, iconv_close);
    }

    return isLoaded();
}


bool TextConverter::isLoaded() const
{
    return _cd != nullptr;
}


void TextConverter::reset()
{
    if (isLoaded())
        iconv(_cd.get(), nullptr, nullptr, nullptr, nullptr);
}


std::vector<std::string> TextConverter::encodings()
{
    std::vector<std::string> results;

    auto list_callback = [](unsigned int namescount,
                            const char * const * names,
                            void* data) -> int
    {
        auto encodingList = reinterpret_cast<std::vector<std::string>*>(data);

        if (encodingList)
            for (unsigned int i = 0; i < namescount; ++i)
                if (names[i] && strlen(names[i]) > 0)
                    encodingList->push_back(std::string(names[i]));

        return 0;
    };

    iconvlist(list_callback, &results);

    return results;
}


int TextConverter::convert(const std::string& input, std::string& output) const
{
    int numEncodingErrors = 0;

    if (!isLoaded())
    {
        ofLogError("TextConverter::convert") << "Converter is not loaded. Call setup().";
        return -1;
    }

    // C++11+ guarantees that std::string is stored in contiguous memory.
    char* pInput = const_cast<char*>(input.data());
    std::size_t sInput = input.size();

    // Here we only resize the output if the caller hasn't already done so.
    if (output.size() < sInput * 2)
        output.resize(sInput * 2);

    char* pOutput = const_cast<char*>(output.data());
    size_t sOutput = output.size();

    while (0 < sInput)
    {
        size_t res = iconv(_cd.get(), // Conversion descriptor.
                           &pInput,   // Pointer to input pointer.
                           &sInput,   // Pointer to input size.
                           &pOutput,  // Pointer to output pointer.
                           &sOutput   // Pointer to output size.
                           );
        if (res == INVALID_CONVERSION)
        {
            if (errno == E2BIG)
            {
                // errno == E2BIG means the output buffer ran out of space.

                // Make a note of where we were in the output buffer.
                std::size_t outputPosition = output.size();

                // Resize output memory. This resize would ideally be calculated
                // based on the maximum theoretical size of the output encoding
                // given the input encoding. For now we'll just use 2x.
                output.resize(output.size() + sInput * 2);

                // Get new pointers in case the resize operation moved memory.
                // Offset pointer to place it at the end.
                pOutput = const_cast<char*>(output.data()) + outputPosition;

                // Set a new remaining size based on the updated output
                // position and the resized output buffer..
                sOutput = output.size() - outputPosition;
            }
            else if (_settings.skipErrors)
            {
                // Skip the character that caused the error.
                ++pInput;
                --sInput;
                *pOutput = _settings.defaultCharacter;
                ++pOutput;
                --sOutput;
                ++numEncodingErrors;
           }
            else
            {
                switch (errno)
                {
                    case EILSEQ:
                    case EINVAL:
                        ofLogError("TextConverter::convert") << std::strerror(errno);
                        break;
                    default:
                        ofLogError("TextConverter::convert") << "Unknown conversion error: " << std::strerror(errno);
                }

                return -1;
            }
        }
    }

    // Remove any excess size if required.
    output.resize(pOutput - const_cast<char*>(output.data()));

    return numEncodingErrors;
}


std::string TextConverter::convert(const std::string& input) const
{
    std::string output;
    convert(input, output);
    return output;
}


int TextConverter::convert(const std::string& input,
                           std::string& output,
                           const std::string& inputEncoding,
                           const std::string& outputEncoding)
{
    if (inputEncoding == outputEncoding)
    {
        output = input;
        return 0;
    }
    else
    {
        TextConverter converter;
        TextConverter::Settings settings;
        settings.inputEncoding = inputEncoding;
        settings.outputEncoding = outputEncoding;
        converter.setup(settings);
        return converter.convert(input, output);
    }
}


} // namespace ofx
