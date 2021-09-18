#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <thread>
#include <wx/wx.h>

using namespace std;

#define pr(wtf) cout << wtf
#define prl(wtf) cout << wtf << endl

#if _WIN32
#define fsep '\\'
#else
#define fsep '/'
#endif

using str = std::string;
namespace fs = std::filesystem;

static str folderN = "uMgrData";
static wxString* emptyWxStrArr{ new wxString[0] };
static ifstream emptyFile;
static wxTextCtrl* emptyText;
static str* emptyStrArr;

enum ReadOptions {
    Anime, Manga, Movies,

    Others
};

enum WriteOption
{
    Create, Add, NQuit, LogIt, NLogIt
};

enum TrackerFileOptions
{
    LogList, G_IndexerAndData, E_IndexerAndData, Entries
    // ..., Genre Indexer and data, entry indexer and data
};


// check id the string is empty or not -> is of only spaces or has nothing in it.
bool isspace(str& string1);


/*
 * Returns the number of entries and genres. 
 * pass the genre selected to get the entries in the genre. Default => uMgrData ([folderN] folder having genres)
 * pass thrue as the 2nd arg if they are entries, cuz y not?
 */
int entriesNGenres(str genre = folderN, bool isEntry = false);


void readFile(ifstream& file, ReadOptions options, wxTextCtrl* logDisp, int history = 0, bool isLLog = 0, bool clearAtS = false);


/*
 * used to read from index files and AllLogs.hentai and LastLogs.baka. 
 * Tracker File Options -->
 * 1. G_IndexerAndData and E_IndexerAndData:
 *    Both do the same and stupid stuff i.e. to index the data
 *    G for genre and E for entry
 * 2. LogList:
 *    List of all the logs done, can be last logs or all logs depending on the file passed
 */

/*
 * read from AllLogs.hentai and LastLogs.baka and (index files, that'll never come, impossibe dreams)
 */
void readTrackerFile(ifstream& file = emptyFile, TrackerFileOptions tfo = LogList, wxTextCtrl* logDisp = emptyText, int history = 0, wxString* list = emptyWxStrArr, str dest = folderN, bool fullName = false, str* listFP = emptyStrArr);



bool readTrackerFile(ifstream& file, bool* choices); // only for settings.baka



// write to files
void writeFile(str paf, str& data, str genre = "Anime", int option = Create, str name = "");
// write to setting file
void writeFile(bool* choices, str paf = (folderN + fsep + "Settings.baka"));`
