//
// Copyright (c) 2012 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <string>
#include <vector>
#include <numeric>
#include <set>
#include "linebreak.h"
#include "linebreakdef.h"
#include "wordbreak.h"
#include "ofConstants.h"
//#include "fribidi/fribidi-bidi.h"
#include "ucdn.h"


namespace ofx {


/// \brief Defines Unicode Blocks.
///
/// Block data is generated from
/// http://www.unicode.org/Public/UNIDATA/Blocks.txt using a script.
///
/// \sa http://www.unicode.org/Public/UNIDATA/Blocks.txt
class Unicode
{
public:
    /// \brief Unicode Normalization Forms
    ///
    /// From http://unicode.org/faq/normalization.html
    ///     The choice of which to use depends on the particular program or
    ///     system. NFC is the best form for general text, since it is more
    ///     compatible with strings converted from legacy encodings. NFKC is the
    ///     preferred form for identifiers, especially where there are security
    ///     concerns (see UTR #36). NFD and NFKD are most useful for internal
    ///     processing.
    ///
    /// \sa http://www.unicode.org/reports/tr15/
    enum class NormalizationForm
    {
        /// \brief Normalization Form C (NFC)
        ///
        /// Canonical Decomposition, followed by Canonical Composition.
        NFC,

        /// \brief Normalization Form D (NFD)
        ///
        /// Canonical Decomposition.
        NFD,

        /// \brief Normalization Form KC (NFKC)
        ///
        /// Compatibility Decomposition, followed by Canonical Composition.
        NFKC,

        /// \brief Normalization Form KD (NFKD)
        ///
        /// Compatibility Decomposition.
        NFKD
    };

    /// \brief An character set covering ASCII and most Western code points.
    static const std::u32string STANDARD_CHARSET;

    struct Block
    {
        /// \brief The first Unicode code point in the Block.
        char32_t begin;

        /// \brief The last Unicode code point in the Block.
        char32_t end;

        /// \brief The name of the block.
        ///
        /// When comparing block names, casing, whitespace, hyphens, and
        /// underbars are ignored. For example, "Latin Extended-A", "latin
        /// extended a" and "LATIN_EXTENDED_A" are equivalent.
        std::string name;

        /// \brief Get the number of Unicode code points in the Block.
        /// \returns the number of Unicode code points in the Block.
        std::size_t size() const;

        /// \brief Get this Block as a UTF32 string.
        /// \returns the Block as a UTF32 string.
        std::u32string charset() const;
        
    };


    /// \brief The BASIC_LATIN Unicode Block.
    static const Block BASIC_LATIN;

    /// \brief The LATIN_1_SUPPLEMENT Unicode Block.
    static const Block LATIN_1_SUPPLEMENT;

    /// \brief The LATIN_EXTENDED_A Unicode Block.
    static const Block LATIN_EXTENDED_A;

    /// \brief The LATIN_EXTENDED_B Unicode Block.
    static const Block LATIN_EXTENDED_B;

    /// \brief The IPA_EXTENSIONS Unicode Block.
    static const Block IPA_EXTENSIONS;

    /// \brief The SPACING_MODIFIER_LETTERS Unicode Block.
    static const Block SPACING_MODIFIER_LETTERS;

    /// \brief The COMBINING_DIACRITICAL_MARKS Unicode Block.
    static const Block COMBINING_DIACRITICAL_MARKS;

    /// \brief The GREEK_AND_COPTIC Unicode Block.
    static const Block GREEK_AND_COPTIC;

    /// \brief The CYRILLIC Unicode Block.
    static const Block CYRILLIC;

    /// \brief The CYRILLIC_SUPPLEMENT Unicode Block.
    static const Block CYRILLIC_SUPPLEMENT;

    /// \brief The ARMENIAN Unicode Block.
    static const Block ARMENIAN;

    /// \brief The HEBREW Unicode Block.
    static const Block HEBREW;

    /// \brief The ARABIC Unicode Block.
    static const Block ARABIC;

    /// \brief The SYRIAC Unicode Block.
    static const Block SYRIAC;

    /// \brief The ARABIC_SUPPLEMENT Unicode Block.
    static const Block ARABIC_SUPPLEMENT;

    /// \brief The THAANA Unicode Block.
    static const Block THAANA;

    /// \brief The NKO Unicode Block.
    static const Block NKO;

    /// \brief The SAMARITAN Unicode Block.
    static const Block SAMARITAN;

    /// \brief The MANDAIC Unicode Block.
    static const Block MANDAIC;

    /// \brief The SYRIAC_SUPPLEMENT Unicode Block.
    static const Block SYRIAC_SUPPLEMENT;

    /// \brief The ARABIC_EXTENDED_A Unicode Block.
    static const Block ARABIC_EXTENDED_A;

    /// \brief The DEVANAGARI Unicode Block.
    static const Block DEVANAGARI;

    /// \brief The BENGALI Unicode Block.
    static const Block BENGALI;

    /// \brief The GURMUKHI Unicode Block.
    static const Block GURMUKHI;

    /// \brief The GUJARATI Unicode Block.
    static const Block GUJARATI;

    /// \brief The ORIYA Unicode Block.
    static const Block ORIYA;

    /// \brief The TAMIL Unicode Block.
    static const Block TAMIL;

    /// \brief The TELUGU Unicode Block.
    static const Block TELUGU;

    /// \brief The KANNADA Unicode Block.
    static const Block KANNADA;

    /// \brief The MALAYALAM Unicode Block.
    static const Block MALAYALAM;

    /// \brief The SINHALA Unicode Block.
    static const Block SINHALA;

    /// \brief The THAI Unicode Block.
    static const Block THAI;

    /// \brief The LAO Unicode Block.
    static const Block LAO;

    /// \brief The TIBETAN Unicode Block.
    static const Block TIBETAN;

