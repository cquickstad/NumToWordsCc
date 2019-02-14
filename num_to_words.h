#include <string>
#include <map>

using namespace std;


// typedef unsigned long long ull;


typedef struct {string name; __uint128_t value;} place_name_value;
typedef struct {string name; __uint128_t value; __uint128_t limit;} place_name_value_limit;


class NumToWords {
public:
	static const string to_words(__uint128_t n);
	static const __uint128_t to128(__uint64_t upper, __uint64_t lower);

protected:
	static const place_name_value get_largest_place_name_value(__uint128_t n);
	static const string convert_from_place(__uint128_t n, string place_name, __uint128_t place_value);
	static const string large_number_to_words(__uint128_t n);
	static const string hundreds_to_words(__uint128_t n);
	static const string two_digit_hyphen_to_words(__uint128_t n);
	static const string compound_teen_to_words(__uint128_t n);
	static const bool translations_has(__uint128_t n);
	static const map<__uint128_t, string> translations;
	static const place_name_value_limit places[];
};
