#include "utils.hpp"

#include "Log.hpp"

Day stringToDay(const std::string& str) {
	if(str == "Monday")
		return Day::Monday;
	else if(str == "Tuesday")
		return Day::Tuesday;
	else if(str == "Wednesday")
		return Day::Wednesday;
	else if(str == "Thursday")
		return Day::Thursday;
	else if(str == "Friday")
		return Day::Friday;
	else if(str == "Saturday")
		return Day::Saturday;
	else if(str == "Sunday")
		return Day::Sunday;
	else
		throw std::runtime_error("'" + str + "' is not a valid day");
}

std::string dayToString(const Day& day) {
	switch(day) {
		case Day::Monday: return "Monday";
		case Day::Tuesday: return "Tuesday";
		case Day::Wednesday: return "Wednesday";
		case Day::Thursday: return "Thursday";
		case Day::Friday: return "Friday";
		case Day::Saturday: return "Saturday";
		case Day::Sunday: return "Sunday";
	}
}

template <typename T>
static std::ostream& operator<<(std::ostream& stream, const std::vector<T>& listType) {
	stream << "{ ";
	for(auto it = listType.begin(); it != listType.end(); it++)
		stream << *it << (std::next(it) != listType.end() ? ", " : " }");
	return stream;
}

template <typename T1, typename T2>
static std::ostream& operator<<(std::ostream& stream, const Day& day) {
	stream << dayToString(day);
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
static std::ostream& operator<<(std::ostream& stream, const std::map<K, V>& um) {
	for(auto i = um.begin(); i != um.end(); i++) {
		stream << i->first << " = " << i->second << ", ";
	}
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

std::vector<std::string> utils::split(std::string str, const std::string& token) {
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

std::string utils::ltrim(const std::string& s) {
	size_t start = s.find_first_not_of(WHITESPACE);
	return (start == std::string::npos) ? "" : s.substr(start);
}
std::string utils::rtrim(const std::string& s) {
	size_t end = s.find_last_not_of(WHITESPACE);
	return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
std::string utils::trim(const std::string& s) {
	return rtrim(ltrim(s));
}

void utils::overwriteFile(const std::string& path, const std::string& text) {
	std::ofstream file(path, std::ofstream::trunc);
	file << text;
	file.close();
}

std::string utils::readFile(const std::string& path) {
	std::ifstream file(path);
	if(file.bad()) { throw std::runtime_error("Bad file."); }

	std::stringstream ret = std::stringstream();
	std::string       tmp;
	while(std::getline(file, tmp))
		ret << tmp << "\n";
	file.close();
	return ret.str();
}

static inline std::string deleteUtil(const std::string& str, const std::string& token) {
	return str.substr(str.find(token), str.size());
}

ParsedData utils::parseData(const std::string& raw) {

	auto t  = deleteUtil(raw, "Currently Streaming SimulDubbed Anime");
	t       = std::regex_replace(t, std::regex(R"((\[|\<).*?(\]|\>)|(^$))"), "");
	auto tl = split(t, "\n");

	tl.erase(
	    std::remove_if(
		tl.begin(),
		tl.end(),
		[](const std::string& str) { return str == ""; }),
	    tl.end());

	std::array<std::vector<std::string>::iterator, 8> dayIndices = {
	    std::find(tl.begin(), tl.end(), "Monday"),
	    std::find(tl.begin(), tl.end(), "Tuesday"),
	    std::find(tl.begin(), tl.end(), "Wednesday"),
	    std::find(tl.begin(), tl.end(), "Thursday"),
	    std::find(tl.begin(), tl.end(), "Friday"),
	    std::find(tl.begin(), tl.end(), "Saturday"),
	    std::find(tl.begin(), tl.end(), "Sunday"),
	    std::find(
		tl.begin(),
		tl.end(),
		"++ = Dub is being produced from home studios with an irregular release "
		"schedule.")};

	std::array<std::vector<std::string>, 7> days = {};

	for(std::uint8_t i = 0; i < 7 /*dayIndices.size() - 1 */; i++) {
		auto next = i + 1;
		while(dayIndices[next] == tl.end())
			next++;

		std::copy(dayIndices[i], dayIndices[next], std::back_inserter(days[i]));

		days[i].erase(days[i].begin());
	}

#ifdef DEBUG
	std::cout << std::boolalpha;
	Log::Debug("monday    : ", dayIndices[0] != tl.end());
	Log::Debug("tuesday   : ", dayIndices[1] != tl.end());
	Log::Debug("wednesday : ", dayIndices[2] != tl.end());
	Log::Debug("thursday  : ", dayIndices[3] != tl.end());
	Log::Debug("friday    : ", dayIndices[4] != tl.end());
	Log::Debug("saturday  : ", dayIndices[5] != tl.end());
	Log::Debug("sunday    : ", dayIndices[6] != tl.end());
	Log::Debug("end       : ", dayIndices[7] != tl.end());
	for(std::uint8_t i = 0; i < days.size(); i++)
		for(const auto& anime: days[i])
			Log::Debug("[", (unsigned) i, "] Anime: ", anime);
	for(const auto& l: tl)
		Log::Debug("{", l, "}");
#endif

	return {
	    {Day::Monday,    days[0]},
	    {Day::Tuesday,   days[1]},
	    {Day::Wednesday, days[2]},
	    {Day::Thursday,  days[3]},
	    {Day::Friday,    days[4]},
	    {Day::Saturday,  days[5]},
	    {Day::Sunday,    days[6]},
	};
}

struct Anime {
	std::string   name;
	std::uint16_t episode;
	std::uint16_t totalEpisodes;
	bool          isDubbedFromHome = false;
};

Anime parseAnimeData(const std::string& animeData) {
	using namespace std;

	Anime ret;

	if(animeData.substr(animeData.size() - 2, animeData.size() - 1) == "++")
		ret.isDubbedFromHome = true;

	smatch episodeSM, totalEpisodesSM, nameSM, bracketsSM;
	regex  nameRE(R"(^.* \()");
	regex  bracketsRE(R"(\(.*\))");
	regex  episodeRE(R"(\d+/)");
	regex  totalEpisodesRE(R"(/\d+)");

	regex_search(animeData, nameSM, nameRE);
	regex_search(animeData, bracketsSM, bracketsRE);

	string bracketsStr = bracketsSM.str();

	regex_search(bracketsStr, episodeSM, episodeRE);
	regex_search(bracketsStr, totalEpisodesSM, totalEpisodesRE);

	string episodeStr       = episodeSM.str();
	string totalEpisodesStr = totalEpisodesSM.str();
	string nameStr          = nameSM.str();

	ret.name                = std::regex_replace(
            nameStr.substr(0, nameStr.size() - 2),
            std::regex(R"(&.*;)"),
            "");
	ret.episode = stoi(episodeStr.substr(0, episodeStr.size() - 1));
	ret.totalEpisodes =
	    totalEpisodesStr.size() > 0
		? stoi(totalEpisodesStr.substr(1, totalEpisodesStr.size()))
		: 0;

	return ret;
}

tabulate::Table utils::genTable(const ParsedData& parseData) {
	using namespace tabulate;
	Table ret;

	ret.add_row({"Day", "Name", "Home Dub", "Episode", "Total Episodes"});

	for(const auto& data: parseData) {
		for(const auto& anime: data.second) {
			auto parsedAnimeData = parseAnimeData(anime);
			ret.add_row(
			    {dayToString(data.first),
			     parsedAnimeData.name,
			     parsedAnimeData.isDubbedFromHome ? "true" : "false",
			     std::to_string(parsedAnimeData.episode),
			     parsedAnimeData.totalEpisodes
				 ? std::to_string(parsedAnimeData.totalEpisodes)
				 : "?"});
		}
	}

	// center align 'Director' column
	ret.column(2).format().font_align(FontAlign::center);

	// right align 'Estimated Budget' column
	ret.column(3).format().font_align(FontAlign::right);

	// right align 'Release Date' column
	ret.column(4).format().font_align(FontAlign::right);

	// center-align and color header cells
	for(size_t i = 0; i < 5; ++i) {
		ret[0][i]
		    .format()
		    .font_color(Color::yellow)
		    .font_align(FontAlign::center)
		    .font_style({FontStyle::bold});
	}

	return ret;
}
