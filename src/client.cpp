#include "malapi/client.hpp"

#include "cpr/api.h"
#include "cpr/curl_container.h"
#include "cpr/parameters.h"
#include "nlohmann/json.hpp"

#include <iostream>

using namespace nlohmann;

Client::Client(Auth& auth) : m_auth(auth) {
	if(!auth.isAuthenticated) m_auth.authenticate();
}

Client::Client(
    std::string clientId,
    std::string clientSecrect,
    std::string redirectUri,
    std::string state) :
    m_auth(clientId, clientSecrect, redirectUri, state) {
	m_auth.authenticate();
}

UserData Client::getUserData(std::string userName, std::optional<std::string> fields) {

	auto headers = cpr::Header({
	    {"Authorization", "Bearer " + m_auth.authData.access_token},
	    {"Accept", "application/json"},
	});
	auto params  = cpr::Parameters {};

	auto res     = cpr::Get(
            cpr::Url("https://api.myanimelist.net/v2/users/" + userName),
            params,
            headers);

	auto resJson = json::parse(res.text);
	return resJson.get<UserData>();
}
