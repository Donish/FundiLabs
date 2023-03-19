#ifndef JSON_BUILDER_H
#define JSON_BUILDER_H

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include "logger.h"
#include "../json-developer/single_include/nlohmann/json.hpp"

class json_builder
{
public:

    virtual json_builder *add_stream(std::string const &) = 0;
    virtual logger *construct() const = 0;

public:

    virtual ~json_builder();

};

#endif