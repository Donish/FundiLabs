#ifndef JSON_BUILDER_CONCRETE_H
#define JSON_BUILDER_CONCRETE_H

#include <iostream>
#include <string>
#include <map>
#include "json_builder.h"

class json_builder_concrete final : public json_builder
{
private:

    std::map<std::string, logger::severity> _construction_info;

public:

    json_builder *add_stream(std::string const &json_filename) override;

    logger *construct() const override;

};

#endif