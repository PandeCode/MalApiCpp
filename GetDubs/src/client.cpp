#include "client.hpp"

#include "malapi/client.hpp"
#include "malapi/jsonDefinitions.hpp"

#include <iostream>

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& stream, const std::pair<T1, T2>& p);
template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& listType);

template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& listType) {
	stream << "{ ";
	for(auto it = listType.begin(); it != listType.end(); it++)
		stream << *it << (std::next(it) != listType.end() ? ", " : " }");
	return stream;
}
template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& stream, const std::pair<T1, T2>& p) {
	stream << "{ " << p.first << ", " << p.second << " }";
	return stream;
}

inline std::vector<std::string> split(std::string str, const std::string& token) {
	std::vector<std::string> result;
	while(str.size()) {
		std::size_t index = str.find(token);
		if(index != std::string::npos) {
			result.push_back(str.substr(0, index));
			str = str.substr(index + token.size());
			if(str.size() == 0) result.push_back(str);
		} else {
			result.push_back(str);
			str = "";
		}
	}
	return result;
}

const std::string  WHITESPACE = " \n\r\t\f\v";
inline std::string ltrim(const std::string& s) {
	size_t start = s.find_first_not_of(WHITESPACE);
	return (start == std::string::npos) ? "" : s.substr(start);
}
inline std::string rtrim(const std::string& s) {
	size_t end = s.find_last_not_of(WHITESPACE);
	return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
inline std::string trim(const std::string& s) {
	return rtrim(ltrim(s));
}

inline void overwriteFile(const std::string& path, const std::string& text) {
	std::ofstream file(path, std::ofstream::trunc);
	file << text;
	file.close();
}

inline std::string readFile(const std::string& path) {
	std::stringstream returnString = std::stringstream();
	std::ifstream     file(path);
	std::string       tmpString;

	while(std::getline(file, tmpString))
		returnString << tmpString << "\n";
	file.close();
	return returnString.str();
}

void ClientWrapper::getDubs() const {
	std::string res = std::get<0>(client.getForumTopicDetail(1692966, 1));

	std::cout << std::string(nlohmann::json::parse(res)["data"]["posts"][0]["body"])
		  << std::endl;
}
