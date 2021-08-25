#pragma once
#include "./auth.hpp"
#include "./clientTypes.hpp"

#include <map>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

class Client {
	Auth m_auth;
      public:
	Client(Auth& auth);

	Client(
	    std::string clientId,
	    std::string clientSecrect,
	    std::string redirectUri,
	    std::string state = "Authenticaion");

	friend bool testClient();

	// Anime
	AnimeList getAnimeList(
	    std::string                query,
	    std::optional<std::string> fields = std::nullopt,
	    uint8_t                    limit  = 100,
	    uint8_t                    offset = 0);

	AnimeDetails
	    getAnimeDetails(uint16_t animeId, std::optional<std::string> fields = "");

	AnimeRanking getAnimeRanking(
	    std::optional<std::string> fields      = std::nullopt,
	    std::string                rankingType = "all", //AnimeRankingParam
	    uint8_t                    limit       = 100,
	    uint8_t                    offset      = 0);

	SeasonalAnime getSeasonalAnime(
	    uint16_t                   year,
	    SeasonParam                season,
	    SeasonSortParam            sort,
	    std::optional<std::string> fields = std::nullopt,
	    uint8_t                    limit  = 100,
	    uint8_t                    offset = 0);

	// User Anime

	UserSuggestedAnime getUserSuggestedAnime(
	    uint8_t                    limit  = 100,
	    uint8_t                    offset = 0,
	    std::optional<std::string> fields = "");

	UserAnimeListStatus updateUserAnimeListStatus(
	    uint16_t                        animeId,
	    std::optional<AnimeStatusParam> status,
	    std::optional<int>              score,
	    std::optional<int>              priority,
	    std::optional<int>              numWatchedEpisodes,
	    std::optional<bool>             isRewatching,
	    std::optional<int>              numTimesRewatched,
	    std::optional<int>              rewatchValue,
	    std::optional<std::string>      tags,
	    std::optional<std::string>      comments);

	bool deleteUserAnime(uint16_t animeId);

	UserAnimeList getUserAnimeList(
	    std::string                       userName = "@me",
	    std::optional<AnimeStatusParam>   status   = std::nullopt,
	    std::optional<UserAnimeSortParam> sort     = std::nullopt,
	    uint8_t                           limit    = 100,
	    uint8_t                           offset   = 0);

	//# Forums

	ForumBoards            getForumBoards();
	ForumBoardsTopicDetail getForumTopicDetail(
	    uint16_t topicId,
	    uint8_t  limit  = 100,
	    uint8_t  offset = 0);
	ForumBoardsTopics getForumTopics(
	    uint16_t                      boardId,
	    uint16_t                      subboardId,
	    std::optional<ForumSortParam> sort          = std::nullopt,
	    std::optional<std::string>    query         = std::nullopt,
	    std::optional<std::string>    topicUserName = std::nullopt,
	    std::optional<std::string>    userName      = std::nullopt,
	    uint8_t                       limit         = 100,
	    uint8_t                       offset        = 0);

	//# Manga
	MangaList getMangaList(
	    std::string                query,
	    std::optional<std::string> fields = std::nullopt,
	    uint8_t                    limit  = 100,
	    uint8_t                    offset = 0);

	MangaDetails getMangaDetails(uint16_t mangaId);

	MangaRankings getMangaRanking(
	    std::string                rankingType = "all", //MangaRankingTypeParam
	    uint8_t                    limit       = 100,
	    uint8_t                    offset      = 0,
	    std::optional<std::string> fields      = std::nullopt);

	//# User Manga

	UserMangaListStatusUpdate updateUserMangaListStatus(
	    uint16_t                        mangaId,
	    std::optional<MangaStatusParam> status          = std::nullopt,
	    std::optional<bool>             isReReading     = std::nullopt,
	    std::optional<uint8_t>          score           = std::nullopt,
	    std::optional<uint8_t>          numVolsRead     = std::nullopt,
	    std::optional<uint8_t>          numChaptersRead = std::nullopt,
	    std::optional<uint8_t>          priority        = std::nullopt,
	    std::optional<uint8_t>          numTimesRead    = std::nullopt,
	    std::optional<uint8_t>          reReadValue     = std::nullopt,
	    std::optional<std::string>      tags            = std::nullopt,
	    std::optional<std::string>      comments        = std::nullopt);

	bool deleteUserMangaListItem(uint16_t mangaId);

	UserMangaList getUserMangaList(
	    std::string                     userName = "@me",
	    std::optional<MangaStatusParam> status   = std::nullopt,
	    std::optional<MangaSortParam>   sort     = std::nullopt,
	    uint8_t                         limit    = 100,
	    uint8_t                         offset   = 0);

	//# User
	UserData getUserData(
	    std::string                userName = "@me",
	    std::optional<std::string> fields   = std::nullopt);
};
