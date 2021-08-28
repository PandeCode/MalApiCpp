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

enum AnimeRankingType : std::uint8_t {
	all,          ///Top Anime Series
	airing,       ///Top Airing Anime
	upcoming,     ///Top Upcoming Anime
	tv,           ///Top Anime TV Series
	ova,          ///Top Anime OVA Series
	movie,        ///Top Anime Movies
	special,      ///Top Anime Specials
	bypopularity, ///Top Anime by Popularity
	favorite,     ///Top Favorited Anime
};

struct SeasonalAnime {};

enum SeasonParam : std::uint8_t {
	winter, /// January, February, March
	spring, /// April, May, June
	summer, /// July, August, September
	fall,   /// October, November, December
};
enum SeasonSortParam : std::uint8_t {
	anime_score,         /// Descending
	anime_num_list_users /// Descending
};

// UserAnime
struct UserSuggestedAnime {};

struct UserAnimeListStatus {};
enum AnimeStatusParam : std::uint8_t {
	watching,
	completed,
	on_hold,
	dropped,
	plan_to_watch,
};
enum UserAnimeSortParam : std::uint8_t {
	list_score,       // Descending
	list_updated_at,  // Descending
	anime_title,      // Ascending
	anime_start_date, // Descending
	anime_id,         // (Under Development) Ascending
};

struct UserAnimeList {};

// Forum
struct ForumBoards {};
struct ForumBoardsTopicDetail {};
struct ForumBoardsTopics {};
enum ForumSortParam : std::uint8_t { recent };

//Manga
struct MangaList {};
struct MangaDetails {};
struct MangaRankings {};
enum MangaRankingTypeParam : std::uint8_t {
	m_all,          // All
	manga,          // Top Manga
	oneshots,       // Top One-shots
	doujin,         // Top Doujinshi
	lightnovels,    // Top Light Novels
	novels,         // Top Novels
	manhwa,         // Top Manhwa
	manhua,         // Top Manhua
	m_bypopularity, // Most Popular
	m_favorite,     // Most Favorited
};

//UserManga
struct UserMangaList {};
enum MangaStatusParam : std::uint8_t {
	reading,
	ms_completed,
	ms_on_hold,
	ms_dropped,
	plan_to_read,
};

enum MangaSortParam : std::uint8_t {
	ms_list_score,      // Descending
	ms_list_updated_at, // Descending
	manga_title,        // Ascending
	manga_start_date,   // Descending
	manga_id,           // (Under Development)	Ascending
};

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
