#pragma once

#include "BangLib/Window.h"

#include <memory>

namespace Bang
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

} // namespace Bang