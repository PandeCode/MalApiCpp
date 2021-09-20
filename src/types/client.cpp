#include "malapi/types/client.hpp"

#define DEF_OPERATOR(CLASS_WITH_toString)        \
	std::ostream& operator<<(                \
	    std::ostream&              stream,   \
	    const CLASS_WITH_toString& object) { \
		stream << object.toString();     \
		return stream;                   \
	}

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
VOID_TO_STRING(ForumTopicDetail);
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
	for(auto it = listType.begin(); it != listType.end(); it++)
		stream << *it << (std::next(it) != listType.end() ? ", " : " }");
	return stream;
}

std::string AnimeObjectNode::toString() const {
	std::stringstream returnString;
	// clang-format off
	returnString <<   "alternative_titles       : " << alternative_titles
				 << "\naverage_episode_duration : " << average_episode_duration
				 << "\nbroadcast                : " << broadcast
				 << "\ncreated_at               : " << created_at
				 << "\nend_date                 : " << end_date
				 << "\ngenres                   : " << genres
				 << "\nid                       : " << id
				 << "\nmain_picture             : " << main_picture
				 << "\nmean                     : " << mean
				 << "\nmedia_type               : " << media_type
				 << "\nnsfw                     : " << nsfw
				 << "\nnum_episodes             : " << num_episodes
				 << "\nnum_favorites            : " << num_favorites
				 << "\nnum_list_users           : " << num_list_users
				 << "\nnum_scoring_users        : " << num_scoring_users
				 << "\npopularity               : " << popularity
				 << "\nrank                     : " << rank
				 << "\nstart_date               : " << start_date
				 << "\nstart_season             : " << start_season
				 << "\nstatus                   : " << status
				 << "\nsynopsis                 : " << synopsis
				 << "\nsource                   : " << source
				 << "\nstudio                   : " << studio
				 << "\ntitle                    : " << title
				 << "\nupdated_at               : " << updated_at
				 << "\nmy_list_status           : " << my_list_status
				 << "\nbackground               : " << background
				 << "\nrelated_anime            : " << related_anime
				 << "\nrating                   : " << rating << "\n";
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
	// clang-format off
	returnString << "node: " << node << "\n";
	// clang-format on
	return returnString.str();
}
std::string AnimeList::toString() const {
	std::stringstream returnString;
	// clang-format off
	returnString << "data: " << data << "\n";
	// clang-format on
	return returnString.str();
}
