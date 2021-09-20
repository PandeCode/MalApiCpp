#include "malapi/listener.hpp"

#include "cpp-httplib/httplib.hpp"

std::string Listener::listen(uint16_t port) {
	std::string     code = "";
	httplib::Server svr;
	svr.Get("/callback", [&](const httplib::Request& req, httplib::Response& res) {
		if(req.has_param("code")) {
			code = req.get_param_value("code");
			res.set_content("Done you may now close this!", "text/plain");
			svr.stop();
		} else
			res.set_content("No code!", "text/plain");
	});
	svr.listen("0.0.0.0", port);
	return code;
}
