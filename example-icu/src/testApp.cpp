#include "testApp.h"

int nTestStrings = 8;
string testStrings[] = {
    "0123456789",       // length = 10, valid
    "ABCDEFGHIJ",       // length = 10, valid
    "\xe6\x97\xa5\xd1\x88\xfa", // length = 6, not valid
    "والثعلب البني السريع.", // arabic, length = 21
    "бързо кафяво лисица.", // bulgarian
    "דער שנעל ברוין פוקס.", // yiddish
    "สุนัขจิ้งจอกสีน้ำตาลอย่างรวดเร็ว", // thai
    "퀵 브라운 폭스 (빠른 갈색 여우).", // korean
};

int nEncoderStrings = 9;
string encoderStrings[] = {
    "költészet",
    "poetry",
    "thơ",
    "詩",
    "ポエトリー",
    "поезия",
    "ಕಾವ್ಯ",
    "கவிதை",
    "أشعار"
};


static const UChar readonly[]={
    0x61, 0x31, 0x20ac
};
static UChar writeable[]={
    0x62, 0x32, 0xdbc0, 0xdc01 // includes a surrogate pair for a supplementary code point
};
static char outz[100];

static UFILE *out;

#define LENGTHOF(array) (sizeof(array)/sizeof((array)[0]))

#define BUFFER_SIZE 8192

static void
printProps(UChar32 codePoint) {
    char buffer[100];
    UErrorCode errorCode;
    
    /* get the character name */
    errorCode=U_ZERO_ERROR;
    u_charName(codePoint, U_UNICODE_CHAR_NAME, buffer, sizeof(buffer), &errorCode);
    
    /* print the code point and the character name */
    printf("U+%04lx\t%s\n", codePoint, buffer);
    
    /* print some properties */
    printf("  general category (numeric enum value): %u\n", u_charType(codePoint));
    
    /* note: these APIs do not provide the data from SpecialCasing.txt */
    printf("  is lowercase: %d  uppercase: U+%04lx\n", u_islower(codePoint), u_toupper(codePoint));
    
    printf("  is digit: %d  decimal digit value: %d\n", u_isdigit(codePoint), u_charDigitValue(codePoint));
    
    printf("  BiDi directional category (numeric enum value): %u\n", u_charDirection(codePoint));
}


void printUChar(UChar32 ch)
{
    if(ch < 127) {
        u_fprintf(out, "%C", (UChar) ch);
    } else if (ch == CharacterIterator::DONE) {
        u_fprintf(out, "[CharacterIterator::DONE = 0xFFFF]");
    } else {
        u_fprintf(out, "[%X]", ch);
    }
}


void printUnicodeString(const UnicodeString &s) {
    char charBuf[1000];
    s.extract(0, s.length(), charBuf, sizeof(charBuf)-1, 0);   
    charBuf[sizeof(charBuf)-1] = 0;          
    printf("%s", charBuf);
}


void printTextRange( BreakIterator& iterator, 
                    int32_t start, int32_t end )
{
    CharacterIterator *strIter = iterator.getText().clone();
    UnicodeString  s;
    strIter->getText(s);
    
    printf(" %ld %ld\t", (long)start, (long)end);
    printUnicodeString(UnicodeString(s, 0, start));
    printf("|");
    printUnicodeString(UnicodeString(s, start, end-start));
    printf("|");
    printUnicodeString(UnicodeString(s, end));
    puts("");
    delete strIter;
}


/* Print each element in order: */
void printEachForward( BreakIterator& boundary)
{
    int32_t start = boundary.first();
    for (int32_t end = boundary.next();
         end != BreakIterator::DONE;
         start = end, end = boundary.next())
    {
        printTextRange( boundary, start, end );
    }
}

/* Print each element in reverse order: */
void printEachBackward( BreakIterator& boundary)
{
    int32_t end = boundary.last();
    for (int32_t start = boundary.previous();
         start != BreakIterator::DONE;
         end = start, start = boundary.previous())
    {
        printTextRange( boundary, start, end );
    }
}

/* Print the first element */
void printFirst(BreakIterator& boundary)
{
    int32_t start = boundary.first();
    int32_t end = boundary.next();
    printTextRange( boundary, start, end );
}

/* Print the last element */
void printLast(BreakIterator& boundary)
{
    int32_t end = boundary.last();
    int32_t start = boundary.previous();
    printTextRange( boundary, start, end );
}

/* Print the element at a specified position */
void printAt(BreakIterator &boundary, int32_t pos )
{
    int32_t end = boundary.following(pos);
    int32_t start = boundary.previous();
    printTextRange( boundary, start, end );
}


//--------------------------------------------------------------
void testApp::setup(){
    
    out = u_finit(stdout, NULL, NULL);

    breakSample();
    caseConversion();
    
    charIter();
    strIter();
    
    charsetDetect();
    
    ucodeData();

    
    unicodeDemo();

}

