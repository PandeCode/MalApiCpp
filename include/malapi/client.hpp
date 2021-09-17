#pragma once
#include "./auth.hpp"
#include "./clientTypes.hpp"
#include "httplib.hpp"
#include "malapi/client.hpp"

#include <optional>
#include <string>

static const std::string BASE_URL = "https://api.myanimelist.net/v2/";

class Client {
	Auth                    m_auth;
	mutable httplib::Client httpClient;
	void                    ___defs();

	// Anime
	std::string M__getAnimeList(
	    std::string                query,
	    std::optional<std::string> fields = std::nullopt,
	    std::uint8_t               limit  = 100,
	    std::uint8_t               offset = 0) const;

	std::string M__getAnimeDetails(
	    std::uint32_t              animeId,
	    std::optional<std::string> fields = std::nullopt) const;

	std::string M__getAnimeRanking(
	    std::optional<std::string> fields      = std::nullopt,
	    AnimeRankingType           rankingType = AnimeRankingType::all,
	    std::uint8_t               limit       = 100,
	    std::uint8_t               offset      = 0) const;

	std::string M__getSeasonalAnime(
	    std::uint32_t              year,
	    SeasonParam                season,
	    SeasonSortParam            sort   = SeasonSortParam::anime_score,
	    std::optional<std::string> fields = std::nullopt,
	    std::uint8_t               limit  = 100,
	    std::uint8_t               offset = 0) const;

	// User Anime

	std::string M__getUserSuggestedAnime(
	    std::uint8_t               limit  = 100,
	    std::uint8_t               offset = 0,
	    std::optional<std::string> fields = std::nullopt) const;

	std::string M__updateUserAnimeListStatus(
	    std::uint32_t                   animeId,
	    std::optional<AnimeStatusParam> status             = std::nullopt,
	    std::optional<int>              score              = std::nullopt,
	    std::optional<int>              priority           = std::nullopt,
	    std::optional<int>              numWatchedEpisodes = std::nullopt,
	    std::optional<bool>             isRewatching       = std::nullopt,
	    std::optional<int>              numTimesRewatched  = std::nullopt,
	    std::optional<int>              rewatchValue       = std::nullopt,
	    std::optional<std::string>      tags               = std::nullopt,
	    std::optional<std::string>      comments           = std::nullopt) const;

	std::string M__getUserAnimeList(
	    std::string                       userName = "@me",
	    std::optional<AnimeStatusParam>   status   = std::nullopt,
	    std::optional<UserAnimeSortParam> sort     = std::nullopt,
	    std::uint8_t                      limit    = 100,
	    std::uint8_t                      offset   = 0) const;

	//# Forums

	std::string M__getForumBoards() const;
	std::string M__getForumTopicDetail(
	    std::uint32_t topicId,
	    std::uint8_t  limit  = 100,
	    std::uint8_t  offset = 0) const;

	std::string M__getForumTopics(
	    std::optional<std::uint32_t>  boardId       = std::nullopt,
	    std::optional<std::uint32_t>  subboardId    = std::nullopt,
	    std::optional<ForumSortParam> sort          = std::nullopt,
	    std::optional<std::string>    query         = std::nullopt,
	    std::optional<std::string>    topicUserName = std::nullopt,
	    std::optional<std::string>    userName      = std::nullopt,
	    std::uint8_t                  limit         = 100,
	    std::uint8_t                  offset        = 0) const;

	//# Manga
	std::string M__getMangaList(
	    std::string                query,
	    std::optional<std::string> fields = std::nullopt,
	    std::uint8_t               limit  = 100,
	    std::uint8_t               offset = 0) const;

	std::string M__getMangaDetails(
	    std::uint32_t              mangaId,
	    std::optional<std::string> fields = std::nullopt) const;

	std::string M__getMangaRanking(
	    MangaRankingTypeParam      rankingType = MangaRankingTypeParam::all,
	    std::uint8_t               limit       = 100,
	    std::uint8_t               offset      = 0,
	    std::optional<std::string> fields      = std::nullopt) const;

	//# User Manga

	std::string M__updateUserMangaListStatus(
	    std::uint32_t                   mangaId,
	    std::optional<MangaStatusParam> status          = std::nullopt,
	    std::optional<bool>             isReReading     = std::nullopt,
	    std::optional<std::uint8_t>     score           = std::nullopt,
	    std::optional<std::uint8_t>     numVolsRead     = std::nullopt,
	    std::optional<std::uint8_t>     numChaptersRead = std::nullopt,
	    std::optional<std::uint8_t>     priority        = std::nullopt,
	    std::optional<std::uint8_t>     numTimesRead    = std::nullopt,
	    std::optional<std::uint8_t>     reReadValue     = std::nullopt,
	    std::optional<std::string>      tags            = std::nullopt,
	    std::optional<std::string>      comments        = std::nullopt) const;

	std::string M__getUserMangaList(
	    std::string                     userName = "@me",
	    std::optional<MangaStatusParam> status   = std::nullopt,
	    std::optional<MangaSortParam>   sort     = std::nullopt,
	    std::uint8_t                    limit    = 100,
	    std::uint8_t                    offset   = 0) const;

	//# User
	std::string M__getUserData(
	    std::string                userName = "@me",
	    std::optional<std::string> fields   = std::nullopt) const;
      public:
	//
	// Anime
	template <class ReturnType = std::string>
	ReturnType getAnimeList(
	    std::string                query,
	    std::optional<std::string> fields = std::nullopt,
	    std::uint8_t               limit  = 100,
	    std::uint8_t               offset = 0) const;

