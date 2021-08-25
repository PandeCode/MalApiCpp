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

#define NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_NON_INLINE(Type, ...)                         \
	void to_json(nlohmann::json& nlohmann_json_j, const Type& nlohmann_json_t) {     \
		NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(NLOHMANN_JSON_TO, __VA_ARGS__)) \
	}                                                                                \
	void from_json(const nlohmann::json& nlohmann_json_j, Type& nlohmann_json_t) {   \
		NLOHMANN_JSON_EXPAND(                                                    \
		    NLOHMANN_JSON_PASTE(NLOHMANN_JSON_FROM, __VA_ARGS__))                \
	}

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_NON_INLINE(
    UserData,
    id,
    birthday,
    joined_at,
    location,
    name);

UserData Client::getUserData(std::string userName, std::optional<std::string> fields) {

	auto authorization = "Bearer " + m_auth.authData.access_token;

	auto params        = cpr::Parameters {};

	auto res           = cpr::Get(
            cpr::Url("https://api.myanimelist.net/v2/users/" + userName),
            params,
            cpr::Header({
                {"Authorization", authorization},
                {"Accept", "application/json"},
            }));

	auto resJson = json::parse(res.text);
	return resJson.get<UserData>();
}
