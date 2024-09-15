#include <gtest/gtest.h>
#include "Soundex.h"
 
TEST(SoundexTestsuite, ReplacesConsonantsWithAppropriateDigits) {
    char soundex[5];
    generateSoundex("AX", soundex);
    ASSERT_STREQ(soundex, "A200");
}
 
TEST(SoundexTestsuite, RetainsSoleLetterOfOneLetterWord) {
    char soundex[5];
    generateSoundex("B", soundex);
    ASSERT_STREQ(soundex, "B000");
}
 
TEST(SoundexTestsuite, PadsWithZerosToEnsureThreeDigits) {
    char soundex[5];
    generateSoundex("N", soundex);
    ASSERT_STREQ(soundex, "N000");
}
 
TEST(SoundexTestsuite, CombinesDuplicateEncodingsSeparatedByVowels) {
    char soundex[5];
    generateSoundex("bbfcg", soundex);
    ASSERT_STREQ(soundex, "B200");
}
 
TEST(SoundexTestsuite, UppercasesFirstLetter) {
    char soundex[5];
    generateSoundex("abcd", soundex);
    ASSERT_STREQ(soundex, "A123");
}
 
TEST(SoundexTestsuite, IgnoresCaseWhenEncodingConsonants) {
    char soundex[5];
    generateSoundex("BCDL", soundex);
    ASSERT_STREQ(soundex, "B234");
}
