#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "malapi/client.hpp"

#include "httplib.hpp"

#include <cstdint>
#include <iostream>

using namespace nlohmann;

static constexpr std::uint8_t LIMIT_DEFAULT  = 100;
static constexpr std::uint8_t OFFSET_DEFAULT = 0;
static const std::string      FAILED_REQUEST_TEXT =
    "{\"message\" : \"failed_request\", \"message\": \"\"}";

httplib::Client httpClient = httplib::Client("https://api.myanimelist.net");

static void printResponse(cpr::Response& res) {
	std::cout << "status_code : " << res.status_code << std::endl;
	std::cout << "text        : " << res.text << std::endl;
	std::cout << "raw_header  : " << res.raw_header << std::endl;
	std::cout << "reason      : " << res.reason << std::endl;
}

static const std::string& handleReturn(cpr::Response& res) {
	switch(res.status_code) {
		case 0: return FAILED_REQUEST_TEXT; break;
		case 200: return res.text; break;
		default:
			std::cout << "\033[91m";
			printResponse(res);
			std::cout << "\033[0m";
			return res.text;
			break;
	}
}

Client::Client(Auth& auth) : m_auth(auth) {
	if(!auth.isAuthenticated) m_auth.authenticate();

	httpClient.set_default_headers({
	    {"Authorization", "Bearer " + m_auth.authData.access_token},
	    {"Accept", "application/json"},
	});
}

Client::Client(
    std::string clientId,
    std::string clientSecrect,
    std::string redirectUri,
    std::string state) :
    m_auth(clientId, clientSecrect, redirectUri, state) {
	m_auth.authenticate();

	this->httpClient.set_default_headers({
	    {"Authorization", "Bearer " + m_auth.authData.access_token},
	    {"Accept", "application/json"},
	});
}

std::string Client::M__getAnimeList(
    std::string                query,
    std::optional<std::string> fields,
    std::uint8_t               limit,
    std::uint8_t               offset) const {

	httplib::Params params {{"q", query}};
	if(fields.has_value()) params.emplace("fields", fields.value());
	if(limit != LIMIT_DEFAULT) params.emplace("limit", std::to_string(limit));
	if(offset != OFFSET_DEFAULT) params.emplace("offset", std::to_string(offset));

	if(auto res = httpClient.Get("/v2/anime", params)) {
		if(res->status == 200) {
			std::cout << res->body << std::endl;
			return res->body;
		}
		return FAILED_REQUEST_TEXT;
	} else {
		auto err = res.error();
		std::cout << "Error: " << err << std::endl;
		return FAILED_REQUEST_TEXT;
	}
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
	return handleReturn(res);
}

std::string Client::M__getAnimeRanking(
    std::optional<std::string> fields,
    AnimeRankingType           rankingType,
    std::uint8_t               limit,
    std::uint8_t               offset) const {
	auto params = cpr::Parameters({});

	switch(rankingType) {
		case all: params.Add({"ranking_type", "all"}); break;
		case airing: params.Add({"ranking_type", "airing"}); break;
		case upcoming: params.Add({"ranking_type", "upcoming"}); break;
		case tv: params.Add({"ranking_type", "tv"}); break;
		case ova: params.Add({"ranking_type", "ova"}); break;
		case movie: params.Add({"ranking_type", "movie"}); break;
		case special: params.Add({"ranking_type", "special"}); break;
		case bypopularity: params.Add({"ranking_type", "bypopularity"}); break;
		case favorite: params.Add({"ranking_type", "favorite"}); break;
	}

	if(fields.has_value()) params.Add({"fields", fields.value()});
	if(limit != LIMIT_DEFAULT) params.Add({"limit", std::to_string(limit)});
	if(offset != OFFSET_DEFAULT) params.Add({"offset", std::to_string(offset)});
	auto res = cpr::Get(cpr::Url(BASE_URL + "anime/ranking"), params, authHeader());
	return handleReturn(res);
}

