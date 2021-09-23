#include "fileIO.h"

// cdf = create default directories
bool settings(bool* choices);

void init(bool* choices);

bool createGen(const wxString& genName);

bool createEntry(const wxString& entryName, const wxString& genName);