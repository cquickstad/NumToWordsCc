#include <gtest/gtest.h>
#include "num_to_words.h"

using namespace std;

TEST(uint128ToWordsTests, testThatSingleDigitsReturnWords) {
	vector<tuple<__uint128_t, string>> tc = {make_tuple(0, "zero"), make_tuple(1, "one"),
		make_tuple(2, "two"), make_tuple(3, "three"), make_tuple(4, "four"),
		make_tuple(5, "five"), make_tuple(6, "six"), make_tuple(7, "seven"),
		make_tuple(8, "eight"), make_tuple(9, "nine")};

	for (auto const& val: tc) { EXPECT_EQ(NumToWords::to_words(get<0>(val)), get<1>(val)); }
}

TEST(uint128ToWordsTests, testSimpleTeens) {
	vector<tuple<__uint128_t, string>> tc = {
		make_tuple(14, "fourteen"), // 'four' combined with 'teen'
		make_tuple(16, "sixteen"), // 'six' combined with 'teen'
		make_tuple(17, "seventeen"), // 'seven' combined with 'teen'
		make_tuple(19, "nineteen") // 'nine' combined with 'teen'
	};

	for (auto const& val: tc) EXPECT_EQ(NumToWords::to_words(get<0>(val)), get<1>(val));
}

TEST(uint128ToWordsTests, testNonTeenTwoDigits) {
	vector<tuple<__uint128_t, string>> tc = {
		make_tuple(10, "ten"), // Not zero-teen
		make_tuple(11, "eleven"), // Not zone-teen
		make_tuple(12, "twelve") // Not two-teen
	};

	for (auto const& val: tc) EXPECT_EQ(NumToWords::to_words(get<0>(val)), get<1>(val));
}

TEST(uint128ToWordsTests, testUniqueTeens) {
	vector<tuple<__uint128_t, string>> tc = {
		make_tuple(13, "thirteen"), // Not three-teen
		make_tuple(15, "fifteen"), // Not five-teen
		make_tuple(18, "eighteen") // Not eight-teen
	};

	for (auto const& val: tc) EXPECT_EQ(NumToWords::to_words(get<0>(val)), get<1>(val));
}

TEST(uint128ToWordsTests, testEvenTens) {
	vector<tuple<__uint128_t, string>> tc = {make_tuple(10, "ten"), make_tuple(20, "twenty"),
		make_tuple(30, "thirty"), make_tuple(40, "forty"), make_tuple(50, "fifty"),
		make_tuple(60, "sixty"), make_tuple(70, "seventy"), make_tuple(80, "eighty"),
		make_tuple(90, "ninety")};

	for (auto const& val: tc) EXPECT_EQ(NumToWords::to_words(get<0>(val)), get<1>(val));
}

TEST(uint128ToWordsTests, testTwoDigitHyphens) {
	vector<tuple<__uint128_t, string>> tc = {make_tuple(21, "twenty-one"),
		make_tuple(22, "twenty-two"), make_tuple(39, "thirty-nine"),
		make_tuple(45, "forty-five"), make_tuple(53, "fifty-three"),
		make_tuple(66, "sixty-six"), make_tuple(78, "seventy-eight"),
		make_tuple(87, "eighty-seven"), make_tuple(98, "ninety-eight")};

	for (auto const& val: tc) EXPECT_EQ(NumToWords::to_words(get<0>(val)), get<1>(val));
}

TEST(uint128ToWordsTests, testHundreds) {
	vector<tuple<__uint128_t, string>> tc = {make_tuple(100, "one hundred"),
		make_tuple(101, "one hundred one"), make_tuple(110, "one hundred ten"),
		make_tuple(253, "two hundred fifty-three"),
		make_tuple(999, "nine hundred ninety-nine")};

	for (auto const& val: tc) EXPECT_EQ(NumToWords::to_words(get<0>(val)), get<1>(val));
}

TEST(uint128ToWordsTests, testThousands) {
	vector<tuple<__uint128_t, string>> tc = {make_tuple(1000, "one thousand"),
		make_tuple(1001, "one thousand one"),
		make_tuple(1999, "one thousand nine hundred ninety-nine"),
		make_tuple(10000, "ten thousand"), make_tuple(10001, "ten thousand one"),
		make_tuple(745111, "seven hundred forty-five thousand one hundred eleven")};

	for (auto const& val: tc) EXPECT_EQ(NumToWords::to_words(get<0>(val)), get<1>(val));
}

TEST(uint128ToWordsTests, testMillions) {
	vector<tuple<__uint128_t, string>> tc = {make_tuple(1000000, "one million"),
		make_tuple(987654321, "nine hundred eighty-seven million "
							  "six hundred fifty-four thousand "
							  "three hundred twenty-one")};

	for (auto const& val: tc) EXPECT_EQ(NumToWords::to_words(get<0>(val)), get<1>(val));
}

TEST(uint128ToWordsTests, allPlaces) {
	// 1001001001001001001001001001001001001 decimal
	EXPECT_EQ(NumToWords::to_words(NumToWords::to128(0xc0c928e47633aeull, 0x31cf28100419a029ull)),
		"one undecillion one decillion one nonillion one octillion one septillion "
		"one sextillion one quintillion one quadrillion one trillion one billion "
		"one million one thousand one");

	// 339999999999999999999999999999999999999 decimal
	EXPECT_EQ(NumToWords::to_words(NumToWords::to128(0xffc99e3c66fd68d2ull, 0x206f413fffffffffull)),
		"three hundred thirty-nine undecillion "
		"nine hundred ninety-nine decillion "
		"nine hundred ninety-nine nonillion "
		"nine hundred ninety-nine octillion "
		"nine hundred ninety-nine septillion "
		"nine hundred ninety-nine sextillion "
		"nine hundred ninety-nine quintillion "
		"nine hundred ninety-nine quadrillion "
		"nine hundred ninety-nine trillion "
		"nine hundred ninety-nine billion "
		"nine hundred ninety-nine million "
		"nine hundred ninety-nine thousand "
		"nine hundred ninety-nine");
}

TEST(uint128ToWordsTests, testLargestNumber) {
	// 340282366920938463463374607431768211455 decimal
	EXPECT_EQ(NumToWords::to_words(NumToWords::to128(0xffffffffffffffffull, 0xffffffffffffffffull)),
		"three hundred forty undecillion two hundred eighty-two decillion "
		"three hundred sixty-six nonillion nine hundred twenty octillion "
		"nine hundred thirty-eight septillion four hundred sixty-three sextillion "
		"four hundred sixty-three quintillion three hundred seventy-four quadrillion "
		"six hundred seven trillion four hundred thirty-one billion "
		"seven hundred sixty-eight million two hundred eleven thousand four hundred fifty-five");
}

