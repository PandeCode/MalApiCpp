#include "malapi/client.hpp"

#include "cpp-httplib/httplib.hpp"
#include "malapi/auth.hpp"
#include "malapi/client.hpp"
#include "malapi/jsonDefinitions.hpp"
#include "nlohmann/json.hpp"

#include <iostream>
#include <optional>
#include <string>
#include <type_traits>
#include <variant>

using namespace nlohmann;

static constexpr std::uint8_t LIMIT_DEFAULT  = 100;
static constexpr std::uint8_t OFFSET_DEFAULT = 0;
static const std::string      FAILED_REQUEST_TEXT =
    R"({"error" : "failed_request", "message": "failedrequest"})";

static void printResult(const httplib::Result& res) {
	if(res) {
		if(res->status == 200) {
			std::cout << "Status         :" << res->status << std::endl;
			std::cout << "Content_length :" << res->content_length_
				  << std::endl;
			std::cout << "Body           :" << res->body << std::endl;
		}
		std::cout << "Status         :" << res->status << std::endl;
		std::cout << "Status: " << res->status << std::endl;
	} else {
		std::cout << "\033[91mError: " << res.error() << "\033[0m\n"
			  << std::flush;
	}
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

Client::Client(Auth& auth, const std::string& cacheFile) :
    m_auth(auth), httpClient(httplib::Client("https://api.myanimelist.net")) {
	auth.m_cacheFilePath = cacheFile;
	if(!auth.isAuthenticated) m_auth.authenticate();

	httpClient.set_default_headers({
	    {"Authorization", "Bearer " + m_auth.authData.access_token},
	    {"Accept",        "application/json"                      },
	});
}

Client::Client(
    const std::string& clientId,
    const std::string& clientSecrect,
    const std::string& redirectUri,
    const std::string& cacheFile,
    const std::string& state) :
    m_auth(clientId, clientSecrect, redirectUri, state, cacheFile),
    httpClient(httplib::Client("https://api.myanimelist.net")) {
	m_auth.authenticate();

	httpClient.set_default_headers({
	    {"Authorization", "Bearer " + m_auth.authData.access_token},
	    {"Accept",        "application/json"                      },
	});
}

std::string Client::M__getAnimeList(
    const std::string&                query,
    const std::optional<std::string>& fields,
    const std::uint8_t&               limit,
    const std::uint8_t&               offset) const {

	httplib::Params params {
	    {"q", query}
        };
	if(fields.has_value()) params.emplace("fields", fields.value());
	if(limit != LIMIT_DEFAULT) params.emplace("limit", std::to_string(limit));
	if(offset != OFFSET_DEFAULT) params.emplace("offset", std::to_string(offset));

	return handleReturn(
	    httpClient.Get(httplib::append_query_params("/v2/anime", params).c_str()));
};

std::string Client::M__getAnimeDetails(
    const std::uint32_t&              animeId,
    const std::optional<std::string>& fields) const {
	httplib::Params params;
	if(fields.has_value()) params.emplace("fields", fields.value());

	return handleReturn(
	    httpClient.Get(httplib::append_query_params(
			       ("/v2/anime/" + std::to_string(animeId)).c_str(),
			       params)
			       .c_str()));
}

std::string Client::M__getAnimeRanking(
    const std::optional<std::string>& fields,
    const AnimeRankingType&           rankingType,
    const std::uint8_t&               limit,
    const std::uint8_t&               offset) const {
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
    const std::uint32_t&              year,
    const SeasonParam&                season,
    const SeasonSortParam&            sort,
    const std::optional<std::string>& fields,
    const std::uint8_t&               limit,
    const std::uint8_t&               offset) const {
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
    const std::uint8_t&               limit,
    const std::uint8_t&               offset,
    const std::optional<std::string>& fields) const {

	httplib::Params params;

	if(fields.has_value()) params.emplace("fields", fields.value());
	if(limit != LIMIT_DEFAULT) params.emplace("limit", std::to_string(limit));
	if(offset != OFFSET_DEFAULT) params.emplace("offset", std::to_string(offset));

	return handleReturn(httpClient.Get(
	    httplib::append_query_params("/v2/anime/suggestions", params).c_str()));
}

std::string Client::M__updateUserAnimeListStatus(
    const std::uint32_t&                   animeId,
    const std::optional<AnimeStatusParam>& status,
    const std::optional<int>&              score,
    const std::optional<int>&              priority,
    const std::optional<int>&              numWatchedEpisodes,
    const std::optional<bool>&             isRewatching,
    const std::optional<int>&              numTimesRewatched,
    const std::optional<int>&              rewatchValue,
    const std::optional<std::string>&      tags,
    const std::optional<std::string>&      comments) const {
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
    const std::string&                       userName,
    const std::optional<AnimeStatusParam>&   status,
    const std::optional<UserAnimeSortParam>& sort,
    const std::uint8_t&                      limit,
    const std::uint8_t&                      offset) const {

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
    const std::uint32_t& topicId,
    const std::uint8_t&  limit,
    const std::uint8_t&  offset) const {

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
    const std::optional<std::uint32_t>&  boardId,
    const std::optional<std::uint32_t>&  subboardId,
    const std::optional<ForumSortParam>& sort,
    const std::optional<std::string>&    query,
    const std::optional<std::string>&    topicUserName,
    const std::optional<std::string>&    userName,
    const std::uint8_t&                  limit,
    const std::uint8_t&                  offset) const {

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
    const std::string&                query,
    const std::optional<std::string>& fields,
    const std::uint8_t&               limit,
    const std::uint8_t&               offset) const {
	auto params = httplib::Params({
	    {"q", query}
        });
	if(limit != LIMIT_DEFAULT) params.emplace("limit", std::to_string(limit));
	if(offset != OFFSET_DEFAULT) params.emplace("offset", std::to_string(offset));
	if(fields.has_value()) params.emplace("fields", fields.value());

	return handleReturn(
	    httpClient.Get(httplib::append_query_params("/v2/manga", params).c_str()));
}

std::string Client::M__getMangaDetails(
    const std::uint32_t&              mangaId,
    const std::optional<std::string>& fields) const {
	httplib::Params params;
	if(fields.has_value()) params.emplace("fields", fields.value());

	return handleReturn(
	    httpClient.Get(httplib::append_query_params(
			       ("/v2/anime/" + std::to_string(mangaId)).c_str(),
			       params)
			       .c_str()));
}

std::string Client::M__getMangaRanking(
    const MangaRankingTypeParam&      rankingType, //MangaRankingTypeParam
    const std::uint8_t&               limit,
    const std::uint8_t&               offset,
    const std::optional<std::string>& fields) const {

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
    const std::uint32_t&                   mangaId,
    const std::optional<MangaStatusParam>& status,
    const std::optional<bool>&             isReReading,
    const std::optional<std::uint8_t>&     score,
    const std::optional<std::uint8_t>&     numVolsRead,
    const std::optional<std::uint8_t>&     numChaptersRead,
    const std::optional<std::uint8_t>&     priority,
    const std::optional<std::uint8_t>&     numTimesRead,
    const std::optional<std::uint8_t>&     reReadValue,
    const std::optional<std::string>&      tags,
    const std::optional<std::string>&      comments) const {
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
    const std::string&                     userName,
    const std::optional<MangaStatusParam>& status,
    const std::optional<MangaSortParam>&   sort,
    const std::uint8_t&                    limit,
    const std::uint8_t&                    offset) const {

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
    const std::string&                userName,
    const std::optional<std::string>& fields) const {
	auto params = httplib::Params {};
	if(fields.has_value()) params.emplace("fields", fields.value());

	return handleReturn(httpClient.Get(
	    httplib::append_query_params(("/v2/users/" + userName).c_str(), params)
		.c_str()));
}

#define DEF_OPT(OBJECT, FUNCTION)                                     \
	if(std::is_same<OBJECT, ReturnType>())                        \
		return nlohmann::json::parse(FUNCTION).get<OBJECT>(); \
	else if(std::is_same<std::string, ReturnType>())              \
		return FUNCTION;                                      \
	else                                                          \
		throw std::string("Wrong Template parameter " #OBJECT);

template <class ReturnType>
std::variant<std::string, AnimeList> Client::getAnimeList(
    const std::string&                query,
    const std::optional<std::string>& fields,
    const std::uint8_t&               limit,
    const std::uint8_t&               offset) const {
	DEF_OPT(AnimeList, M__getAnimeList(query, fields, limit, offset));
}

template <class ReturnType>
std::variant<std::string, AnimeDetails> Client::getAnimeDetails(
    const std::uint32_t&              animeId,
    const std::optional<std::string>& fields) const {
	DEF_OPT(AnimeDetails, M__getAnimeDetails(animeId, fields));
}

template <class ReturnType>
std::variant<std::string, AnimeRanking> Client::getAnimeRanking(
    const std::optional<std::string>& fields,
    const AnimeRankingType&           rankingType,
    const std::uint8_t&               limit,
    const std::uint8_t&               offset) const {
	DEF_OPT(AnimeRanking, M__getAnimeRanking(fields, rankingType, limit, offset));
}

template <class ReturnType>
std::variant<std::string, SeasonalAnime> Client::getSeasonalAnime(
    const std::uint32_t&              year,
    const SeasonParam&                season,
    const SeasonSortParam&            sort,
    const std::optional<std::string>& fields,
    const std::uint8_t&               limit,
    const std::uint8_t&               offset) const {
	DEF_OPT(
	    SeasonalAnime,
	    M__getSeasonalAnime(year, season, sort, fields, limit, offset));
}

// User Anime

template <class ReturnType>
std::variant<std::string, UserSuggestedAnime> Client::getUserSuggestedAnime(
    const std::uint8_t&               limit,
    const std::uint8_t&               offset,
    const std::optional<std::string>& fields) const {
	DEF_OPT(UserSuggestedAnime, M__getUserSuggestedAnime(limit, offset, fields));
}

template <class ReturnType>
std::variant<std::string, UserAnimeListStatus> Client::updateUserAnimeListStatus(
    const std::uint32_t&                   animeId,
    const std::optional<AnimeStatusParam>& status,
    const std::optional<int>&              score,
    const std::optional<int>&              priority,
    const std::optional<int>&              numWatchedEpisodes,
    const std::optional<bool>&             isRewatching,
    const std::optional<int>&              numTimesRewatched,
    const std::optional<int>&              rewatchValue,
    const std::optional<std::string>&      tags,
    const std::optional<std::string>&      comments) const {
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
std::variant<std::string, UserAnimeList> Client::getUserAnimeList(
    const std::string&                       userName,
    const std::optional<AnimeStatusParam>&   status,
    const std::optional<UserAnimeSortParam>& sort,
    const std::uint8_t&                      limit,
    const std::uint8_t&                      offset) const {
	DEF_OPT(
	    UserAnimeList,
	    M__getUserAnimeList(userName, status, sort, limit, offset));
}

//# Forums

template <class ReturnType>
std::variant<std::string, ForumBoards> Client::getForumBoards() const {
	DEF_OPT(ForumBoards, M__getForumBoards());
}

template <class ReturnType>
std::variant<std::string, ForumTopicDetail> Client::getForumTopicDetail(
    const std::uint32_t& topicId,
    const std::uint8_t&  limit,
    const std::uint8_t&  offset) const {
	DEF_OPT(ForumTopicDetail, M__getForumTopicDetail(topicId, limit, offset));
}

template <class ReturnType>
std::variant<std::string, ForumTopics> Client::getForumTopics(
    const std::optional<std::uint32_t>&  boardId,
    const std::optional<std::uint32_t>&  subboardId,
    const std::optional<ForumSortParam>& sort,
    const std::optional<std::string>&    query,
    const std::optional<std::string>&    topicUserName,
    const std::optional<std::string>&    userName,
    const std::uint8_t&                  limit,
    const std::uint8_t&                  offset) const {
	DEF_OPT(
	    ForumTopics,
	    M__getForumTopics(
		boardId,
		subboardId,
		sort,
		query,
		topicUserName,
		userName,
		limit,
		offset));
}

//# Manga
template <class ReturnType>
std::variant<std::string, MangaList> Client::getMangaList(
    const std::string&                query,
    const std::optional<std::string>& fields,
    const std::uint8_t&               limit,
    const std::uint8_t&               offset) const {
	DEF_OPT(MangaList, M__getMangaList(query, fields, limit, offset));
}

template <class ReturnType>
std::variant<std::string, MangaDetails> Client::getMangaDetails(
    const std::uint32_t&              mangaId,
    const std::optional<std::string>& fields) const {
	DEF_OPT(MangaDetails, M__getMangaDetails(mangaId, fields));
}

template <class ReturnType>
std::variant<std::string, MangaRanking> Client::getMangaRanking(
    const MangaRankingTypeParam&      rankingType,
    const std::uint8_t&               limit,
    const std::uint8_t&               offset,
    const std::optional<std::string>& fields) const {
	DEF_OPT(MangaRanking, M__getMangaRanking(rankingType, limit, offset, fields));
}

//# User Manga

template <class ReturnType>
std::variant<std::string, UserMangaListStatus> Client::updateUserMangaListStatus(
    const std::uint32_t&                   mangaId,
    const std::optional<MangaStatusParam>& status,
    const std::optional<bool>&             isReReading,
    const std::optional<std::uint8_t>&     score,
    const std::optional<std::uint8_t>&     numVolsRead,
    const std::optional<std::uint8_t>&     numChaptersRead,
    const std::optional<std::uint8_t>&     priority,
    const std::optional<std::uint8_t>&     numTimesRead,
    const std::optional<std::uint8_t>&     reReadValue,
    const std::optional<std::string>&      tags,
    const std::optional<std::string>&      comments) const {
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
std::variant<std::string, UserMangaList> Client::getUserMangaList(
    const std::string&                     userName,
    const std::optional<MangaStatusParam>& status,
    const std::optional<MangaSortParam>&   sort,
    const std::uint8_t&                    limit,
    const std::uint8_t&                    offset) const {
	DEF_OPT(
	    UserMangaList,
	    M__getUserMangaList(userName, status, sort, limit, offset));
}

//# User
template <class ReturnType>
std::variant<std::string, UserObject> Client::getUserData(
    const std::string&                userName,
    const std::optional<std::string>& fields) const {
	DEF_OPT(UserData, M__getUserData(userName, fields));
}

bool Client::deleteUserAnime(const std::uint32_t& animeId) const {
	if(auto res = httpClient.Delete(
	       (("/v2/anime/" + std::to_string(animeId) + "/my_list_status").c_str()))) {
		return res->status == 200;
	} else
		return false;
}

bool Client::deleteUserMangaListItem(const std::uint32_t& mangaId) const {
	if(auto res = httpClient.Delete(
	       ("/v2/manga/" + std::to_string(mangaId) + "/my_list_status").c_str())) {
		return res->status == 200;
	} else
		return false;
}

void Client::___defs() {
	// Anime
	getAnimeList<std::string>("");
	getAnimeList<AnimeList>("");

	getAnimeDetails<std::string>(0);
	getAnimeDetails<AnimeDetails>(0);

	getAnimeRanking<std::string>();
	getAnimeRanking<AnimeRanking>();

	getSeasonalAnime<std::string>(0, SeasonParam ::fall);
	getSeasonalAnime<SeasonalAnime>(0, SeasonParam ::fall);

	// User Anime
	getUserSuggestedAnime<std::string>();
	getUserSuggestedAnime<UserSuggestedAnime>();
	updateUserAnimeListStatus<std::string>(0);
	updateUserAnimeListStatus<UserAnimeListStatus>(0);
	getUserAnimeList<std::string>("");
	getUserAnimeList<UserAnimeList>("");

	// Forums
	getForumBoards<std::string>();
	getForumBoards<ForumBoards>();

	getForumTopicDetail<std::string>(0);
	getForumTopicDetail<ForumTopicDetail>(0);

	getForumTopics<std::string>();
	getForumTopics<ForumTopics>();

	// Manga
	getMangaList<std::string>("");
	getMangaList<MangaList>("");

	getMangaDetails<std::string>(0);
	getMangaDetails<MangaDetails>(0);

	getMangaRanking<std::string>(MangaRankingTypeParam::all);
	getMangaRanking<MangaRanking>(MangaRankingTypeParam::all);

	// User Manga
	updateUserMangaListStatus<std::string>(0);
	updateUserMangaListStatus<UserMangaListStatus>(0);

	getUserMangaList<std::string>("");
	getUserMangaList<UserMangaList>("");

	// User
	getUserData<std::string>("");
	getUserData<UserObject>("");
}
