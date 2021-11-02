#include "malapi/types/client.hpp"

#define DEF_OPERATOR(CLASS_WITH_toString)        \
	std::ostream& operator<<(                \
	    std::ostream&              stream,   \
	    const CLASS_WITH_toString& object) { \
		stream << object.toString();     \
		return stream;                   \
	}

std ::ostream& operator<<(std ::ostream& stream, const Post& object) {
	std::cout  << "posts will be  here p: " << object.toString();
	stream << object.toString();
	return stream;
};

DEF_OPERATOR(CreatedBy);
DEF_OPERATOR(AlternativeTitlesObject);
DEF_OPERATOR(AnimeStudioObject);
DEF_OPERATOR(BroadcastObject);
DEF_OPERATOR(GenreObject);
DEF_OPERATOR(PictureObject);
DEF_OPERATOR(SeasonObject);
DEF_OPERATOR(MyListStatusObject);
DEF_OPERATOR(UserObject);
DEF_OPERATOR(AnimeObjectNode);
DEF_OPERATOR(AnimeObject);
DEF_OPERATOR(AnimeList);

#define VOID_TO_STRING(Type)                         \
	std::string Type::toString() const {         \
		std::stringstream returnString;      \
		returnString << #Type << " String."; \
		return returnString.str();           \
	}

VOID_TO_STRING(AnimeRanking);
VOID_TO_STRING(ForumBoards);
VOID_TO_STRING(ForumTopics);
VOID_TO_STRING(MangaDetails);
VOID_TO_STRING(MangaList);
VOID_TO_STRING(MangaRanking);
VOID_TO_STRING(SeasonalAnime);
VOID_TO_STRING(UserAnimeList);
VOID_TO_STRING(UserAnimeListStatus);
VOID_TO_STRING(UserMangaList);
VOID_TO_STRING(UserMangaListStatusUpdate);
VOID_TO_STRING(UserSuggestedAnime);

template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& listType) {
	stream << "{ ";
	if(listType.size()) {
		stream << "}";
		return stream;
	}
	for(auto it = listType.begin(); it != listType.end(); it++)
		stream << *it << (std::next(it) != listType.end() ? ", " : " }");
	return stream;
}

std::string AnimeObjectNode::toString() const {
	std::stringstream returnString;

	// clang-format off
	returnString                                           <<   "id                       : " << id;
	returnString                                           << "\ntitle                    : " << title;
	returnString                                           << "\nmain_picture             : " << main_picture;
	if(alternative_titles       .has_value()) returnString << "\nalternative_titles       : " << alternative_titles       .value();
	if(average_episode_duration .has_value()) returnString << "\naverage_episode_duration : " << average_episode_duration .value();
	if(broadcast                .has_value()) returnString << "\nbroadcast                : " << broadcast                .value();
	if(created_at               .has_value()) returnString << "\ncreated_at               : " << created_at               .value();
	if(end_date                 .has_value()) returnString << "\nend_date                 : " << end_date                 .value();
	if(genres                   .has_value()) returnString << "\ngenres                   : " << genres                   .value();
	if(mean                     .has_value()) returnString << "\nmean                     : " << mean                     .value();
	if(media_type               .has_value()) returnString << "\nmedia_type               : " << media_type               .value();
	if(nsfw                     .has_value()) returnString << "\nnsfw                     : " << nsfw                     .value();
	if(num_episodes             .has_value()) returnString << "\nnum_episodes             : " << num_episodes             .value();
	if(num_favorites            .has_value()) returnString << "\nnum_favorites            : " << num_favorites            .value();
	if(num_list_users           .has_value()) returnString << "\nnum_list_users           : " << num_list_users           .value();
	if(num_scoring_users        .has_value()) returnString << "\nnum_scoring_users        : " << num_scoring_users        .value();
	if(popularity               .has_value()) returnString << "\npopularity               : " << popularity               .value();
	if(rank                     .has_value()) returnString << "\nrank                     : " << rank                     .value();
	if(start_date               .has_value()) returnString << "\nstart_date               : " << start_date               .value();
	if(start_season             .has_value()) returnString << "\nstart_season             : " << start_season             .value();
	if(status                   .has_value()) returnString << "\nstatus                   : " << status                   .value();
	if(synopsis                 .has_value()) returnString << "\nsynopsis                 : " << synopsis                 .value();
	if(source                   .has_value()) returnString << "\nsource                   : " << source                   .value();
	if(studio                   .has_value()) returnString << "\nstudio                   : " << studio                   .value();
	if(updated_at               .has_value()) returnString << "\nupdated_at               : " << updated_at               .value();
	if(my_list_status           .has_value()) returnString << "\nmy_list_status           : " << my_list_status           .value();
	if(background               .has_value()) returnString << "\nbackground               : " << background               .value();
	if(related_anime            .has_value()) returnString << "\nrelated_anime            : " << related_anime            .value();
	if(rating                   .has_value()) returnString << "\nrating                   : " << rating                   .value();

	returnString << "\n";
	// clang-format on
	return returnString.str();
}

