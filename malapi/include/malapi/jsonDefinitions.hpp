#pragma once
#include "MacroForEach64.hpp"
#include "malapi/types/client.hpp"
#include "nlohmann/json.hpp"

#define DECL_JSON(Type)                                                             \
	void to_json(nlohmann::json& nlohmann_json_j, const Type& nlohmann_json_t); \
	void from_json(const nlohmann::json& nlohmann_json_j, Type& nlohmann_json_t);

#define TRY(EXP)     \
	try {        \
		EXP; \
	} catch(const nlohmann::detail::out_of_range&) {}

#define JSON_TO(v1)   TRY(nlohmann_json_j[#v1] = nlohmann_json_t.v1;)
#define JSON_FROM(v1) TRY(nlohmann_json_j.at(#v1).get_to(nlohmann_json_t.v1);)

// NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Type, ...)
#define JSON_DEFINE(Type, ...)                                                         \
	void to_json(nlohmann::json& nlohmann_json_j, const Type& nlohmann_json_t) {   \
		NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(JSON_TO, __VA_ARGS__))        \
	}                                                                              \
	void from_json(const nlohmann::json& nlohmann_json_j, Type& nlohmann_json_t) { \
		NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(JSON_FROM, __VA_ARGS__))      \
	}

#define VOID_JSON_DEFINE(Type)                        \
	void to_json(nlohmann::json&, const Type&) {} \
	void from_json(const nlohmann::json&, Type&) {}

#define _MY_FROM_JSON_NORM(ARG) t.ARG = j.at(#ARG).get<decltype(t.ARG)>();
#define _MY_FROM_JSON_OPT(ARG) \
	if(j.count(#ARG) != 0) t.ARG = j.at(#ARG).get<decltype(optionalType(t.ARG))>();

#define _MY_TO_JSON_NORM(ARG) j[#ARG] = t.ARG;
#define _MY_TO_JSON_OPT(ARG) \
	if(t.ARG.has_value()) j[#ARG] = t.ARG.value();

#define MY_FROM_JSON_NORM(...)  FOR_EACH(_MY_FROM_JSON_NORM, __VA_ARGS__)
#define MY_FROM_JSON_OPT(...)  FOR_EACH(_MY_FROM_JSON_OPT, __VA_ARGS__)
#define MY_TO_JSON_NORM(...)  FOR_EACH(_MY_TO_JSON_NORM, __VA_ARGS__)
#define MY_TO_JSON_OPT(...)  FOR_EACH(_MY_TO_JSON_OPT, __VA_ARGS__)


DECL_JSON(AlternativeTitlesObject);
DECL_JSON(AnimeDetails);
DECL_JSON(AnimeList);
DECL_JSON(AnimeObject);
DECL_JSON(AnimeObjectNode);
DECL_JSON(AnimeRanking);
DECL_JSON(AnimeStudioObject);
DECL_JSON(BroadcastObject);
DECL_JSON(ForumBoards);
DECL_JSON(ForumTopicDetail);
DECL_JSON(ForumTopics);
DECL_JSON(GenreObject);
DECL_JSON(MangaDetails);
DECL_JSON(MangaList);
DECL_JSON(MangaRanking);
DECL_JSON(MyListStatusObject);
DECL_JSON(PictureObject);
DECL_JSON(SeasonObject);
DECL_JSON(SeasonalAnime);
DECL_JSON(UserAnimeList);
DECL_JSON(UserDetails);
DECL_JSON(UserMangaList);
DECL_JSON(UserObject);
DECL_JSON(UserSuggestedAnime);
