#include "malapi/listener.hpp"

#include "pistache/endpoint.h"

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>

using namespace std;
using namespace Pistache;

std::string       code;
std::atomic<bool> state = true;

class CallbackHandler : public Http::Handler {
      public:
	HTTP_PROTOTYPE(CallbackHandler)

	void onRequest(const Http::Request& request,
		       Http::ResponseWriter response) override {

		for(auto it = request.query().parameters_begin();
		    it != request.query().parameters_end();
		    it++) {
			if(it->first == "code") {
				state = false;
				code  = it->second;
				response.send(Http::Code::Ok,
					      "Done! You can now close this tab.");
				return;
			}
		}
		response.send(Http::Code::Bad_Request,
			      "{\"message\": \"no callback code \"}");
	}
};

std::string Listener::listen(uint16_t port) {
	code = "";

	Address addr(Ipv4::any(), Port(port));
	auto    server = Http::Endpoint(addr);

	auto opts      = Http::Endpoint::options().threads(1);

	server.init(opts);
	server.setHandler(Http::make_handler<CallbackHandler>());
	server.serveThreaded();

	while(state)
		sleep(1);

	server.shutdown();

	state = true;

	return code;
}
