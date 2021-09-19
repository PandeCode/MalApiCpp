#include "client.hpp"

#include "httplib.hpp"
#include "malapi/client.hpp"
#include "malapi/jsonDefinitions.hpp"

#include <cstdint>
#include <future>
#include <iostream>

static constexpr const char* const BANNER =
    "\033[92m==============================================\033[0m";

//testUpdateUserAnimeListStatus();
//client.deleteUserAnime
//testUpdateUserMangaListStatus();
//client.deleteUserMangaListItem
//DEF_STR_TEST( testUpdateUserAnimeListStatus , updateUserAnimeListStatus<std::string>(39535));
//DEF_STR_TEST( testUpdateUserMangaListStatus , updateUserMangaListStatus<std::string>(5114));

void TestClient::testAllString() const {
	testStringGetUserData();
	testStringGetAnimeList();
	testStringGetAnimeDetails();
	testStringGetAnimeRanking();
	testStringGetSeasonalAnime();
	testStringGetUserSuggestedAnime();
	testStringGetUserAnimeList();
	testStringGetForumBoards();
	testStringGetForumTopicDetail();
	testStringGetForumTopics();
	testStringGetMangaList();
	testStringGetMangaRanking();
	testStringGetMangaDetails();
	testStringGetUserMangaList();
}

void TestClient::testAllStringAsync() const {
	using namespace std;
	// clang-format off
	future PromiseTestStringGetUserData                 = async ( launch::async, [this] ( ) { this->testStringGetUserData                 () ;});
	future PromiseTestStringGetAnimeList                = async ( launch::async, [this] ( ) { this->testStringGetAnimeList                () ;});
	future PromiseTestStringGetAnimeDetails             = async ( launch::async, [this] ( ) { this->testStringGetAnimeDetails             () ;});
	future PromiseTestStringGetAnimeRanking             = async ( launch::async, [this] ( ) { this->testStringGetAnimeRanking             () ;});
	future PromiseTestStringGetSeasonalAnime            = async ( launch::async, [this] ( ) { this->testStringGetSeasonalAnime            () ;});
	future PromiseTestStringGetUserSuggestedAnime       = async ( launch::async, [this] ( ) { this->testStringGetUserSuggestedAnime       () ;});
	future PromiseTestStringGetUserAnimeList            = async ( launch::async, [this] ( ) { this->testStringGetUserAnimeList            () ;});
	future PromiseTestStringGetForumBoards              = async ( launch::async, [this] ( ) { this->testStringGetForumBoards              () ;});
	future PromiseTestStringGetForumTopicDetail         = async ( launch::async, [this] ( ) { this->testStringGetForumTopicDetail         () ;});
	future PromiseTestStringGetForumTopics              = async ( launch::async, [this] ( ) { this->testStringGetForumTopics              () ;});
	future PromiseTestStringGetMangaList                = async ( launch::async, [this] ( ) { this->testStringGetMangaList                () ;});
	future PromiseTestStringGetMangaRanking             = async ( launch::async, [this] ( ) { this->testStringGetMangaRanking             () ;});
	future PromiseTestStringGetMangaDetails             = async ( launch::async, [this] ( ) { this->testStringGetMangaDetails             () ;});
	future PromiseTestStringGetUserMangaList            = async ( launch::async, [this] ( ) { this->testStringGetUserMangaList            () ;});
	// clang-format on
	PromiseTestStringGetUserData.wait();
	PromiseTestStringGetAnimeList.wait();
	PromiseTestStringGetAnimeDetails.wait();
	PromiseTestStringGetAnimeRanking.wait();
	PromiseTestStringGetSeasonalAnime.wait();
	PromiseTestStringGetUserSuggestedAnime.wait();
	PromiseTestStringGetUserAnimeList.wait();
	PromiseTestStringGetForumBoards.wait();
	PromiseTestStringGetForumTopicDetail.wait();
	PromiseTestStringGetForumTopics.wait();
	PromiseTestStringGetMangaRanking.wait();
	PromiseTestStringGetMangaList.wait();
	PromiseTestStringGetMangaDetails.wait();
	PromiseTestStringGetUserMangaList.wait();
}

