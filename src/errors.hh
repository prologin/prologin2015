#ifndef ERRORS_HH
#define ERRORS_HH

#include <exception>

#include "constant.hh"

class BaseException : public std::exception
{
public:
    virtual const char* what() const noexcept;

protected:
    std::string message_;
};

// Exception to raise when provided an invalid position.
class InvalidPosition : public BaseException
{
public:
    InvalidPosition(const position& p);
};

// Exception to raise when provided an invalid player.
class InvalidPlayer : public BaseException
{
public:
    InvalidPlayer(int player_id);
};

#endif