std::string Client::M__getSeasonalAnime(
    std::uint32_t              year,
    SeasonParam                season,
    SeasonSortParam            sort,
    std::optional<std::string> fields,
    std::uint8_t               limit,
    std::uint8_t               offset) const {
	std::string seasonString;
	switch(season) {
		case winter: seasonString = "/winter"; break;
		case spring: seasonString = "/spring"; break;
		case summer: seasonString = "/summer"; break;
		case fall: seasonString = "/fall"; break;
	}

	auto params = cpr::Parameters({});

	if(sort != anime_score) {
		switch(sort) {
			case anime_num_list_users:
				params.Add({"sort", "anime_num_list_users"});
				break;
			case anime_score:
				params.Add({"sort", "anime_score"});
				break; // Dead Code
		}
	}

	if(fields.has_value()) params.Add({"fields", fields.value()});
	if(limit != LIMIT_DEFAULT) params.Add({"limit", std::to_string(limit)});
	if(offset != OFFSET_DEFAULT) params.Add({"offset", std::to_string(offset)});

	auto res = cpr::Get(
	    cpr::Url(BASE_URL + "anime/season/" + std::to_string(year) + seasonString),
	    params,
	    authHeader());
	return handleReturn(res);
}

// User Anime

std::string Client::M__getUserSuggestedAnime(
    std::uint8_t               limit,
    std::uint8_t               offset,
    std::optional<std::string> fields) const {

	auto params = cpr::Parameters({});

	if(fields.has_value()) params.Add({"fields", fields.value()});
	if(limit != LIMIT_DEFAULT) params.Add({"limit", std::to_string(limit)});
	if(offset != OFFSET_DEFAULT) params.Add({"offset", std::to_string(offset)});

	auto res =
	    cpr::Get(cpr::Url(BASE_URL + "anime/suggestions"), params, authHeader());
	return handleReturn(res);
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
	auto params = cpr::Parameters({});

	if(status.has_value()) switch(status.value()) {
			case watching: params.Add({"status", "watching"}); break;
			case completed: params.Add({"status", "completed"}); break;
			case on_hold: params.Add({"status", "on_hold"}); break;
			case dropped: params.Add({"status", "dropped"}); break;
			case plan_to_watch:
				params.Add({"status", "plan_to_watch"});
				break;
		}

	if(score.has_value()) params.Add({"score", std::to_string(score.value())});
	if(priority.has_value())
		params.Add({"priority", std::to_string(priority.value())});
	if(numWatchedEpisodes.has_value())
		params.Add(
		    {"num_watched_episodes", std::to_string(numWatchedEpisodes.value())});
	if(isRewatching.has_value())
		params.Add({"is_rewatching", std::to_string(isRewatching.value())});
	if(numTimesRewatched.has_value())
		params.Add(
		    {"num_times_rewatched", std::to_string(numTimesRewatched.value())});
	if(rewatchValue.has_value())
		params.Add({"rewatch_value", std::to_string(rewatchValue.value())});
	if(tags.has_value()) params.Add({"tags", tags.value()});
	if(comments.has_value()) params.Add({"comments", comments.value()});

	auto res = cpr::Patch(
	    cpr::Url(BASE_URL + "anime/" + std::to_string(animeId) + "/my_list_status"),
	    params,
	    authHeader());
	return handleReturn(res);
}

std::string Client::M__getUserAnimeList(
    std::string                       userName,
    std::optional<AnimeStatusParam>   status,
    std::optional<UserAnimeSortParam> sort,
    std::uint8_t                      limit,
    std::uint8_t                      offset) const {

	auto params = cpr::Parameters({});

	if(sort.has_value()) switch(sort.value()) {
			case list_score: params.Add({"sort", "list_score"}); break;
			case list_updated_at:
				params.Add({"sort", "list_updated_at"});
				break;
			case anime_title: params.Add({"sort", "anime_title"}); break;
			case anime_start_date:
				params.Add({"sort", "anime_start_date"});
				break;
			case anime_id: params.Add({"sort", "anime_id"}); break;
		}
	if(status.has_value()) switch(status.value()) {
			case watching: params.Add({"status", "watching"}); break;
			case completed: params.Add({"status", "completed"}); break;
			case on_hold: params.Add({"status", "on_hold"}); break;
			case dropped: params.Add({"status", "dropped"}); break;
			case plan_to_watch:
				params.Add({"status", "plan_to_watch"});
				break;
		}

	if(limit != LIMIT_DEFAULT) params.Add({"limit", std::to_string(limit)});
	if(offset != OFFSET_DEFAULT) params.Add({"offset", std::to_string(offset)});

	auto res = cpr::Get(
	    cpr::Url(BASE_URL + "users/" + userName + "/animelist"),
	    params,
	    authHeader());
	return handleReturn(res);
}

//# Forums

std::string Client::M__getForumBoards() const {
	auto res = cpr::Get(cpr::Url(BASE_URL + "forum/boards"), authHeader());
	return handleReturn(res);
}

