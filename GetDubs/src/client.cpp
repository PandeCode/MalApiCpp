#include "client.hpp"

#include "malapi/client.hpp"
#include "malapi/jsonDefinitions.hpp"

#include <iostream>


std::string ClientWrapper::getDubs() const {
	return nlohmann::json::parse(std::get<0>(
	    client.getForumTopicDetail(1692966, 1)))["data"]["posts"][0]["body"];
}
