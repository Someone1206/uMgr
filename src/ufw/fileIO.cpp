#include <wx/wx.h>
#include "fileIO.h"

inline void reportErr(std::string msg = "Error", std::string title = "Error", int styles = wxOK | wxICON_ERROR)
{
    wxMessageBox(msg, title, styles);
}

inline bool isspace(std::string string1)
{
    unsigned int len = string1.length();
    for (unsigned int i = 0; i < len; ++i)
    {
        char c = string1.at(i);
        if (!(isspace(c) || c == '　'))
            return false;
    }
    return true;
}

/* ******************************************************************************
 *
 * How the file will be read (this is bound to change):
 * <!-- Others:  distinguished by file names-->
 * <name>
 * (char)1
 * <date>
 * <time>
 * <details> ...optional
 * (char)1
 * <date>
 * <time>
 * <details> ...optional
 *
 * <!-- Anime -->
 * <name>
 * (char)1
 * <date>
 * <time>
 * <season>  ...optional
 * <episode> ...optional
 * <details> ...optional
 * (char)1
 *
 * <!-- Manga -->
 * <name>
 * (char)1
 * <date>
 * <time>
 * <chapter> ...optional
 * <page>    ...optional
 * <details> ...optional
 * (char)1
 *
 * <!-- Movies -->
 * <name>
 * (char)1
 * <date>
 * <time>
 * <part>    ...optional
 * <details> ...optional
 * (char)1
 *
 *
 * <!-- Tracker File Formats --!>
 * M --> the second part(folder name/file name with baka ext.) is changeable,
 *       it can hold the relative path(preferred and default) or you can change them,
 *       to meet your needs {
 *       [(char)1 to be replaced with the character with value ASCII value 1]
 *          {1} like the relative path to any other genre/entry with baka ext.
 *             Eg: Date A Live(char)1..\..\personal logs\Date A Live.baka
 *             Eg: |Rosario + Vampire|(char)1..\..\Manga\_Rosario + Vampire_.baka
 *              --> \ / : | * "" < > are not allowed as per Windows 10, it also specifies ?
 *               but I've seen filenames with ?
 *             Eg: <変態>(char)1..\..\..\protected folder\hentai
 *          {2} like the absolute path
 *             Eg: Ero-Anime(char)1/home/someone/protected/super_protected/no_one_but_me/Hentai
 *             Eg: エロアニメ(char)1D:\private\protected\justMe\super protected\エロアニメ
 *       }
 * -----------------------------------------------
 * <!-- GenreIndex.baka - M ->
 * <-- list of all genres[(char)1]the actual name in the file system -->
 * -----------------------------------------------
 * <!-- EntryIndex.baka - M ->
 * <-- list of all entries[(char)1]the file name -->
 *
 *
 * <!-- Settings.baka -->
 * <choice>
 *
 *
 * <!-- LastLogs.baka (LastLogs)-->
 * (char)1
 * <genre>
 * <entry>
 * (char)1
 * (char)1
 * ...
 * ...
 * ...
 * ... shows last 10 logs
 *
 * <!-- AllLogs.hentai -->
 * <-- may be really memory intensive -->
 * (char)1
 * <genre>
 * <entry>
 * (char)1
 * (char)1
 * ...
 * ...
 * ...
 * ... stores and may show all logs
 *
 *
 * ******************************************************************************
 */


int entriesNGenres(std::string genre, bool isEntry)
{
    int i = 0;
    for (auto& gen : std::filesystem::directory_iterator(genre))
        if (gen.is_directory() == !isEntry)
            i++;
    return i;
}

void mt_Field(const wxString& data, wxTextCtrl* logDisp)
{
    if (data == "")
    {
        logDisp->SetDefaultStyle(wxTextAttr(wxNullColour, wxColor(200, 200, 255)));
        (*logDisp) << "<-- Empty -->" << '\n';
        logDisp->SetDefaultStyle(wxTextAttr(wxNullColour));
        return;
    }
    (*logDisp) << data << '\n';
}

