#include "testClient.hpp"

#include "httplib.hpp"
#include "malapi/client.hpp"

#include <cstdint>
#include <future>
#include <iostream>

static const std::string MAL_CLIENT_ID = "430ce643e7b01ec2e8ae3d290e6cb56b";
static const std::string MAL_CLIENT_SECRET =
    "6ba61c3c229804b69f7ee7290bc93d80c64f6fb9ece92b11a081281ba5552557";
static const std::string MAL_REDIRECT_URI = "http://127.0.0.1:8000/callback";

bool testClient() {
	Client client(MAL_CLIENT_ID, MAL_CLIENT_SECRET, MAL_REDIRECT_URI);

	std::cout << "Test Client\n";

	// clang-format off
	std::future PromiseTestGetUserData           = std::async ( std::launch::async, [&client] ( ) { testGetUserData           ( client );});
	std::future PromiseTestGetAnimeList          = std::async ( std::launch::async, [&client] ( ) { testGetAnimeList          ( client );});
	std::future PromiseTestGetAnimeDetails       = std::async ( std::launch::async, [&client] ( ) { testGetAnimeDetails       ( client );});
	std::future PromiseTestGetAnimeRanking       = std::async ( std::launch::async, [&client] ( ) { testGetAnimeRanking       ( client );});
	std::future PromiseTestGetSeasonalAnime      = std::async ( std::launch::async, [&client] ( ) { testGetSeasonalAnime      ( client );});
	std::future PromiseTestGetUserSuggestedAnime = std::async ( std::launch::async, [&client] ( ) { testGetUserSuggestedAnime ( client );});
	std::future PromiseTestGetUserAnimeList      = std::async ( std::launch::async, [&client] ( ) { testGetUserAnimeList      ( client );});
	std::future PromiseTestGetForumBoards        = std::async ( std::launch::async, [&client] ( ) { testGetForumBoards        ( client );});
	std::future PromiseTestGetForumTopicDetail   = std::async ( std::launch::async, [&client] ( ) { testGetForumTopicDetail   ( client );});
	std::future PromiseTestGetForumTopics        = std::async ( std::launch::async, [&client] ( ) { testGetForumTopics        ( client );});
	std::future PromiseTestGetMangaList          = std::async ( std::launch::async, [&client] ( ) { testGetMangaList          ( client );});
	std::future PromiseTestGetMangaRanking       = std::async ( std::launch::async, [&client] ( ) { testGetMangaRanking       ( client );});
	std::future PromiseTestGetMangaDetails       = std::async ( std::launch::async, [&client] ( ) { testGetMangaDetails       ( client );});
	std::future PromiseTestGetUserMangaList      = std::async ( std::launch::async, [&client] ( ) { testGetUserMangaList      ( client );});
	// clang-format on

	PromiseTestGetUserData.wait();
	PromiseTestGetAnimeList.wait();
	PromiseTestGetAnimeDetails.wait();
	PromiseTestGetAnimeRanking.wait();
	PromiseTestGetSeasonalAnime.wait();
	PromiseTestGetUserSuggestedAnime.wait();
	PromiseTestGetUserAnimeList.wait();
	PromiseTestGetForumBoards.wait();
	PromiseTestGetForumTopicDetail.wait();
	PromiseTestGetForumTopics.wait();
	PromiseTestGetMangaRanking.wait();
	PromiseTestGetMangaList.wait();
	PromiseTestGetMangaDetails.wait();
	PromiseTestGetUserMangaList.wait();

	//testUpdateUserAnimeListStatus(client);
	//client.deleteUserAnime
	//testUpdateUserMangaListStatus(client);
	//client.deleteUserMangaListItem

	return true;
}
static const std::string BANNER = "\033[92m=============================================="
				  "==================================\033[0m\n";

