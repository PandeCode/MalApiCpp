#include "client.hpp"
#include "tabulate/tabulate.hpp"
#include "utils.hpp"

#include <iostream>
#include <sstream>

template <typename T1, typename T2>
static std::ostream& operator<<(std::ostream& stream, const Day day) {
	stream << dayToString(day);
	return stream;
}

template <typename T1, typename T2>
static std::ostream& operator<<(std::ostream& stream, const Day& day) {
	stream << dayToString(day);
	return stream;
}

template <typename T>
static std::ostream& operator<<(std::ostream& stream, const std::vector<T>& listType) {
	stream << "{ ";
	for(auto it = listType.begin(); it != listType.end(); it++)
		stream << *it << (std::next(it) != listType.end() ? ", " : " }");
	return stream;
}

template <typename T1, typename T2>
static std::ostream& operator<<(std::ostream& stream, const std::pair<T1, T2>& p) {
	stream << "{ " << p.first << ", " << p.second << " }";
	return stream;
}

template <typename T, size_t size>
static std::ostream&
    operator<<(std::ostream& stream, const std::array<T, size>& listType) {
	stream << "{ ";
	for(auto it = listType.begin(); it != listType.end(); it++)
		stream << *it << (std::next(it) != listType.end() ? ", " : " }");
	return stream;
}

template <typename K, typename V>
static std::ostream&
    operator<<(std::ostream& stream, const std::unordered_map<K, V>& um) {
	for(auto i = um.begin(); i != um.end(); i++) {
		stream << i->first << " = " << i->second << ", ";
	}
	return stream;
}

std::string toString(const ParsedData& um) {
	std::stringstream stream;
	for(auto i = um.begin(); i != um.end(); i++) {
		stream << dayToString(i->first) << " = " << i->second << ", ";
	}
	return stream.str();
}

using namespace utils;
using namespace tabulate;

int main(int, char**) {
	std::string raw;

	try {
		ClientWrapper testClient;
		raw = testClient.getDubs();
	} catch(std::exception e) {
		std::cout << "You seem to be offline. using getDubs.txt. \n"
			  << e.what() << std::endl;
		raw = readFile("getDubs.txt");
	}

	auto parsedData     = parseData(raw);
	auto generatedTable = genTable(parsedData);

	std::cout << generatedTable << std::endl;
#ifdef DEBUG
	std::cout << "parsedData    : " << toString(parsedData) << std::endl;
	std::cout << "raw           : " << raw << std::endl;
#endif

	return 0;
}