    /// \brief The MYANMAR Unicode Block.
    static const Block MYANMAR;

    /// \brief The GEORGIAN Unicode Block.
    static const Block GEORGIAN;

    /// \brief The HANGUL_JAMO Unicode Block.
    static const Block HANGUL_JAMO;

    /// \brief The ETHIOPIC Unicode Block.
    static const Block ETHIOPIC;

    /// \brief The ETHIOPIC_SUPPLEMENT Unicode Block.
    static const Block ETHIOPIC_SUPPLEMENT;

    /// \brief The CHEROKEE Unicode Block.
    static const Block CHEROKEE;

    /// \brief The UNIFIED_CANADIAN_ABORIGINAL_SYLLABICS Unicode Block.
    static const Block UNIFIED_CANADIAN_ABORIGINAL_SYLLABICS;

    /// \brief The OGHAM Unicode Block.
    static const Block OGHAM;

    /// \brief The RUNIC Unicode Block.
    static const Block RUNIC;

    /// \brief The TAGALOG Unicode Block.
    static const Block TAGALOG;

    /// \brief The HANUNOO Unicode Block.
    static const Block HANUNOO;

    /// \brief The BUHID Unicode Block.
    static const Block BUHID;

    /// \brief The TAGBANWA Unicode Block.
    static const Block TAGBANWA;

    /// \brief The KHMER Unicode Block.
    static const Block KHMER;

    /// \brief The MONGOLIAN Unicode Block.
    static const Block MONGOLIAN;

    /// \brief The UNIFIED_CANADIAN_ABORIGINAL_SYLLABICS_EXTENDED Unicode Block.
    static const Block UNIFIED_CANADIAN_ABORIGINAL_SYLLABICS_EXTENDED;

    /// \brief The LIMBU Unicode Block.
    static const Block LIMBU;

    /// \brief The TAI_LE Unicode Block.
    static const Block TAI_LE;

    /// \brief The NEW_TAI_LUE Unicode Block.
    static const Block NEW_TAI_LUE;

    /// \brief The KHMER_SYMBOLS Unicode Block.
    static const Block KHMER_SYMBOLS;

    /// \brief The BUGINESE Unicode Block.
    static const Block BUGINESE;

    /// \brief The TAI_THAM Unicode Block.
    static const Block TAI_THAM;

    /// \brief The COMBINING_DIACRITICAL_MARKS_EXTENDED Unicode Block.
    static const Block COMBINING_DIACRITICAL_MARKS_EXTENDED;

    /// \brief The BALINESE Unicode Block.
    static const Block BALINESE;

    /// \brief The SUNDANESE Unicode Block.
    static const Block SUNDANESE;

    /// \brief The BATAK Unicode Block.
    static const Block BATAK;

    /// \brief The LEPCHA Unicode Block.
    static const Block LEPCHA;

    /// \brief The OL_CHIKI Unicode Block.
    static const Block OL_CHIKI;

    /// \brief The CYRILLIC_EXTENDED_C Unicode Block.
    static const Block CYRILLIC_EXTENDED_C;

    /// \brief The GEORGIAN_EXTENDED Unicode Block.
    static const Block GEORGIAN_EXTENDED;

    /// \brief The SUNDANESE_SUPPLEMENT Unicode Block.
    static const Block SUNDANESE_SUPPLEMENT;

    /// \brief The VEDIC_EXTENSIONS Unicode Block.
    static const Block VEDIC_EXTENSIONS;

    /// \brief The PHONETIC_EXTENSIONS Unicode Block.
    static const Block PHONETIC_EXTENSIONS;

    /// \brief The PHONETIC_EXTENSIONS_SUPPLEMENT Unicode Block.
    static const Block PHONETIC_EXTENSIONS_SUPPLEMENT;

    /// \brief The COMBINING_DIACRITICAL_MARKS_SUPPLEMENT Unicode Block.
    static const Block COMBINING_DIACRITICAL_MARKS_SUPPLEMENT;

    /// \brief The LATIN_EXTENDED_ADDITIONAL Unicode Block.
    static const Block LATIN_EXTENDED_ADDITIONAL;

    /// \brief The GREEK_EXTENDED Unicode Block.
    static const Block GREEK_EXTENDED;

    /// \brief The GENERAL_PUNCTUATION Unicode Block.
    static const Block GENERAL_PUNCTUATION;

    /// \brief The SUPERSCRIPTS_AND_SUBSCRIPTS Unicode Block.
    static const Block SUPERSCRIPTS_AND_SUBSCRIPTS;

    /// \brief The CURRENCY_SYMBOLS Unicode Block.
    static const Block CURRENCY_SYMBOLS;

    /// \brief The COMBINING_DIACRITICAL_MARKS_FOR_SYMBOLS Unicode Block.
    static const Block COMBINING_DIACRITICAL_MARKS_FOR_SYMBOLS;

    /// \brief The LETTERLIKE_SYMBOLS Unicode Block.
    static const Block LETTERLIKE_SYMBOLS;

    /// \brief The NUMBER_FORMS Unicode Block.
    static const Block NUMBER_FORMS;

    /// \brief The ARROWS Unicode Block.
    static const Block ARROWS;

    /// \brief The MATHEMATICAL_OPERATORS Unicode Block.
    static const Block MATHEMATICAL_OPERATORS;

    /// \brief The MISCELLANEOUS_TECHNICAL Unicode Block.
    static const Block MISCELLANEOUS_TECHNICAL;

    /// \brief The CONTROL_PICTURES Unicode Block.
    static const Block CONTROL_PICTURES;

    /// \brief The OPTICAL_CHARACTER_RECOGNITION Unicode Block.
    static const Block OPTICAL_CHARACTER_RECOGNITION;

    /// \brief The ENCLOSED_ALPHANUMERICS Unicode Block.
    static const Block ENCLOSED_ALPHANUMERICS;

