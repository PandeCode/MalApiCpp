#include "malapi/clientTypes.hpp"

#include "nlohmann/json.hpp"

#define NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_NON_INLINE(Type, ...)                         \
	void to_json(nlohmann::json& nlohmann_json_j, const Type& nlohmann_json_t) {     \
		NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(NLOHMANN_JSON_TO, __VA_ARGS__)) \
	}                                                                                \
	void from_json(const nlohmann::json& nlohmann_json_j, Type& nlohmann_json_t) {   \
		NLOHMANN_JSON_EXPAND(                                                    \
		    NLOHMANN_JSON_PASTE(NLOHMANN_JSON_FROM, __VA_ARGS__))                \
	}

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_NON_INLINE(
    UserObject,
    id,
    birthday,
    joined_at,
    location,
    name);
