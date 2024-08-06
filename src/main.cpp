#define FMT_HEADER_ONLY
#include "../include/fmt/core.h"
#include "../include/fmt/chrono.h"
#include "../include/taskmanager.hpp"
#include "../include/menumanager.hpp"

const char *STATUS_COMPLETE = "Complete";
const char *STATUS_INCOMPLETE = "Incomplete";

void Foo1(int x)
{
  clear();
  mvprintw(0, 20, "Foo1");
  refresh();
  getch();
  clear();
}
std::string Align(std::string s, int width)
{
  return s.length() > width ? s.substr(0, width - 4).append("... ") : s.append(width - s.length(), ' ');
}
void AddNewTask(Tasks &taskmngr)
{
  char tBuffer[256];
  char dBuffer[256];
  clear();
  echo();
  mvprintw(0, 0, "# New task #");
  mvprintw(1, 0, "Title:");
  mvgetstr(1, 7, tBuffer);
  if (strlen(tBuffer) == 0)
  {
    mvprintw(2, 0, "Task wasn't created: no title provided.");
    mvprintw(3, 0, "Press any key to return.");
  }
  else
  {
    mvprintw(2, 0, "Description:");
    mvgetstr(2, 13, dBuffer);
    taskmngr.SetTask(tBuffer, dBuffer, STATUS_INCOMPLETE, fmt::format("{:%Y-%m-%d %H:%M:%S}", fmt::localtime(std::time(nullptr))));
    mvprintw(3, 0, "Task created.");
    mvprintw(4, 0, "Press any key to return.");
  }
  refresh();
  getch();
  clear();
}
void ChangeTaskTitle(Task &task)
{
  clear();
  echo();
  mvprintw(0, 0, "New title:");
  char buffer[256];
  mvgetstr(0, 11, buffer);
  task.SetTitle(buffer);
  mvprintw(1, 0, "Title changed.");
  mvprintw(2, 0, "Press any key to return.");
  refresh();
  noecho();
  getch();
  clear();
}
void ChangeTaskDescription(Task &task)
{
  clear();
  echo();
  mvprintw(0, 0, "New description:");
  char buffer[256];
  mvgetstr(0, 17, buffer);
  task.SetDescription(buffer);
  mvprintw(1, 0, "Description changed.");
  mvprintw(2, 0, "Press any key to return.");
  refresh();
  noecho();
  getch();
  clear();
}
void ChangeTaskStatus(Task &task)
{
  clear();
  task.GetStatus() == STATUS_INCOMPLETE ? task.SetStatus(STATUS_COMPLETE) : task.SetStatus(STATUS_INCOMPLETE);

  mvprintw(0, 0, "Status was changed to [%s].", task.GetStatus().c_str());
  mvprintw(1, 0, "Press any key to return.");
  refresh();
  getch();
  clear();
}

