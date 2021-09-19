#include "listener.hpp"

#include <iostream>
#include <malapi/listener.hpp>

bool testListener() {
	std::cout << "Callaback Code" << Listener::listen() << "\n";
	return true;
}
