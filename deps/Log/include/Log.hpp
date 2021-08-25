#pragma once
#include <iostream>

#define ERROR_COLOR                  "\033[91m"
#define DEBUG_COLOR                  "\033[95m"
#define INFO_COLOR                   "\033[94m"
#define SUCCESS_COLOR                "\033[92m"
#define WARN_COLOR                   "\033[93m"
#define ENDC                         "\033[0m"

#define STREAM_WRAP_ERROR_COLOR(X)   ERROR_COLOR << X << ENDC
#define STREAM_WRAP_DEBUG_COLOR(X)   DEBUG_COLOR << X << ENDC
#define STREAM_WRAP_INFO_COLOR(X)    INFO_COLOR << X << ENDC
#define STREAM_WRAP_SUCCESS_COLOR(X) SUCCESS_COLOR << X << ENDC
#define STREAM_WRAP_WARN_COLOR(X)    WARN_COLOR << X << ENDC

namespace Log {

	void Info(const std::string& text);
	void Error(const std::string& text);
	void Warn(const std::string& text);
	void Debug(const std::string& text);
	void Success(const std::string& text);

}
