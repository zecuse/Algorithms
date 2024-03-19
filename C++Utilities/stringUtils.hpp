#pragma once
#include <string_view>

namespace StringUtils
{
std::string_view ltrim(std::string_view);
std::string_view rtrim(std::string_view);
std::string_view trim(std::string_view);
std::string toLower(std::string&);
std::string toUpper(std::string&);
}