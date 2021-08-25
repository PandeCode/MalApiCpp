#include "testAuth.hpp"

#include "Log.hpp"
#include "cpr/api.h"
#include "cpr/cprtypes.h"
#include "cpr/response.h"
#include "nlohmann/json.hpp"

#include <cstdlib>
#include <iostream>
#include <malapi/auth.hpp>
#include <string>

using namespace nlohmann;
void printResponse(cpr::Response& response) {
	std::cout << "Status Code : " << response.status_code << std::endl;
	std::cout << "Raw Header  : " << response.raw_header << std::endl;
	std::cout << "Text        : " << response.text << std::endl;
	std::cout << "Reason      : " << response.reason << std::endl;
}

bool testAuth() {
	const std::string MAL_CLIENT_ID = "430ce643e7b01ec2e8ae3d290e6cb56b";
	const std::string MAL_CLIENT_SECRET =
	    "6ba61c3c229804b69f7ee7290bc93d80c64f6fb9ece92b11a081281ba5552557";
	const std::string MAL_REDIRECT_URI = "http://127.0.0.1:8000/callback";

	Auth auth = Auth(MAL_CLIENT_ID, MAL_CLIENT_SECRET, MAL_REDIRECT_URI);

	Log::Info("Authentic: " + std::to_string(auth.isAuthenticated));
	auth.authenticate();
	Log::Info("Authentic: " + std::to_string(auth.isAuthenticated));

	if(!auth.isAuthenticated) {
		Log::Error("Failed to authenticate");
		return false;
	}

	auto authorization = "Bearer " + auth.authData.access_token;

	auto res     = cpr::Get(cpr::Url("https://api.myanimelist.net/v2/users/@me"),
                            cpr::Header({
                                {"Authorization", authorization},
                                {"Accept", "application/json"},
                            }));

	auto resJson = json::parse(res.text);

	std::cout << "Result: \n" << resJson.dump(4) << std::endl;

	return true;
}

bool testAuthPath() {
	const std::string MAL_CLIENT_ID = "430ce643e7b01ec2e8ae3d290e6cb56b";
	const std::string MAL_CLIENT_SECRET =
	    "6ba61c3c229804b69f7ee7290bc93d80c64f6fb9ece92b11a081281ba5552557";
	const std::string MAL_REDIRECT_URI = "http://127.0.0.1:8000/callback";

	Auth auth = Auth(MAL_CLIENT_ID, MAL_CLIENT_SECRET, MAL_REDIRECT_URI);

	std::cout << "PKCE code verifier [" << auth.m_codeChallenge.length()
		  << "]: " << auth.m_codeChallenge << "\n";
	std::cout << "Auth url:" << auth.m_authUrl << "\n";

	system(std::string("xdg-open '" + auth.m_authUrl + "'").c_str());

	std::string authCode = auth.listenForCode();
	std::cout << "Auth Code: " << authCode << "\n";

	auto authData = auth.getUserToken(authCode);
	printResponse(authData);

	auto                authJson      = json::parse(authData.text);
	AuthTypes::AuthData j             = authJson.get<AuthTypes::AuthData>();
	auto                authorization = "Bearer " + j.access_token;
	return true;
}
