#pragma once

namespace Utils
{

class SDL
{
public:
  SDL();
  ~SDL();
  SDL(const SDL &) = delete;
  SDL(SDL &&) = delete;

public:
  auto operator=(const SDL &) -> const SDL & = delete;
  auto operator=(SDL &&) -> const SDL & = delete;
};

} // namespace Utils