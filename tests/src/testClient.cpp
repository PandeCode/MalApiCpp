#include "testClient.hpp"

#include "malapi/client.hpp"

#include <iostream>

bool testClient() {
	const std::string MAL_CLIENT_ID = "430ce643e7b01ec2e8ae3d290e6cb56b";
	const std::string MAL_CLIENT_SECRET =
	    "6ba61c3c229804b69f7ee7290bc93d80c64f6fb9ece92b11a081281ba5552557";
	const std::string MAL_REDIRECT_URI = "http://127.0.0.1:8000/callback";

	Client client(MAL_CLIENT_ID, MAL_CLIENT_SECRET, MAL_REDIRECT_URI);

	std::cout << "Test Client\n";
	auto userData = client.getUserData();

	std::cout << userData.id << std::endl;

	std::cout << "id        : " << userData.id << std::endl;
	std::cout << "birthday  : " << userData.birthday << std::endl;
	std::cout << "joined_at : " << userData.joined_at << std::endl;
	std::cout << "location  : " << userData.location << std::endl;
	std::cout << "name      : " << userData.name << std::endl;

	return true;
}
