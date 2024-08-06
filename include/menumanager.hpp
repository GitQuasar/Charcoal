#pragma once

#include "../include/pdcurses/curses.h"

#include <string>
#include <vector>
#include <functional>

class Entry
{
public:
  // Constructors/Destructors
  Entry(const std::string &title, std::function<void()> function = nullptr);
  // Getters/Setters
  const std::string &GetTitle() const;
  const std::vector<Entry> &GetSubentries() const;
  void SetTitle(const std::string &title);
  void SetSubentry(const Entry &subentry);
  // Methods
  void ExecuteFunction() const;
protected:
  std::vector<Entry> m_Subentries;
private:
  std::string m_Title;
  std::function<void()> m_Function;
};

class Menu
{
public:
  // Constructors/Destructors
  Menu();
  // Getters/Setters
  void SetEntry(const Entry &entry);
  // Methods
  void Navigate(int x, int y);

private:
  int m_Selection;
  std::vector<Entry> m_Entries;
  // Methods
  void GoUp() { m_Selection--; }
  void GoDown() { m_Selection++; }
  void HandleSubMenu(int x, int y, const Entry &entry);
  void DisplayEntries(int x, int y);
};