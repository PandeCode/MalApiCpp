#include <optional>
#include <string>

#define NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_NON_INLINE(Type, ...)                         \
	void to_json(nlohmann::json& nlohmann_json_j, const Type& nlohmann_json_t) {     \
		NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(NLOHMANN_JSON_TO, __VA_ARGS__)) \
	}                                                                                \
	void from_json(const nlohmann::json& nlohmann_json_j, Type& nlohmann_json_t) {   \
		NLOHMANN_JSON_EXPAND(                                                    \
		    NLOHMANN_JSON_PASTE(NLOHMANN_JSON_FROM, __VA_ARGS__))                \
	}

// Anime
struct AnimeList {};
struct AnimeDetails {};

struct AnimeRanking {};
struct AnimeRankingParam {};

struct SeasonalAnime {};
struct SeasonParam {};
struct SeasonSortParam {};

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

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_NON_INLINE(
    UserData,
    id,
    birthday,
    joined_at,
    location,
    name);
