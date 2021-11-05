#pragma once
#include "malapi/client.hpp"

static const std::string MAL_CLIENT_ID = "430ce643e7b01ec2e8ae3d290e6cb56b";
static const std::string MAL_CLIENT_SECRET =
    "6ba61c3c229804b69f7ee7290bc93d80c64f6fb9ece92b11a081281ba5552557";
static const std::string MAL_REDIRECT_URI = "http://127.0.0.1:8000/callback";

struct ClientWrapper {
	ClientWrapper() = default;
	Client client   = Client(MAL_CLIENT_ID, MAL_CLIENT_SECRET, MAL_REDIRECT_URI);

	std::string getDubs() const;
};
