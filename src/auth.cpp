#include "malapi/auth.hpp"

#include "cpp-httplib/httplib.hpp"
#include "malapi/listener.hpp"
#include "nlohmann/json.hpp"
#include "malapi/jsonDefinitions.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

#define NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_NON_INLINE(Type, ...)                         \
	void to_json(nlohmann::json& nlohmann_json_j, const Type& nlohmann_json_t) {     \
		NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(NLOHMANN_JSON_TO, __VA_ARGS__)) \
	}                                                                                \
	void from_json(const nlohmann::json& nlohmann_json_j, Type& nlohmann_json_t) {   \
		NLOHMANN_JSON_EXPAND(                                                    \
		    NLOHMANN_JSON_PASTE(NLOHMANN_JSON_FROM, __VA_ARGS__))                \
	}

using namespace nlohmann;

namespace AuthTypes {

	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_NON_INLINE(
	    AuthData,
	    access_token,
	    token_type,
	    expires_in,
	    refresh_token);
}

std::string readFile(const std::string& path) {

	std::ifstream file(path);
	if(!file.good()) return "";

	std::stringstream returnString = std::stringstream();

	std::string tmpString;
	while(std::getline(file, tmpString)) {
		returnString << tmpString << "\n";
	}

	file.close();
	return returnString.str();
}

void overwriteFile(const std::string& filePath, const std::string& text) {
	std::ofstream file(filePath, std::ofstream::trunc);
	file << text;
}

Auth::Auth(
    std::string clientId,
    std::string clientSecrect,
    std::string redirectUri,
    std::string state,
    std::string cacheFilePath) :
    m_clientId(clientId),
    m_clientSecrect(clientSecrect), m_redirectUri(redirectUri),
    m_codeChallenge(getNewCodeVerifier()), m_state(state),
    m_authUrl(
	"https://myanimelist.net/v1/oauth2/authorize"
	"?response_type=code"
	"&client_id=" +
	m_clientId + "&code_challenge=" + m_codeChallenge + "&state" + m_state +
	"&redirect_uri=" + m_redirectUri),
    m_cacheFilePath(cacheFilePath) {}

std::string Auth::getNewCodeVerifier() {
	char       token[128]   = {};
	const char charPool[66] = {
	    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B',
	    'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3',
	    '4', '5', '6', '7', '8', '9', '-', '.', '_', '~',
	};

	for(std::uint8_t i = 0; i < 128; i++)
		token[i] = charPool[rand() % 66];

	return std::string(token, 128);
}
std::string Auth::listenForCode() {
	return Listener::listen();
}

httplib::Result Auth::getUserToken(std::string code) const {
	httplib::Client cli("https://myanimelist.net");

	auto data = std::stringstream();
	data << "grant_type=authorization_code&client_id=" << m_clientId
	     << "&client_secret=" << m_clientSecrect
	     << "&code_verifier=" << m_codeChallenge << "&redirect_uri=" << m_redirectUri
	     << "&code=" << code;

	auto res =
	    cli.Post("/v1/oauth2/token", data.str(), "application/x-www-form-urlencoded");

	//httplib::Conten({
	//{"client_id", m_clientId},
	//{"client_secret", m_clientSecrect},
	//{"code_verifier", m_codeChallenge},
	//{"redirect_uri", m_redirectUri},
	//{"code", code},
	//{"grant_type", "authorization_code"},
	//})

	return res;
}

void Auth::authenticate() {

	std::string authText = readFile(m_cacheFilePath);
	if(authText == "") {
reAuth:
#ifdef __linux__
		system(std::string("xdg-open '" + m_authUrl + "'").c_str());
#elif __APPLE__
		system(std::string("open '" + m_authUrl + "'").c_str());
#elif _WIN32
		system(std::string("start '" + m_authUrl + "'").c_str());
#endif

		auto code        = listenForCode();
		auto authDataRaw = getUserToken(code);

		if(authDataRaw->status != 200) {
			std::cout << "Response failed" << std::endl;
			return;
		}
		authText = authDataRaw->body;
		overwriteFile(m_cacheFilePath, authText);
	}
	auto authJson = json::parse(authText);
	authData      = authJson.get<AuthTypes::AuthData>();
	if(authData.token_type == "Bearer") isAuthenticated = true;
	if(expired()) {
		std::cout << "expired\n";
		goto reAuth;
	}
}

bool Auth::expired() {
	if(!isAuthenticated) return true;
	if(authData.access_token == "") return true;

	httplib::Client cli("https://api.myanimelist.net");

	auto res = cli.Get(
	    "/v2/users/@me",
	    httplib::Headers {
		{"Authorization", "Bearer " + authData.access_token},
		{"Accept", "application/json"},
	    });

	if(res->status == 200)
		return false;
	else if(res->status == 0) {
		std::cout << "Library is not working. Or offline.\n";
		std::abort();
	}
	return true;
}
