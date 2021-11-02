#include "malapi/jsonDefinitions.hpp"

#include "malapi/types/client.hpp"
#include "nlohmann/json.hpp"

VOID_JSON_DEFINE(AnimeRanking);
VOID_JSON_DEFINE(ForumBoards);
VOID_JSON_DEFINE(ForumTopics);
VOID_JSON_DEFINE(ForumTopicDetail);
VOID_JSON_DEFINE(MangaDetails);
VOID_JSON_DEFINE(MangaList);
VOID_JSON_DEFINE(MangaRanking);
VOID_JSON_DEFINE(SeasonalAnime);
VOID_JSON_DEFINE(UserAnimeList);
VOID_JSON_DEFINE(UserAnimeListStatus);
VOID_JSON_DEFINE(UserMangaList);
VOID_JSON_DEFINE(UserMangaListStatusUpdate);
VOID_JSON_DEFINE(UserSuggestedAnime);

// clang-format off
void to_json(nlohmann ::json& j, const AnimeObjectNode& t) {
	j["id"]                 = t.id;
	j["title"]              = t.title;
	j["main_picture"]       = t.main_picture;
	if (t.alternative_titles      .has_value()) j["alternative_titles"]       = t.alternative_titles      .value();
	if (t.average_episode_duration.has_value()) j["average_episode_duration"] = t.average_episode_duration.value();
	if (t.background              .has_value()) j["background"]               = t.background              .value();
	if (t.broadcast               .has_value()) j["broadcast"]                = t.broadcast               .value();
	if (t.created_at              .has_value()) j["created_at"]               = t.created_at              .value();
	if (t.end_date                .has_value()) j["end_date"]                 = t.end_date                .value();
	if (t.genres                  .has_value()) j["genres"]                   = t.genres                  .value();
	if (t.mean                    .has_value()) j["mean"]                     = t.mean                    .value();
	if (t.media_type              .has_value()) j["media_type"]               = t.media_type              .value();
	if (t.my_list_status          .has_value()) j["my_list_status"]           = t.my_list_status          .value();
	if (t.nsfw                    .has_value()) j["nsfw"]                     = t.nsfw                    .value();
	if (t.num_episodes            .has_value()) j["num_episodes"]             = t.num_episodes            .value();
	if (t.num_favorites           .has_value()) j["num_favorites"]            = t.num_favorites           .value();
	if (t.num_list_users          .has_value()) j["num_list_users"]           = t.num_list_users          .value();
	if (t.num_scoring_users       .has_value()) j["num_scoring_users"]        = t.num_scoring_users       .value();
	if (t.popularity              .has_value()) j["popularity"]               = t.popularity              .value();
	if (t.rank                    .has_value()) j["rank"]                     = t.rank                    .value();
	if (t.rating                  .has_value()) j["rating"]                   = t.rating                  .value();
	if (t.related_anime           .has_value()) j["related_anime"]            = t.related_anime           .value();
	if (t.source                  .has_value()) j["source"]                   = t.source                  .value();
	if (t.start_date              .has_value()) j["start_date"]               = t.start_date              .value();
	if (t.start_season            .has_value()) j["start_season"]             = t.start_season            .value();
	if (t.status                  .has_value()) j["status"]                   = t.status                  .value();
	if (t.studio                  .has_value()) j["studio"]                   = t.studio                  .value();
	if (t.synopsis                .has_value()) j["synopsis"]                 = t.synopsis                .value();
	if (t.updated_at              .has_value()) j["updated_at"]               = t.updated_at              .value();
}

void from_json(const nlohmann ::json& j, AnimeObjectNode& t) {
	t.id                       = j["id"];
	t.main_picture             = j["main_picture"];
	t.title                    = j["title"];

	if (j . count("alternative_titles")       != 0)t . alternative_titles       = j . at("alternative_titles")         . get<AlternativeTitlesObject>();
	if (j . count("average_episode_duration") != 0)t . average_episode_duration = j . at( "average_episode_duration" ) . get<std::uint16_t>();
	if (j . count("broadcast")                != 0)t . broadcast                = j . at( "broadcast" )                . get<BroadcastObject>();
	if (j . count("created_at")               != 0)t . created_at               = j . at( "created_at" )               . get<std::string>();
	if (j . count("end_date")                 != 0)t . end_date                 = j . at( "end_date" )                 . get<std::string>();
	if (j . count("genres")                   != 0)t . genres                   = j . at( "genres" )                   . get<std::vector<GenreObject>>();
	if (j . count("mean")                     != 0)t . mean                     = j . at( "mean" )                     . get<std::uint16_t>();
	if (j . count("media_type")               != 0)t . media_type               = j . at( "media_type" )               . get<std::string>();
	if (j . count("nsfw")                     != 0)t . nsfw                     = j . at( "nsfw" )                     . get<std::string>();
	if (j . count("num_episodes")             != 0)t . num_episodes             = j . at( "num_episodes" )             . get<std::uint16_t>();
	if (j . count("num_favorites")            != 0)t . num_favorites            = j . at( "num_favorites" )            . get<std::uint16_t>();
	if (j . count("num_list_users")           != 0)t . num_list_users           = j . at( "num_list_users" )           . get<std::uint16_t>();
	if (j . count("num_scoring_users")        != 0)t . num_scoring_users        = j . at( "num_scoring_users" )        . get<std::uint16_t>();
	if (j . count("popularity")               != 0)t . popularity               = j . at( "popularity" )               . get<std::uint16_t>();
	if (j . count("rank")                     != 0)t . rank                     = j . at( "rank" )                     . get<std::uint16_t>();
	if (j . count("start_date")               != 0)t . start_date               = j . at( "start_date" )               . get<std::string>();
	if (j . count("start_season")             != 0)t . start_season             = j . at( "start_season" )             . get<SeasonObject>();
	if (j . count("status")                   != 0)t . status                   = j . at( "status" )                   . get<std::string>();
	if (j . count("synopsis")                 != 0)t . synopsis                 = j . at( "synopsis" )                 . get<std::string>();
	if (j . count("source")                   != 0)t . source                   = j . at( "source" )                   . get<std::string>();
	if (j . count("studio")                   != 0)t . studio                   = j . at( "studio" )                   . get<AnimeStudioObject>();
	if (j . count("updated_at")               != 0)t . updated_at               = j . at( "updated_at" )               . get<std::string>();
	if (j . count("my_list_status")           != 0)t . my_list_status           = j . at( "my_list_status" )           . get<MyListStatusObject>();
	if (j . count("background")               != 0)t . background               = j . at( "background" )               . get<std::string>();
	if (j . count("related_anime")            != 0)t . related_anime            = j . at( "related_anime" )            . get<std::vector<AnimeObject>>();
	if (j . count("rating")                   != 0)t . rating                   = j . at("rating")                     . get<std::string>();
};
// clang-format on

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

JSON_DEFINE(AlternativeTitlesObject, en, ja, synonyms);

JSON_DEFINE(AnimeList, data);

JSON_DEFINE(AnimeObject, node);

JSON_DEFINE(AnimeStudioObject, id, name);

JSON_DEFINE(BroadcastObject, day_of_the_week, start_time);

JSON_DEFINE(PictureObject, large, medium);

JSON_DEFINE(SeasonObject, season, year);

JSON_DEFINE(UserObject, id, birthday, joined_at, location, name);

JSON_DEFINE(GenreObject, id, name);
