#pragma once
#include <fstream>
#include <wx\wx.h>
#include <optional>
#include "GV.h"

/// <summary>
/// How to read from log files  
/// Actually it also affects the way data is formatted in the display
/// 1. Anime: Read in as if its Anime log (Also includes ero-anime(a.k.a Hentai) cuz its also anime)
/// 2. Manga: for manga
/// 3. Movies: for movies
/// 4. Others: for other genres
/// </summary>
enum ReadOptions {
    Anime, Hentai, Ero_Anime, // for Anime. Last 2 are the same tho... and are interchangeable
    Series,                   // Added series, for series... Has the same formatting as Anime
    Manga, Movies,
    Diary,                    // Diary format...
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
    Create, Add, NQuit,

    Preferences  // only to be used in 1 fn --> indexData
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

// check if the string is empty or not -> is of only spaces or has nothing
// in it.
inline bool isspace(const std::string& string1);

/*
 * Returns the number of entries and genres.
 * pass the genre selected to get the entries in the genre
 * pass thrue as the 2nd arg if they are entries, cuz y not?
 * Pass the type as string& or string&&
 */
template<typename Type>
int entriesNGenres(Type genre, bool isEntry = false);

/// <summary>
/// Read from files
/// </summary>
/// <param name="file"> = The file to read from</param>
/// <param name="options"> = The read option</param>
/// <param name="logDisp"> = The log to display it to</param>
/// <param name="history"> = The no of logs to show, 0 for all, Its not used now</param>
/// <param name="clearAtS"> = Clear the display when calling this fn (dosen't work now)</param>
void readFile(std::ifstream& file, ReadOptions options,
    wxTextCtrl* logDisp, int history = 0, bool clearAtS = false);

/// <summary>
/// Read from tracker files like GenreIndex.baka, EntryIndex.baka,
/// AllLogs.hentai and LastLogs.baka
/// </summary>
/// <param name="file"> = The file to read from</param>
/// <param name="tfo"> = Tracker File Options -> is it Index or Log file</param>
/// <param name="logDisp"> = The the text ctrl to which it is to be shown</param>
/// <param name="history"> = The depth to look into the file. The number of logs to read>/param>
/// <param name="list"> = The list of display names from the index files</param>
/// <param name="dest"> = The folder to look into. Depricated, don't use</param>
/// <param name="listFP"> = String array for the full path</param>
void readTrackerFile(std::ifstream& file, 
    TrackerFileOptions tfo = LogList, wxTextCtrl* logDisp = nullptr,
    int history = 0, wxString* list = nullptr, 
    std::string dest = uFolder, 
    std::string* listFP = nullptr);

/// <summary>
/// To read settings from settings file
/// </summary>
/// <param name="file"> = Ptr to the file to read, nullptr for default -> Settings.baka in uFolder</param>
/// <param name="choices"> = Array of choices, bool</param>
std::optional<bool> readTrackerFile(std::ifstream& file, bool (&choices)[SET_NO]);


/// <summary>
/// Write to log files
/// </summary>
/// <typeparam name="Type_paf"> : The path type, either std::string& or std::string&&</typeparam>
/// <typeparam name="Type_data"> : The data type, either std::string& or std::string&&</typeparam>
/// <param name="paf"> = Path of the Entry.</param>
/// <param name="data"> = The data to be written, Needs to be pre formatted</param>
/// <param name="genre"> = The genre of the entry, needed for log summary</param>
/// <param name="option"> = Create only or add a log</param>
/// <param name="name"> = The ctual name of the entry</param>
template<typename Type_paf, typename Type_data>
void writeFile(Type_paf paf, Type_data data, int option = Create, const std::string& name = "");


// write to setting file
void writeFile(bool(&choices)[SET_NO], std::string&& paf = (uFolder + FSEP + "Settings.baka"));

/// <summary>
/// index genre or entry
/// </summary>
/// <typeparam name="Type_paf"> : The path type, either std::filesystem::path & or &&</typeparam>
/// <param name="tfo">: Index option, either G_IndexerAndData, E_IndexerAndData, Preferences, with RE_CONST or _CONST</param>
/// <param name="paf">: The path to file</param>
template<typename Type_paf>
void indexData(int options, Type_paf paf = "");