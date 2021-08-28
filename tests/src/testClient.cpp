#include "testClient.hpp"

#include "malapi/client.hpp"

#include <cstdint>
#include <iostream>

static const std::string MAL_CLIENT_ID = "430ce643e7b01ec2e8ae3d290e6cb56b";
static const std::string MAL_CLIENT_SECRET =
    "6ba61c3c229804b69f7ee7290bc93d80c64f6fb9ece92b11a081281ba5552557";
static const std::string MAL_REDIRECT_URI = "http://127.0.0.1:8000/callback";

bool testClient() {

	Client client(MAL_CLIENT_ID, MAL_CLIENT_SECRET, MAL_REDIRECT_URI);

	std::cout << "Test Client\n";

	testGetUserData(client);
	testGetAnimeList(client);
	testGetAnimeDetails(client);
	testGetAnimeRanking(client);
	testGetSeasonalAnime(client);
	testGetUserSuggestedAnime(client);
	//testUpdateUserAnimeListStatus(client);
	//client.deleteUserAnime
	testGetUserAnimeList(client);
	testGetForumBoards(client);
	testGetForumTopicDetail(client);
	testGetForumTopics(client);
	testGetMangaList(client);
	testGetMangaDetails(client);
	testGetMangaRanking(client);
	//testUpdateUserMangaListStatus(client);
	//client.deleteUserMangaListItem
	testGetUserMangaList(client);

	return true;
}
static const std::string BANNER = "\033[92m=============================================="
				  "==================================\033[0m\n";

void testGetAnimeList(const Client& client) {
	std::cout << BANNER;
	std::cout << "Test GetAnimeList" << std::endl;
	auto animeList = client.M__getAnimeList("mushoku", std::nullopt, 4, 0);
	std::cout << nlohmann::json::parse(animeList).dump(4) << std::endl;
}
void testGetAnimeDetails(const Client& client) {
	std::cout << BANNER;
	std::cout << "Test GetAnimeDetails" << std::endl;
	auto animeDetails = client.M__getAnimeDetails(39535);
	std::cout << nlohmann::json::parse(animeDetails).dump(4) << std::endl;
}
void testGetAnimeRanking(const Client& client) {
	std::cout << BANNER;
	std::cout << "Test GetAnimeRanking" << std::endl;
	auto animeRanking = client.M__getAnimeRanking(std::nullopt, all, 4, 0);
	std::cout << nlohmann::json::parse(animeRanking).dump(4) << std::endl;
}
void testGetSeasonalAnime(const Client& client) {
	std::cout << BANNER;
	std::cout << "Test GetSeasonalAnime" << std::endl;
	auto seasonalAnime = client.M__getSeasonalAnime(2021, winter);
	std::cout << nlohmann::json::parse(seasonalAnime).dump(4) << std::endl;
}
void testGetUserSuggestedAnime(const Client& client) {
	std::cout << BANNER;
	std::cout << "Test GetUserSuggestedAnime" << std::endl;
	auto userSuggestedAnime = client.M__getUserSuggestedAnime();
	std::cout << nlohmann::json::parse(userSuggestedAnime).dump(4) << std::endl;
}
void testUpdateUserAnimeListStatus(const Client& client) {
	std::cout << BANNER;
	std::cout << "Test UpdateUserAnimeListStatus" << std::endl;
	auto userAnimeListStatus = client.M__updateUserAnimeListStatus(39535);
	std::cout << nlohmann::json::parse(userAnimeListStatus).dump(4) << std::endl;
}
void testGetUserAnimeList(const Client& client) {
	std::cout << BANNER;
	std::cout << "Test GetUserAnimeList" << std::endl;
	auto userAnimeList = client.M__getUserAnimeList();
	std::cout << nlohmann::json::parse(userAnimeList).dump(4) << std::endl;
}
void testGetForumBoards(const Client& client) {
	std::cout << BANNER;
	std::cout << "Test GetForumBoards" << std::endl;
	auto forumBoards = client.M__getForumBoards();
	std::cout << nlohmann::json::parse(forumBoards).dump(4) << std::endl;
}
void testGetForumTopicDetail(const Client& client) {
	std::cout << BANNER;
	std::cout << "Test GetForumTopicDetail" << std::endl;
	auto forumTopicDetail = client.M__getForumTopicDetail(14, 4, 0);
	std::cout << nlohmann::json::parse(forumTopicDetail).dump(4) << std::endl;
}
void testGetForumTopics(const Client& client) {
	std::cout << BANNER;
	std::cout << "Test GetForumTopics" << std::endl;
	auto forumTopics = client.M__getForumTopics(14, 1);
	std::cout << forumTopics << std::endl;
	//std::cout << nlohmann::json::parse(forumTopics).dump(4) << std::endl;
}
void testGetMangaList(const Client& client) {
	std::cout << BANNER;
	std::cout << "Test GetMangaList" << std::endl;
	auto mangaList = client.M__getMangaList("new game");
	std::cout << nlohmann::json::parse(mangaList).dump(4) << std::endl;
}
void testGetMangaDetails(const Client& client) {
	std::cout << BANNER;
	std::cout << "Test GetMangaDetails" << std::endl;
	auto mangaDetails = client.M__getMangaDetails(5114);
	std::cout << nlohmann::json::parse(mangaDetails).dump(4) << std::endl;
}
void testGetMangaRanking(const Client& client) {
	std::cout << BANNER;
	std::cout << "Test GetMangaRanking" << std::endl;
	auto mangaRanking = client.M__getMangaRanking(m_all, 4);
	std::cout << nlohmann::json::parse(mangaRanking).dump(4) << std::endl;
}
void testUpdateUserMangaListStatus(const Client& client) {
	std::cout << BANNER;
	std::cout << "Test UpdateUserMangaListStatus" << std::endl;
	auto userMangaListStatus = client.M__updateUserMangaListStatus(5114);
	std::cout << nlohmann::json::parse(userMangaListStatus).dump(4) << std::endl;
}
void testGetUserMangaList(const Client& client) {
	std::cout << BANNER;
	std::cout << "Test GetUserMangaList" << std::endl;
	auto getUserMangaList =
	    client.M__getUserMangaList("@me", std::nullopt, std::nullopt, 4);
	std::cout << nlohmann::json::parse(getUserMangaList).dump(4) << std::endl;
}
void testGetUserData(const Client& client) {
	std::cout << BANNER;
	std::cout << "Test GetUserData" << std::endl;
	auto userData = client.M__getUserData();
	std::cout << nlohmann::json::parse(userData).dump(4) << std::endl;
}
