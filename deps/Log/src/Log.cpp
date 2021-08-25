#include "Log.hpp"

namespace Log {
	void Info(const char* text) {
		std::cout << "[" << STREAM_WRAP_INFO_COLOR("INFO") << "] " << text
			  << std::endl;
	}
	void Error(const char* text) {
		std::cout << "[" << STREAM_WRAP_ERROR_COLOR("ERROR") << "] "
			  << STREAM_WRAP_ERROR_COLOR(text) << std::endl;
	}
	void Warn(const char* text) {
		std::cout << "[" << STREAM_WRAP_WARN_COLOR("WARN") << "] " << text
			  << std::endl;
	}
	void Debug(const char* text) {
		std::cout << "[" << STREAM_WRAP_DEBUG_COLOR("DEBUG") << "] "
			  << STREAM_WRAP_DEBUG_COLOR(text) << std::endl;
	}
	void Success(const char* text) {
		std::cout << "[" << STREAM_WRAP_SUCCESS_COLOR("SUCCESS") << "] " << text
			  << std::endl;
	}

	void Info(const std::string& text) {
		std::cout << "[" << STREAM_WRAP_INFO_COLOR("INFO") << "] " << text
			  << std::endl;
	}
	void Error(const std::string& text) {
		std::cout << "[" << STREAM_WRAP_ERROR_COLOR("ERROR") << "] "
			  << STREAM_WRAP_ERROR_COLOR(text) << std::endl;
	}
	void Warn(const std::string& text) {
		std::cout << "[" << STREAM_WRAP_WARN_COLOR("WARN") << "] " << text
			  << std::endl;
	}
	void Debug(const std::string& text) {
		std::cout << "[" << STREAM_WRAP_DEBUG_COLOR("DEBUG") << "] "
			  << STREAM_WRAP_DEBUG_COLOR(text) << std::endl;
	}
	void Success(const std::string& text) {
		std::cout << "[" << STREAM_WRAP_SUCCESS_COLOR("SUCCESS") << "] " << text
			  << std::endl;
	}
}
