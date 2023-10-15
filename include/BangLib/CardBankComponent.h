#pragma once

#include <Card.h>

#include <vector>

namespace Bang
{

class CardBankComponent
{
public:
  CardBankComponent() = default;
  CardBankComponent(const CardBankComponent &) = delete;
  CardBankComponent(CardBankComponent &&) = delete;
  ~CardBankComponent() = default;

public:
  auto operator=(const CardBankComponent &) -> const CardBankComponent & = delete;
  auto operator=(CardBankComponent &&) -> const CardBankComponent & = delete;

public:
  auto LoadAllBanks(const std::string &bankDirectoryPath) -> void;

public:
  CardPointerVector characterCards;
  CardPointerVector playCards;
};

} // namespace Bang