void testApp::breakSample() {
    
    puts("ICU Break Iterator Sample Program\n");
    puts("C++ Break Iteration\n");
    BreakIterator* boundary;
    UnicodeString stringToExamine("Aaa bbb ccc. Ddd eee fff.");
    printf("Examining: ");
    printUnicodeString(stringToExamine);
    puts("");
    
    //print each sentence in forward and reverse order
    UErrorCode status = U_ZERO_ERROR;
    boundary = BreakIterator::createSentenceInstance(
                                                     Locale::getUS(), status );
    if (U_FAILURE(status)) {
        printf("failed to create sentence break iterator.  status = %s", 
               u_errorName(status));
       // exit(1);
    }
    
    boundary->setText(stringToExamine);
    puts("\n Sentence Boundaries... ");
    puts("----- forward: -----------");
    printEachForward(*boundary);
    puts("----- backward: ----------");
    printEachBackward(*boundary);
    delete boundary;
    
    //print each word in order
    printf("\n Word Boundaries... \n");
    boundary = BreakIterator::createWordInstance(
                                                 Locale::getUS(), status);
    boundary->setText(stringToExamine);
    puts("----- forward: -----------");
    printEachForward(*boundary);
    //print first element
    puts("----- first: -------------");
    printFirst(*boundary);
    //print last element
    puts("----- last: --------------");
    printLast(*boundary);
    //print word at charpos 10
    puts("----- at pos 10: ---------");
    printAt(*boundary, 10 );
    
    delete boundary;
    
    puts("\nEnd C++ Break Iteration");
}

void testApp::caseConversion() {
    /* End Demo boilerplate */
    
    UnicodeString string("This is a test");
    /* lowercase = "istanbul" */ 
    UChar lowercase[] = {0x69, 0x73, 0x74, 0x61, 0x6e, 0x62, 0x75, 0x6c, 0};
    /* uppercase = "LATIN CAPITAL I WITH DOT ABOVE STANBUL" */  
    UChar uppercase[] = {0x0130, 0x53, 0x54, 0x41, 0x4e, 0x42, 0x55, 0x4C, 0};
    
    UnicodeString upper(uppercase);
    UnicodeString lower(lowercase);
    
    cout << "\nstring: ";
    printUnicodeString(string);
    string.toUpper(); /* string = "THIS IS A TEST" */
    cout << "\ntoUpper(): ";
    printUnicodeString(string);
    string.toLower(); /* string = "this is a test" */
    cout <<  "\ntoLower(): ";
    printUnicodeString(string);
    
//    cout <<  "\n\nlowercase=%S, uppercase=%S\n", lowercase, uppercase);
    
    
    string = upper; 
    string.toLower(Locale("tr", "TR")); /* Turkish lower case map string =
                                         lowercase */
    cout <<  "\nupper.toLower: ";
    printUnicodeString(string);
    
    string = lower;
    string.toUpper(Locale("tr", "TR")); /* Turkish upper case map string =
                                         uppercase */
    cout <<  "\nlower.toUpper: ";
    printUnicodeString(string);
    
    
    cout <<  "\nEnd C++ sample\n\n";

}

