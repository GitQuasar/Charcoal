#include "../include/taskmanager.hpp"

#include <string>

// ========== START Task class function definitions ========== //
Task::Task(const std::string &title, const std::string &desc, const std::string &status, const std::string &creation_date) :
  m_Title(title), m_Description(desc), m_Status(status), m_CreationDate(creation_date)
{}
Task::Task() :
  m_Title(""), m_Description(""), m_Status(""), m_CreationDate("")
{}
Task::~Task() {}

const std::string &Task::GetTitle() const { return m_Title; }
const std::string &Task::GetDescription() const { return m_Description; }
const std::string &Task::GetStatus() const { return m_Status; }
const std::string &Task::GetCreationDate() const { return m_CreationDate; }
void Task::SetTitle(const std::string &title) { m_Title = title; }
void Task::SetDescription(const std::string &desc) { m_Description = desc; }
void Task::SetStatus(const std::string &status) { m_Status = status; }
void Task::SetCreationDate(const std::string &creation_date) { m_CreationDate = creation_date; }

// Deserialize a single object from JSON-formatted string
bool Task::Deserialize(const rapidjson::Value &obj)
{
  SetTitle(obj["title"].GetString());
  SetDescription(obj["desc"].GetString());
  SetStatus(obj["status"].GetString());
  SetCreationDate(obj["creation_date"].GetString());
  return true;
}

// Serialize a single object to JSON-formatted string
bool Task::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer> *writer) const
{
  writer->StartObject();
  writer->String("title");        // create "title" property
  writer->String(m_Title.c_str()); // write the "title" value from the object instance
  writer->String("desc");
  writer->String(m_Description.c_str());
  writer->String("status");
  writer->String(m_Status.c_str());
  writer->String("creation_date");
  writer->String(m_CreationDate.c_str());
  writer->EndObject();
  return true;
}
// ========== END Task class function definitions ========== //

// ========== START Tasks class function definitions ========== //
Tasks::Tasks() { m_Tasks.reserve(128); }

void Tasks::SetTask(const std::string &title, const std::string &desc, const std::string &status, const std::string &creation_date)
{
  m_Tasks.emplace_back(title, desc, status, creation_date);
}

void Tasks::DeleteTask(int ind) { m_Tasks.erase(m_Tasks.begin() + ind); }

// Deserialize all objects from JSON-formatted string
bool Tasks::Deserialize(const std::string &s)
{
  rapidjson::Document doc;
  if (!InitDocument(s, doc)) { return false; }
  if (!doc.IsArray()) { return false; }
  m_Tasks.clear();
  for (rapidjson::Value::ConstValueIterator itr = doc.Begin(); itr != doc.End(); ++itr)
  {
    Task task;
    task.Deserialize(*itr);
    m_Tasks.push_back(task);
  }
  return true;
}

// Serialize all object to JSON-formatted string
bool Tasks::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer> *writer) const
{
  writer->StartArray();
  for (std::vector<Task>::const_iterator it = m_Tasks.begin(); it != m_Tasks.end(); it++) { (*it).Serialize(writer); }
  writer->EndArray();
  return true;
}
// ========== END Tasks class function definitions ========== //