    /// \brief The BOX_DRAWING Unicode Block.
    static const Block BOX_DRAWING;

    /// \brief The BLOCK_ELEMENTS Unicode Block.
    static const Block BLOCK_ELEMENTS;

    /// \brief The GEOMETRIC_SHAPES Unicode Block.
    static const Block GEOMETRIC_SHAPES;

    /// \brief The MISCELLANEOUS_SYMBOLS Unicode Block.
    static const Block MISCELLANEOUS_SYMBOLS;

    /// \brief The DINGBATS Unicode Block.
    static const Block DINGBATS;

    /// \brief The MISCELLANEOUS_MATHEMATICAL_SYMBOLS_A Unicode Block.
    static const Block MISCELLANEOUS_MATHEMATICAL_SYMBOLS_A;

    /// \brief The SUPPLEMENTAL_ARROWS_A Unicode Block.
    static const Block SUPPLEMENTAL_ARROWS_A;

    /// \brief The BRAILLE_PATTERNS Unicode Block.
    static const Block BRAILLE_PATTERNS;

    /// \brief The SUPPLEMENTAL_ARROWS_B Unicode Block.
    static const Block SUPPLEMENTAL_ARROWS_B;

    /// \brief The MISCELLANEOUS_MATHEMATICAL_SYMBOLS_B Unicode Block.
    static const Block MISCELLANEOUS_MATHEMATICAL_SYMBOLS_B;

    /// \brief The SUPPLEMENTAL_MATHEMATICAL_OPERATORS Unicode Block.
    static const Block SUPPLEMENTAL_MATHEMATICAL_OPERATORS;

    /// \brief The MISCELLANEOUS_SYMBOLS_AND_ARROWS Unicode Block.
    static const Block MISCELLANEOUS_SYMBOLS_AND_ARROWS;

    /// \brief The GLAGOLITIC Unicode Block.
    static const Block GLAGOLITIC;

    /// \brief The LATIN_EXTENDED_C Unicode Block.
    static const Block LATIN_EXTENDED_C;

    /// \brief The COPTIC Unicode Block.
    static const Block COPTIC;

    /// \brief The GEORGIAN_SUPPLEMENT Unicode Block.
    static const Block GEORGIAN_SUPPLEMENT;

    /// \brief The TIFINAGH Unicode Block.
    static const Block TIFINAGH;

    /// \brief The ETHIOPIC_EXTENDED Unicode Block.
    static const Block ETHIOPIC_EXTENDED;

    /// \brief The CYRILLIC_EXTENDED_A Unicode Block.
    static const Block CYRILLIC_EXTENDED_A;

    /// \brief The SUPPLEMENTAL_PUNCTUATION Unicode Block.
    static const Block SUPPLEMENTAL_PUNCTUATION;

    /// \brief The CJK_RADICALS_SUPPLEMENT Unicode Block.
    static const Block CJK_RADICALS_SUPPLEMENT;

    /// \brief The KANGXI_RADICALS Unicode Block.
    static const Block KANGXI_RADICALS;

    /// \brief The IDEOGRAPHIC_DESCRIPTION_CHARACTERS Unicode Block.
    static const Block IDEOGRAPHIC_DESCRIPTION_CHARACTERS;

    /// \brief The CJK_SYMBOLS_AND_PUNCTUATION Unicode Block.
    static const Block CJK_SYMBOLS_AND_PUNCTUATION;

    /// \brief The HIRAGANA Unicode Block.
    static const Block HIRAGANA;

    /// \brief The KATAKANA Unicode Block.
    static const Block KATAKANA;

    /// \brief The BOPOMOFO Unicode Block.
    static const Block BOPOMOFO;

    /// \brief The HANGUL_COMPATIBILITY_JAMO Unicode Block.
    static const Block HANGUL_COMPATIBILITY_JAMO;

    /// \brief The KANBUN Unicode Block.
    static const Block KANBUN;

    /// \brief The BOPOMOFO_EXTENDED Unicode Block.
    static const Block BOPOMOFO_EXTENDED;

    /// \brief The CJK_STROKES Unicode Block.
    static const Block CJK_STROKES;

    /// \brief The KATAKANA_PHONETIC_EXTENSIONS Unicode Block.
    static const Block KATAKANA_PHONETIC_EXTENSIONS;

    /// \brief The ENCLOSED_CJK_LETTERS_AND_MONTHS Unicode Block.
    static const Block ENCLOSED_CJK_LETTERS_AND_MONTHS;

    /// \brief The CJK_COMPATIBILITY Unicode Block.
    static const Block CJK_COMPATIBILITY;

    /// \brief The CJK_UNIFIED_IDEOGRAPHS_EXTENSION_A Unicode Block.
    static const Block CJK_UNIFIED_IDEOGRAPHS_EXTENSION_A;

    /// \brief The YIJING_HEXAGRAM_SYMBOLS Unicode Block.
    static const Block YIJING_HEXAGRAM_SYMBOLS;

    /// \brief The CJK_UNIFIED_IDEOGRAPHS Unicode Block.
    static const Block CJK_UNIFIED_IDEOGRAPHS;

    /// \brief The YI_SYLLABLES Unicode Block.
    static const Block YI_SYLLABLES;

    /// \brief The YI_RADICALS Unicode Block.
    static const Block YI_RADICALS;

    /// \brief The LISU Unicode Block.
    static const Block LISU;

    /// \brief The VAI Unicode Block.
    static const Block VAI;

    /// \brief The CYRILLIC_EXTENDED_B Unicode Block.
    static const Block CYRILLIC_EXTENDED_B;

    /// \brief The BAMUM Unicode Block.
    static const Block BAMUM;

    /// \brief The MODIFIER_TONE_LETTERS Unicode Block.
    static const Block MODIFIER_TONE_LETTERS;

