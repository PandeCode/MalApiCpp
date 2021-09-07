#define CROW_MAIN
#include "malapi/listener.hpp"
#include "crow.h"

std::string Listener::listen(uint16_t port) {
	char*           code = nullptr;
	crow::SimpleApp app;

	CROW_ROUTE(app, "/callback")
	([&code, &app](const crow::request& req) {
		code = req.url_params.get("code");

		if(code == nullptr) return "Done, No code receviced.";

		app.stop();
		return "Done, You can now close this page.";
	});

	app.port(port).loglevel(crow::LogLevel::Critical).run();

	return code;
}
