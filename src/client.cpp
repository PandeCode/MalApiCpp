#include "malapi/client.hpp"

#include "httplib.hpp"

#include <iostream>

using namespace nlohmann;

static constexpr std::uint8_t LIMIT_DEFAULT  = 100;
static constexpr std::uint8_t OFFSET_DEFAULT = 0;
static const std::string      FAILED_REQUEST_TEXT =
    "{\"error\" : \"failed_request\", \"message\": \"failed request\"}";

static void printResult(const httplib::Result& res) {
	std::cout << "status_code : " << res->status << "\nbody        : " << res->body
		  << "\nreason      : " << res->reason << "\n";
}

static const std::string& handleReturn(const httplib::Result& res) {
	if(res) {
		if(res->status == 200) {
			//std::cout << res->body << std::endl;
			return res->body;
		}
		std::cout << "\033[91mError: " << res->reason << std::endl;
		printResult(res);
		std::cout << "\033[0m";
		return res->body;
	} else {
		auto err = res.error();
		std::cout << "\033[91mError: " << err << std::endl;
		printResult(res);
		std::cout << "\033[0m";
		return FAILED_REQUEST_TEXT;
	}
}

Client::Client(Auth& auth) :
    m_auth(auth), httpClient(httplib::Client("https://api.myanimelist.net")) {
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
    m_auth(clientId, clientSecrect, redirectUri, state),
    httpClient(httplib::Client("https://api.myanimelist.net")) {
	m_auth.authenticate();

	httpClient.set_default_headers({
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

	return handleReturn(
	    httpClient.Get(httplib::append_query_params("/v2/anime", params).c_str()));
};

std::string Client::M__getAnimeDetails(
    std::uint32_t              animeId,
    std::optional<std::string> fields) const {
	httplib::Params params;
	if(fields.has_value()) params.emplace("fields", fields.value());

	return handleReturn(
	    httpClient.Get(httplib::append_query_params(
			       ("/v2/anime/" + std::to_string(animeId)).c_str(),
			       params)
			       .c_str()));
}

std::string Client::M__getAnimeRanking(
    std::optional<std::string> fields,
    AnimeRankingType           rankingType,
    std::uint8_t               limit,
    std::uint8_t               offset) const {
	httplib::Params params;

	switch(rankingType) {
		// clang-format off
		case  AnimeRankingType::all          :  params.emplace("ranking_type", "all"          ); break;
		case  AnimeRankingType::airing       :  params.emplace("ranking_type", "airing"       ); break;
		case  AnimeRankingType::upcoming     :  params.emplace("ranking_type", "upcoming"     ); break;
		case  AnimeRankingType::tv           :  params.emplace("ranking_type", "tv"           ); break;
		case  AnimeRankingType::ova          :  params.emplace("ranking_type", "ova"          ); break;
		case  AnimeRankingType::movie        :  params.emplace("ranking_type", "movie"        ); break;
		case  AnimeRankingType::special      :  params.emplace("ranking_type", "special"      ); break;
		case  AnimeRankingType::bypopularity :  params.emplace("ranking_type", "bypopularity" ); break;
		case  AnimeRankingType::favorite     :  params.emplace("ranking_type", "favorite"     ); break;
			// clang-format on
	}

	if(fields.has_value()) params.emplace("fields", fields.value());
	if(limit != LIMIT_DEFAULT) params.emplace("limit", std::to_string(limit));
	if(offset != OFFSET_DEFAULT) params.emplace("offset", std::to_string(offset));
	return handleReturn(httpClient.Get(
	    httplib::append_query_params("/v2/anime/ranking", params).c_str()));
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
		case SeasonParam::winter: seasonString = "/winter"; break;
		case SeasonParam::spring: seasonString = "/spring"; break;
		case SeasonParam::summer: seasonString = "/summer"; break;
		case SeasonParam::fall: seasonString = "/fall"; break;
	}

	httplib::Params params;

	if(sort != SeasonSortParam::anime_score) {
		switch(sort) {
			case SeasonSortParam::anime_num_list_users:
				params.emplace("sort", "anime_num_list_users");
				break;
			case SeasonSortParam::anime_score:
				params.emplace("sort", "anime_score");
				break; // Dead Code
		}
	}

	if(fields.has_value()) params.emplace("fields", fields.value());
	if(limit != LIMIT_DEFAULT) params.emplace("limit", std::to_string(limit));
	if(offset != OFFSET_DEFAULT) params.emplace("offset", std::to_string(offset));

	return handleReturn(httpClient.Get(
	    httplib::append_query_params(
		("/v2/anime/season/" + std::to_string(year) + seasonString).c_str(),
		params)
		.c_str()));
}

// User Anime

std::string Client::M__getUserSuggestedAnime(
    std::uint8_t               limit,
    std::uint8_t               offset,
    std::optional<std::string> fields) const {

	httplib::Params params;

	if(fields.has_value()) params.emplace("fields", fields.value());
	if(limit != LIMIT_DEFAULT) params.emplace("limit", std::to_string(limit));
	if(offset != OFFSET_DEFAULT) params.emplace("offset", std::to_string(offset));

	return handleReturn(httpClient.Get(
	    httplib::append_query_params("/v2/anime/suggestions", params).c_str()));
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
	httplib::Params params;

	if(status.has_value()) switch(status.value()) {
			// clang-format off
				case AnimeStatusParam::watching      :  params.emplace("status", "watching"      ); break;
				case AnimeStatusParam::completed     :  params.emplace("status", "completed"     ); break;
				case AnimeStatusParam::on_hold       :  params.emplace("status", "on_hold"       ); break;
				case AnimeStatusParam::dropped       :  params.emplace("status", "dropped"       ); break;
				case AnimeStatusParam::plan_to_watch :  params.emplace("status", "plan_to_watch" ); break;
				// clang-format on
		}

	if(score.has_value()) params.emplace("score", std::to_string(score.value()));
	if(priority.has_value())
		params.emplace("priority", std::to_string(priority.value()));
	if(numWatchedEpisodes.has_value())
		params.emplace(
		    "num_watched_episodes",
		    std::to_string(numWatchedEpisodes.value()));
	if(isRewatching.has_value())
		params.emplace("is_rewatching", std::to_string(isRewatching.value()));
	if(numTimesRewatched.has_value())
		params.emplace(
		    "num_times_rewatched",
		    std::to_string(numTimesRewatched.value()));
	if(rewatchValue.has_value())
		params.emplace("rewatch_value", std::to_string(rewatchValue.value()));
	if(tags.has_value()) params.emplace("tags", tags.value());
	if(comments.has_value()) params.emplace("comments", comments.value());

	return handleReturn(httpClient.Patch(
	    httplib::append_query_params(
		("/v2/anime/" + std::to_string(animeId) + "/my_list_status").c_str(),
		params)
		.c_str()));
}

std::string Client::M__getUserAnimeList(
    std::string                       userName,
    std::optional<AnimeStatusParam>   status,
    std::optional<UserAnimeSortParam> sort,
    std::uint8_t                      limit,
    std::uint8_t                      offset) const {

	httplib::Params params;

	if(sort.has_value()) switch(sort.value()) {
				// clang-format off
			case UserAnimeSortParam::list_score       :  params.emplace("sort", "list_score"); break;
			case UserAnimeSortParam::list_updated_at  :  params.emplace("sort", "list_updated_at"); break;
			case UserAnimeSortParam::anime_title      :  params.emplace("sort", "anime_title"); break;
			case UserAnimeSortParam::anime_start_date :  params.emplace("sort", "anime_start_date"); break;
			case UserAnimeSortParam::anime_id         :  params.emplace("sort", "anime_id"); break;
				// clang-format on
		}

	if(status.has_value()) switch(status.value()) {
				// clang-format off
			case AnimeStatusParam::watching      :  params.emplace("status", "watching"); break;
			case AnimeStatusParam::completed     :  params.emplace("status", "completed"); break;
			case AnimeStatusParam::on_hold       :  params.emplace("status", "on_hold"); break;
			case AnimeStatusParam::dropped       :  params.emplace("status", "dropped"); break;
			case AnimeStatusParam::plan_to_watch :  params.emplace("status", "plan_to_watch"); break;
				// clang-format on
		}

	if(limit != LIMIT_DEFAULT) params.emplace("limit", std::to_string(limit));
	if(offset != OFFSET_DEFAULT) params.emplace("offset", std::to_string(offset));

	return handleReturn(
	    httpClient.Get(httplib::append_query_params(
			       ("/v2/users/" + userName + "/animelist").c_str(),
			       params)
			       .c_str()));
}

//# Forums

std::string Client::M__getForumBoards() const {

	return handleReturn(httpClient.Get("/v2/forum/boards"));
}

std::string Client::M__getForumTopicDetail(
    std::uint32_t topicId,
    std::uint8_t  limit,
    std::uint8_t  offset) const {

	httplib::Params params;
	if(limit != LIMIT_DEFAULT) params.emplace("limit", std::to_string(limit));
	if(offset != OFFSET_DEFAULT) params.emplace("offset", std::to_string(offset));

	return handleReturn(
	    httpClient.Get(httplib::append_query_params(
			       ("/v2/forum/topic/" + std::to_string(topicId)).c_str(),
			       params)
			       .c_str()));
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

	httplib::Params params;

	if(sort.has_value()) switch(sort.value()) {
			case ForumSortParam::recent:
				params.emplace("sort", "recent");
				break;
		}

	if(boardId.has_value())
		params.emplace("board_id", std::to_string(boardId.value()));
	if(subboardId.has_value())
		params.emplace("subboard_id", std::to_string(subboardId.value()));
	if(query.has_value()) params.emplace("query", query.value());
	if(topicUserName.has_value())
		params.emplace("topic_user_name", topicUserName.value());
	if(userName.has_value()) params.emplace("user_name", userName.value());

	if(limit != LIMIT_DEFAULT) params.emplace("limit", std::to_string(limit));
	if(offset != OFFSET_DEFAULT) params.emplace("offset", std::to_string(offset));

	return handleReturn(httpClient.Get(
	    httplib::append_query_params("/v2/forum/topics", params).c_str()));
}

//# Manga
std::string Client::M__getMangaList(
    std::string                query,
    std::optional<std::string> fields,
    std::uint8_t               limit,
    std::uint8_t               offset) const {
	auto params = httplib::Params({{"q", query}});
	if(limit != LIMIT_DEFAULT) params.emplace("limit", std::to_string(limit));
	if(offset != OFFSET_DEFAULT) params.emplace("offset", std::to_string(offset));
	if(fields.has_value()) params.emplace("fields", fields.value());

	return handleReturn(
	    httpClient.Get(httplib::append_query_params("/v2/manga", params).c_str()));
}

std::string Client::M__getMangaDetails(
    std::uint32_t              mangaId,
    std::optional<std::string> fields) const {
	httplib::Params params;
	if(fields.has_value()) params.emplace("fields", fields.value());

	return handleReturn(
	    httpClient.Get(httplib::append_query_params(
			       ("/v2/anime/" + std::to_string(mangaId)).c_str(),
			       params)
			       .c_str()));
}

std::string Client::M__getMangaRanking(
    MangaRankingTypeParam      rankingType, //MangaRankingTypeParam
    std::uint8_t               limit,
    std::uint8_t               offset,
    std::optional<std::string> fields) const {

	httplib::Params params;

	switch(rankingType) {
			// clang-format off
		case MangaRankingTypeParam::all          :  params.emplace("ranking_type", "all"          ); break;
		case MangaRankingTypeParam::bypopularity :  params.emplace("ranking_type", "bypopularity" ); break;
		//case MangaRankingTypeParam::favorite     :  params.emplace("ranking_type", "favorite"     ); break;
		//case MangaRankingTypeParam::manga        :  params.emplace("ranking_type", "manga"        ); break;
		//case MangaRankingTypeParam::oneshots     :  params.emplace("ranking_type", "oneshots"     ); break;
		//case MangaRankingTypeParam::doujin       :  params.emplace("ranking_type", "doujin"       ); break;
		//case MangaRankingTypeParam::lightnovels  :  params.emplace("ranking_type", "lightnovels"  ); break;
		//case MangaRankingTypeParam::novels       :  params.emplace("ranking_type", "novels"       ); break;
		//case MangaRankingTypeParam::manhwa       :  params.emplace("ranking_type", "manhwa"       ); break;
		//case MangaRankingTypeParam::manhua       :  params.emplace("ranking_type", "manhua"       ); break;
			// clang-format on
	}

	if(fields.has_value()) params.emplace("fields", fields.value());
	if(limit != LIMIT_DEFAULT) params.emplace("limit", std::to_string(limit));
	if(offset != OFFSET_DEFAULT) params.emplace("offset", std::to_string(offset));

	std::string str = httplib::append_query_params("/v2/anime/ranking", params);
	//str = "/v2/anime/ranking?limit=4&ranking_type=manga";
	//str = "/v2/anime/ranking?ranking_type=manga&limit=4";

	return handleReturn((httpClient.Get(str.c_str())));
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
	httplib::Params params;

	if(status.has_value()) switch(status.value()) {
				// clang-format off
			case MangaStatusParam::reading      :  params.emplace("status", "reading"      ); break;
			case MangaStatusParam::completed :  params.emplace("status", "completed"    ); break;
			case MangaStatusParam::on_hold   :  params.emplace("status", "on_hold"      ); break;
			case MangaStatusParam::dropped   :  params.emplace("status", "dropped"      ); break;
			case MangaStatusParam::plan_to_read :  params.emplace("status", "plan_to_read" ); break;
				// clang-format on
		}

	if(isReReading.has_value())
		params.emplace("is_re_reading", std::to_string(isReReading.value()));
	if(numVolsRead.has_value())
		params.emplace("num_vols_read", std::to_string(numVolsRead.value()));
	if(numChaptersRead.has_value())
		params.emplace(
		    "num_chapters_read",
		    std::to_string(numChaptersRead.value()));
	if(priority.has_value())
		params.emplace("priority", std::to_string(priority.value()));
	if(numTimesRead.has_value())
		params.emplace("num_times_read", std::to_string(numTimesRead.value()));
	if(reReadValue.has_value())
		params.emplace("re_read_value", std::to_string(reReadValue.value()));
	if(score.has_value()) params.emplace("score", std::to_string(score.value()));
	if(priority.has_value())
		params.emplace("priority", std::to_string(priority.value()));
	if(tags.has_value()) params.emplace("tags", tags.value());
	if(comments.has_value()) params.emplace("comments", comments.value());

	return handleReturn(httpClient.Patch(
	    httplib::append_query_params(
		("/v2/manga/" + std::to_string(mangaId) + "/my_list_status").c_str(),
		params)
		.c_str()));
}

std::string Client::M__getUserMangaList(
    std::string                     userName,
    std::optional<MangaStatusParam> status,
    std::optional<MangaSortParam>   sort,
    std::uint8_t                    limit,
    std::uint8_t                    offset) const {

	httplib::Params params;

	if(sort.has_value()) switch(sort.value()) {
			// clang-format off
			case MangaSortParam::list_score      :  params.emplace("sort", "list_score"       ); break;
			case MangaSortParam::list_updated_at :  params.emplace("sort", "list_updated_at"  ); break;
			case MangaSortParam::manga_title        :  params.emplace("sort", "manga_title"      ); break;
			case MangaSortParam::manga_start_date   :  params.emplace("sort", "manga_start_date" ); break;
			case MangaSortParam::manga_id           :  params.emplace("sort", "manga_id"         ); break;
				// clang-format on
		}

	if(status.has_value()) switch(status.value()) {
			// clang-format off
			case MangaStatusParam::reading      :  params.emplace("status", "reading"      ); break;
			case MangaStatusParam::completed :  params.emplace("status", "completed"    ); break;
			case MangaStatusParam::on_hold   :  params.emplace("status", "on_hold"      ); break;
			case MangaStatusParam::dropped   :  params.emplace("status", "dropped"      ); break;
			case MangaStatusParam::plan_to_read :  params.emplace("status", "plan_to_read" ); break;
				// clang-format on
		}

	if(limit != LIMIT_DEFAULT) params.emplace("limit", std::to_string(limit));
	if(offset != OFFSET_DEFAULT) params.emplace("offset", std::to_string(offset));

	return handleReturn(
	    httpClient.Get(httplib::append_query_params(
			       ("/v2/users/" + userName + "/animelist").c_str(),
			       params)
			       .c_str()));
}

std::string Client::M__getUserData(
    std::string                userName,
    std::optional<std::string> fields) const {
	auto params = httplib::Params {};
	if(fields.has_value()) params.emplace("fields", fields.value());

	return handleReturn(httpClient.Get(
	    httplib::append_query_params(("/v2/users/" + userName).c_str(), params)
		.c_str()));
}

template <class ReturnType>
ReturnType Client::getAnimeList(
    std::string                query,
    std::optional<std::string> fields,
    std::uint8_t               limit,
    std::uint8_t               offset) const {
	return M__getAnimeList(query, fields, limit, offset);
}

template <class ReturnType>
ReturnType Client::getAnimeDetails(
    std::uint32_t              animeId,
    std::optional<std::string> fields) const {
	return M__getAnimeDetails(animeId, fields);
}

template <class ReturnType>
ReturnType Client::getAnimeRanking(
    std::optional<std::string> fields,
    AnimeRankingType           rankingType,
    std::uint8_t               limit,
    std::uint8_t               offset) const {
	return M__getAnimeRanking(fields, rankingType, limit, offset);
}

template <class ReturnType>
ReturnType Client::getSeasonalAnime(
    std::uint32_t              year,
    SeasonParam                season,
    SeasonSortParam            sort,
    std::optional<std::string> fields,
    std::uint8_t               limit,
    std::uint8_t               offset) const {
	return M__getSeasonalAnime(year, season, sort, fields, limit, offset);
}

// User Anime

template <class ReturnType>
ReturnType Client::getUserSuggestedAnime(
    std::uint8_t               limit,
    std::uint8_t               offset,
    std::optional<std::string> fields) const {
	return M__getUserSuggestedAnime(limit, offset, fields);
}

template <class ReturnType>
ReturnType Client::updateUserAnimeListStatus(
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
	return M__updateUserAnimeListStatus(
	    animeId,
	    status,
	    score,
	    priority,
	    numWatchedEpisodes,
	    isRewatching,
	    numTimesRewatched,
	    rewatchValue,
	    tags,
	    comments);
}

template <class ReturnType>
ReturnType Client::getUserAnimeList(
    std::string                       userName,
    std::optional<AnimeStatusParam>   status,
    std::optional<UserAnimeSortParam> sort,
    std::uint8_t                      limit,
    std::uint8_t                      offset) const {
	return M__getUserAnimeList(userName, status, sort, limit, offset);
}

//# Forums

template <class ReturnType>
ReturnType Client::getForumBoards() const {
	return M__getForumBoards();
}
template <class ReturnType>
ReturnType Client::getForumTopicDetail(
    std::uint32_t topicId,
    std::uint8_t  limit,
    std::uint8_t  offset) const {
	return M__getForumTopicDetail(topicId, limit, offset);
}

template <class ReturnType>
ReturnType Client::getForumTopics(
    std::optional<std::uint32_t>  boardId,
    std::optional<std::uint32_t>  subboardId,
    std::optional<ForumSortParam> sort,
    std::optional<std::string>    query,
    std::optional<std::string>    topicUserName,
    std::optional<std::string>    userName,
    std::uint8_t                  limit,
    std::uint8_t                  offset) const {
	return M__getForumTopics(
	    boardId,
	    subboardId,
	    sort,
	    query,
	    topicUserName,
	    userName,
	    limit,
	    offset);
}

//# Manga
template <class ReturnType>
ReturnType Client::getMangaList(
    std::string                query,
    std::optional<std::string> fields,
    std::uint8_t               limit,
    std::uint8_t               offset) const {
	return M__getMangaList(query, fields, limit, offset);
}

template <class ReturnType>
ReturnType Client::getMangaDetails(
    std::uint32_t              mangaId,
    std::optional<std::string> fields) const {
	return M__getMangaDetails(mangaId, fields);
}

template <class ReturnType>
ReturnType Client::getMangaRanking(
    MangaRankingTypeParam      rankingType,
    std::uint8_t               limit,
    std::uint8_t               offset,
    std::optional<std::string> fields) const {
	return M__getMangaRanking(rankingType, limit, offset, fields);
}

//# User Manga

template <class ReturnType>
ReturnType Client::updateUserMangaListStatus(
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
	return M__updateUserMangaListStatus(
	    mangaId,
	    status,
	    isReReading,
	    score,
	    numVolsRead,
	    numChaptersRead,
	    priority,
	    numTimesRead,
	    reReadValue,
	    tags,
	    comments);
}

template <class ReturnType>
ReturnType Client::getUserMangaList(
    std::string                     userName,
    std::optional<MangaStatusParam> status,
    std::optional<MangaSortParam>   sort,
    std::uint8_t                    limit,
    std::uint8_t                    offset) const {
	return M__getUserMangaList(userName, status, sort, limit, offset);
}

//# User
template <class ReturnType>
ReturnType
    Client::getUserData(std::string userName, std::optional<std::string> fields) const {
	return M__getUserData(userName, fields);
}

bool Client::deleteUserAnime(std::uint32_t animeId) const {
	if(auto res = httpClient.Delete(
	       (("/v2/anime/" + std::to_string(animeId) + "/my_list_status").c_str()))) {
		return res->status == 200;
	} else
		return false;
}

bool Client::deleteUserMangaListItem(std::uint32_t mangaId) const {
	if(auto res = httpClient.Delete(
	       ("/v2/manga/" + std::to_string(mangaId) + "/my_list_status").c_str())) {
		return res->status == 200;
	} else
		return false;
}

void Client::___defs() {
	// Anime
	getAnimeList<std::string>("");
	getAnimeDetails<std::string>(0);
	getAnimeRanking<std::string>();
	getSeasonalAnime<std::string>(0, SeasonParam ::fall);

	// User Anime
	getUserSuggestedAnime<std::string>();
	updateUserAnimeListStatus<std::string>(0);
	getUserAnimeList<std::string>("");

	// Forums
	getForumBoards<std::string>();
	getForumTopicDetail<std::string>(0);
	getForumTopics<std::string>();

	// Manga
	getMangaList<std::string>("");
	getMangaDetails<std::string>(0);
	getMangaRanking<std::string>(MangaRankingTypeParam::all);

	// User Manga
	updateUserMangaListStatus<std::string>(0);
	getUserMangaList<std::string>("");

	// User
	getUserData<std::string>("");
}
