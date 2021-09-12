#pragma once
#include "../nlohmann/json.hpp"
#include "cpr/response.h"
#include "httplib.hpp"

#include <string>

class Client;

#define NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_NON_INLINE_DELCRATION(Type)    \
	void to_json(json& nlohmann_json_j, const Type& nlohmann_json_t); \
	void from_json(const json& nlohmann_json_j, Type& nlohmann_json_t);

namespace AuthTypes {

	using json = nlohmann::json;

	struct AuthData {
		std::string  access_token;
		std::string  token_type;
		std::string  refresh_token;
		unsigned int expires_in;
	};

	void to_json(json& nlohmann_json_j, const AuthData& nlohmann_json_t);
	void from_json(const json& nlohmann_json_j, AuthData& nlohmann_json_t);

}

class Auth {

	std::string m_clientId;
	std::string m_clientSecrect;
	std::string m_redirectUri;
	std::string m_codeChallenge;
	std::string m_state;
	std::string m_authUrl;
	std::string m_cacheFilePath;

      public:
	Auth(
	    std::string clientId,
	    std::string clientSecrect,
	    std::string redirectUri,
	    std::string state         = "Authenticaion",
	    std::string cacheFilePath = "./cache.json");
	~Auth()                             = default;

	bool                isAuthenticated = false;
	AuthTypes::AuthData authData;

	cpr::Response getUserToken(std::string code) const;

	static std::string listenForCode();
	static std::string getNewCodeVerifier();

	//httplib::Client httpClient =
		//httplib::Client("https://api.myanimelist.net/v2/users/@me");

	void authenticate();
	bool expired();

	friend bool testAuthPath();
	friend Client;
};
