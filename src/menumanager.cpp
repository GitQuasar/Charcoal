#include "../include/menumanager.hpp"

// ========== START Entry class function definitions ========== //
Entry::Entry(const std::string &title, std::function<void()> function) : m_Title(title), m_Function(function)
{}

const std::string &Entry::GetTitle() const { return m_Title; }
const std::vector<Entry> &Entry::GetSubentries() const { return m_Subentries; }
void Entry::SetTitle(const std::string &title) { m_Title = title; }
void Entry::SetSubentry(const Entry &subentry) { m_Subentries.push_back(subentry); }

void Entry::ExecuteFunction() const { if (m_Function) { m_Function(); } }
// ========== END Entry class function definitions ========== //

// ========== START Menu class function definitions ========== //
Menu::Menu() : m_Selection(0) {}

void Menu::SetEntry(const Entry &entry) { m_Entries.push_back(entry); }

void Menu::DisplayEntries(int x, int y)
{
  for (size_t i = 0; i < m_Entries.size(); ++i)
  {
    if (i == m_Selection) { attron(A_REVERSE); } // ON Highlight the current selection
    mvprintw(x + i, y, ("[%d] - " + m_Entries[i].GetTitle()).c_str(), i);
    // mvprintw(x + i, y + 30, "[%d][%d][%d] - I, Selection, Size", i, m_Selection, (int)m_Entries.size());
    if (i == m_Selection) { attroff(A_REVERSE); } // OFF Highlight the current selection
  }
  mvprintw(x + m_Entries.size() + 1, y, "[Up], [Down] - navigate");
  mvprintw(x + m_Entries.size() + 2, y, "[Enter] - select");
  mvprintw(x + m_Entries.size() + 3, y, "[Esc] - return");
  refresh();
}

void Menu::Navigate(int x, int y)
{
  int ch;
  while (true)
  {
    DisplayEntries(x, y);
    ch = getch();
    switch (ch)
    {
    case KEY_UP:
      if (m_Selection > 0) { GoUp(); }
      break;
    case KEY_DOWN:
      if (m_Selection < (int)(m_Entries.size()) - 1) { GoDown(); }
      break;
    case '\n': // Enter key
      if (!m_Entries[m_Selection].GetSubentries().empty()) { HandleSubMenu(x, y, m_Entries[m_Selection]); }
      else { m_Entries[m_Selection].ExecuteFunction(); }
      break;
    case 27: // Escape key
      return;
    }
  }
}

void Menu::HandleSubMenu(int x, int y, const Entry &entry)
{
  Menu subMenu;
  for (const auto &subentry : entry.GetSubentries()) { subMenu.SetEntry(subentry); }
  subMenu.Navigate(x, y);
}
// ========== END Menu class function definitions ========== //