void testApp::charIter() {
    const char testChars[] = "Now is the time for all good men to come "
    "to the aid of their country.";
    
    UnicodeString testString(testChars,"");
    const UChar *testText = testString.getTerminatedBuffer();
    
    UCharCharacterIterator iter(testText, u_strlen(testText));
    UCharCharacterIterator* test2 = (UCharCharacterIterator*)iter.clone();
    
    u_fprintf(out, "testText = %s", testChars);
    
    if (iter != *test2 ) {
        u_fprintf(out, "clone() or equals() failed: Two clones tested unequal\n");
    }
    
    UnicodeString result1, result2;
    // getting and comparing the text within the iterators
    iter.getText(result1);
    test2->getText(result2);
    if (result1 != result2) {
        u_fprintf(out, "iter.getText() != clone.getText()\n");
    } 
    
    u_fprintf(out, "\n");
    
    // Demonstrates seeking forward using the iterator.
    u_fprintf(out, "Forward  = ");
    
    UChar c = iter.first();
    printUChar(c);    // The first char
    int32_t i = 0;
    
    if (iter.startIndex() != 0 || iter.endIndex() != u_strlen(testText)) {
        u_fprintf(out, "startIndex() or endIndex() failed\n");
    }
    
    
    // Testing forward iteration...
    do {
        if (c == CharacterIterator::DONE && i != u_strlen(testText)) {
            u_fprintf(out, "Iterator reached end prematurely");
        }
        else if (c != testText[i]) {
            u_fprintf(out, "Character mismatch at position %d\n" + i);
        }
        if (iter.current() != c) {
            u_fprintf(out, "current() isn't working right");
        }
        if (iter.getIndex() != i) {
            u_fprintf(out, "getIndex() isn't working right\n");
        }
        if (c != CharacterIterator::DONE) {
            c = iter.next();
            i++;
        }
        
        u_fprintf(out, "|");
        printUChar(c);
        
    } while (c != CharacterIterator::DONE);        
    
    delete test2;
    u_fprintf(out, "\n");

}
void testApp::strIter() {
    
    const char testChars[] = "Now is the time for all good men to come "
    "to the aid of their country.";
    
    UnicodeString testString(testChars,"");
    const UChar *testText    = testString.getTerminatedBuffer();
    
    StringCharacterIterator iter(testText, u_strlen(testText));
    StringCharacterIterator* test2 = (StringCharacterIterator*)iter.clone();
    
    if (iter != *test2 ) {
        u_fprintf(out, "clone() or equals() failed: Two clones tested unequal\n");
    }
    
    UnicodeString result1, result2;
    // getting and comparing the text within the iterators
    iter.getText(result1);
    test2->getText(result2);
    if (result1 != result2) {
        u_fprintf(out, "getText() failed\n");
    }
    
    u_fprintf(out, "Backwards: ");
    
    UChar c = iter.last();
    int32_t i = iter.endIndex();
    
    printUChar(c);
    i--; // already printed out the last char 
    
    if (iter.startIndex() != 0 || iter.endIndex() != u_strlen(testText)) {
        u_fprintf(out, "startIndex() or endIndex() failed\n");
    }
    
    // Testing backward iteration over a range...
    do {
        if (c == CharacterIterator::DONE) {
            u_fprintf(out, "Iterator reached end prematurely\n");
        }
        else if (c != testText[i]) {
            u_fprintf(out, "Character mismatch at position %d\n", i);
        }
        if (iter.current() != c) {
            u_fprintf(out, "current() isn't working right\n");
        }
        if (iter.getIndex() != i) {
            u_fprintf(out, "getIndex() isn't working right [%d should be %d]\n", iter.getIndex(), i);
        }
        if (c != CharacterIterator::DONE) {
            c = iter.previous();
            i--;
        }
        
        u_fprintf(out, "|");
        printUChar(c);
    } while (c != CharacterIterator::DONE);
    
    u_fprintf(out, "\n");
    delete test2;

}

void testApp::charsetDetect() {
    
    static char buffer[BUFFER_SIZE];

    string files[] = {ofToDataPath("test_UTF8.txt"), 
        ofToDataPath("test_UTF16_NO_BOM.txt"),
        ofToDataPath("test_UTF16.txt") };
    int arg;
    
    for(arg = 0; arg < 3; arg += 1) {
        FILE *file;
        const char *filename = files[arg].c_str();
        int32_t inputLength, match, matchCount = 0;
        UCharsetDetector* csd;
        const UCharsetMatch **csm;
        UErrorCode status = U_ZERO_ERROR;
        
        if (arg > 1) {
            printf("\n");
        }
        
        file = fopen(filename, "rb");
        
        if (file == NULL) {
            printf("Cannot open file \"%s\"\n\n", filename);
            continue;
        }
        
        printf("%s:\n", filename);
        
        inputLength = (int32_t) fread(buffer, 1, BUFFER_SIZE, file);
        
        fclose(file);
        
        csd = ucsdet_open(&status);
        ucsdet_setText(csd, buffer, inputLength, &status);
        
        csm = ucsdet_detectAll(csd, &matchCount, &status);
        
        for(match = 0; match < matchCount; match += 1) {
            const char *name = ucsdet_getName(csm[match], &status);
            const char *lang = ucsdet_getLanguage(csm[match], &status);
            int32_t confidence = ucsdet_getConfidence(csm[match], &status);
            
            if (lang == NULL || strlen(lang) == 0) {
                lang = "**";
            }
            
            printf("%s (%s) %d\n", name, lang, confidence);
        }
        
        ucsdet_close(csd);
    }

}

void testApp::ucodeData() {
    static const UChar32
    codePoints[]={
        0xd, 0x20, 0x2d, 0x35, 0x65, 0x284, 0x665, 0x5678, 0x23456, 0x10317, 0x1D01F, 0x10fffd
    };
    int i;
    
    for(i=0; i<sizeof(codePoints)/sizeof(codePoints[0]); ++i) {
        printProps(codePoints[i]);
        puts("");
    }
    
    u_cleanup();

}

// default converter for the platform encoding
static UConverter *cnv=NULL;

