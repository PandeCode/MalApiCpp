#pragma once
#include "cpp-httplib/httplib.hpp"
#include "malapi/auth.hpp"
#include "malapi/client.hpp"
#include "malapi/types/client.hpp"

#include <optional>
#include <pwd.h>
#include <string>
#include <sys/types.h>
#include <unistd.h>

class Client {
	Auth                    m_auth;
	mutable httplib::Client httpClient;

	// To get templates correct predefined
	void ___defs();

	// Anime
	std::string M__getAnimeList(
	    const std::string&                query,
	    const std::optional<std::string>& fields = std::nullopt,
	    const std::uint8_t&               limit  = 100,
	    const std::uint8_t&               offset = 0) const;

	std::string M__getAnimeDetails(
	    const std::uint32_t&              animeId,
	    const std::optional<std::string>& fields = std::nullopt) const;

	std::string M__getAnimeRanking(
	    const std::optional<std::string>& fields      = std::nullopt,
	    const AnimeRankingType&           rankingType = AnimeRankingType::all,
	    const std::uint8_t&               limit       = 100,
	    const std::uint8_t&               offset      = 0) const;

	std::string M__getSeasonalAnime(
	    const std::uint32_t&              year,
	    const SeasonParam&                season,
	    const SeasonSortParam&            sort   = SeasonSortParam::anime_score,
	    const std::optional<std::string>& fields = std::nullopt,
	    const std::uint8_t&               limit  = 100,
	    const std::uint8_t&               offset = 0) const;

	// User Anime

	std::string M__getUserSuggestedAnime(
	    const std::uint8_t&               limit  = 100,
	    const std::uint8_t&               offset = 0,
	    const std::optional<std::string>& fields = std::nullopt) const;

	std::string M__updateUserAnimeListStatus(
	    const std::uint32_t&                   animeId,
	    const std::optional<AnimeStatusParam>& status             = std::nullopt,
	    const std::optional<int>&              score              = std::nullopt,
	    const std::optional<int>&              priority           = std::nullopt,
	    const std::optional<int>&              numWatchedEpisodes = std::nullopt,
	    const std::optional<bool>&             isRewatching       = std::nullopt,
	    const std::optional<int>&              numTimesRewatched  = std::nullopt,
	    const std::optional<int>&              rewatchValue       = std::nullopt,
	    const std::optional<std::string>&      tags               = std::nullopt,
	    const std::optional<std::string>&      comments = std::nullopt) const;

	std::string M__getUserAnimeList(
	    const std::string&                       userName = "@me",
	    const std::optional<AnimeStatusParam>&   status   = std::nullopt,
	    const std::optional<UserAnimeSortParam>& sort     = std::nullopt,
	    const std::uint8_t&                      limit    = 100,
	    const std::uint8_t&                      offset   = 0) const;

	//# Forums

	std::string M__getForumBoards() const;
	std::string M__getForumTopicDetail(
	    const std::uint32_t& topicId,
	    const std::uint8_t&  limit  = 100,
	    const std::uint8_t&  offset = 0) const;

	std::string M__getForumTopics(
	    const std::optional<std::uint32_t>&  boardId       = std::nullopt,
	    const std::optional<std::uint32_t>&  subboardId    = std::nullopt,
	    const std::optional<ForumSortParam>& sort          = std::nullopt,
	    const std::optional<std::string>&    query         = std::nullopt,
	    const std::optional<std::string>&    topicUserName = std::nullopt,
	    const std::optional<std::string>&    userName      = std::nullopt,
	    const std::uint8_t&                  limit         = 100,
	    const std::uint8_t&                  offset        = 0) const;

	//# Manga
	std::string M__getMangaList(
	    const std::string&                query,
	    const std::optional<std::string>& fields = std::nullopt,
	    const std::uint8_t&               limit  = 100,
	    const std::uint8_t&               offset = 0) const;

	std::string M__getMangaDetails(
	    const std::uint32_t&              mangaId,
	    const std::optional<std::string>& fields = std::nullopt) const;

	std::string M__getMangaRanking(
	    const MangaRankingTypeParam&      rankingType = MangaRankingTypeParam::all,
	    const std::uint8_t&               limit       = 100,
	    const std::uint8_t&               offset      = 0,
	    const std::optional<std::string>& fields      = std::nullopt) const;

