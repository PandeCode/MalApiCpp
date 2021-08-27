#pragma once
#include "./auth.hpp"
#include "./clientTypes.hpp"
#include "malapi/client.hpp"

#include <optional>
#include <string>

static const std::string BASE_URL = "https://api.myanimelist.net/v2/";

/*"opening_themes,ending_themes,synopsis,alternative_titles,media_type,my_list_"*/
/*"status{start_date,finish_"*/
/*"date,priority,comments}"*/
class Client {
	Auth               m_auth;
	inline cpr::Header authHeader() const {
		return cpr::Header({
		    {"Authorization", "Bearer " + m_auth.authData.access_token},
		    {"Accept", "application/json"},
		});
	};

	// Anime
	std::string M__getAnimeList(
	    std::string                query,
	    std::optional<std::string> fields = std::nullopt,
	    uint8_t                    limit  = 100,
	    uint8_t                    offset = 0) const;

	std::string M__getAnimeDetails(
	    std::uint32_t              animeId,
	    std::optional<std::string> fields = std::nullopt) const;

	std::string M__getAnimeRanking(
	    std::optional<std::string> fields      = std::nullopt,
	    AnimeRankingParam          rankingType = all,
	    uint8_t                    limit       = 100,
	    uint8_t                    offset      = 0) const;

	std::string M__getSeasonalAnime(
	    std::uint32_t              year,
	    SeasonParam                season,
	    SeasonSortParam            sort   = anime_score,
	    std::optional<std::string> fields = std::nullopt,
	    uint8_t                    limit  = 100,
	    uint8_t                    offset = 0) const;

	// User Anime

	std::string M__getUserSuggestedAnime(
	    uint8_t                    limit  = 100,
	    uint8_t                    offset = 0,
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
	    uint8_t                           limit    = 100,
	    uint8_t                           offset   = 0) const;

	//# Forums

	std::string M__getForumBoards() const;
	std::string M__getForumTopicDetail(
	    std::uint32_t topicId,
	    uint8_t       limit  = 100,
	    uint8_t       offset = 0) const;

	std::string M__getForumTopics(
	    std::optional<std::uint32_t>  boardId       = std::nullopt,
	    std::optional<std::uint32_t>  subboardId    = std::nullopt,
	    std::optional<ForumSortParam> sort          = std::nullopt,
	    std::optional<std::string>    query         = std::nullopt,
	    std::optional<std::string>    topicUserName = std::nullopt,
	    std::optional<std::string>    userName      = std::nullopt,
	    uint8_t                       limit         = 100,
	    uint8_t                       offset        = 0) const;

	//# Manga
	std::string M__getMangaList(
	    std::string                query,
	    std::optional<std::string> fields = std::nullopt,
	    uint8_t                    limit  = 100,
	    uint8_t                    offset = 0) const;

	std::string M__getMangaDetails(std::uint32_t mangaId) const;

	std::string M__getMangaRanking(
	    std::string                rankingType = "all", //MangaRankingTypeParam
	    uint8_t                    limit       = 100,
	    uint8_t                    offset      = 0,
	    std::optional<std::string> fields      = std::nullopt) const;

	//# User Manga

	std::string M__updateUserMangaListStatus(
	    std::uint32_t                   mangaId,
	    std::optional<MangaStatusParam> status          = std::nullopt,
	    std::optional<bool>             isReReading     = std::nullopt,
	    std::optional<uint8_t>          score           = std::nullopt,
	    std::optional<uint8_t>          numVolsRead     = std::nullopt,
	    std::optional<uint8_t>          numChaptersRead = std::nullopt,
	    std::optional<uint8_t>          priority        = std::nullopt,
	    std::optional<uint8_t>          numTimesRead    = std::nullopt,
	    std::optional<uint8_t>          reReadValue     = std::nullopt,
	    std::optional<std::string>      tags            = std::nullopt,
	    std::optional<std::string>      comments        = std::nullopt) const;

	std::string M__getUserMangaList(
	    std::string                     userName = "@me",
	    std::optional<MangaStatusParam> status   = std::nullopt,
	    std::optional<MangaSortParam>   sort     = std::nullopt,
	    uint8_t                         limit    = 100,
	    uint8_t                         offset   = 0) const;

	//# User
	std::string M__getUserData(
	    std::string                userName = "@me",
	    std::optional<std::string> fields   = std::nullopt) const;
      public:
	bool deleteUserAnime(std::uint32_t animeId) const;
	bool deleteUserMangaListItem(std::uint32_t mangaId) const;

	Client(Auth& auth);

	Client(
	    std::string clientId,
	    std::string clientSecrect,
	    std::string redirectUri,
	    std::string state = "Authenticaion");

	friend bool testClient();

	friend void testGetUserData(const Client&);
	friend void testGetAnimeList(const Client&);
	friend void testGetAnimeDetails(const Client&);
	friend void testGetAnimeRanking(const Client&);
	friend void testGetSeasonalAnime(const Client&);
	friend void testGetUserSuggestedAnime(const Client&);
	friend void testUpdateUserAnimeListStatus(const Client&);
	friend void testGetUserAnimeList(const Client&);
	friend void testGetForumBoards(const Client&);
	friend void testGetForumTopicDetail(const Client&);
	friend void testGetForumTopics(const Client&);
	friend void testGetMangaList(const Client&);
	friend void testGetMangaDetails(const Client&);
	friend void testGetMangaRanking(const Client&);
	friend void testUpdateUserMangaListStatus(const Client&);
	friend void testGetUserMangaList(const Client&);
};
