#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>

class logger
{

public:

    enum class severity
    {
        trace,
        debug,
        information,
        warning,
        error,
        critical
    };

public:

    virtual ~logger();

public:

    virtual logger const *log(const std::string &, severity) const = 0;

};

#endif