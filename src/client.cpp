#include "malapi/client.hpp"

#include "cpr/api.h"
#include "cpr/curl_container.h"
#include "cpr/parameters.h"

using namespace nlohmann;

Client::Client(Auth& auth) : m_auth(auth) {
	if(!auth.isAuthenticated) m_auth.authenticate();
}

Client::Client(
    std::string clientId,
    std::string clientSecrect,
    std::string redirectUri,
    std::string state) :
    m_auth(clientId, clientSecrect, redirectUri, state) {
	m_auth.authenticate();
}

std::string Client::M__getAnimeList(
    std::string                query,
    std::optional<std::string> fields,
    uint8_t                    limit,
    uint8_t                    offset) const {
	auto params = cpr::Parameters({
	    {"q", query},
	    {"limit", std::to_string(limit)},
	    {"offset", std::to_string(offset)},
	});
	if(fields.has_value()) params.Add({"fields", fields.value()});
	auto res = cpr::Get(cpr::Url(BASE_URL + "anime"), params, authHeader());
	return res.text;
};

std::string Client::M__getAnimeDetails(
    std::uint32_t              animeId,
    std::optional<std::string> fields) const {
	auto params = cpr::Parameters({});
	if(fields.has_value()) params.Add({"fields", fields.value()});
	auto res = cpr::Get(
	    cpr::Url(BASE_URL + "anime/" + std::to_string(animeId)),
	    params,
	    authHeader());
	return res.text;
}

std::string Client::M__getAnimeRanking(
    std::optional<std::string> fields,
    AnimeRankingParam          rankingType, //AnimeRankingParam
    uint8_t                    limit,
    uint8_t                    offset) const {
	return "{\"hey\": \"Not Implemented\"}";
}

std::string Client::M__getSeasonalAnime(
    std::uint32_t              year,
    SeasonParam                season,
    SeasonSortParam            sort,
    std::optional<std::string> fields,
    uint8_t                    limit,
    uint8_t                    offset) const {
	return "{\"hey\": \"Not Implemented\"}";
}

// User Anime

std::string Client::M__getUserSuggestedAnime(
    uint8_t                    limit,
    uint8_t                    offset,
    std::optional<std::string> fields) const {
	return "{\"hey\": \"Not Implemented\"}";
}

std::string Client::M__updateUserAnimeListStatus(
    std::uint32_t                   animeId,
    std::optional<AnimeStatusParam> status,
    std::optional<int>              score,
    std::optional<int>              priority,
    std::optional<int>              numWatchedEpisodes,
    std::optional<bool>             isRewatching,
    std::optional<int>              numTimesRewatched,
    std::optional<int>              rewatchValue,
    std::optional<std::string>      tags,
    std::optional<std::string>      comments) const {
	return "{\"hey\": \"Not Implemented\"}";
}

std::string Client::M__getUserAnimeList(
    std::string                       userName,
    std::optional<AnimeStatusParam>   status,
    std::optional<UserAnimeSortParam> sort,
    uint8_t                           limit,
    uint8_t                           offset) const {
	return "{\"hey\": \"Not Implemented\"}";
}

//# Forums

std::string Client::M__getForumBoards() const {
	return "{\"hey\": \"Not Implemented\"}";
}
std::string Client::M__getForumTopicDetail(
    std::uint32_t topicId,
    uint8_t       limit,
    uint8_t       offset) const {
	return "{\"hey\": \"Not Implemented\"}";
}

std::string Client::M__getForumTopics(
    std::optional<std::uint32_t>  boardId,
    std::optional<std::uint32_t>  subboardId,
    std::optional<ForumSortParam> sort,
    std::optional<std::string>    query,
    std::optional<std::string>    topicUserName,
    std::optional<std::string>    userName,
    uint8_t                       limit,
    uint8_t                       offset) const {
	return "{\"hey\": \"Not Implemented\"}";
}

//# Manga
std::string Client::M__getMangaList(
    std::string                query,
    std::optional<std::string> fields,
    uint8_t                    limit,
    uint8_t                    offset) const {
	return "{\"hey\": \"Not Implemented\"}";
}

std::string Client::M__getMangaDetails(std::uint32_t mangaId) const {
	return "{\"hey\": \"Not Implemented\"}";
}

std::string Client::M__getMangaRanking(
    std::string                rankingType, //MangaRankingTypeParam
    uint8_t                    limit,
    uint8_t                    offset,
    std::optional<std::string> fields) const {
	return "{\"hey\": \"Not Implemented\"}";
}

//# User Manga

std::string Client::M__updateUserMangaListStatus(
    std::uint32_t                   mangaId,
    std::optional<MangaStatusParam> status,
    std::optional<bool>             isReReading,
    std::optional<uint8_t>          score,
    std::optional<uint8_t>          numVolsRead,
    std::optional<uint8_t>          numChaptersRead,
    std::optional<uint8_t>          priority,
    std::optional<uint8_t>          numTimesRead,
    std::optional<uint8_t>          reReadValue,
    std::optional<std::string>      tags,
    std::optional<std::string>      comments) const {
	return "{\"hey\": \"Not Implemented\"}";
}

std::string Client::M__getUserMangaList(
    std::string                     userName,
    std::optional<MangaStatusParam> status,
    std::optional<MangaSortParam>   sort,
    uint8_t                         limit,
    uint8_t                         offset) const {
	return "{\"hey\": \"Not Implemented\"}";
}

std::string Client::M__getUserData(
    std::string                userName,
    std::optional<std::string> fields) const {
	auto params = cpr::Parameters {};
	if(fields.has_value()) params.Add({"fields", fields.value()});
	auto res =
	    cpr::Get(cpr::Url(BASE_URL + "users/" + userName), params, authHeader());
	return res.text;
}
