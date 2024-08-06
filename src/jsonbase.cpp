#include "../include/jsonbase.hpp"

#include <string>
#include <fstream>
#include <sstream>

// ========== START JsonBase class function definitions ========== //
std::string JsonBase::Serialize() const
{
  rapidjson::StringBuffer buffer;
  rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
  return Serialize(&writer) ? buffer.GetString() : "";
}

bool JsonBase::Deserialize(const std::string &s)
{
  rapidjson::Document doc;
  if (!InitDocument(s, doc)) { return false; }
  Deserialize(doc);
  return true;
}

bool JsonBase::InitDocument(const std::string &s, rapidjson::Document &doc)
{
  if (s.empty()) { return false; }
  std::string validJson(s);
  return !doc.Parse(validJson.c_str()).HasParseError() ? true : false;
}

bool JsonBase::DeserializeFromFile(const std::string &filepath)
{
  std::ifstream f(filepath);
  std::stringstream buffer;
  buffer << f.rdbuf();
  f.close();
  return Deserialize(buffer.str());
}

bool JsonBase::SerializeToFile(const std::string &filepath)
{
  std::ofstream f(filepath);
  std::string s = Serialize();
  f << s;
  f.flush();
  f.close();
  return true;
}
// ========== END JsonBase class function definitions ========== //
