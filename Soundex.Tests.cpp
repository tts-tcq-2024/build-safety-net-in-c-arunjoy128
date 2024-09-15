#include <gtest/gtest.h>
#include "Soundex.h"

TEST(SoudexTestSuite, ReplacesConsonantsWithAppropriateDigits) {
  char soundex[5];

  generateSoundex("ab", soundex);
  ASSERT_STREQ(soundex,"A100");
  generateSoundex("ac", soundex);
  ASSERT_STREQ(soundex,"A200");
  generateSoundex("ad", soundex);
  ASSERT_STREQ(soundex,"A300");
  generateSoundex("af", soundex);
  ASSERT_STREQ(soundex,"A100");
  generateSoundex("ag", soundex);
  ASSERT_STREQ(soundex,"A200");
  generateSoundex("aj", soundex);
  ASSERT_STREQ(soundex,"A200");
  generateSoundex("ak", soundex);
  ASSERT_STREQ(soundex,"A200");
  generateSoundex("al", soundex);
  ASSERT_STREQ(soundex,"A400");
  generateSoundex("am", soundex);
  ASSERT_STREQ(soundex,"A500");
  generateSoundex("an", soundex);
  ASSERT_STREQ(soundex,"A500");
  generateSoundex("ap", soundex);
  ASSERT_STREQ(soundex,"A100");
  generateSoundex("aq", soundex);
  ASSERT_STREQ(soundex,"A200");
  generateSoundex("ar", soundex);
  ASSERT_STREQ(soundex,"A600");
  generateSoundex("as", soundex);
  ASSERT_STREQ(soundex,"A200");
  generateSoundex("at", soundex);
  ASSERT_STREQ(soundex,"A300");
  generateSoundex("av", soundex);
  ASSERT_STREQ(soundex,"A100");
  generateSoundex("ax", soundex);
  ASSERT_STREQ(soundex,"A200");
  generateSoundex("az", soundex);
  ASSERT_STREQ(soundex,"A200");
}

TEST(SoudexTestSuite, RetainsFirstCharacter) {
  char soundex[5];
  
  generateSoundex("Meera", soundex);
  ASSERT_STREQ(soundex,"M600");
  generateSoundex("aeiouyhw", soundex);
  ASSERT_STREQ(soundex,"A000");
}

TEST(SoudexTestSuite, DropsAllVowels) {
  char soundex[5], soundex1[5];
  
  generateSoundex("Cameroon", soundex);
  ASSERT_STREQ(soundex,"C565");
  generateSoundex("Cmrn", soundex1);
  ASSERT_STREQ(soundex1,"C565");
  ASSERT_STREQ(soundex,soundex1);
}

TEST(SoudexTestSuite, DropsRepeatedAdjacentEncodings) {
  char soundex[5], soundex1[5], soundex2[5];
  
  generateSoundex("Mississippi", soundex);
  ASSERT_STREQ(soundex,"M221");
  generateSoundex("Misisipi", soundex1);
  ASSERT_STREQ(soundex1,"M221");
  ASSERT_STREQ(soundex,soundex1);

  generateSoundex("Pfister", soundex2);
  ASSERT_STREQ(soundex2,"P236");
}

TEST(SoudexTestSuite, DropsRepeatedAdjacentEncodingsSeparatedByHOrW) {
  char soundex[5];
  
  generateSoundex("Vanhn", soundex);
  ASSERT_STREQ(soundex,"V500");
  generateSoundex("Vamhn", soundex);
  ASSERT_STREQ(soundex,"V500");
}

TEST(SoudexTestSuite, RetainsRepeatedAdjacentEncodingsSeparatedByVowels) {
  char soundex[5];
  
  generateSoundex("Halal", soundex);
  ASSERT_STREQ(soundex,"H440");
}

TEST(SoudexTestSuite, PadsWithZerosIfLengthIsLessThanFour) {
  char soundex[5];
  
  generateSoundex("a", soundex);
  ASSERT_STREQ(soundex,"A000");
  generateSoundex("ab", soundex);
  ASSERT_STREQ(soundex,"A100");
  generateSoundex("abc", soundex);
  ASSERT_STREQ(soundex,"A120");
  generateSoundex("abcd", soundex);
  ASSERT_STREQ(soundex,"A123");
}

TEST(SoudexTestSuite, GivesSameSoundexCodeForSimilarInputStrings) {
  char soundex[5], soundex1[5];
  
  generateSoundex("Robert", soundex);
  ASSERT_STREQ(soundex,"R163");
  generateSoundex("Ruperd", soundex1);
  ASSERT_STREQ(soundex1,"R163");
  ASSERT_STREQ(soundex,soundex1);
}

TEST(SoudexTestSuite, ProcessesEmptyString) {
  char soundex[5];
  
  generateSoundex("", soundex);
  ASSERT_STREQ(soundex,"");
}

TEST(SoudexTestSuite, ProcessesLowercaseAndUppercaseAlphabets) {
  char soundex[5];
  
  generateSoundex("McCormick", soundex);
  ASSERT_STREQ(soundex,"M265");
}

TEST(SoudexTestSuite, IgnoresNonAlphabeticCharacters) {
  char soundex[5];
  
  generateSoundex("MeeraSunu3103!", soundex);
  ASSERT_STREQ(soundex,"M625");
  generateSoundex("Van Dyke", soundex);
  ASSERT_STREQ(soundex,"V532");
}

TEST(SoudexTestSuite, TruncatesLargeInputStrings) {
  char soundex[5],soundex1[5];
  
  generateSoundex("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.", soundex);
  ASSERT_STREQ(soundex,"L651");  
  generateSoundex("Lorem ipsum", soundex1);
  ASSERT_STREQ(soundex1,"L651");
  ASSERT_STREQ(soundex,soundex1);
}
