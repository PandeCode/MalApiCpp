#pragma once
#include "cpp-httplib/httplib.hpp"
#include "nlohmann/json.hpp"

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
	    const std::string& clientId,
	    const std::string& clientSecrect,
	    const std::string& redirectUri,
	    const std::string& state         = "Authenticaion",
	    const std::string& cacheFilePath = "./cache.json");
	~Auth()                             = default;

	bool                isAuthenticated = false;
	AuthTypes::AuthData authData;

	httplib::Result getUserToken(const std::string& code) const;

	static std::string listenForCode();
	static std::string getNewCodeVerifier();

	void authenticate();
	bool expired();

	friend bool testAuthPath();
	friend Client;
};
