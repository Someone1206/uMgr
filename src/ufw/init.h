#pragma once
#include <wx/wx.h>
#include <filesystem>

bool settings(bool* choices);

void init(bool* choices);

bool createGen(const wxString& genName);

bool createEntry(const wxString& entryName, const wxString& genName);

inline std::string getFrameTitle();