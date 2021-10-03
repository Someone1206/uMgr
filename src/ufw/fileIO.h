#pragma once
#include <fstream>
#include <wx/wx.h>
#include "GV.h"

namespace fs = std::filesystem;

static wxString* emptyWxStrArr{ new wxString[0] };
static std::ifstream emptyFile;
static wxTextCtrl* emptyText;
static std::string* emptyStrArr;

/// <summary>
/// How to read from log files  
/// 1. Anime: Read in as if its Anime log (Also includes ero-anime(a.k.a Hentai) cuz its also anime)
/// 2. Manga: for manga
/// 3. Movies: for movies
/// 4. Others: for other genres
/// </summary>
enum ReadOptions {
    Anime, Manga, Movies,

    Others
};

/*
 * Write options for some reason
 * 1. Create: Just create an entry (NQuit is preferred to be used with it to reduce iterations.
 * 2. NQuit: Quit (idk why I added it ._.)
 * 3. Add: Add a log for the entry
 */
enum WriteOption
{
    Create, Add, NQuit
};

/*
 * Tracker File Options -->
 * 1. G_IndexerAndData and E_IndexerAndData:
 *    Both do the same and stupid stuff i.e. to index the data
 *    ( I had some really advanced and idea in mind, but found an easier one )
 * 2. LogList:
 *    List of all the logs done, can be last logs or all logs depending on the file passed
 * 3. Entries
 *    Only for entries
 */
enum TrackerFileOptions
{
    LogList, G_IndexerAndData, E_IndexerAndData, Entries
    // ..., Genre Indexer and data, entry indexer and data
};


// check id the string is empty or not -> is of only spaces or has nothing in it.
bool isspace(std::string& string1);


/*
 * Returns the number of entries and genres.
 * pass the genre selected to get the entries in the genre. Default => uMgrData ([folderN] folder having genres)
 * pass thrue as the 2nd arg if they are entries, cuz y not?
 */
int entriesNGenres(std::string genre = GV::consts::user_data_folder, bool isEntry = false);

/// <summary>
/// Read from files
/// </summary>
/// <param name="file"> = The file to read from</param>
/// <param name="options"> = The read option</param>
/// <param name="logDisp"> = The log to display it to</param>
/// <param name="history"> = The no of logs to show, 0 for all</param>
/// <param name="isLLog"> = Is the file a log summary file</param>
/// <param name="clearAtS"> = Clear the display when calling this fn (dosen't work now)</param>
void readFile(std::ifstream& file, ReadOptions options, wxTextCtrl* logDisp, int history = 0, bool isLLog = 0, bool clearAtS = false);

// Read from AllLogs.hentai and LastLogs.baka
void readTrackerFile(std::ifstream& file = emptyFile, TrackerFileOptions tfo = LogList, wxTextCtrl* logDisp = emptyText, int history = 0, wxString* list = emptyWxStrArr, std::string dest = GV::consts::user_data_folder, bool fullName = false, std::string* listFP = emptyStrArr);

// only for settings.baka
bool readTrackerFile(std::ifstream& file, bool* choices);

/// <summary>
/// Write to log files
/// </summary>
/// <param name="paf"> = Path of the Entry.</param>
/// <param name="data"> = The data to be written, Needs to be pre formatted</param>
/// <param name="genre"> = The genre of the entry, needed for log summary</param>
/// <param name="option"> = Create only or add a log</param>
/// <param name="name"> = The ctual name of the entry</param>
void writeFile(std::string paf, std::string& data, int option = Create, std::string name = "");
// write to setting file
void writeFile(bool* choices, std::string paf = (GV::consts::user_data_folder + GV::consts::fsep + "Settings.baka"));
