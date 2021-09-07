#include <initializer_list>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

enum class Fields : std::uint8_t {
	opening_themes,
	ending_themes,
	synopsis,
	alternative_titles,
	media_type,
	my_list_status // {start_date,finish_date,priority,comments},
};

static inline std::string parseFields(std::vector<Fields> field) {
	if (field.size() == 0) return "";

	std::stringstream finalStringStream;

	if(std::find(field.begin(),field.end(), Fields::opening_themes    ) != field.end()) finalStringStream << "opening_themes,";
	if(std::find(field.begin(),field.end(), Fields::ending_themes     ) != field.end()) finalStringStream << "ending_themes,";
	if(std::find(field.begin(),field.end(), Fields::synopsis          ) != field.end()) finalStringStream << "synopsis,";
	if(std::find(field.begin(),field.end(), Fields::alternative_titles) != field.end()) finalStringStream << "alternative_titles,";
	if(std::find(field.begin(),field.end(), Fields::media_type        ) != field.end()) finalStringStream << "media_type,";
	if(std::find(field.begin(),field.end(), Fields::my_list_status    ) != field.end()) finalStringStream << "my_list_status,";

	return finalStringStream.str();
}

int main() {
	std::cout << "main\n";

	//std::cout << parseFields({Fields::alternative_titles, Fields::media_type, Fields::my_list_status}) << std::endl;

	return 0;
}