    /// \brief The LATIN_EXTENDED_D Unicode Block.
    static const Block LATIN_EXTENDED_D;

    /// \brief The SYLOTI_NAGRI Unicode Block.
    static const Block SYLOTI_NAGRI;

    /// \brief The COMMON_INDIC_NUMBER_FORMS Unicode Block.
    static const Block COMMON_INDIC_NUMBER_FORMS;

    /// \brief The PHAGS_PA Unicode Block.
    static const Block PHAGS_PA;

    /// \brief The SAURASHTRA Unicode Block.
    static const Block SAURASHTRA;

    /// \brief The DEVANAGARI_EXTENDED Unicode Block.
    static const Block DEVANAGARI_EXTENDED;

    /// \brief The KAYAH_LI Unicode Block.
    static const Block KAYAH_LI;

    /// \brief The REJANG Unicode Block.
    static const Block REJANG;

    /// \brief The HANGUL_JAMO_EXTENDED_A Unicode Block.
    static const Block HANGUL_JAMO_EXTENDED_A;

    /// \brief The JAVANESE Unicode Block.
    static const Block JAVANESE;

    /// \brief The MYANMAR_EXTENDED_B Unicode Block.
    static const Block MYANMAR_EXTENDED_B;

    /// \brief The CHAM Unicode Block.
    static const Block CHAM;

    /// \brief The MYANMAR_EXTENDED_A Unicode Block.
    static const Block MYANMAR_EXTENDED_A;

    /// \brief The TAI_VIET Unicode Block.
    static const Block TAI_VIET;

    /// \brief The MEETEI_MAYEK_EXTENSIONS Unicode Block.
    static const Block MEETEI_MAYEK_EXTENSIONS;

    /// \brief The ETHIOPIC_EXTENDED_A Unicode Block.
    static const Block ETHIOPIC_EXTENDED_A;

    /// \brief The LATIN_EXTENDED_E Unicode Block.
    static const Block LATIN_EXTENDED_E;

    /// \brief The CHEROKEE_SUPPLEMENT Unicode Block.
    static const Block CHEROKEE_SUPPLEMENT;

    /// \brief The MEETEI_MAYEK Unicode Block.
    static const Block MEETEI_MAYEK;

    /// \brief The HANGUL_SYLLABLES Unicode Block.
    static const Block HANGUL_SYLLABLES;

    /// \brief The HANGUL_JAMO_EXTENDED_B Unicode Block.
    static const Block HANGUL_JAMO_EXTENDED_B;

    /// \brief The HIGH_SURROGATES Unicode Block.
    static const Block HIGH_SURROGATES;

    /// \brief The HIGH_PRIVATE_USE_SURROGATES Unicode Block.
    static const Block HIGH_PRIVATE_USE_SURROGATES;

    /// \brief The LOW_SURROGATES Unicode Block.
    static const Block LOW_SURROGATES;

    /// \brief The PRIVATE_USE_AREA Unicode Block.
    static const Block PRIVATE_USE_AREA;

    /// \brief The CJK_COMPATIBILITY_IDEOGRAPHS Unicode Block.
    static const Block CJK_COMPATIBILITY_IDEOGRAPHS;

    /// \brief The ALPHABETIC_PRESENTATION_FORMS Unicode Block.
    static const Block ALPHABETIC_PRESENTATION_FORMS;

    /// \brief The ARABIC_PRESENTATION_FORMS_A Unicode Block.
    static const Block ARABIC_PRESENTATION_FORMS_A;

    /// \brief The VARIATION_SELECTORS Unicode Block.
    static const Block VARIATION_SELECTORS;

    /// \brief The VERTICAL_FORMS Unicode Block.
    static const Block VERTICAL_FORMS;

    /// \brief The COMBINING_HALF_MARKS Unicode Block.
    static const Block COMBINING_HALF_MARKS;

    /// \brief The CJK_COMPATIBILITY_FORMS Unicode Block.
    static const Block CJK_COMPATIBILITY_FORMS;

    /// \brief The SMALL_FORM_VARIANTS Unicode Block.
    static const Block SMALL_FORM_VARIANTS;

    /// \brief The ARABIC_PRESENTATION_FORMS_B Unicode Block.
    static const Block ARABIC_PRESENTATION_FORMS_B;

    /// \brief The HALFWIDTH_AND_FULLWIDTH_FORMS Unicode Block.
    static const Block HALFWIDTH_AND_FULLWIDTH_FORMS;

    /// \brief The SPECIALS Unicode Block.
    static const Block SPECIALS;

    /// \brief The LINEAR_B_SYLLABARY Unicode Block.
    static const Block LINEAR_B_SYLLABARY;

    /// \brief The LINEAR_B_IDEOGRAMS Unicode Block.
    static const Block LINEAR_B_IDEOGRAMS;

    /// \brief The AEGEAN_NUMBERS Unicode Block.
    static const Block AEGEAN_NUMBERS;

    /// \brief The ANCIENT_GREEK_NUMBERS Unicode Block.
    static const Block ANCIENT_GREEK_NUMBERS;

    /// \brief The ANCIENT_SYMBOLS Unicode Block.
    static const Block ANCIENT_SYMBOLS;

    /// \brief The PHAISTOS_DISC Unicode Block.
    static const Block PHAISTOS_DISC;

    /// \brief The LYCIAN Unicode Block.
    static const Block LYCIAN;

    /// \brief The CARIAN Unicode Block.
    static const Block CARIAN;

    /// \brief The COPTIC_EPACT_NUMBERS Unicode Block.
    static const Block COPTIC_EPACT_NUMBERS;

    /// \brief The OLD_ITALIC Unicode Block.
    static const Block OLD_ITALIC;

    /// \brief The GOTHIC Unicode Block.
    static const Block GOTHIC;