void testGetAnimeList(const Client& client) {
	auto animeList = client.M__getAnimeList("mushoku", std::nullopt, 4, 0);
	std::cout << BANNER << "\nTest GetAnimeList" << std::endl;
	std::cout << nlohmann::json::parse(animeList).dump(4) << std::endl;
}
void testGetAnimeDetails(const Client& client) {
	auto animeDetails = client.M__getAnimeDetails(39535);
	std::cout << BANNER << "\nTest GetAnimeDetails" << std::endl;
	std::cout << nlohmann::json::parse(animeDetails).dump(4) << std::endl;
}
void testGetAnimeRanking(const Client& client) {
	auto animeRanking =
	    client.M__getAnimeRanking(std::nullopt, AnimeRankingType::all, 4, 0);
	std::cout << BANNER << "\nTest GetAnimeRanking" << std::endl;
	std::cout << nlohmann::json::parse(animeRanking).dump(4) << std::endl;
}
void testGetSeasonalAnime(const Client& client) {
	auto seasonalAnime = client.M__getSeasonalAnime(2021, SeasonParam::winter);
	std::cout << BANNER << "\nTest GetSeasonalAnime" << std::endl;
	std::cout << nlohmann::json::parse(seasonalAnime).dump(4) << std::endl;
}
void testGetUserSuggestedAnime(const Client& client) {
	auto userSuggestedAnime = client.M__getUserSuggestedAnime(4);
	std::cout << BANNER << "\nTest GetUserSuggestedAnime" << std::endl;
	std::cout << nlohmann::json::parse(userSuggestedAnime).dump(4) << std::endl;
}
void testUpdateUserAnimeListStatus(const Client& client) {
	auto userAnimeListStatus = client.M__updateUserAnimeListStatus(39535);
	std::cout << BANNER << "\nTest UpdateUserAnimeListStatus" << std::endl;
	std::cout << nlohmann::json::parse(userAnimeListStatus).dump(4) << std::endl;
}
void testGetUserAnimeList(const Client& client) {
	auto userAnimeList = client.M__getUserAnimeList();
	std::cout << BANNER << "\nTest GetUserAnimeList" << std::endl;
	std::cout << nlohmann::json::parse(userAnimeList).dump(4) << std::endl;
}
void testGetForumBoards(const Client& client) {
	auto forumBoards = client.M__getForumBoards();
	std::cout << BANNER << "\nTest GetForumBoards" << std::endl;
	std::cout << nlohmann::json::parse(forumBoards).dump(4) << std::endl;
}
void testGetForumTopicDetail(const Client& client) {
	auto forumTopicDetail = client.M__getForumTopicDetail(14, 4, 0);
	std::cout << BANNER << "\nTest GetForumTopicDetail" << std::endl;
	std::cout << nlohmann::json::parse(forumTopicDetail).dump(4) << std::endl;
}
void testGetForumTopics(const Client& client) {
	auto forumTopics = client.M__getForumTopics(
	    std::nullopt,
	    2,
	    std::nullopt,
	    "love",
	    std::nullopt,
	    std::nullopt,
	    4,
	    0);
	std::cout << BANNER << "\nTest GetForumTopics" << std::endl;
	std::cout << nlohmann::json::parse(forumTopics).dump(4) << std::endl;
}
void testGetMangaList(const Client& client) {
	auto mangaList = client.M__getMangaList("new game");
	std::cout << BANNER << "\nTest GetMangaList" << std::endl;
	std::cout << nlohmann::json::parse(mangaList).dump(4) << std::endl;
}
void testGetMangaDetails(const Client& client) {
	auto mangaDetails = client.M__getMangaDetails(5114);
	std::cout << BANNER << "\nTest GetMangaDetails" << std::endl;
	std::cout << nlohmann::json::parse(mangaDetails).dump(4) << std::endl;
}
void testGetMangaRanking(const Client& client) {
	auto mangaRanking = client.M__getMangaRanking(MangaRankingTypeParam::all, 4);
	std::cout << BANNER << "\nTest GetMangaRanking" << std::endl;
	std::cout << nlohmann::json::parse(mangaRanking).dump(4) << std::endl;
}
void testUpdateUserMangaListStatus(const Client& client) {
	auto userMangaListStatus = client.M__updateUserMangaListStatus(5114);
	std::cout << BANNER << "\nTest UpdateUserMangaListStatus" << std::endl;
	std::cout << nlohmann::json::parse(userMangaListStatus).dump(4) << std::endl;
}
void testGetUserMangaList(const Client& client) {
	auto getUserMangaList =
	    client.M__getUserMangaList("@me", std::nullopt, std::nullopt, 4);
	std::cout << BANNER << "\nTest GetUserMangaList" << std::endl;
	std::cout << nlohmann::json::parse(getUserMangaList).dump(4) << std::endl;
}
void testGetUserData(const Client& client) {
	auto userData = client.M__getUserData();
	std::cout << BANNER << "\nTest GetUserData" << std::endl;
	std::cout << nlohmann::json::parse(userData).dump(4) << std::endl;
}