void TestClient::testAllObjectAsync() const {
	using namespace std;
	// clang-format off
	future PromiseTestObjectGetUserData           = async ( launch::async, [this] ( ) { this->testObjectGetUserData           () ;});
	future PromiseTestObjectGetAnimeList          = async ( launch::async, [this] ( ) { this->testObjectGetAnimeList          () ;});
	future PromiseTestObjectGetAnimeDetails       = async ( launch::async, [this] ( ) { this->testObjectGetAnimeDetails       () ;});
	future PromiseTestObjectGetAnimeRanking       = async ( launch::async, [this] ( ) { this->testObjectGetAnimeRanking       () ;});
	future PromiseTestObjectGetSeasonalAnime      = async ( launch::async, [this] ( ) { this->testObjectGetSeasonalAnime      () ;});
	future PromiseTestObjectGetUserSuggestedAnime = async ( launch::async, [this] ( ) { this->testObjectGetUserSuggestedAnime () ;});
	future PromiseTestObjectGetUserAnimeList      = async ( launch::async, [this] ( ) { this->testObjectGetUserAnimeList      () ;});
	future PromiseTestObjectGetForumBoards        = async ( launch::async, [this] ( ) { this->testObjectGetForumBoards        () ;});
	future PromiseTestObjectGetForumTopicDetail   = async ( launch::async, [this] ( ) { this->testObjectGetForumTopicDetail   () ;});
	future PromiseTestObjectGetForumTopics        = async ( launch::async, [this] ( ) { this->testObjectGetForumTopics        () ;});
	future PromiseTestObjectGetMangaList          = async ( launch::async, [this] ( ) { this->testObjectGetMangaList          () ;});
	future PromiseTestObjectGetMangaRanking       = async ( launch::async, [this] ( ) { this->testObjectGetMangaRanking       () ;});
	future PromiseTestObjectGetMangaDetails       = async ( launch::async, [this] ( ) { this->testObjectGetMangaDetails       () ;});
	future PromiseTestObjectGetUserMangaList      = async ( launch::async, [this] ( ) { this->testObjectGetUserMangaList      () ;});
	// clang-format on
	PromiseTestObjectGetUserData.wait();
	PromiseTestObjectGetAnimeList.wait();
	PromiseTestObjectGetAnimeDetails.wait();
	PromiseTestObjectGetAnimeRanking.wait();
	PromiseTestObjectGetSeasonalAnime.wait();
	PromiseTestObjectGetUserSuggestedAnime.wait();
	PromiseTestObjectGetUserAnimeList.wait();
	PromiseTestObjectGetForumBoards.wait();
	PromiseTestObjectGetForumTopicDetail.wait();
	PromiseTestObjectGetForumTopics.wait();
	PromiseTestObjectGetMangaRanking.wait();
	PromiseTestObjectGetMangaList.wait();
	PromiseTestObjectGetMangaDetails.wait();
	PromiseTestObjectGetUserMangaList.wait();
}

void TestClient::testAllObject() const {
	testObjectGetUserData();
	testObjectGetAnimeList();
	testObjectGetAnimeDetails();
	testObjectGetAnimeRanking();
	testObjectGetSeasonalAnime();
	testObjectGetUserSuggestedAnime();
	testObjectGetUserAnimeList();
	testObjectGetForumBoards();
	testObjectGetForumTopicDetail();
	testObjectGetForumTopics();
	testObjectGetMangaList();
	testObjectGetMangaRanking();
	testObjectGetMangaDetails();
	testObjectGetUserMangaList();
}

void TestClient::testAllAsync() const {
	testAllStringAsync();
	testAllObjectAsync();
}

void TestClient::testAll() const {
	testAllString();
	testAllObject();
}

#define VOID_DEF_STR_TEST(TEST, FUNCTION) \
	void TestClient::TEST() const {}

#define VOID_DEF_OBJ_TEST(TEST, FUNCTION) \
	void TestClient::TEST() const {}