static void
printUString(const char *announce, const UChar *s, int32_t length) {
    static char out[200];
    UChar32 c;
    int32_t i;
    UErrorCode errorCode=U_ZERO_ERROR;
    
    /*
     * Convert to the "platform encoding". See notes in printUnicodeString().
     * ucnv_fromUChars(), like most ICU APIs understands length==-1
     * to mean that the string is NUL-terminated.
     */
    ucnv_fromUChars(cnv, out, sizeof(out), s, length, &errorCode);
    if(U_FAILURE(errorCode) || errorCode==U_STRING_NOT_TERMINATED_WARNING) {
        printf("%sproblem converting string from Unicode: %s\n", announce, u_errorName(errorCode));
        return;
    }
    
    printf("%s%s {", announce, out);
    
    /* output the code points (not code units) */
    if(length>=0) {
        /* s is not NUL-terminated */
        for(i=0; i<length; /* U16_NEXT post-increments */) {
            U16_NEXT(s, i, length, c);
            printf(" %04x", c);
        }
    } else {
        /* s is NUL-terminated */
        for(i=0; /* condition in loop body */; /* U16_NEXT post-increments */) {
            U16_NEXT(s, i, length, c);
            if(c==0) {
                break;
            }
            printf(" %04x", c);
        }
    }
    printf(" }\n");
}

static void
printUnicodeString(const char *announce, const UnicodeString &s) {
    static char out[200];
    int32_t i, length;
    
    // output the string, converted to the platform encoding
    
    // Note for Windows: The "platform encoding" defaults to the "ANSI codepage",
    // which is different from the "OEM codepage" in the console window.
    // However, if you pipe the output into a file and look at it with Notepad
    // or similar, then "ANSI" characters will show correctly.
    // Production code should be aware of what encoding is required,
    // and use a UConverter or at least a charset name explicitly.
    out[s.extract(0, 99, out)]=0;
    printf("%s%s {", announce, out);
    
    // output the code units (not code points)
    length=s.length();
    for(i=0; i<length; ++i) {
        printf(" %04x", s.charAt(i));
    }
    printf(" }\n");
}

// sample code for utf.h macros -------------------------------------------- ***

static void
demo_utf_h_macros() {
    static UChar input[]={ 0x0061, 0xd800, 0xdc00, 0xdbff, 0xdfff, 0x0062 };
    UChar32 c;
    int32_t i;
    UBool isError;
    
    printf("\n* demo_utf_h_macros() -------------- ***\n\n");
    
    printUString("iterate forward through: ", input, LENGTHOF(input));
    for(i=0; i<LENGTHOF(input); /* U16_NEXT post-increments */) {
        /* Iterating forwards 
         Codepoint at offset 0: U+0061
         Codepoint at offset 1: U+10000
         Codepoint at offset 3: U+10ffff
         Codepoint at offset 5: U+0062
         */
        printf("Codepoint at offset %d: U+", i);
        U16_NEXT(input, i, LENGTHOF(input), c);
        printf("%04x\n", c); 
    }
    
    puts("");
    
    isError=FALSE;
    i=1; /* write position, gets post-incremented so needs to be in an l-value */
    U16_APPEND(input, i, LENGTHOF(input), 0x0062, isError);
    
    printUString("iterate backward through: ", input, LENGTHOF(input));
    for(i=LENGTHOF(input); i>0; /* U16_PREV pre-decrements */) {
        U16_PREV(input, 0, i, c);
        /* Iterating backwards
         Codepoint at offset 5: U+0062
         Codepoint at offset 3: U+10ffff
         Codepoint at offset 2: U+dc00 -- unpaired surrogate because lead surr. overwritten
         Codepoint at offset 1: U+0062 -- by this BMP code point
         Codepoint at offset 0: U+0061
         */
        printf("Codepoint at offset %d: U+%04x\n", i, c);
    }
}

// sample code for Unicode strings in C ------------------------------------ ***

static void demo_C_Unicode_strings() {
    printf("\n* demo_C_Unicode_strings() --------- ***\n\n");
    
    static const UChar text[]={ 0x41, 0x42, 0x43, 0 };          /* "ABC" */
    static const UChar appendText[]={ 0x61, 0x62, 0x63, 0 };    /* "abc" */
    static const UChar cmpText[]={ 0x61, 0x53, 0x73, 0x43, 0 }; /* "aSsC" */
    UChar buffer[32];
    int32_t compare;
    int32_t length=u_strlen(text); /* length=3 */
    
    /* simple ANSI C-style functions */
    buffer[0]=0;                    /* empty, NUL-terminated string */
    u_strncat(buffer, text, 1);     /* append just n=1 character ('A') */
    u_strcat(buffer, appendText);   /* buffer=="Aabc" */
    length=u_strlen(buffer);        /* length=4 */
    printUString("should be \"Aabc\": ", buffer, -1);
    
    /* bitwise comparing buffer with text */
    compare=u_strcmp(buffer, text);
    if(compare<=0) {
        printf("String comparison error, expected \"Aabc\" > \"ABC\"\n");
    }
    
    /* Build "A<sharp s>C" in the buffer... */
    u_strcpy(buffer, text);
    buffer[1]=0xdf; /* sharp s, case-compares equal to "ss" */
    printUString("should be \"A<sharp s>C\": ", buffer, -1);
    
    /* Compare two strings case-insensitively using full case folding */
    compare=u_strcasecmp(buffer, cmpText, U_FOLD_CASE_DEFAULT);
    if(compare!=0) {
        printf("String case insensitive comparison error, expected \"AbC\" to be equal to \"ABC\"\n");
    }
}

