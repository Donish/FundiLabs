#ifndef LOGGER_BUILDER_CONCRETE_H
#define LOGGER_BUILDER_CONCRETE_H

#include <iostream>
#include <string>
#include <map>
#include "logger_builder.h"

class logger_builder_concrete final : public logger_builder
{
private:

    std::map<std::string, logger::severity> _construction_info;

public:

    logger_builder *add_stream(std::string const &, logger::severity) override;

    logger *construct() const override;

};

#endif