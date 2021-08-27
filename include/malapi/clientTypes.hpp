#include "../nlohmann/json.hpp"

#include <cstdint>
#include <optional>
#include <string>

#define DECL_JSON(Type)                                                             \
	void to_json(nlohmann::json& nlohmann_json_j, const Type& nlohmann_json_t); \
	void from_json(const nlohmann::json& nlohmann_json_j, Type& nlohmann_json_t);

// Anime
struct AnimeList {};

struct AnimeDetails {};

struct AnimeRanking {};
enum AnimeRankingParam { all };

struct SeasonalAnime {};

enum SeasonParam {
	winter, /// January, February, March
	spring, /// April, May, June
	summer, /// July, August, September
	fall,   /// October, November, December
};
enum SeasonSortParam {
	anime_score,         /// Descending
	anime_num_list_users /// Descending
};

// UserAnime
struct UserSuggestedAnime {};

struct UserAnimeListStatus {};
struct AnimeStatusParam {};

struct UserAnimeList {};
struct UserAnimeSortParam {};

// Forum
struct ForumBoards {};
struct ForumBoardsTopicDetail {};
struct ForumBoardsTopics {};
struct ForumSortParam {}; //[Literal["recent"], None]

//Manga
struct MangaList {};
struct MangaDetails {};
struct MangaRankings {};
struct MangaRankingTypeParam {};

//UserManga
struct UserMangaList {};
struct MangaStatusParam {};
struct MangaSortParam {};
struct UserMangaListStatusUpdate {};

//User Data
struct UserData {
	int         id;
	std::string birthday;
	std::string joined_at;
	std::string location;
	std::string name;
};

//DECL_JSON(UserData);