// sample code for case mappings with C APIs -------------------------------- ***

static void demoCaseMapInC() {
    /*
     * input=
     *   "aB<capital sigma>"
     *   "iI<small dotless i><capital dotted I> "
     *   "<sharp s> <small lig. ffi>"
     *   "<small final sigma><small sigma><capital sigma>"
     */
    static const UChar input[]={
        0x61, 0x42, 0x3a3,
        0x69, 0x49, 0x131, 0x130, 0x20,
        0xdf, 0x20, 0xfb03,
        0x3c2, 0x3c3, 0x3a3, 0
    };
    UChar buffer[32];
    
    UErrorCode errorCode;
    UChar32 c;
    int32_t i, j, length;
    UBool isError;
    
    printf("\n* demoCaseMapInC() ----------------- ***\n\n");
    
    /*
     * First, use simple case mapping functions which provide
     * 1:1 code point mappings without context/locale ID.
     *
     * Note that some mappings will not be "right" because some "real"
     * case mappings require context, depend on the locale ID,
     * and/or result in a change in the number of code points.
     */
    printUString("input string: ", input, -1);
    
    /* uppercase */
    isError=FALSE;
    for(i=j=0; j<LENGTHOF(buffer) && !isError; /* U16_NEXT post-increments */) {
        U16_NEXT(input, i, INT32_MAX, c); /* without length because NUL-terminated */
        if(c==0) {
            break; /* stop at terminating NUL, no need to terminate buffer */
        }
        c=u_toupper(c);
        U16_APPEND(buffer, j, LENGTHOF(buffer), c, isError);
    }
    printUString("simple-uppercased: ", buffer, j);
    /* lowercase */
    isError=FALSE;
    for(i=j=0; j<LENGTHOF(buffer) && !isError; /* U16_NEXT post-increments */) {
        U16_NEXT(input, i, INT32_MAX, c); /* without length because NUL-terminated */
        if(c==0) {
            break; /* stop at terminating NUL, no need to terminate buffer */
        }
        c=u_tolower(c);
        U16_APPEND(buffer, j, LENGTHOF(buffer), c, isError);
    }
    printUString("simple-lowercased: ", buffer, j);
    /* titlecase */
    isError=FALSE;
    for(i=j=0; j<LENGTHOF(buffer) && !isError; /* U16_NEXT post-increments */) {
        U16_NEXT(input, i, INT32_MAX, c); /* without length because NUL-terminated */
        if(c==0) {
            break; /* stop at terminating NUL, no need to terminate buffer */
        }
        c=u_totitle(c);
        U16_APPEND(buffer, j, LENGTHOF(buffer), c, isError);
    }
    printUString("simple-titlecased: ", buffer, j);
    /* case-fold/default */
    isError=FALSE;
    for(i=j=0; j<LENGTHOF(buffer) && !isError; /* U16_NEXT post-increments */) {
        U16_NEXT(input, i, INT32_MAX, c); /* without length because NUL-terminated */
        if(c==0) {
            break; /* stop at terminating NUL, no need to terminate buffer */
        }
        c=u_foldCase(c, U_FOLD_CASE_DEFAULT);
        U16_APPEND(buffer, j, LENGTHOF(buffer), c, isError);
    }
    printUString("simple-case-folded/default: ", buffer, j);
    /* case-fold/Turkic */
    isError=FALSE;
    for(i=j=0; j<LENGTHOF(buffer) && !isError; /* U16_NEXT post-increments */) {
        U16_NEXT(input, i, INT32_MAX, c); /* without length because NUL-terminated */
        if(c==0) {
            break; /* stop at terminating NUL, no need to terminate buffer */
        }
        c=u_foldCase(c, U_FOLD_CASE_EXCLUDE_SPECIAL_I);
        U16_APPEND(buffer, j, LENGTHOF(buffer), c, isError);
    }
    printUString("simple-case-folded/Turkic: ", buffer, j);
    
    /*
     * Second, use full case mapping functions which provide
     * 1:n code point mappings (n can be 0!) and are sensitive to context and locale ID.
     *
     * Note that lower/upper/titlecasing take a locale ID while case-folding
     * has bit flag options instead, by design of the Unicode SpecialCasing.txt UCD file.
     *
     * Also, string titlecasing requires a BreakIterator to find starts of words.
     * The sample code here passes in a NULL pointer; u_strToTitle() will open and close a default
     * titlecasing BreakIterator automatically.
     * For production code where many strings are titlecased it would be more efficient
     * to open a BreakIterator externally and pass it in.
     */
    printUString("\ninput string: ", input, -1);
    
    /* lowercase/English */
    errorCode=U_ZERO_ERROR;
    length=u_strToLower(buffer, LENGTHOF(buffer), input, -1, "en", &errorCode);
    if(U_SUCCESS(errorCode)) {
        printUString("full-lowercased/en: ", buffer, length);
    } else {
        printf("error in u_strToLower(en)=%ld error=%s\n", length, u_errorName(errorCode));
    }
    /* lowercase/Turkish */
    errorCode=U_ZERO_ERROR;
    length=u_strToLower(buffer, LENGTHOF(buffer), input, -1, "tr", &errorCode);
    if(U_SUCCESS(errorCode)) {
        printUString("full-lowercased/tr: ", buffer, length);
    } else {
        printf("error in u_strToLower(tr)=%ld error=%s\n", length, u_errorName(errorCode));
    }
    /* uppercase/English */
    errorCode=U_ZERO_ERROR;
    length=u_strToUpper(buffer, LENGTHOF(buffer), input, -1, "en", &errorCode);
    if(U_SUCCESS(errorCode)) {
        printUString("full-uppercased/en: ", buffer, length);
    } else {
        printf("error in u_strToUpper(en)=%ld error=%s\n", length, u_errorName(errorCode));
    }
    /* uppercase/Turkish */
    errorCode=U_ZERO_ERROR;
    length=u_strToUpper(buffer, LENGTHOF(buffer), input, -1, "tr", &errorCode);
    if(U_SUCCESS(errorCode)) {
        printUString("full-uppercased/tr: ", buffer, length);
    } else {
        printf("error in u_strToUpper(tr)=%ld error=%s\n", length, u_errorName(errorCode));
    }
    /* titlecase/English */
    errorCode=U_ZERO_ERROR;
    length=u_strToTitle(buffer, LENGTHOF(buffer), input, -1, NULL, "en", &errorCode);
    if(U_SUCCESS(errorCode)) {
        printUString("full-titlecased/en: ", buffer, length);
    } else {
        printf("error in u_strToTitle(en)=%ld error=%s\n", length, u_errorName(errorCode));
    }
    /* titlecase/Turkish */
    errorCode=U_ZERO_ERROR;
    length=u_strToTitle(buffer, LENGTHOF(buffer), input, -1, NULL, "tr", &errorCode);
    if(U_SUCCESS(errorCode)) {
        printUString("full-titlecased/tr: ", buffer, length);
    } else {
        printf("error in u_strToTitle(tr)=%ld error=%s\n", length, u_errorName(errorCode));
    }
    /* case-fold/default */
    errorCode=U_ZERO_ERROR;
    length=u_strFoldCase(buffer, LENGTHOF(buffer), input, -1, U_FOLD_CASE_DEFAULT, &errorCode);
    if(U_SUCCESS(errorCode)) {
        printUString("full-case-folded/default: ", buffer, length);
    } else {
        printf("error in u_strFoldCase(default)=%ld error=%s\n", length, u_errorName(errorCode));
    }
    /* case-fold/Turkic */
    errorCode=U_ZERO_ERROR;
    length=u_strFoldCase(buffer, LENGTHOF(buffer), input, -1, U_FOLD_CASE_EXCLUDE_SPECIAL_I, &errorCode);
    if(U_SUCCESS(errorCode)) {
        printUString("full-case-folded/Turkic: ", buffer, length);
    } else {
        printf("error in u_strFoldCase(Turkic)=%ld error=%s\n", length, u_errorName(errorCode));
    }
}

