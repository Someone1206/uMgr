#pragma once
#include <wx/wx.h>
#include <filesystem>
#include "GV.h"

bool settings(bool(&choices)[SET_NO]);

void init(bool(&choices)[SET_NO]);

bool createGen(const wxString& genName);

bool createEntry(const wxString& entryName, const wxString& genName);

inline std::string getFrameTitle();