void readFile(std::ifstream& file, ReadOptions options, wxTextCtrl* logDisp, int history, bool isLLog, bool clearAtS) {

    if (!file.is_open()) {
        reportErr("Can't open file");
        return;
    }

    if (file.peek() == std::ifstream::traits_type::eof()) {
        std::string str = "";
        mt_Field(str, logDisp);
        return;
    }

    std::string line = "";
    int counter = 0;
    bool hasContent = false;

    if (clearAtS)
        logDisp->Clear();

    /*
    history = (bool)history * history + ((!(bool)history) * -1) + (((bool)history) * 1);
    /*
     * ☝☝this takes avg. of 1000 μs when numbers are between 0 and 50
     *
     *
     * if (history > 0)
     *     history++;
     * else
     *     history = -1;
     * ☝☝ this takes avg of 1000 μs when numbers are large (>500 idk y?)
     * when 0, avg of 2100 μs is needed, therefore, its inefficient.
     *
     * here μ = https://seeklogo.com/images/M/mew-logo-8F891D0488-seeklogo.com.png
    * /
    // if history is 0, print all -> -1, else print the number of logs from first and add 1 to it
    */
    getline(file, line);
    (*logDisp) << "Name:    " << line << "\n";

    while (getline(file, line) /* && ((bool)history) */) {
        if (line.find((char)1) != std::string::npos)
        {
            if (isLLog)
                return;
            counter = 0;
            // history--;
            continue;
        }
        switch (counter) {
        case 0:
            // prl("Date:" << "\t\t" << line << '\n');
            // Display date
            (*logDisp) << "Date:    " << line << "\n";
            break;
        case 1:
            // prl("Time:" << "\t\t" << line);
            (*logDisp) << "Time:    " << line << "\n";
            break;
        default:
            switch (options) {
            case Others:
                if (counter == 2)
                    (*logDisp) << "Details and Remarks:\n";
                mt_Field(line, logDisp);
                break;
            case Anime:
                if (counter == 2)
                    (*logDisp) << "Season:    " << line << "\n";
                else if (counter == 3)
                    (*logDisp) << "Episode:    " << line << "\n";
                else {
                    if (counter == 4)
                        (*logDisp) << "Details and Remarks:\n";
                    mt_Field(line, logDisp);
                }
                break;

            case Manga:
                if (counter == 2)
                    (*logDisp) << "Last Chapter read:    " << line << "\n";
                else if (counter == 3)
                    (*logDisp) << "Page read last:    " << line << "\n";
                else {
                    if (counter == 4)
                        (*logDisp) << "Details and Remarks:\n";
                    mt_Field(line, logDisp);
                }
                break;

            case Movies:
                if (counter == 2 && line != "") // if not empty
                    (*logDisp) << "Part Last seen:    " << line << "\n";
                else {
                    if (counter == 3)
                        (*logDisp) << "Details and Remarks:" << "\n";
                    mt_Field(line, logDisp);
                }
            }
            hasContent = true;
        }
        counter++;
    }
    if (!hasContent)
        (*logDisp) << "No Logs Made";
    if (clearAtS)
        logDisp->SetInsertionPoint(0);
    logDisp = nullptr;
}

void readTrackerFile(std::ifstream& file, TrackerFileOptions tfo, wxTextCtrl* logDisp, int history,
    wxString* list, std::string dist, std::string* listFP) {

    if (logDisp != nullptr && tfo == LogList)
        logDisp->Clear();
    else {
        reportErr("logDisp is nullptr in readTrackerFile");
        return;
    }

    std::string line = "";

    switch (tfo) {
    case G_IndexerAndData:
    case E_IndexerAndData:
    {
        std::string line = "";
        int index = 0, i = 0;
        while (getline(file, line))
        {
            index = line.find_last_of(FSEP);
            listFP[i] = line.substr(index + 1);
            list[i++] = line.substr(0, index);
        }
    }
    break;
    case Entries:
    {
        int i = 0;
        for (auto& entry : std::filesystem::directory_iterator(dist))
            if (!entry.is_directory()) {
                std::string temp = entry.path().filename().string();
                list[i] = temp.substr(0, temp.length() - 5);
                listFP[i] = entry.path().string();
                i++;
            }
    }
    break;
    case LogList:
    {
        if (!file.is_open()) {
            reportErr("Can't open log file -> Log List -> Read Tracker file");
            return;
        }
        bool isGenN = 0;
        while (getline(file, line)) {
            if (line.find((char)1) != std::string::npos) {
                isGenN = 1;
                continue;
            }
            if (isGenN) {
                (*logDisp) << line << "\n--------------------\n";
                if (line.find("Anime") == 0)
                    readFile(file, Anime, logDisp, 1, 1);
                else if (line.find("Manga") == 0)
                    readFile(file, Manga, logDisp, 1, 1);
                else if (line.find("Movies") == 0)
                    readFile(file, Movies, logDisp, 1, 1);
                else
                    readFile(file, Others, logDisp, 1, 1);
                (*logDisp) << "====================\n";
            }
            isGenN *= 0;
        }
    }
    break;
    default:
    {
        reportErr("We've (rather I have) encountered some problems"
            " while parsing the source code. "
            "The devs have made some problems. You can"
            " edit the src yourself, or wait for it to be fixed by the dev or cry (the best option)"
            );
    }
    }
    logDisp->SetInsertionPoint(0);
}

