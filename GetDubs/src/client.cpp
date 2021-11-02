#include "client.hpp"

#include "malapi/client.hpp"
#include "malapi/jsonDefinitions.hpp"

#include <iostream>

void ClientWrapper::getDubs() const {
	std::string res = std::get<0>(client.getForumTopicDetail(1692966, 1));

	std::cout << std::string(nlohmann::json::parse(res)["data"]["posts"][0]["body"])
		  << std::endl;
}