std::string Client::M__getForumTopicDetail(
    std::uint32_t topicId,
    std::uint8_t  limit,
    std::uint8_t  offset) const {

	auto params = cpr::Parameters({});
	if(limit != LIMIT_DEFAULT) params.Add({"limit", std::to_string(limit)});
	if(offset != OFFSET_DEFAULT) params.Add({"offset", std::to_string(offset)});

	auto res = cpr::Get(
	    cpr::Url(BASE_URL + "forum/topic/" + std::to_string(topicId)),
	    params,
	    authHeader());
	return handleReturn(res);
}

std::string Client::M__getForumTopics(
    std::optional<std::uint32_t>  boardId,
    std::optional<std::uint32_t>  subboardId,
    std::optional<ForumSortParam> sort,
    std::optional<std::string>    query,
    std::optional<std::string>    topicUserName,
    std::optional<std::string>    userName,
    std::uint8_t                  limit,
    std::uint8_t                  offset) const {

	auto params = cpr::Parameters({});

	if(sort.has_value()) switch(sort.value()) {
			case recent: params.Add({"sort", "recent"}); break;
		}

	if(boardId.has_value()) params.Add({"board_id", std::to_string(boardId.value())});
	if(subboardId.has_value())
		params.Add({"subboard_id", std::to_string(subboardId.value())});
	if(query.has_value()) params.Add({"query", query.value()});
	if(topicUserName.has_value())
		params.Add({"topic_user_name", topicUserName.value()});
	if(userName.has_value()) params.Add({"user_name", userName.value()});

	if(limit != LIMIT_DEFAULT) params.Add({"limit", std::to_string(limit)});
	if(offset != OFFSET_DEFAULT) params.Add({"offset", std::to_string(offset)});

	auto res = cpr::Get(cpr::Url(BASE_URL + "forum/topics"), params, authHeader());
	return handleReturn(res);
}

//# Manga
std::string Client::M__getMangaList(
    std::string                query,
    std::optional<std::string> fields,
    std::uint8_t               limit,
    std::uint8_t               offset) const {
	auto params = cpr::Parameters({{"q", query}});
	if(limit != LIMIT_DEFAULT) params.Add({"limit", std::to_string(limit)});
	if(offset != OFFSET_DEFAULT) params.Add({"offset", std::to_string(offset)});
	if(fields.has_value()) params.Add({"fields", fields.value()});
	auto res = cpr::Get(cpr::Url(BASE_URL + "manga"), params, authHeader());
	return handleReturn(res);
}

std::string Client::M__getMangaDetails(
    std::uint32_t              mangaId,
    std::optional<std::string> fields) const {
	auto params = cpr::Parameters({});
	if(fields.has_value()) params.Add({"fields", fields.value()});
	auto res = cpr::Get(
	    cpr::Url(BASE_URL + "anime/" + std::to_string(mangaId)),
	    params,
	    authHeader());
	return handleReturn(res);
}

std::string Client::M__getMangaRanking(
    MangaRankingTypeParam      rankingType, //MangaRankingTypeParam
    std::uint8_t               limit,
    std::uint8_t               offset,
    std::optional<std::string> fields) const {

	auto params = cpr::Parameters({});

	switch(rankingType) {
		case m_all: params.Add({"ranking_type", "all"}); break;
		case m_bypopularity: params.Add({"ranking_type", "bypopularity"}); break;
		case m_favorite: params.Add({"ranking_type", "favorite"}); break;
		case manga: params.Add({"ranking_type", "manga"}); break;
		case oneshots: params.Add({"ranking_type", "oneshots"}); break;
		case doujin: params.Add({"ranking_type", "doujin"}); break;
		case lightnovels: params.Add({"ranking_type", "lightnovels"}); break;
		case novels: params.Add({"ranking_type", "novels"}); break;
		case manhwa: params.Add({"ranking_type", "manhwa"}); break;
		case manhua: params.Add({"ranking_type", "manhua"}); break;
	}

	if(fields.has_value()) params.Add({"fields", fields.value()});
	if(limit != LIMIT_DEFAULT) params.Add({"limit", std::to_string(limit)});
	if(offset != OFFSET_DEFAULT) params.Add({"offset", std::to_string(offset)});
	auto res = cpr::Get(cpr::Url(BASE_URL + "anime/ranking"), params, authHeader());
	return handleReturn(res);
}

//# User Manga