// sample code for case mappings with C++ APIs ------------------------------ ***

static void demoCaseMapInCPlusPlus() {
    /*
     * input=
     *   "aB<capital sigma>"
     *   "iI<small dotless i><capital dotted I> "
     *   "<sharp s> <small lig. ffi>"
     *   "<small final sigma><small sigma><capital sigma>"
     */
    static const UChar input[]={
        0x61, 0x42, 0x3a3,
        0x69, 0x49, 0x131, 0x130, 0x20,
        0xdf, 0x20, 0xfb03,
        0x3c2, 0x3c3, 0x3a3, 0
    };
    
    printf("\n* demoCaseMapInCPlusPlus() --------- ***\n\n");
    
    UnicodeString s(input), t;
    const Locale &en=Locale::getEnglish();
    Locale tr("tr");
    
    /*
     * Full case mappings as in demoCaseMapInC(), using UnicodeString functions.
     * These functions modify the string object itself.
     * Since we want to keep the input string around, we copy it each time
     * and case-map the copy.
     */
    printUnicodeString("input string: ", s);
    
    /* lowercase/English */
    printUnicodeString("full-lowercased/en: ", (t=s).toLower(en));
    /* lowercase/Turkish */
    printUnicodeString("full-lowercased/tr: ", (t=s).toLower(tr));
    /* uppercase/English */
    printUnicodeString("full-uppercased/en: ", (t=s).toUpper(en));
    /* uppercase/Turkish */
    printUnicodeString("full-uppercased/tr: ", (t=s).toUpper(tr));
    /* titlecase/English */
    printUnicodeString("full-titlecased/en: ", (t=s).toTitle(NULL, en));
    /* titlecase/Turkish */
    printUnicodeString("full-titlecased/tr: ", (t=s).toTitle(NULL, tr));
    /* case-folde/default */
    printUnicodeString("full-case-folded/default: ", (t=s).foldCase(U_FOLD_CASE_DEFAULT));
    /* case-folde/Turkic */
    printUnicodeString("full-case-folded/Turkic: ", (t=s).foldCase(U_FOLD_CASE_EXCLUDE_SPECIAL_I));
}

