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

enum class AnimeRankingType : std::uint8_t {
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

enum class SeasonParam : std::uint8_t {
	winter, /// January, February, March
	spring, /// April, May, June
	summer, /// July, August, September
	fall,   /// October, November, December
};
enum class SeasonSortParam : std::uint8_t {
	anime_score,         /// Descending
	anime_num_list_users /// Descending
};

// UserAnime
struct UserSuggestedAnime {};

struct UserAnimeListStatus {};
enum class AnimeStatusParam : std::uint8_t {
	watching,
	completed,
	on_hold,
	dropped,
	plan_to_watch,
};
enum class UserAnimeSortParam : std::uint8_t {
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
enum class ForumSortParam : std::uint8_t { recent };

//Manga
struct MangaList {};
struct MangaDetails {};
struct MangaRankings {};
enum class MangaRankingTypeParam : std::uint8_t {
	all,          // All
	bypopularity, // Most Popular
		      //manga,        // Top Manga
		      //oneshots,     // Top One-shots
		      //doujin,       // Top Doujinshi
		      //lightnovels,  // Top Light Novels
		      //novels,       // Top Novels
		      //manhwa,       // Top Manhwa
		      //manhua,       // Top Manhua
	//favorite,     // Most Favorited
};

//UserManga
struct UserMangaList {};
enum class MangaStatusParam : std::uint8_t {
	reading,
	completed,
	on_hold,
	dropped,
	plan_to_read,
};

enum class MangaSortParam : std::uint8_t {
	list_score,       // Descending
	list_updated_at,  // Descending
	manga_title,      // Ascending
	manga_start_date, // Descending
	manga_id,         // (Under Development)	Ascending
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