	//# User Manga

	std::string M__updateUserMangaListStatus(
	    const std::uint32_t&                   mangaId,
	    const std::optional<MangaStatusParam>& status          = std::nullopt,
	    const std::optional<bool>&             isReReading     = std::nullopt,
	    const std::optional<std::uint8_t>&     score           = std::nullopt,
	    const std::optional<std::uint8_t>&     numVolsRead     = std::nullopt,
	    const std::optional<std::uint8_t>&     numChaptersRead = std::nullopt,
	    const std::optional<std::uint8_t>&     priority        = std::nullopt,
	    const std::optional<std::uint8_t>&     numTimesRead    = std::nullopt,
	    const std::optional<std::uint8_t>&     reReadValue     = std::nullopt,
	    const std::optional<std::string>&      tags            = std::nullopt,
	    const std::optional<std::string>&      comments        = std::nullopt) const;

	std::string M__getUserMangaList(
	    const std::string&                     userName = "@me",
	    const std::optional<MangaStatusParam>& status   = std::nullopt,
	    const std::optional<MangaSortParam>&   sort     = std::nullopt,
	    const std::uint8_t&                    limit    = 100,
	    const std::uint8_t&                    offset   = 0) const;

	//# User
	std::string M__getUserData(
	    const std::string&                userName = "@me",
	    const std::optional<std::string>& fields   = std::nullopt) const;
      public:
	//
	// Anime
	template <class ReturnType = std::string>
	std::variant<std::string, AnimeList> getAnimeList(
	    const std::string&                query,
	    const std::optional<std::string>& fields = std::nullopt,
	    const std::uint8_t&               limit  = 100,
	    const std::uint8_t&               offset = 0) const;

	template <class ReturnType = std::string>
	std::variant<std::string, AnimeDetails> getAnimeDetails(
	    const std::uint32_t&              animeId,
	    const std::optional<std::string>& fields = std::nullopt) const;

	template <class ReturnType = std::string>
	std::variant<std::string, AnimeRanking> getAnimeRanking(
	    const std::optional<std::string>& fields      = std::nullopt,
	    const AnimeRankingType&           rankingType = AnimeRankingType::all,
	    const std::uint8_t&               limit       = 100,
	    const std::uint8_t&               offset      = 0) const;

	template <class ReturnType = std::string>
	std::variant<std::string, SeasonalAnime> getSeasonalAnime(
	    const std::uint32_t&              year,
	    const SeasonParam&                season,
	    const SeasonSortParam&            sort   = SeasonSortParam::anime_score,
	    const std::optional<std::string>& fields = std::nullopt,
	    const std::uint8_t&               limit  = 100,
	    const std::uint8_t&               offset = 0) const;

	// User Anime

	template <class ReturnType = std::string>
	std::variant<std::string, UserSuggestedAnime> getUserSuggestedAnime(
	    const std::uint8_t&               limit  = 100,
	    const std::uint8_t&               offset = 0,
	    const std::optional<std::string>& fields = std::nullopt) const;

	template <class ReturnType = std::string>
	std::variant<std::string, UserAnimeListStatus> updateUserAnimeListStatus(
	    const std::uint32_t&                   animeId,
	    const std::optional<AnimeStatusParam>& status             = std::nullopt,
	    const std::optional<int>&              score              = std::nullopt,
	    const std::optional<int>&              priority           = std::nullopt,
	    const std::optional<int>&              numWatchedEpisodes = std::nullopt,
	    const std::optional<bool>&             isRewatching       = std::nullopt,
	    const std::optional<int>&              numTimesRewatched  = std::nullopt,
	    const std::optional<int>&              rewatchValue       = std::nullopt,
	    const std::optional<std::string>&      tags               = std::nullopt,
	    const std::optional<std::string>&      comments = std::nullopt) const;

	template <class ReturnType = std::string>
	std::variant<std::string, UserAnimeList> getUserAnimeList(
	    const std::string&                       userName = "@me",
	    const std::optional<AnimeStatusParam>&   status   = std::nullopt,
	    const std::optional<UserAnimeSortParam>& sort     = std::nullopt,
	    const std::uint8_t&                      limit    = 100,
	    const std::uint8_t&                      offset   = 0) const;