// sample code for UnicodeString storage models ----------------------------- ***

static void
demoUnicodeStringStorage() {
    // These sample code lines illustrate how to use UnicodeString, and the
    // comments tell what happens internally. There are no APIs to observe
    // most of this programmatically, except for stepping into the code
    // with a debugger.
    // This is by design to hide such details from the user.
    int32_t i;
    
    printf("\n* demoUnicodeStringStorage() ------- ***\n\n");
    
    // * UnicodeString with internally stored contents
    // instantiate a UnicodeString from a single code point
    // the few (2) UChars will be stored in the object itself
    UnicodeString one((UChar32)0x24001);
    // this copies the few UChars into the "two" object
    UnicodeString two=one;
    printf("length of short string copy: %d\n", two.length());
    // set "one" to contain the 3 UChars from readonly
    // this setTo() variant copies the characters
    one.setTo(readonly, LENGTHOF(readonly));
    
    // * UnicodeString with allocated contents
    // build a longer string that will not fit into the object's buffer
    one+=UnicodeString(writeable, LENGTHOF(writeable));
    one+=one;
    one+=one;
    printf("length of longer string: %d\n", one.length());
    // copying will use the same allocated buffer and increment the reference
    // counter
    two=one;
    printf("length of longer string copy: %d\n", two.length());
    
    // * UnicodeString using readonly-alias to a const UChar array
    // construct a string that aliases a readonly buffer
    UnicodeString three(FALSE, readonly, LENGTHOF(readonly));
    printUnicodeString("readonly-alias string: ", three);
    // copy-on-write: any modification to the string results in
    // a copy to either the internal buffer or to a newly allocated one
    three.setCharAt(1, 0x39);
    printUnicodeString("readonly-aliasing string after modification: ", three);
    // the aliased array is not modified
    for(i=0; i<three.length(); ++i) {
        printf("readonly buffer[%d] after modifying its string: 0x%lx\n",
               i, readonly[i]);
    }
    // setTo() readonly alias
    one.setTo(FALSE, writeable, LENGTHOF(writeable));
    // copying the readonly-alias object with fastCopyFrom() (new in ICU 2.4)
    // will readonly-alias the same buffer
    two.fastCopyFrom(one);
    printUnicodeString("fastCopyFrom(readonly alias of \"writeable\" array): ", two);
    printf("verify that a fastCopyFrom(readonly alias) uses the same buffer pointer: %d (should be 1)\n",
           one.getBuffer()==two.getBuffer());
    // a normal assignment will clone the contents (new in ICU 2.4)
    two=one;
    printf("verify that a regular copy of a readonly alias uses a different buffer pointer: %d (should be 0)\n",
           one.getBuffer()==two.getBuffer());
    
    // * UnicodeString using writeable-alias to a non-const UChar array
    UnicodeString four(writeable, LENGTHOF(writeable), LENGTHOF(writeable));
    printUnicodeString("writeable-alias string: ", four);
    // a modification writes through to the buffer
    four.setCharAt(1, 0x39);
    for(i=0; i<four.length(); ++i) {
        printf("writeable-alias backing buffer[%d]=0x%lx "
               "after modification\n", i, writeable[i]);
    }
    // a copy will not alias any more;
    // instead, it will get a copy of the contents into allocated memory
    two=four;
    two.setCharAt(1, 0x21);
    for(i=0; i<two.length(); ++i) {
        printf("writeable-alias backing buffer[%d]=0x%lx after "
               "modification of string copy\n", i, writeable[i]);
    }
    // setTo() writeable alias, capacity==length
    one.setTo(writeable, LENGTHOF(writeable), LENGTHOF(writeable));
    // grow the string - it will not fit into the backing buffer any more
    // and will get copied before modification
    one.append((UChar)0x40);
    // shrink it back so it would fit
    one.truncate(one.length()-1);
    // we still operate on the copy
    one.setCharAt(1, 0x25);
    printf("string after growing too much and then shrinking[1]=0x%lx\n"
           "                          backing store for this[1]=0x%lx\n",
           one.charAt(1), writeable[1]);
    // if we need it in the original buffer, then extract() to it
    // extract() does not do anything if the string aliases that same buffer
    // i=min(one.length(), length of array)
    if(one.length()<LENGTHOF(writeable)) {
        i=one.length();
    } else {
        i=LENGTHOF(writeable);
    }
    one.extract(0, i, writeable);
    for(i=0; i<LENGTHOF(writeable); ++i) {
        printf("writeable-alias backing buffer[%d]=0x%lx after re-extract\n",
               i, writeable[i]);
    }
}

