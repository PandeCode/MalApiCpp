#pragma once
#include "tabulate/tabulate.hpp"

enum class Day : std::uint16_t {
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday,
};

Day         stringToDay(const std::string& str);
std::string dayToString(const Day& day);

using ParsedData = std::map<Day, std::vector<std::string>>;

namespace utils {
	const std::string WHITESPACE = " \n\r\t\f\v";

	std::vector<std::string> split(std::string str, const std::string& token = " ");
	std::string              ltrim(const std::string& s);
	std::string              rtrim(const std::string& s);
	std::string              trim(const std::string& s);

	void        overwriteFile(const std::string& path, const std::string& text);
	std::string readFile(const std::string& path);

	ParsedData      parseData(const std::string& data);
	tabulate::Table genTable(const ParsedData& parsedData);
}
