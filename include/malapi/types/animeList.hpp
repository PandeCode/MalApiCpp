#pragma once

enum class AnimeRankingType : std::uint8_t;
enum class AnimeStatusParam : std::uint8_t;
enum class ForumSortParam : std::uint8_t;
enum class MangaRankingTypeParam : std::uint8_t;
enum class MangaSortParam : std::uint8_t;
enum class MangaStatusParam : std::uint8_t;
enum class SeasonParam : std::uint8_t;
enum class SeasonSortParam : std::uint8_t;
enum class UserAnimeSortParam : std::uint8_t;

struct AlternativeTitlesObject;
struct AnimeList;
struct AnimeObject;
struct AnimeObjectNode;
struct AnimeRanking ;
struct AnimeStudioObject;
struct BroadcastObject;
struct ForumBoards;
struct ForumBoardsTopicDetail;
struct ForumBoardsTopics;
struct ForumTopics;
struct GenreObject;
struct MangaDetails;
struct MangaList;
struct MangaRanking;
struct MyListStatusObject;
struct PictureObject;
struct SeasonObject;
struct SeasonalAnime;
struct UserAnimeList;
struct UserAnimeListStatus;
struct UserMangaList;
struct UserMangaListStatusUpdate;
struct UserObject;
struct UserSuggestedAnime;

// A simple date formatted as yyyymmdd (e.g. 20070208).
typedef std::string CalendarDate;
// A specific time. A ISO 8601 formatted time string.
typedef std::string Date;
// The method of sorting the entries in the response lists.( anime_title|list_score|list_updated_at|anime_start_date )
typedef std::string SortingMethodEnum;
// ListStatusEnum The list status of the user.( watching|completed|on_hold|dropped|plan_to_watch )
typedef std::string  ListStatusEnum;
typedef AnimeObject  AnimeDetails;
typedef UserObject   UserDetails;
typedef MangaRanking MangaRankings;
typedef AnimeRanking AnimeRankings;
