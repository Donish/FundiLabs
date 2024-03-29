#include "logger_concrete.h"
#include <iostream>
#include <fstream>

std::map<std::string, std::pair<std::ofstream *, size_t> > logger_concrete::_streams =
    std::map<std::string, std::pair<std::ofstream *, size_t> >();

std::map<logger::severity, std::string> logger_concrete::_str_severity = {
    {logger::severity::trace, "trace"},
    {logger::severity::debug, "debug"},
    {logger::severity::information, "information"},
    {logger::severity::warning, "warning"},
    {logger::severity::error, "error"},
    {logger::severity::critical, "critical"}
};

logger_concrete::logger_concrete(
    std::map<std::string, logger::severity> const & targets)
{
    for (auto & target : targets)
    {
        auto global_stream = _streams.find(target.first);
        std::ofstream *stream = nullptr;

        if (global_stream == _streams.end())
        {
            if (target.first != "console")
            {
                stream = new std::ofstream;
                stream->open(target.first);
            }

            _streams.insert(std::make_pair(target.first, std::make_pair(stream, 1)));
        }
        else
        {
            stream = global_stream->second.first;
            global_stream->second.second++;
        }

        _logger_streams.insert(std::make_pair(target.first, std::make_pair(stream, target.second)));
    }
}

logger_concrete::~logger_concrete()
{
    for (auto & logger_stream : _logger_streams)
    {
        auto global_stream = _streams.find(logger_stream.first);

        if (--(global_stream->second.second) == 0)
        {
            if (global_stream->second.first != nullptr)
            {
                global_stream->second.first->flush();
                global_stream->second.first->close();
                delete global_stream->second.first;
            }

            _streams.erase(global_stream);
        }
    }
}

logger const *logger_concrete::log(
    const std::string &to_log,
    logger::severity severity) const
{
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    for (auto & logger_stream : _logger_streams)
    {
        if (logger_stream.second.second > severity)
        {
            continue;
        }

        if (logger_stream.second.first == nullptr)
        {
            std::cout << "[" << _str_severity[severity] << "]" 
            << "[" << now->tm_mday << "/" << now->tm_mon + 1 << "/" << now->tm_year + 1900 << " " 
            << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << "] " << to_log << std::endl;
        }
        else
        {
            (*logger_stream.second.first) << "[" << _str_severity[severity] << "]" 
            << "[" << now->tm_mday << "/" << now->tm_mon + 1 << "/" << now->tm_year + 1900 << " " 
            << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << "] " << to_log << std::endl;
        }
    }

    return this;
}
