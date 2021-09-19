#pragma once
#include "malapi/client.hpp"

static const std::string MAL_CLIENT_ID = "430ce643e7b01ec2e8ae3d290e6cb56b";
static const std::string MAL_CLIENT_SECRET =
    "6ba61c3c229804b69f7ee7290bc93d80c64f6fb9ece92b11a081281ba5552557";
static const std::string MAL_REDIRECT_URI = "http://127.0.0.1:8000/callback";

struct TestClient {
	TestClient()  = default;
	Client client = Client(MAL_CLIENT_ID, MAL_CLIENT_SECRET, MAL_REDIRECT_URI);

	void testAll() const;
	void testAllString() const;
	void testAllObject() const;

	void testAllAsync() const;
	void testAllStringAsync() const;
	void testAllObjectAsync() const;

	void testObjectGetUserData() const;
	void testObjectGetAnimeList() const;
	void testObjectGetAnimeDetails() const;
	void testObjectGetAnimeRanking() const;
	void testObjectGetSeasonalAnime() const;
	void testObjectGetUserSuggestedAnime() const;
	void testObjectUpdateUserAnimeListStatus() const;
	void testObjectGetUserAnimeList() const;
	void testObjectGetForumBoards() const;
	void testObjectGetForumTopicDetail() const;
	void testObjectGetForumTopics() const;
	void testObjectGetMangaList() const;
	void testObjectGetMangaDetails() const;
	void testObjectGetMangaRanking() const;
	void testObjectUpdateUserMangaListStatus() const;
	void testObjectGetUserMangaList() const;

	void testStringGetUserData() const;
	void testStringGetAnimeList() const;
	void testStringGetAnimeDetails() const;
	void testStringGetAnimeRanking() const;
	void testStringGetSeasonalAnime() const;
	void testStringGetUserSuggestedAnime() const;
	void testStringUpdateUserAnimeListStatus() const;
	void testStringGetUserAnimeList() const;
	void testStringGetForumBoards() const;
	void testStringGetForumTopicDetail() const;
	void testStringGetForumTopics() const;
	void testStringGetMangaList() const;
	void testStringGetMangaDetails() const;
	void testStringGetMangaRanking() const;
	void testStringUpdateUserMangaListStatus() const;
	void testStringGetUserMangaList() const;
};
