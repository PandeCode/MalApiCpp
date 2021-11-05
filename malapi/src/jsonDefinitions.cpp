#include "malapi/jsonDefinitions.hpp"

#include "malapi/types/client.hpp"
#include "nlohmann/json.hpp"

template <typename T>
static constexpr T optionalType(std::optional<T> const &) {
	static_assert(!std::is_default_constructible_v<T>);
	return T {};
}

VOID_JSON_DEFINE(AnimeRanking);
VOID_JSON_DEFINE(ForumBoards);
VOID_JSON_DEFINE(ForumTopicDetail);
VOID_JSON_DEFINE(ForumTopics);
VOID_JSON_DEFINE(MangaDetails);
VOID_JSON_DEFINE(MangaList);
VOID_JSON_DEFINE(MangaRanking);
VOID_JSON_DEFINE(SeasonalAnime);
VOID_JSON_DEFINE(UserAnimeList);
VOID_JSON_DEFINE(UserAnimeListStatus);
VOID_JSON_DEFINE(UserMangaList);
VOID_JSON_DEFINE(UserMangaListStatusUpdate);
VOID_JSON_DEFINE(UserSuggestedAnime);

void to_json(nlohmann::json& j, const AnimeObjectNode& t) {
	MY_TO_JSON_NORM(id, title, main_picture);
	MY_TO_JSON_OPT(
	    alternative_titles,
	    average_episode_duration,
	    background,
	    broadcast,
	    created_at,
	    end_date,
	    genres,
	    mean,
	    media_type,
	    my_list_status,
	    nsfw,
	    num_episodes,
	    num_favorites,
	    num_list_users,
	    num_scoring_users,
	    popularity,
	    rank,
	    rating,
	    related_anime,
	    source,
	    start_date,
	    start_season,
	    status,
	    studio,
	    synopsis,
	    updated_at);
}
void from_json(const nlohmann::json& j, AnimeObjectNode& t) {
	MY_FROM_JSON_NORM(id, title, main_picture);
	MY_FROM_JSON_OPT(
	    alternative_titles,
	    average_episode_duration,
	    background,
	    broadcast,
	    created_at,
	    end_date,
	    genres,
	    mean,
	    media_type,
	    my_list_status,
	    nsfw,
	    num_episodes,
	    num_favorites,
	    num_list_users,
	    num_scoring_users,
	    popularity,
	    rank,
	    rating,
	    related_anime,
	    source,
	    start_date,
	    start_season,
	    status,
	    studio,
	    synopsis,
	    updated_at);
}

JSON_DEFINE(AlternativeTitlesObject, en, ja, synonyms);
JSON_DEFINE(AnimeList, data);
JSON_DEFINE(AnimeObject, node);
JSON_DEFINE(AnimeStudioObject, id, name);
JSON_DEFINE(BroadcastObject, day_of_the_week, start_time);
JSON_DEFINE(GenreObject, id, name);
JSON_DEFINE(
    MyListStatusObject,
    comments,
    is_rewatching,
    num_episodes_watched,
    num_times_rewatched,
    priority,
    rewatch_value,
    score,
    status,
    tags,
    updated_at);
JSON_DEFINE(PictureObject, large, medium);
JSON_DEFINE(SeasonObject, season, year);
JSON_DEFINE(UserObject, id, birthday, joined_at, location, name);