    /// \brief The OLD_PERMIC Unicode Block.
    static const Block OLD_PERMIC;

    /// \brief The UGARITIC Unicode Block.
    static const Block UGARITIC;

    /// \brief The OLD_PERSIAN Unicode Block.
    static const Block OLD_PERSIAN;

    /// \brief The DESERET Unicode Block.
    static const Block DESERET;

    /// \brief The SHAVIAN Unicode Block.
    static const Block SHAVIAN;

    /// \brief The OSMANYA Unicode Block.
    static const Block OSMANYA;

    /// \brief The OSAGE Unicode Block.
    static const Block OSAGE;

    /// \brief The ELBASAN Unicode Block.
    static const Block ELBASAN;

    /// \brief The CAUCASIAN_ALBANIAN Unicode Block.
    static const Block CAUCASIAN_ALBANIAN;

    /// \brief The LINEAR_A Unicode Block.
    static const Block LINEAR_A;

    /// \brief The CYPRIOT_SYLLABARY Unicode Block.
    static const Block CYPRIOT_SYLLABARY;

    /// \brief The IMPERIAL_ARAMAIC Unicode Block.
    static const Block IMPERIAL_ARAMAIC;

    /// \brief The PALMYRENE Unicode Block.
    static const Block PALMYRENE;

    /// \brief The NABATAEAN Unicode Block.
    static const Block NABATAEAN;

    /// \brief The HATRAN Unicode Block.
    static const Block HATRAN;

    /// \brief The PHOENICIAN Unicode Block.
    static const Block PHOENICIAN;

    /// \brief The LYDIAN Unicode Block.
    static const Block LYDIAN;

    /// \brief The MEROITIC_HIEROGLYPHS Unicode Block.
    static const Block MEROITIC_HIEROGLYPHS;

    /// \brief The MEROITIC_CURSIVE Unicode Block.
    static const Block MEROITIC_CURSIVE;

    /// \brief The KHAROSHTHI Unicode Block.
    static const Block KHAROSHTHI;

    /// \brief The OLD_SOUTH_ARABIAN Unicode Block.
    static const Block OLD_SOUTH_ARABIAN;

    /// \brief The OLD_NORTH_ARABIAN Unicode Block.
    static const Block OLD_NORTH_ARABIAN;

    /// \brief The MANICHAEAN Unicode Block.
    static const Block MANICHAEAN;

    /// \brief The AVESTAN Unicode Block.
    static const Block AVESTAN;

    /// \brief The INSCRIPTIONAL_PARTHIAN Unicode Block.
    static const Block INSCRIPTIONAL_PARTHIAN;

    /// \brief The INSCRIPTIONAL_PAHLAVI Unicode Block.
    static const Block INSCRIPTIONAL_PAHLAVI;

    /// \brief The PSALTER_PAHLAVI Unicode Block.
    static const Block PSALTER_PAHLAVI;

    /// \brief The OLD_TURKIC Unicode Block.
    static const Block OLD_TURKIC;

    /// \brief The OLD_HUNGARIAN Unicode Block.
    static const Block OLD_HUNGARIAN;

    /// \brief The HANIFI_ROHINGYA Unicode Block.
    static const Block HANIFI_ROHINGYA;

    /// \brief The RUMI_NUMERAL_SYMBOLS Unicode Block.
    static const Block RUMI_NUMERAL_SYMBOLS;

    /// \brief The OLD_SOGDIAN Unicode Block.
    static const Block OLD_SOGDIAN;

    /// \brief The SOGDIAN Unicode Block.
    static const Block SOGDIAN;

    /// \brief The ELYMAIC Unicode Block.
    static const Block ELYMAIC;

    /// \brief The BRAHMI Unicode Block.
    static const Block BRAHMI;

    /// \brief The KAITHI Unicode Block.
    static const Block KAITHI;

    /// \brief The SORA_SOMPENG Unicode Block.
    static const Block SORA_SOMPENG;

    /// \brief The CHAKMA Unicode Block.
    static const Block CHAKMA;

    /// \brief The MAHAJANI Unicode Block.
    static const Block MAHAJANI;

    /// \brief The SHARADA Unicode Block.
    static const Block SHARADA;

    /// \brief The SINHALA_ARCHAIC_NUMBERS Unicode Block.
    static const Block SINHALA_ARCHAIC_NUMBERS;

    /// \brief The KHOJKI Unicode Block.
    static const Block KHOJKI;

    /// \brief The MULTANI Unicode Block.
    static const Block MULTANI;

    /// \brief The KHUDAWADI Unicode Block.
    static const Block KHUDAWADI;

    /// \brief The GRANTHA Unicode Block.
    static const Block GRANTHA;

    /// \brief The NEWA Unicode Block.
    static const Block NEWA;

    /// \brief The TIRHUTA Unicode Block.
    static const Block TIRHUTA;

    /// \brief The SIDDHAM Unicode Block.
    static const Block SIDDHAM;

    /// \brief The MODI Unicode Block.
    static const Block MODI;

    /// \brief The MONGOLIAN_SUPPLEMENT Unicode Block.
    static const Block MONGOLIAN_SUPPLEMENT;

    /// \brief The TAKRI Unicode Block.
    static const Block TAKRI;

    /// \brief The AHOM Unicode Block.
    static const Block AHOM;

    /// \brief The DOGRA Unicode Block.
    static const Block DOGRA;

    /// \brief The WARANG_CITI Unicode Block.
    static const Block WARANG_CITI;

    /// \brief The NANDINAGARI Unicode Block.
    static const Block NANDINAGARI;

    /// \brief The ZANABAZAR_SQUARE Unicode Block.
    static const Block ZANABAZAR_SQUARE;

    /// \brief The SOYOMBO Unicode Block.
    static const Block SOYOMBO;