// sample code for UnicodeString instantiations ----------------------------- ***

static void
demoUnicodeStringInit() {
    // *** Make sure to read about invariant characters in utypes.h! ***
    // Initialization of Unicode strings from C literals works _only_ for
    // invariant characters!
    
    printf("\n* demoUnicodeStringInit() ---------- ***\n\n");
    
    // the string literal is 32 chars long - this must be counted for the macro
    UnicodeString invariantOnly=UNICODE_STRING("such characters are safe 123 %-.", 32);
    
    /*
     * In C, we need two macros: one to declare the UChar[] array, and
     * one to populate it; the second one is a noop on platforms where
     * wchar_t is compatible with UChar and ASCII-based.
     * The length of the string literal must be counted for both macros.
     */
    /* declare the invString array for the string */
    U_STRING_DECL(invString, "such characters are safe 123 %-.", 32);
    /* populate it with the characters */
    U_STRING_INIT(invString, "such characters are safe 123 %-.", 32);
    
    // compare the C and C++ strings
    printf("C and C++ Unicode strings are equal: %d\n", invariantOnly==UnicodeString(TRUE, invString, 32));
    
    /*
     * convert between char * and UChar * strings that
     * contain only invariant characters
     */
    static const char *cs1="such characters are safe 123 %-.";
    static UChar us1[40];
    static char cs2[40];
    u_charsToUChars(cs1, us1, 33); /* include the terminating NUL */
    u_UCharsToChars(us1, cs2, 33);
    printf("char * -> UChar * -> char * with only "
           "invariant characters: \"%s\"\n",
           cs2);
    
    // initialize a UnicodeString from a string literal that contains
    // escape sequences written with invariant characters
    // do not forget to duplicate the backslashes for ICU to see them
    // then, count each double backslash only once!
    UnicodeString german=UNICODE_STRING(
                                        "Sch\\u00f6nes Auto: \\u20ac 11240.\\fPrivates Zeichen: \\U00102345\\n", 64).
    unescape();
    printUnicodeString("german UnicodeString from unescaping:\n    ", german);
    
    /*
     * C: convert and unescape a char * string with only invariant
     * characters to fill a UChar * string
     */
    UChar buffer[200];
    int32_t length;
    length=u_unescape(
                      "Sch\\u00f6nes Auto: \\u20ac 11240.\\fPrivates Zeichen: \\U00102345\\n",
                      buffer, LENGTHOF(buffer));
    printf("german C Unicode string from char * unescaping: (length %d)\n    ", length);
    printUnicodeString("", UnicodeString(buffer));
}


void testApp::unicodeDemo() {
    UErrorCode errorCode=U_ZERO_ERROR;
    
    // Note: Using a global variable for any object is not exactly thread-safe...
    
    // You can change this call to e.g. ucnv_open("UTF-8", &errorCode) if you pipe
    // the output to a file and look at it with a Unicode-capable editor.
    // This will currently affect only the printUString() function, see the code above.
    // printUnicodeString() could use this, too, by changing to an extract() overload
    // that takes a UConverter argument.
    cnv=ucnv_open(NULL, &errorCode);
    if(U_FAILURE(errorCode)) {
        fprintf(stderr, "error %s opening the default converter\n", u_errorName(errorCode));
      //  return errorCode;
    }
    
    ucnv_setFromUCallBack(cnv, UCNV_FROM_U_CALLBACK_ESCAPE, UCNV_ESCAPE_C, NULL, NULL, &errorCode);
    if(U_FAILURE(errorCode)) {
        fprintf(stderr, "error %s setting the escape callback in the default converter\n", u_errorName(errorCode));
        ucnv_close(cnv);
       // return errorCode;
    }
    
    demo_utf_h_macros();
    demo_C_Unicode_strings();
    demoCaseMapInC();
    demoCaseMapInCPlusPlus();
    demoUnicodeStringStorage();
    demoUnicodeStringInit();
    
    ucnv_close(cnv);

}

