#pragma once

#include <Card.h>

#include <json/json.h>

namespace Bang
{

namespace CardFactory
{

auto FromJson(const Json::Value &cards) -> CardPointerVector;

} // namespace CardFactory

} // namespace Bang