	//# Forums

	template <class ReturnType = std::string>
	std::variant<std::string, ForumBoards> getForumBoards() const;

	template <class ReturnType = std::string>
	std::variant<std::string, ForumTopicDetail> getForumTopicDetail(
	    const std::uint32_t& topicId,
	    const std::uint8_t&  limit  = 100,
	    const std::uint8_t&  offset = 0) const;

	template <class ReturnType = std::string>
	std::variant<std::string, ForumTopics> getForumTopics(
	    const std::optional<std::uint32_t>&  boardId       = std::nullopt,
	    const std::optional<std::uint32_t>&  subboardId    = std::nullopt,
	    const std::optional<ForumSortParam>& sort          = std::nullopt,
	    const std::optional<std::string>&    query         = std::nullopt,
	    const std::optional<std::string>&    topicUserName = std::nullopt,
	    const std::optional<std::string>&    userName      = std::nullopt,
	    const std::uint8_t&                  limit         = 100,
	    const std::uint8_t&                  offset        = 0) const;

	//# Manga
	template <class ReturnType = std::string>
	std::variant<std::string, MangaList> getMangaList(
	    const std::string&                query,
	    const std::optional<std::string>& fields = std::nullopt,
	    const std::uint8_t&               limit  = 100,
	    const std::uint8_t&               offset = 0) const;

	template <class ReturnType = std::string>
	std::variant<std::string, MangaDetails> getMangaDetails(
	    const std::uint32_t&              mangaId,
	    const std::optional<std::string>& fields = std::nullopt) const;

	template <class ReturnType = std::string>
	std::variant<std::string, MangaRanking> getMangaRanking(
	    const MangaRankingTypeParam&      rankingType = MangaRankingTypeParam::all,
	    const std::uint8_t&               limit       = 100,
	    const std::uint8_t&               offset      = 0,
	    const std::optional<std::string>& fields      = std::nullopt) const;

	//# User Manga

	template <class ReturnType = std::string>
	std::variant<std::string, UserMangaListStatus> updateUserMangaListStatus(
	    const std::uint32_t&                   mangaId,
	    const std::optional<MangaStatusParam>& status          = std::nullopt,
	    const std::optional<bool>&             isReReading     = std::nullopt,
	    const std::optional<std::uint8_t>&     score           = std::nullopt,
	    const std::optional<std::uint8_t>&     numVolsRead     = std::nullopt,
	    const std::optional<std::uint8_t>&     numChaptersRead = std::nullopt,
	    const std::optional<std::uint8_t>&     priority        = std::nullopt,
	    const std::optional<std::uint8_t>&     numTimesRead    = std::nullopt,
	    const std::optional<std::uint8_t>&     reReadValue     = std::nullopt,
	    const std::optional<std::string>&      tags            = std::nullopt,
	    const std::optional<std::string>&      comments        = std::nullopt) const;

	template <class ReturnType = std::string>
	std::variant<std::string, UserMangaList> getUserMangaList(
	    const std::string&                     userName = "@me",
	    const std::optional<MangaStatusParam>& status   = std::nullopt,
	    const std::optional<MangaSortParam>&   sort     = std::nullopt,
	    const std::uint8_t&                    limit    = 100,
	    const std::uint8_t&                    offset   = 0) const;

	//# User
	template <class ReturnType = std::string>
	std::variant<std::string, UserObject> getUserData(
	    const std::string&                userName = "@me",
	    const std::optional<std::string>& fields   = std::nullopt) const;

	bool deleteUserAnime(const std::uint32_t& animeId) const;
	bool deleteUserMangaListItem(const std::uint32_t& mangaId) const;

	static inline const std::string defaultCacheFile =
	    std::string(getpwuid(getuid())->pw_dir) + "/.cache/.malcache.json";

	Client(Auth& auth, const std::string& cacheFile = defaultCacheFile);

	Client(
	    const std::string& clientId,
	    const std::string& clientSecrect,
	    const std::string& redirectUri,
	    const std::string& cacheFile = defaultCacheFile,
	    const std::string& state     = "Authenticaion");
};
