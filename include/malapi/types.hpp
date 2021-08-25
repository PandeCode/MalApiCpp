#include <string>

struct UserAccessToken {
	std::string token_type;    // "Bearer",
	std::string expires_in;    //  2678400,
	std::string access_token;  // "a1b2c3d4e5...",
	std::string refresh_token; // "z9y8x7w6u5..."
};