std::string Client::M__updateUserMangaListStatus(
    std::uint32_t                   mangaId,
    std::optional<MangaStatusParam> status,
    std::optional<bool>             isReReading,
    std::optional<std::uint8_t>     score,
    std::optional<std::uint8_t>     numVolsRead,
    std::optional<std::uint8_t>     numChaptersRead,
    std::optional<std::uint8_t>     priority,
    std::optional<std::uint8_t>     numTimesRead,
    std::optional<std::uint8_t>     reReadValue,
    std::optional<std::string>      tags,
    std::optional<std::string>      comments) const {
	auto params = cpr::Parameters({});

	if(status.has_value()) switch(status.value()) {
			case reading: params.Add({"status", "reading"}); break;
			case ms_completed: params.Add({"status", "completed"}); break;
			case ms_on_hold: params.Add({"status", "on_hold"}); break;
			case ms_dropped: params.Add({"status", "dropped"}); break;
			case plan_to_read: params.Add({"status", "plan_to_read"}); break;
		}

	if(isReReading.has_value())
		params.Add({"is_re_reading", std::to_string(isReReading.value())});
	if(numVolsRead.has_value())
		params.Add({"num_vols_read", std::to_string(numVolsRead.value())});
	if(numChaptersRead.has_value())
		params.Add(
		    {"num_chapters_read", std::to_string(numChaptersRead.value())});
	if(priority.has_value())
		params.Add({"priority", std::to_string(priority.value())});
	if(numTimesRead.has_value())
		params.Add({"num_times_read", std::to_string(numTimesRead.value())});
	if(reReadValue.has_value())
		params.Add({"re_read_value", std::to_string(reReadValue.value())});
	if(score.has_value()) params.Add({"score", std::to_string(score.value())});
	if(priority.has_value())
		params.Add({"priority", std::to_string(priority.value())});
	if(tags.has_value()) params.Add({"tags", tags.value()});
	if(comments.has_value()) params.Add({"comments", comments.value()});

	auto res = cpr::Patch(
	    cpr::Url(BASE_URL + "manga/" + std::to_string(mangaId) + "/my_list_status"),
	    params,
	    authHeader());
	return handleReturn(res);
}

std::string Client::M__getUserMangaList(
    std::string                     userName,
    std::optional<MangaStatusParam> status,
    std::optional<MangaSortParam>   sort,
    std::uint8_t                    limit,
    std::uint8_t                    offset) const {

	auto params = cpr::Parameters({});

	if(sort.has_value()) switch(sort.value()) {
			case ms_list_score: params.Add({"sort", "list_score"}); break;
			case ms_list_updated_at:
				params.Add({"sort", "list_updated_at"});
				break;
			case manga_title: params.Add({"sort", "manga_title"}); break;
			case manga_start_date:
				params.Add({"sort", "manga_start_date"});
				break;
			case manga_id: params.Add({"sort", "manga_id"}); break;
		}

	if(status.has_value()) switch(status.value()) {
			case reading: params.Add({"status", "reading"}); break;
			case ms_completed: params.Add({"status", "completed"}); break;
			case ms_on_hold: params.Add({"status", "on_hold"}); break;
			case ms_dropped: params.Add({"status", "dropped"}); break;
			case plan_to_read: params.Add({"status", "plan_to_read"}); break;
		}

	if(limit != LIMIT_DEFAULT) params.Add({"limit", std::to_string(limit)});
	if(offset != OFFSET_DEFAULT) params.Add({"offset", std::to_string(offset)});

	auto res = cpr::Get(
	    cpr::Url(BASE_URL + "users/" + userName + "/animelist"),
	    params,
	    authHeader());
	return handleReturn(res);
}

std::string Client::M__getUserData(
    std::string                userName,
    std::optional<std::string> fields) const {
	auto params = cpr::Parameters {};
	if(fields.has_value()) params.Add({"fields", fields.value()});
	auto res =
	    cpr::Get(cpr::Url(BASE_URL + "users/" + userName), params, authHeader());
	return handleReturn(res);
}

bool Client::deleteUserAnime(std::uint32_t animeId) const {
	auto res = cpr::Get(
	    cpr::Url(BASE_URL + "anime/" + std::to_string(animeId) + "/my_list_status"));
	return res.status_code == 200;
}
bool Client::deleteUserMangaListItem(std::uint32_t mangaId) const {
	auto res = cpr::Get(
	    cpr::Url(BASE_URL + "manga/" + std::to_string(mangaId) + "/my_list_status"));
	return res.status_code == 200;
}
