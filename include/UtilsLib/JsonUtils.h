#pragma once

#include <json/json.h>

#include <format>

namespace Utils
{

auto ParseJsonFromFile(const std::string &pathToFile) -> Json::Value;

} // namespace Utils

template<>
struct std::formatter<Json::ValueType> : public std::formatter<std::string_view>
{
  auto format(const Json::ValueType& valueType, std::format_context& ctx)
  {
    std::string temp;
    switch (valueType)
    {
      case Json::ValueType::arrayValue:
        temp = "array";
        break;
      case Json::ValueType::booleanValue:
        temp = "bool";
        break;
      case Json::ValueType::intValue:
        temp = "int";
        break;
      case Json::ValueType::nullValue:
        temp = "null";
        break;
      case Json::ValueType::objectValue:
        temp = "object";
        break;
      case Json::ValueType::realValue:
        temp = "real";
        break;
      case Json::ValueType::stringValue:
        temp = "string";
        break;
      case Json::ValueType::uintValue:
        temp = "uint";
        break;
    }

    return std::format_to(ctx.out(), "{}", temp);
  }
};