bool TasksEmptyCheck(std::vector <Task> &vTask)
{
  if (vTask.size() == 0)
  {
    clear();
    mvprintw(0, 0, "No tasks to display.");
    mvprintw(1, 0, "Press any key to return.");
    refresh();
    getch();
    clear();
    return true;
  }
  return false;
}
void ViewTaskTable(int x, int y, std::vector<Task> vTask, int tabW, int tableW, int startR, int curR, int maxRpPage)
{
  clear();
  int toDraw = std::min(startR + maxRpPage, (int)vTask.size());
  std::string separator(tableW, '-');
  mvprintw(x, y, ("|" + separator + "|").c_str()); // Draw table separator
  mvprintw(x + 1, y + tabW * 0, "| Title");
  mvprintw(x + 1, y + tabW * 1, "| Description");
  mvprintw(x + 1, y + tabW * 2, "| Creation date");
  mvprintw(x + 1, y + tabW * 3, ("| " + Align("Status", tabW) + " |").c_str());
  mvprintw(x + 2, y, ("|" + separator + "|").c_str());
  for (int i = startR; i < toDraw; i++) // Draw current <maxRpPage> rows
  {
    mvprintw(x + i - startR + 3, y + tabW * 0, ("| " + Align(vTask[i].GetTitle(), tabW)).c_str());
    mvprintw(x + i - startR + 3, y + tabW * 1, ("| " + Align(vTask[i].GetDescription(), tabW)).c_str());
    mvprintw(x + i - startR + 3, y + tabW * 2, ("| " + Align(vTask[i].GetCreationDate(), tabW)).c_str());
    mvprintw(x + i - startR + 3, y + tabW * 3, ("| " + Align(vTask[i].GetStatus(), tabW) + " |").c_str());
  }
  attron(A_REVERSE);  // ON Highlight ; Highlight selected row
  mvprintw(x + curR - startR + 3, y + tabW * 0, ("| " + Align(vTask[curR].GetTitle(), tabW)).c_str());
  mvprintw(x + curR - startR + 3, y + tabW * 1, ("| " + Align(vTask[curR].GetDescription(), tabW)).c_str());
  mvprintw(x + curR - startR + 3, y + tabW * 2, ("| " + Align(vTask[curR].GetCreationDate(), tabW)).c_str());
  mvprintw(x + curR - startR + 3, y + tabW * 3, ("| " + Align(vTask[curR].GetStatus(), tabW) + " |").c_str());
  attroff(A_REVERSE); // OFF Highlight 

  mvprintw(x + toDraw - startR + 3, y, ("|" + separator + "|").c_str());
  mvprintw(x + toDraw - startR + 4, y, "[Up], [Down] - navigate");
  mvprintw(x + toDraw - startR + 5, y, "[Enter] - view details");
  mvprintw(x + toDraw - startR + 6, y, "[Esc] - return");
  refresh();
}
void ViewTaskDetails(const Task &tData)
{
  clear();
  mvprintw(0, 0, "Task info:");
  mvprintw(1, 0, "Title: %s", tData.GetTitle().c_str());
  mvprintw(2, 0, "Description: %s", tData.GetDescription().c_str());
  mvprintw(3, 0, "Creation date: %s", tData.GetCreationDate().c_str());
  mvprintw(4, 0, "Status: %s", tData.GetStatus().c_str());
  // mvprintw(5, 0, "Press any key to return...");
  refresh();
  // getch();
}
void ViewTasks(std::vector<Task> &vTask)
{
  if (TasksEmptyCheck(vTask)) { return; }

  int maxRpPage = 10;
  int curR = 0;
  int startR = 0;

  ViewTaskTable(0, 0, vTask, 25, 102, startR, curR, maxRpPage); // Draw table
  Menu taskOptions;
  taskOptions.SetEntry(
    Entry("Change title", [&]() { ChangeTaskTitle(vTask[curR]); ViewTaskDetails(vTask[curR]); }));
  taskOptions.SetEntry(
    Entry("Change description", [&]() { ChangeTaskDescription(vTask[curR]); ViewTaskDetails(vTask[curR]); }));
  taskOptions.SetEntry(
    Entry("Change status", [&]() { ChangeTaskStatus(vTask[curR]); ViewTaskDetails(vTask[curR]); }));

  while (true)
  {
    int ch = getch();
    switch (ch)
    {
    case KEY_UP: // Arrov 'Up', Upper boundry
      if ((curR > 0) && (--curR < startR)) { startR--; }
      break;
    case KEY_DOWN: // Arrow 'Down', Lower boundry
      if ((curR < vTask.size() - 1) && (++curR >= startR + maxRpPage)) { startR++; }
      break;
    case '\n': // 'Enter', Show details
    {
      ViewTaskDetails(vTask[curR]); // View task details
      taskOptions.Navigate(7, 1); // Show (draw) task options after
      ViewTaskTable(0, 0, vTask, 25, 102, startR, curR, maxRpPage);
    }
    }
    if (ch == 27) { clear(); break; } // '27', Escape
    ViewTaskTable(0, 0, vTask, 25, 102, startR, curR, maxRpPage);
  }
}
void RemoveTasks(Tasks &taskmngr, std::vector<Task> &vTask)
{
  int maxRpPage = 10;
  int curR = 0;
  int startR = 0;
  if (TasksEmptyCheck(vTask)) { return; }

  while (true)
  {
    ViewTaskTable(0, 0, vTask, 25, 102, startR, curR, maxRpPage); // Draw table
    int ch = getch();
    switch (ch)
    {
    case KEY_UP: // Arrov 'Up', Upper boundry
      if ((curR > 0) && (--curR < startR)) { startR--; }
      break;
    case KEY_DOWN: // Arrow 'Down', Lower boundry
      if ((curR < vTask.size() - 1) && (++curR >= startR + maxRpPage)) { startR++; }
      break;
    }
    if (ch == '\n') // 'Enter', Delete selected task
    {
      clear();
      taskmngr.DeleteTask(curR);
      mvprintw(0, 0, "Task was succesfully deleted.");
      mvprintw(1, 0, "Press any key to return.");
      refresh();
      getch();
      clear();
      if (!(vTask.size() == 0)) { if (curR == vTask.size()) { curR--; } }
      else { break; }
    }
    if (ch == 27) { clear(); break; } // '27', Escape
    ViewTaskTable(0, 0, vTask, 25, 102, startR, curR, maxRpPage);
  }
}

int main()
{
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  Tasks TaskData; // Load tasks from JSON file
  TaskData.DeserializeFromFile("tasksdb.json");

  Menu mainMenu;
  mainMenu.SetEntry(Entry("View tasks", [&]() { ViewTasks(TaskData.GetTasks()); }));
  mainMenu.SetEntry(Entry("Add task", [&]() { AddNewTask(TaskData); }));
  mainMenu.SetEntry(Entry("Remove task", [&]() { RemoveTasks(TaskData, TaskData.GetTasks()); }));
  mainMenu.Navigate(0, 0);

  TaskData.SerializeToFile("tasksdb.json");
}