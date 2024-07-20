#include <JsonUtils.h>

#include <Exception.h>

#include <format>

#include <json/json.h>

#include <fstream>
#include <iostream>

namespace Utils
{

auto ParseJsonFromFile(const std::string &pathToFile) -> Json::Value
{
  std::ifstream file(pathToFile);
  if (!file.is_open())
    throw Utils::Exception{ std::format("File {} couldn't be opened to read json,", pathToFile) };

  Json::Reader r;
  Json::Value jsonRoot;
  if (!r.parse(file, jsonRoot, false))
    throw Utils::Exception{ std::format("File {} didn't contain valid json.", pathToFile) };

  return jsonRoot;
}

} // namespace Utils