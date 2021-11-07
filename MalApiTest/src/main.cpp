#include "auth.hpp"
#include "client.hpp"
#include "listener.hpp"

#include <iostream>

int main() {
	//testAuth();
	//testAuthPath();
	//testListener();
	TestClient testClient;
	testClient.testAllString();
	testClient.testAllObject();

	//std::cout << testAuth() << std::endl;
	//std::cout << testClient() << std::endl;
	//std::cout << testListener() << std::endl;
	return 0;
}