	template <class ReturnType = std::string>
	ReturnType getAnimeDetails(
	    std::uint32_t              animeId,
	    std::optional<std::string> fields = std::nullopt) const;

	template <class ReturnType = std::string>
	ReturnType getAnimeRanking(
	    std::optional<std::string> fields      = std::nullopt,
	    AnimeRankingType           rankingType = AnimeRankingType::all,
	    std::uint8_t               limit       = 100,
	    std::uint8_t               offset      = 0) const;

	template <class ReturnType = std::string>
	ReturnType getSeasonalAnime(
	    std::uint32_t              year,
	    SeasonParam                season,
	    SeasonSortParam            sort   = SeasonSortParam::anime_score,
	    std::optional<std::string> fields = std::nullopt,
	    std::uint8_t               limit  = 100,
	    std::uint8_t               offset = 0) const;

	// User Anime

	template <class ReturnType = std::string>
	ReturnType getUserSuggestedAnime(
	    std::uint8_t               limit  = 100,
	    std::uint8_t               offset = 0,
	    std::optional<std::string> fields = std::nullopt) const;

	template <class ReturnType = std::string>
	ReturnType updateUserAnimeListStatus(
	    std::uint32_t                   animeId,
	    std::optional<AnimeStatusParam> status             = std::nullopt,
	    std::optional<int>              score              = std::nullopt,
	    std::optional<int>              priority           = std::nullopt,
	    std::optional<int>              numWatchedEpisodes = std::nullopt,
	    std::optional<bool>             isRewatching       = std::nullopt,
	    std::optional<int>              numTimesRewatched  = std::nullopt,
	    std::optional<int>              rewatchValue       = std::nullopt,
	    std::optional<std::string>      tags               = std::nullopt,
	    std::optional<std::string>      comments           = std::nullopt) const;

	template <class ReturnType = std::string>
	ReturnType getUserAnimeList(
	    std::string                       userName = "@me",
	    std::optional<AnimeStatusParam>   status   = std::nullopt,
	    std::optional<UserAnimeSortParam> sort     = std::nullopt,
	    std::uint8_t                      limit    = 100,
	    std::uint8_t                      offset   = 0) const;

	//# Forums

	template <class ReturnType = std::string>
	ReturnType getForumBoards() const;
	template <class ReturnType = std::string>
	ReturnType getForumTopicDetail(
	    std::uint32_t topicId,
	    std::uint8_t  limit  = 100,
	    std::uint8_t  offset = 0) const;

	template <class ReturnType = std::string>
	ReturnType getForumTopics(
	    std::optional<std::uint32_t>  boardId       = std::nullopt,
	    std::optional<std::uint32_t>  subboardId    = std::nullopt,
	    std::optional<ForumSortParam> sort          = std::nullopt,
	    std::optional<std::string>    query         = std::nullopt,
	    std::optional<std::string>    topicUserName = std::nullopt,
	    std::optional<std::string>    userName      = std::nullopt,
	    std::uint8_t                  limit         = 100,
	    std::uint8_t                  offset        = 0) const;

	//# Manga
	template <class ReturnType = std::string>
	ReturnType getMangaList(
	    std::string                query,
	    std::optional<std::string> fields = std::nullopt,
	    std::uint8_t               limit  = 100,
	    std::uint8_t               offset = 0) const;

	template <class ReturnType = std::string>
	ReturnType getMangaDetails(
	    std::uint32_t              mangaId,
	    std::optional<std::string> fields = std::nullopt) const;

	template <class ReturnType = std::string>
	ReturnType getMangaRanking(
	    MangaRankingTypeParam      rankingType = MangaRankingTypeParam::all,
	    std::uint8_t               limit       = 100,
	    std::uint8_t               offset      = 0,
	    std::optional<std::string> fields      = std::nullopt) const;

	//# User Manga

	template <class ReturnType = std::string>
	ReturnType updateUserMangaListStatus(
	    std::uint32_t                   mangaId,
	    std::optional<MangaStatusParam> status          = std::nullopt,
	    std::optional<bool>             isReReading     = std::nullopt,
	    std::optional<std::uint8_t>     score           = std::nullopt,
	    std::optional<std::uint8_t>     numVolsRead     = std::nullopt,
	    std::optional<std::uint8_t>     numChaptersRead = std::nullopt,
	    std::optional<std::uint8_t>     priority        = std::nullopt,
	    std::optional<std::uint8_t>     numTimesRead    = std::nullopt,
	    std::optional<std::uint8_t>     reReadValue     = std::nullopt,
	    std::optional<std::string>      tags            = std::nullopt,
	    std::optional<std::string>      comments        = std::nullopt) const;

	template <class ReturnType = std::string>
	ReturnType getUserMangaList(
	    std::string                     userName = "@me",
	    std::optional<MangaStatusParam> status   = std::nullopt,
	    std::optional<MangaSortParam>   sort     = std::nullopt,
	    std::uint8_t                    limit    = 100,
	    std::uint8_t                    offset   = 0) const;

	//# User
	template <class ReturnType = std::string>
	std::variant<std::string, UserObject> getUserData(
	    std::string                userName = "@me",
	    std::optional<std::string> fields   = std::nullopt) const;

	bool deleteUserAnime(std::uint32_t animeId) const;
	bool deleteUserMangaListItem(std::uint32_t mangaId) const;

	Client(Auth& auth);

	Client(
	    std::string clientId,
	    std::string clientSecrect,
	    std::string redirectUri,
	    std::string state = "Authenticaion");
};