    /// \brief The PAU_CIN_HAU Unicode Block.
    static const Block PAU_CIN_HAU;

    /// \brief The BHAIKSUKI Unicode Block.
    static const Block BHAIKSUKI;

    /// \brief The MARCHEN Unicode Block.
    static const Block MARCHEN;

    /// \brief The MASARAM_GONDI Unicode Block.
    static const Block MASARAM_GONDI;

    /// \brief The GUNJALA_GONDI Unicode Block.
    static const Block GUNJALA_GONDI;

    /// \brief The MAKASAR Unicode Block.
    static const Block MAKASAR;

    /// \brief The TAMIL_SUPPLEMENT Unicode Block.
    static const Block TAMIL_SUPPLEMENT;

    /// \brief The CUNEIFORM Unicode Block.
    static const Block CUNEIFORM;

    /// \brief The CUNEIFORM_NUMBERS_AND_PUNCTUATION Unicode Block.
    static const Block CUNEIFORM_NUMBERS_AND_PUNCTUATION;

    /// \brief The EARLY_DYNASTIC_CUNEIFORM Unicode Block.
    static const Block EARLY_DYNASTIC_CUNEIFORM;

    /// \brief The EGYPTIAN_HIEROGLYPHS Unicode Block.
    static const Block EGYPTIAN_HIEROGLYPHS;

    /// \brief The EGYPTIAN_HIEROGLYPH_FORMAT_CONTROLS Unicode Block.
    static const Block EGYPTIAN_HIEROGLYPH_FORMAT_CONTROLS;

    /// \brief The ANATOLIAN_HIEROGLYPHS Unicode Block.
    static const Block ANATOLIAN_HIEROGLYPHS;

    /// \brief The BAMUM_SUPPLEMENT Unicode Block.
    static const Block BAMUM_SUPPLEMENT;

    /// \brief The MRO Unicode Block.
    static const Block MRO;

    /// \brief The BASSA_VAH Unicode Block.
    static const Block BASSA_VAH;

    /// \brief The PAHAWH_HMONG Unicode Block.
    static const Block PAHAWH_HMONG;

    /// \brief The MEDEFAIDRIN Unicode Block.
    static const Block MEDEFAIDRIN;

    /// \brief The MIAO Unicode Block.
    static const Block MIAO;

    /// \brief The IDEOGRAPHIC_SYMBOLS_AND_PUNCTUATION Unicode Block.
    static const Block IDEOGRAPHIC_SYMBOLS_AND_PUNCTUATION;

    /// \brief The TANGUT Unicode Block.
    static const Block TANGUT;

    /// \brief The TANGUT_COMPONENTS Unicode Block.
    static const Block TANGUT_COMPONENTS;

    /// \brief The KANA_SUPPLEMENT Unicode Block.
    static const Block KANA_SUPPLEMENT;

    /// \brief The KANA_EXTENDED_A Unicode Block.
    static const Block KANA_EXTENDED_A;

    /// \brief The SMALL_KANA_EXTENSION Unicode Block.
    static const Block SMALL_KANA_EXTENSION;

    /// \brief The NUSHU Unicode Block.
    static const Block NUSHU;

    /// \brief The DUPLOYAN Unicode Block.
    static const Block DUPLOYAN;

    /// \brief The SHORTHAND_FORMAT_CONTROLS Unicode Block.
    static const Block SHORTHAND_FORMAT_CONTROLS;

    /// \brief The BYZANTINE_MUSICAL_SYMBOLS Unicode Block.
    static const Block BYZANTINE_MUSICAL_SYMBOLS;

    /// \brief The MUSICAL_SYMBOLS Unicode Block.
    static const Block MUSICAL_SYMBOLS;

    /// \brief The ANCIENT_GREEK_MUSICAL_NOTATION Unicode Block.
    static const Block ANCIENT_GREEK_MUSICAL_NOTATION;

    /// \brief The MAYAN_NUMERALS Unicode Block.
    static const Block MAYAN_NUMERALS;

    /// \brief The TAI_XUAN_JING_SYMBOLS Unicode Block.
    static const Block TAI_XUAN_JING_SYMBOLS;

    /// \brief The COUNTING_ROD_NUMERALS Unicode Block.
    static const Block COUNTING_ROD_NUMERALS;

    /// \brief The MATHEMATICAL_ALPHANUMERIC_SYMBOLS Unicode Block.
    static const Block MATHEMATICAL_ALPHANUMERIC_SYMBOLS;

    /// \brief The SUTTON_SIGNWRITING Unicode Block.
    static const Block SUTTON_SIGNWRITING;

    /// \brief The GLAGOLITIC_SUPPLEMENT Unicode Block.
    static const Block GLAGOLITIC_SUPPLEMENT;

    /// \brief The NYIAKENG_PUACHUE_HMONG Unicode Block.
    static const Block NYIAKENG_PUACHUE_HMONG;

    /// \brief The WANCHO Unicode Block.
    static const Block WANCHO;

    /// \brief The MENDE_KIKAKUI Unicode Block.
    static const Block MENDE_KIKAKUI;

    /// \brief The ADLAM Unicode Block.
    static const Block ADLAM;

    /// \brief The INDIC_SIYAQ_NUMBERS Unicode Block.
    static const Block INDIC_SIYAQ_NUMBERS;

    /// \brief The OTTOMAN_SIYAQ_NUMBERS Unicode Block.
    static const Block OTTOMAN_SIYAQ_NUMBERS;

    /// \brief The ARABIC_MATHEMATICAL_ALPHABETIC_SYMBOLS Unicode Block.
    static const Block ARABIC_MATHEMATICAL_ALPHABETIC_SYMBOLS;

    /// \brief The MAHJONG_TILES Unicode Block.
    static const Block MAHJONG_TILES;

