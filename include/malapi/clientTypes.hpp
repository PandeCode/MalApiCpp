// Anime
#include <string>
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
