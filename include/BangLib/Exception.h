#pragma once

#include <string>

namespace Bang
{

/*!
* @brief A base class for exceptions.
* 
* Can be thrown directly as well (without inheriting from it).
*/
class Exception
{
public:
  Exception(const std::string &message)
    : _message {message}
  {}

public:
  auto Message() const -> const std::string
  { return _message; }

private:
  const std::string _message;
};

} // namespace Bang