    /// \brief The DOMINO_TILES Unicode Block.
    static const Block DOMINO_TILES;

    /// \brief The PLAYING_CARDS Unicode Block.
    static const Block PLAYING_CARDS;

    /// \brief The ENCLOSED_ALPHANUMERIC_SUPPLEMENT Unicode Block.
    static const Block ENCLOSED_ALPHANUMERIC_SUPPLEMENT;

    /// \brief The ENCLOSED_IDEOGRAPHIC_SUPPLEMENT Unicode Block.
    static const Block ENCLOSED_IDEOGRAPHIC_SUPPLEMENT;

    /// \brief The MISCELLANEOUS_SYMBOLS_AND_PICTOGRAPHS Unicode Block.
    static const Block MISCELLANEOUS_SYMBOLS_AND_PICTOGRAPHS;

    /// \brief The EMOTICONS Unicode Block.
    static const Block EMOTICONS;

    /// \brief The ORNAMENTAL_DINGBATS Unicode Block.
    static const Block ORNAMENTAL_DINGBATS;

    /// \brief The TRANSPORT_AND_MAP_SYMBOLS Unicode Block.
    static const Block TRANSPORT_AND_MAP_SYMBOLS;

    /// \brief The ALCHEMICAL_SYMBOLS Unicode Block.
    static const Block ALCHEMICAL_SYMBOLS;

    /// \brief The GEOMETRIC_SHAPES_EXTENDED Unicode Block.
    static const Block GEOMETRIC_SHAPES_EXTENDED;

    /// \brief The SUPPLEMENTAL_ARROWS_C Unicode Block.
    static const Block SUPPLEMENTAL_ARROWS_C;

    /// \brief The SUPPLEMENTAL_SYMBOLS_AND_PICTOGRAPHS Unicode Block.
    static const Block SUPPLEMENTAL_SYMBOLS_AND_PICTOGRAPHS;

    /// \brief The CHESS_SYMBOLS Unicode Block.
    static const Block CHESS_SYMBOLS;

    /// \brief The SYMBOLS_AND_PICTOGRAPHS_EXTENDED_A Unicode Block.
    static const Block SYMBOLS_AND_PICTOGRAPHS_EXTENDED_A;

    /// \brief The CJK_UNIFIED_IDEOGRAPHS_EXTENSION_B Unicode Block.
    static const Block CJK_UNIFIED_IDEOGRAPHS_EXTENSION_B;

    /// \brief The CJK_UNIFIED_IDEOGRAPHS_EXTENSION_C Unicode Block.
    static const Block CJK_UNIFIED_IDEOGRAPHS_EXTENSION_C;

    /// \brief The CJK_UNIFIED_IDEOGRAPHS_EXTENSION_D Unicode Block.
    static const Block CJK_UNIFIED_IDEOGRAPHS_EXTENSION_D;

    /// \brief The CJK_UNIFIED_IDEOGRAPHS_EXTENSION_E Unicode Block.
    static const Block CJK_UNIFIED_IDEOGRAPHS_EXTENSION_E;

    /// \brief The CJK_UNIFIED_IDEOGRAPHS_EXTENSION_F Unicode Block.
    static const Block CJK_UNIFIED_IDEOGRAPHS_EXTENSION_F;

    /// \brief The CJK_COMPATIBILITY_IDEOGRAPHS_SUPPLEMENT Unicode Block.
    static const Block CJK_COMPATIBILITY_IDEOGRAPHS_SUPPLEMENT;

    /// \brief The TAGS Unicode Block.
    static const Block TAGS;

    /// \brief The VARIATION_SELECTORS_SUPPLEMENT Unicode Block.
    static const Block VARIATION_SELECTORS_SUPPLEMENT;

    /// \brief The SUPPLEMENTARY_PRIVATE_USE_AREA_A Unicode Block.
    static const Block SUPPLEMENTARY_PRIVATE_USE_AREA_A;

    /// \brief The SUPPLEMENTARY_PRIVATE_USE_AREA_B Unicode Block.
    static const Block SUPPLEMENTARY_PRIVATE_USE_AREA_B;


};


/// \brief A class for breaking lines according to the Unicode standard.
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
    /// \brief The language used for line breaking.
    std::string _language;
    
};


/// \brief A class for breaking lines according to the Unicode standard.
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
    /// \brief Normalize string.
    /// \param utf8 The string to normalize.
    /// \param form The normalization form to apply.
    /// \returns the normalized strring.
    static std::string normalize(const std::string& utf8,
                                 Unicode::NormalizationForm form = Unicode::NormalizationForm::NFC);

    /// \brief Perform case folding.
    ///
    /// Performs unicode case folding, to be able to do a case-insensitive
    /// string comparison.
    ///
    /// \param utf8 a utf8-encoded string.
    /// \returns a case-folded utf8-encoded string.
    static std::string casefold(const std::string& utf8);

    /// \brief Check to see if a UTF8 string has valid UTF8 encoding.

    /// \returns true if the UTF8 encoding is valid.
    static bool isValid(const std::string& utf8);

    // check to see if a string starts with a UTF8 BOM (byte order mark)
    static bool startsWithBOM(const std::string& utf8);

    // attempt to repair a broken UTF8 string
    static std::string repair(const std::string& utf8, char32_t replacement = -1);

    static std::string& repairInPlace(std::string& txt, char32_t replacement = -1);

    // calculate the number of UTF8 chars (string.length() returns the number of bytes)
    static std::size_t distance(const std::string& utf8);

    /// \brief Perform a case-insensitive string comparison on UTF-8 encoded strings.
    ///
    /// Strings are normalized and case-folded according to the Unicode standard
    /// and the strings are then compared.
    ///
    /// \param utf8String0 The first UTF8-encoded string to compare.
    /// \param utf8String1 The second UTF8-encoded string to compare.
    /// \returs 1) a negative value if utf8String0 appears before the character
    ///         sequence specified by utf8String1, in lexicographical order,
    ///         2) (0) zero if both character sequences compare equivalent,
    ///         3) A positive value if utf8String0 appears after the character
    ///         sequence specified by utf8String1, in lexicographical order.
    static int icompare(const std::string& utf8String0, const std::string& utf8String1);

    // Unicode-based case conversion
    static std::string toUpper(const std::string& utf8);
    static std::string& toUpperInPlace(std::string& utf8);
    static std::string toLower(const std::string& utf8);
    static std::string& toLowerInPlace(std::string& utf8);

    static std::u16string toUTF16(const std::string& utf8);
    static std::u32string toUTF32(const std::string& utf8);
};


