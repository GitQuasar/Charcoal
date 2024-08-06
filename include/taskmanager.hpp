#pragma once

#include "jsonbase.hpp"

#include <vector>

class Task : public JsonBase
{
public:
  // Constructors/Destructors 
  Task();
  Task(const std::string &title, const std::string &desc, const std::string &status, const std::string &creation_date);
  virtual ~Task();
  // Getters/Setters
  const std::string &GetTitle() const;
  const std::string &GetDescription() const;
  const std::string &GetStatus() const;
  const std::string &GetCreationDate() const;
  void SetTitle(const std::string &title);
  void SetDescription(const std::string &desc);
  void SetStatus(const std::string &status);
  void SetCreationDate(const std::string &creation_date);
  // Methods
  virtual bool Deserialize(const rapidjson::Value &obj);
  virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer> *writer) const;
private:
  std::string m_Title;
  std::string m_Description;
  std::string m_Status;
  std::string m_CreationDate;
};

class Tasks : public JsonBase
{
public:
  // Constructors/Destructors
  Tasks();
  virtual ~Tasks() {};
  // Getters/Setters
  std::vector<Task> &GetTasks() { return m_Tasks; }
  void SetTask(const std::string &title, const std::string &desc, const std::string &status, const std::string &creation_date);
  // Methods
  void DeleteTask(int ind);
  virtual bool Deserialize(const std::string &s);
  virtual bool Deserialize(const rapidjson::Value &obj) { return false; };
  virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer> *writer) const;

private:
  std::vector<Task> m_Tasks;
};