#define DEF_STR_TEST(TEST, FUNCTION)                                          \
	void TestClient::TEST() const {                                       \
		auto res = std::get<0>(client.FUNCTION);                      \
		std::cout << BANNER << "TEST" << BANNER << "\n"               \
			  << nlohmann::json::parse(res).dump(4) << std::endl; \
	}

// clang-format off
DEF_STR_TEST(testStringGetAnimeList,          getAnimeList("mushoku", std::nullopt, 4, 0));
DEF_STR_TEST(testStringGetAnimeDetails,       getAnimeDetails(39535));
DEF_STR_TEST(testStringGetUserData,           getUserData());
VOID_DEF_STR_TEST(testStringGetAnimeRanking,       getAnimeRanking(std::nullopt, AnimeRankingType::all, 4, 0));
VOID_DEF_STR_TEST(testStringGetSeasonalAnime,      getSeasonalAnime(2021, SeasonParam::winter));
VOID_DEF_STR_TEST(testStringGetUserSuggestedAnime, getUserSuggestedAnime(4));
VOID_DEF_STR_TEST(testStringGetUserAnimeList,      getUserAnimeList());
VOID_DEF_STR_TEST(testStringGetForumBoards,        getForumBoards());
VOID_DEF_STR_TEST(testStringGetForumTopicDetail,   getForumTopicDetail(14, 4, 0));
VOID_DEF_STR_TEST(testStringGetForumTopics,        getForumTopics());
VOID_DEF_STR_TEST(testStringGetMangaList,          getMangaList("new game"));
VOID_DEF_STR_TEST(testStringGetMangaDetails,       getMangaDetails(5114));
VOID_DEF_STR_TEST(testStringGetMangaRanking,       getMangaRanking(MangaRankingTypeParam::all, 4));
VOID_DEF_STR_TEST(testStringGetUserMangaList,      getUserMangaList("@me", std::nullopt, std::nullopt, 4));
// clang-format on

#define DEF_OBJ_TEST(TEST, FUNCTION)                           \
	void TestClient::TEST() const {                        \
		auto res = std::get<1>(client.FUNCTION);       \
		std::cout << BANNER << #TEST << BANNER << "\n" \
			  << res.toString() << std::endl;      \
	}

// clang-format off
DEF_OBJ_TEST(testObjectGetAnimeList,          getAnimeList<AnimeList>("mushoku", std::nullopt, 4, 0));
DEF_OBJ_TEST(testObjectGetAnimeDetails,       getAnimeDetails<AnimeDetails>(39535));
DEF_OBJ_TEST(testObjectGetUserData,           getUserData<UserDetails>());
VOID_DEF_OBJ_TEST(testObjectGetAnimeRanking,       getAnimeRanking<AnimeRanking>(std::nullopt, AnimeRankingType::all, 4, 0));
VOID_DEF_OBJ_TEST(testObjectGetSeasonalAnime,      getSeasonalAnime<SeasonalAnime>(2021, SeasonParam::winter));
VOID_DEF_OBJ_TEST(testObjectGetUserSuggestedAnime, getUserSuggestedAnime<UserSuggestedAnime>(4));
VOID_DEF_OBJ_TEST(testObjectGetUserAnimeList,      getUserAnimeList<UserAnimeList>());
VOID_DEF_OBJ_TEST(testObjectGetForumBoards,        getForumBoards<ForumBoards>());
VOID_DEF_OBJ_TEST(testObjectGetForumTopicDetail,   getForumTopicDetail<ForumBoardsTopicDetail>(14, 4, 0));
VOID_DEF_OBJ_TEST(testObjectGetForumTopics,        getForumTopics<ForumTopics>());
VOID_DEF_OBJ_TEST(testObjectGetMangaList,          getMangaList<MangaList>("new game"));
VOID_DEF_OBJ_TEST(testObjectGetMangaDetails,       getMangaDetails<MangaDetails>(5114));
VOID_DEF_OBJ_TEST(testObjectGetMangaRanking,       getMangaRanking<MangaRanking>(MangaRankingTypeParam::all, 4));
VOID_DEF_OBJ_TEST(testObjectGetUserMangaList,      getUserMangaList<UserMangaList>("@me", std::nullopt, std::nullopt, 4));
// clang-format on
