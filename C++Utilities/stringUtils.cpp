#include <C++Utilities/stringUtils.hpp>
#include <algorithm>
#include <cctype>

using namespace std;

string_view StringUtils::ltrim(string_view s)
{
	s.remove_prefix(distance(s.cbegin(), find_if(s.cbegin(), s.cend(),
		[](unsigned char c) { return !isspace(c); })));
	return s;
}

string_view StringUtils::rtrim(string_view s)
{
	s.remove_suffix(distance(s.crbegin(), find_if(s.crbegin(), s.crend(),
		[](unsigned char c) { return !isspace(c); })));
	return s;
}

string_view StringUtils::trim(string_view s)
{
	return ltrim(rtrim(s));
}

string StringUtils::toLower(string &s)
{
	string result = s;
	transform(s.cbegin(), s.cend(), result.begin(),
		[](unsigned char c) { return tolower(c); });
	return result;
}

string StringUtils::toUpper(string &s)
{
	string result = s;
	transform(s.cbegin(), s.cend(), result.begin(),
		[](unsigned char c) { return toupper(c); });
	return result;
}
