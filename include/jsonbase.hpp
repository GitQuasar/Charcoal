#pragma once

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"     // Rapidjson's DOM-style API
#include "rapidjson/stringbuffer.h"	// Wrapper of C stream for prettywriter as output
#include "rapidjson/prettywriter.h" // JSON stringifying

class JsonBase
{
public:
  // Methods
  bool DeserializeFromFile(const std::string &filepath);
  bool SerializeToFile(const std::string &filepath);
  virtual std::string Serialize() const;
  virtual bool Deserialize(const std::string &s);
  // By declaring one of the (deserialize) functions as pure virtual (= 0), the class enforces
  // that any derived class must provide an implementation for that specific version of the (deserialize) function.
  // This is a way to ensure that derived classes conform to a common interface or contract.
  virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer> *writer) const = 0;
  virtual bool Deserialize(const rapidjson::Value &obj) = 0;
protected:
  // Methods
  bool InitDocument(const std::string &s, rapidjson::Document &doc);
};