class UTF16
{
public:
    static std::string toUTF8(const std::u16string& utf16);
    static std::u32string toUTF32(const std::u16string& utf16);
};


class UTF32
{
public:
    /// \brief Determine if a char32_t is a valid Unicode code point.
    /// \param utf32 A char32_t value to test.
    /// \returns true if the given value is a valid Unicode code point.
    static bool isValid(char32_t utf32);

    static bool isPrintable(char32_t utf32); // is this a "printable" character?
                                                             // True if the Unicode category is not CONTROL
                                                             // This does not guarantee that the character
                                                             // has a visible "glyph".
    
    // is this a "control" Unicode character?
    // this is broadly defined to include Unicode
    // CONTROL category, and other invisible glyphs
    // this is Not the opposite of isPrintable.
    static bool isControl(char32_t utf32);

    /// \brief is this a Unicode "Titlecase" code point?
    static bool isTitle(char32_t utf32);
    static bool isSpace(char32_t utf32);
    static bool isDigit(char32_t utf32);
    static bool isPunct(char32_t utf32);
    static bool isAlpha(char32_t utf32);

    /// \brief Is this character alphanumeric?
    ///
    /// isAlphaNumeric() is equivalent to isAlpha() || isDigit()
    ///
    /// \returns true if alphanumeric.
    static bool isAlphaNumeric(char32_t utf32); // isAlpha || isDigit
    static bool isLower(char32_t utf32);
    static bool isUpper(char32_t utf32);

    // conversions
    static char32_t toLower(char32_t utf32);
    static char32_t toUpper(char32_t utf32);
    static char32_t& toLowerInPlace(char32_t& utf32);
    static char32_t& toUpperInPlace(char32_t& utf32);

    // Unicode string based conversions
    static std::u32string toLower(const std::u32string& utf32);
    static std::u32string toUpper(const std::u32string& utf32);
    static std::u32string& toLowerInPlace(std::u32string& utf32);
    static std::u32string& toUpperInPlace(std::u32string& utf32);

    static std::string toUTF8(char32_t utf32);
    static std::string toUTF8(const std::u32string& utf32);
    static std::u16string toUTF16(char32_t utf32);
    static std::u16string toUTF16(const std::u32string& utf32);

};


/// \brief A class for converting between character sets.
///
/// This class is not thread-safe.
class TextConverter
{
public:
    struct Settings;

    /// \brief Create an unloaded TextConverter.
    TextConverter();

    /// \brief Create a TextConverter with the given Settings.
    TextConverter(const Settings& settings);

    /// \brief Create a TextConverter with the given input and output encoding.
    /// \param inputEncoding The input encoding character encoding.
    /// \param outputEncoding The output encoding character encoding.
    TextConverter(const std::string& inputEncoding,
                  const std::string& outputEncoding);

    /// \brief Create a TextConverter with a UTF-8 input encoding.
    /// \param outputEncoding The desired output encoding.
    TextConverter(const std::string& outputEncoding);

    /// \brief Destroy the text converter.
    ~TextConverter();

    /// \brief Set up a TextConverter with a UTF-8 input encoding.
    /// \param outputEncoding The desired output encoding.
    /// \returns true if the TextConverter is loaded with valid Settings.
    bool setup(const std::string& outputEncoding);

    /// \brief Set up a TextConverter with a UTF-8 input encoding.
    /// \param outputEncoding The desired output encoding.
    /// \returns true if the TextConverter is loaded with valid Settings.
    bool setup(const Settings& settings);

    /// \brief True if the TextConverter is loaded with valid Settings.
    bool isLoaded() const;

    /// \brief Reset the converter state.
    void reset();

    /// \brief Convert encoded input text to the encoded output text.
    /// \param input The input string corresponding to inputEncoding.
    /// \param output A string in which to write the output encoded with outputEncoding.
    /// \returns -1 if error.
    ///           0 if no error.
    ///          >0 For number of invalid byte sequences in source.
    int convert(const std::string& input, std::string& output) const;

    /// \brief Convert encoded input text to the encoded output text.
    /// \param input The input string corresponding to inputEncoding.
    /// \returns the encoded input or an empty string on error.
    std::string convert(const std::string& input) const;

    /// \brief Settings to configure the TextConverter.
    struct Settings
    {
        /// \brief The input encoding.
        std::string inputEncoding;

        /// \brief The output encoding.
        std::string outputEncoding;

        /// \brief True if errors should be skipped.
        ///
        /// If errors are skipped, \p defaultCharacter is used.
        bool skipErrors = true;

        /// \brief If errors are skipped, this character will be used.
        char defaultCharacter = '?';

        /// \brief Transliterate when an output encoding is not available.
        ///
        /// If true, characters unrepresented in output encoding it can be
        /// approximated by characters that look similar.
        bool transliterate = false;
    };


    /// \returns a list of available encodings.
    static std::vector<std::string> encodings();

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

private:
    /// \brief The Settings for this converter.
    Settings _settings;

    /// \brief The conversion descriptor.
    std::shared_ptr<void> _cd = nullptr;
};


} // namespace ofx

