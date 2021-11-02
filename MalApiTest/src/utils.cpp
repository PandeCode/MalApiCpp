#include <array>
#include <cstdarg>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <list>
#include <ostream>
#include <set>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>

namespace std {

	template <typename T>
	string getString(const T& input) {
		bool isString = is_same_v<decltype(input), std::string> ||
				is_same_v<decltype(input), const char*>;
		bool isChar = is_same_v<decltype(input), char>;

		string returnString;

		if(isString)
			returnString += "\"";
		else if(isChar)
			returnString += "'";

		returnString += to_string(input);

		if(isString)
			returnString += "\"";
		else if(isChar)
			returnString += "'";

		return returnString;
	}
	//tuple
	template <typename... _Tps>
	string to_string(const tuple<_Tps...>& input) {
		string returnString = "{ ";
		(void) (input);

		//std::apply([&returnString](
		//auto&&... args) { ((returnString += args + ", "), ...); },
		//input);

		returnString += " }";
		return returnString;
	}

	//set
	template <typename _Key>
	string to_string(const set<_Key>& input) {
		string returnString = "{ ";
		for(auto it = input.begin(); it != input.end(); it++)
			returnString +=
			    std::to_string(*it) + (next(it) != input.end() ? ", " : " }");
		return returnString;
	}

	//unordered_map
	template <typename _Key, typename _Tp>
	string to_string(const std::unordered_map<_Key, _Tp>& input) {
		std::string returnString = "{ ";

		for(auto it = input.begin(); it != input.end(); it++)
			returnString += getString(it->first) + " : " +
					getString(it->second) +
					(next(it) != input.end() ? ", " : " }");
		return returnString;
	}

	//pair
	template <typename _T1, typename _T2>
	string to_string(const pair<_T1, _T2>& input) {
		return "{ " + getString(input.first) + ", " + getString(input.second) +
		       " }";
	}

	//array
	template <typename _Tp, size_t _Nm>
	string to_string(const array<_Tp, _Nm>& input) {
		string returnString = "{ ";
		for(auto it = input.begin(); it != input.end(); it++)
			returnString +=
			    std::to_string(*it) + (next(it) != input.end() ? ", " : " }");
		return returnString;
	}

	//list
	template <typename _Tp>
	string to_string(const list<_Tp>& input) {
		string returnString = "{ ";
		for(auto it = input.begin(); it != input.end(); it++)
			returnString +=
			    std::to_string(*it) + (next(it) != input.end() ? ", " : " }");
		return returnString;
	}

	//vector
	template <typename _Tp>
	string to_string(const vector<_Tp>& input) {
		string returnString = "{ ";
		for(auto it = input.begin(); it != input.end(); it++)
			returnString +=
			    std::to_string(*it) + (next(it) != input.end() ? ", " : " }");
		return returnString;
	}
}

namespace BetterStl {
	template <typename... _Tps>
	std::ostream& operator<<(std::ostream& stream, const std::tuple<_Tps...>& input) {
		stream << std::to_string(input);
		return stream;
	}
	template <typename _Tp, std::size_t _Nm>
	std::ostream& operator<<(std::ostream&               stream,
				 const std::array<_Tp, _Nm>& input) {
		stream << std::to_string(input);
		return stream;
	}
	template <typename _Tp>
	std::ostream& operator<<(std::ostream& stream, const std::list<_Tp>& input) {
		stream << std::to_string(input);
		return stream;
	}
	template <typename _Tp>
	std::ostream& operator<<(std::ostream& stream, const std::vector<_Tp>& input) {
		stream << std::to_string(input);
		return stream;
	}
	template <typename _Key>
	std::ostream& operator<<(std::ostream& stream, const std::set<_Key>& input) {
		stream << std::to_string(input);
		return stream;
	}

	template <typename _T1, typename _T2>
	std::ostream& operator<<(std::ostream& stream, const std::pair<_T1, _T2>& input) {
		stream << std::to_string(input);
		return stream;
	}
	template <typename _Key, typename _Tp>
	std::ostream& operator<<(std::ostream&                        stream,
				 const std::unordered_map<_Key, _Tp>& input) {
		stream << std::to_string(input);
		return stream;
	}

}
