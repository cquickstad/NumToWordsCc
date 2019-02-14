// Integer To Words
//
// Convert integer value to word equivalent similar to how you would write out
// the number on a check.
//
// FYI:
//
//       Review english grammar:
//           http://www.grammarbook.com/numbers/numbers.asp
//
//       Review large number names:
//           http://bmanolov.free.fr/numbers_names.php

#include "num_to_words.h"
#include <iostream>
#include <assert.h>


const __uint128_t NumToWords::to128(__uint64_t upper, __uint64_t lower) {
	__uint128_t result = upper;
	result <<= 64;
	return result | lower;
}


// translations is a dictionary that handles basic cases (i.e. 2=>'two')
// and cases which must map because they are special (i.e. 13=>'thirteen' not 'threeteen').
// This dictionary is the base of higher recursive calls that handle the billions, thousands, etc.
// (i.e. the 'three' in 'three billion').
const map<__uint128_t, string> NumToWords::translations = {
	{0, "zero"}, {1, "one"}, {2, "two"}, {3, "three"},
	{4, "four"}, {5, "five"}, {6, "six"}, {7, "seven"},
	{8, "eight"}, {9, "nine"}, {10, "ten"}, {11, "eleven"},
	{12, "twelve"}, {13, "thirteen"}, {15, "fifteen"}, {18, "eighteen"},
	{20, "twenty"}, {30, "thirty"}, {40, "forty"}, {50, "fifty"},
	{60, "sixty"}, {70, "seventy"}, {80, "eighty"}, {90, "ninety"}
};


const place_name_value_limit NumToWords::places[] = {
	//        Name,                                               Value,                                               Limit
	{   "thousand",                                             1000ull,                                           999999ull},
	{    "million",                                          1000000ull,                                        999999999ull},
	{    "billion",                                       1000000000ull,                                     999999999999ull},
	{   "trillion",                                    1000000000000ull,                                  999999999999999ull},
	{"quadrillion",                                 1000000000000000ull,                               999999999999999999ull},
	// The following hex values were worked out from a python shell
	// because python is cool and handles arbitrarily large integers.
	{"quintillion",                              1000000000000000000ull, to128(              0x36ull, 0x35c9adc5de9fffffull)},
	{ "sextillion", to128(              0x36ull, 0x35c9adc5dea00000ull), to128(            0xd3c2ull, 0x1bcecceda0ffffffull)},
	{ "septillion", to128(            0xd3c2ull, 0x1bcecceda1000000ull), to128(         0x33b2e3cull, 0x9fd0803ce7ffffffull)},
	{  "octillion", to128(         0x33b2e3cull, 0x9fd0803ce8000000ull), to128(       0xc9f2c9cd0ull, 0x4674edea3fffffffull)},
	{  "nonillion", to128(       0xc9f2c9cd0ull, 0x4674edea40000000ull), to128(    0x314dc6448d93ull, 0x38c15b09ffffffffull)},
	{  "decillion", to128(    0x314dc6448d93ull, 0x38c15b0a00000000ull), to128(  0xc097ce7bc90715ull, 0xb34b9f0fffffffffull)},
	{"undecillion", to128(  0xc097ce7bc90715ull, 0xb34b9f1000000000ull), to128(0xffffffffffffffffull, 0xffffffffffffffffull)}
};


const bool NumToWords::translations_has(__uint128_t n) {
	return translations.find(n) != translations.end();
}


const place_name_value NumToWords::get_largest_place_name_value(__uint128_t n) {
	int i = 0;
	while (n > places[i].limit) ++i;
	return {places[i].name, places[i].value};
}


const string NumToWords::convert_from_place(__uint128_t n, string place_name, __uint128_t place_value) {
	__uint128_t value_in_place = n / place_value;
	assert(value_in_place > 0);
	__uint128_t remaining = n - (value_in_place * place_value);
	string remaining_words = (remaining == 0) ? "" : (" " + to_words(remaining));
	return to_words(value_in_place) + " " + place_name + remaining_words;
}


const string NumToWords::large_number_to_words(__uint128_t n) {
	auto nv = get_largest_place_name_value(n);
	return convert_from_place(n, nv.name, nv.value);
}


const string NumToWords::hundreds_to_words(__uint128_t n) {
	return convert_from_place(n, "hundred", 100);
}


const string NumToWords::two_digit_hyphen_to_words(__uint128_t n) {
	__uint128_t tens_place = (n / 10) * 10;
	__uint128_t ones_place = n - tens_place;
	return translations.at(tens_place) + "-" + translations.at(ones_place);
}


const string NumToWords::compound_teen_to_words(__uint128_t n) {
	return to_words(n - 10) + "teen";
}


const string NumToWords::to_words(__uint128_t n) {
	if (translations_has(n)) return translations.at(n);
	else if (n < 20) return compound_teen_to_words(n);
	else if (n < 100) return two_digit_hyphen_to_words(n);
	else if (n < 1000) return hundreds_to_words(n);
	else return large_number_to_words(n);
}