std::string AlternativeTitlesObject::toString() const {
	std::stringstream returnString;
	// clang-format off
	returnString <<   "en       : " << en
				 << "\nja       : " << ja
				 << "\nsynonyms : " << synonyms << "\n";
	// clang-format on
	return returnString.str();
}

std::string AnimeStudioObject::toString() const {
	std::stringstream returnString;
	// clang-format off
	returnString <<   "id   : " << id 
				 << "\nname : " << name << "\n";
	// clang-format on
	return returnString.str();
}
std::string BroadcastObject::toString() const {
	std::stringstream returnString;
	// clang-format off
	returnString <<  "day_of_the_week : " << day_of_the_week
				<< "\nstart_time      : " << start_time << "\n";
	// clang-format on
	return returnString.str();
}
std::string GenreObject::toString() const {
	std::stringstream returnString;
	// clang-format off
	returnString <<  "id   : " << id 
				<< "\nname : " << name << "\n";
	// clang-format on
	return returnString.str();
}
std::string PictureObject::toString() const {
	std::stringstream returnString;
	// clang-format off
	returnString <<  "large  : " << large 
				<< "\nmedium : " << medium << "\n";
	// clang-format on
	return returnString.str();
}
std::string SeasonObject::toString() const {
	std::stringstream returnString;
	// clang-format off
	returnString <<  "season : " << season
				<< "\nyear   : " << year << "\n";
	// clang-format on
	return returnString.str();
}

std::string MyListStatusObject::toString() const {
	std::stringstream returnString;
	// clang-format off
	returnString <<  "comments               : " << comments
				<< "\nis_rewatching          : " << is_rewatching
				<< "\nnum_episodes_watched   : " << num_episodes_watched
				<< "\nnum_times_rewatched    : " << num_times_rewatched
				<< "\npriority               : " << priority
				<< "\nrewatch_value          : " << rewatch_value
				<< "\nscore                  : " << score
				<< "\nstatus                 : " << status
				<< "\ntags                   : " << tags
				<< "\nupdated_at             : " << updated_at << "\n";
	// clang-format on
	return returnString.str();
}

std::string UserObject::toString() const {
	std::stringstream returnString;
	// clang-format off
	returnString <<  "id         : " << id 
				<< "\nname       : " << name
				<< "\nlocation   : " << location
				<< "\njoined_at  : " << joined_at
				<< "\nbirthday   : " << birthday << "\n";
	// clang-format on
	return returnString.str();
}

std::string AnimeObject::toString() const {
	std::stringstream returnString;
	returnString << "node: " << node << "\n";
	return returnString.str();
}
std::string AnimeList::toString() const {
	std::stringstream returnString;
	returnString << "data: " << data << "\n";
	return returnString.str();
}

std ::string ForumTopicDetail ::toString() const {
	std ::stringstream returnString;
	returnString << "data: " << data.toString();

	return returnString.str();
};

std::string ForumTopicDetailData::toString() const {
	std ::stringstream returnString;
	returnString << "posts: " << posts;
	return returnString.str();
}

std::string CreatedBy::toString() const {
	std ::stringstream returnString;
	returnString << "forum_avator" << forum_avator;
	returnString << "forum_title" << forum_title;
	returnString << "mods_title" << mods_title;
	returnString << "name" << name;
	returnString << "id" << id;

	return returnString.str();
}

// clang-format off
std::string Post::toString() const {
	std ::stringstream returnString;
	returnString << "\nbody" << body;
	returnString << "\ncreated_at" << created_at;
	returnString << "\ncreated_by" << created_by;
	returnString << "\nid" << id;
	returnString << "\nnumber" << number;
	returnString << "\nsignature" << signature;

	return returnString.str();
}
// clang-format on
