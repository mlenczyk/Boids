#pragma once

#include <exception>
#include <string_view>

class Exception : public std::exception
{
public:
    Exception(std::string_view msg) : _msg(msg)
    {
    }

    virtual const char* what() const throw()
    {
        return _msg.data();
    }

private:
    const std::string_view _msg;
};