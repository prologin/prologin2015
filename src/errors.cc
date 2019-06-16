#include <sstream>

#include "errors.hh"
#include "geometry.hh"

const char* BaseException::what() const noexcept
{
    return message_.c_str();
}

InvalidPosition::InvalidPosition(const position& p)
{
    message_ = "Invalid position: " + position_str(p);
}

InvalidPlayer::InvalidPlayer(int player_id)
{
    std::ostringstream msg_stream;
    msg_stream << "Invalid player: " << player_id;
    message_ = msg_stream.str();
}
