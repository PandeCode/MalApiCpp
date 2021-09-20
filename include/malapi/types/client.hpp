#pragma once
#include "malapi/types/animeList.hpp"
#include "nlohmann/json.hpp"

#include <cstdint>
#include <optional>
#include <sstream>
#include <string>

// Anime

// AlternativeTitlesObject The set of titles and synonyms of the anime.
struct AlternativeTitlesObject {
	std::string              en;       //  The English title of the media
	std::string              ja;       //  The original (native) name of the media
	std::vector<std::string> synonyms; // A list of synonyms of the media

	std::string toString() const;
};

// AnimeStudioObject The studio of the anime.
struct AnimeStudioObject {
	std::uint16_t id;   //eger  The id of the studio
	std::string   name; //  The name of the studio

	std::string toString() const;
};

// BroadcastObject The broadcasting schedule of the anime.
struct BroadcastObject {
	std::string
		    day_of_the_week; //  A lowercased string of the day that the media is released in a week. E.g. thursday
	std::string start_time; //  The time of the broadcast. E.g. 19:30

	std::string toString() const;
};

// GenreObject The genre of the anime.
struct GenreObject {
	std::uint16_t id; //eger  The id of the genre
	std::string
	    name; //  The name of the genre (Action, Adventure, Cars, Comedy, Dementia, Demons, Drama, Ecchi, Fantasy, Game, Harem, Hentai, Historical, Horror, Josei, Kids, Magic, Martial Arts, Mecha, Military, Music, Mystery, Parody, Police, Psychological, Romance, Samurai, School, SciFi, Seinen, Shoujo, Shoujo Ai, Shounen, Shounen Ai, Slice of Life, Space, Sports, Super Power, Supernatural, Thriller, Vampire, Yaoi, Yuri)

	std::string toString() const;
};

// PictureObject A set of pictures.
struct PictureObject {
	std::string large;  //  An absulute URL to the high(er) resolution picture
	std::string medium; //  An absulute URL to the medium resolution picture

	std::string toString() const;
};

// SeasonObject Representing a season in a year.
struct SeasonObject {
	std::string season; //  The season in a year (E.g. fall).
	std::uint16_t
	    year; //  The four digits integer representation of a year (E.g. 2002).

	std::string toString() const;
};

// MyListStatusObject The library entry.
struct MyListStatusObject {
	std::string    comments;
	bool           is_rewatching;
	std::uint16_t  num_episodes_watched;
	std::uint16_t  num_times_rewatched;
	std::uint16_t  priority;
	std::uint16_t  rewatch_value;
	double         score;
	ListStatusEnum status;
	std::string    tags;
	std::string    updated_at;

	std::string toString() const;
};

// UserObject
struct UserObject {
	std::uint16_t id; // An integer id of the user.
	std::string   name;
	std::string   location;
	std::string   joined_at;
	std::string   birthday;

	std::string toString() const;
};

struct AnimeObjectNode {
	AlternativeTitlesObject alternative_titles;
	uint16_t average_episode_duration; //Average duration(in seconds)of the episodes.
	BroadcastObject          broadcast;
	Date                     created_at;
	CalendarDate             end_date; // The date at which the anime ended.
	std::vector<GenreObject> genres;   // Genres of the anime.
	std::uint16_t            id; //  The identifier of this media on MyAnimeList.
	PictureObject            main_picture; // The poster artwork of the anime.
	double                   mean; //  The mean score of this media on MyAnimeList.
	std::string media_type; // Type of media(tv,ova,movie,special,ona,music,unknown).
	std::string nsfw;       //  The NSFW state for this media (white, gray, black).
	std::uint16_t num_episodes;  //  The number of episodes in this anime.
	std::uint16_t num_favorites; //Number of users that added this to their favorites.
	std::uint16_t num_list_users;    //Number of uses that added this to their lists.
	std::uint16_t num_scoring_users; //  Number of users that voted for the scores.
	std::uint16_t popularity;        //  The popularity rankings of this anime.
	std::uint16_t rank;              //  The rankings of this anime.
	CalendarDate  start_date;        // The date at which the anime started.
	SeasonObject  start_season; // The season at which the anime started broadcasting.
	std::string
		    status; //  An enumeration representing the broadcasting status of the anime (finished_airing, currently_airing, not_yet_aired).
	std::string synopsis; //  The synopsis of the anime.
	std::string
			  source; //  The original work that inspired this anime (original, manga, 4_koma_manga, web_manga, digital_manga, novel, light_novel, visual_novel, game, card_game, book, picture_book, radio, music, other).
	AnimeStudioObject studio;
	std::string       title; //  The canonical (?) title of the anime.
	Date updated_at; //  The last time that the information is updated on MyAnimeList.
	MyListStatusObject       my_list_status;
	std::string              background;    //  Background story of the anime
	std::vector<AnimeObject> related_anime; // A list of anime related to this anime
	std::string
	    rating; //  The rating of this anime (g All Ages, pg Children, pg_13 Teens 13 and Older, r 17+ (violence & profanity), r+ Profanity & Mild Nudity, rx Hentai).

	std::string toString() const;
};

// AnimeObject An AnimeObject represents an anime in MAL’s database.
struct AnimeObject {
	AnimeObjectNode node;

	std::string toString() const;
};

struct AnimeList {
	std::vector<AnimeObject> data;

	std::string toString() const;
};

struct AnimeRanking {
	std::string toString() const;
};

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

struct SeasonalAnime {

	std::string toString() const;
};

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
struct UserSuggestedAnime {
	std::string toString() const;
};

struct UserAnimeListStatus {
	std::string toString() const;
};
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

struct UserAnimeList {

	std::string toString() const;
};

// Forum
struct ForumBoards {
	std::string toString() const;
};
struct ForumTopicDetail {
	std::string toString() const;
};
struct ForumTopics {
	std::string toString() const;
};
enum class ForumSortParam : std::uint8_t { recent };

//Manga
struct MangaList {

	std::string toString() const;
};
struct MangaDetails {
	std::string toString() const;
};
struct MangaRanking {
	std::string toString() const;
};

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
struct UserMangaListStatus {
	std::string toString() const;
};
struct UserMangaList {
	std::string toString() const;
};
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

struct UserMangaListStatusUpdate {
	std::string toString() const;
};

