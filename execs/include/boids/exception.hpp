#pragma once

#include <exception>
#include <string>

class Exception : public std::exception
{
public:
    Exception(std::string msg) : _msg(msg)
    {
    }

    virtual const char* what() const throw()
    {
        return _msg.c_str();
    }

private:
    const std::string _msg;
};