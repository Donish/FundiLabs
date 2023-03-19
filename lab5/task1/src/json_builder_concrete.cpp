#include "json_builder_concrete.h"
#include "logger_concrete.h"

json_builder* json_builder_concrete::add_stream(const std::string& json_filename)
{
    std::ifstream fin(json_filename);
    auto data = nlohmann::json::parse(fin);
    auto pairs = data["logger"];

    for(auto& elem : pairs){
        _construction_info[elem.value("file", "Not found!")] = elem["severity"];
    }

    return this;
}

logger *json_builder_concrete::construct() const
{
    return new logger_concrete(_construction_info);
}