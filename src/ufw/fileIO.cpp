#include <thread>
#include "fileIO.h"

inline void reportErr(std::string msg = "Error", std::string title = "Error", int styles = wxOK | wxICON_ERROR)
{
    wxMessageBox(msg, title, styles);
}

bool isspace(const std::string& string1)
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
 * <!-- Anime, Hentai, Ero-Anime, Series -->
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
 * <!-- Diary -->
 * <<-- Diary -->>
 * (char)1
 * <date>
 * <time>
 * <details> ...optional
 * (char)1
 * <date>
 * <time>
 * <details> ...optional ...
 *
 *
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
 * <-- list of all genres[(char)1]the actual name/path in the file system -->
 * -----------------------------------------------
 * <!-- EntryIndex.baka - M ->
 * <-- list of all entries[(char)1]the file path/name -->
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


template<typename Type>
inline int entriesNGenres(Type genre, bool isEntry)
{
    int i = 0;
    for (auto& gen : std::filesystem::directory_iterator(genre))
        if (gen.is_directory() == !isEntry)
            i++;
    return i;
}

void mt_field(const wxString& data, wxTextCtrl* const logDisp)
{
    if (data == "")
    {
        logDisp->SetDefaultStyle(wxTextAttr(wxNullColour, wxColor(200, 200, 255)));
        (*logDisp) << "<--Empty-->\n";
        logDisp->SetDefaultStyle(wxTextAttr(wxNullColour));
        return;
    }
    (*logDisp) << data << '\n';
}

void readFile(std::ifstream& file, ReadOptions options, wxTextCtrl* logDisp, int history, bool clearAtS)
{
    if (!file)
    {
        reportErr("Can't open file -> readFile fn");
        return;
    }
    if (file.peek() == std::ifstream::traits_type::eof()) {
        mt_field("", logDisp);
        return;
    }

    std::string line = "";
    int counter = 0;
    bool hasContent = false;

    if (clearAtS)
        logDisp->Clear();

    /*
    history = (bool)history * history + ((!(bool)history) * -1) + (((bool)history) * 1);
     *
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

    while (getline(file, line) && ((bool)history)) {
        if (line.find(SEP) != std::string::npos)
        {
            counter = 0;
            history--;
            continue;
        }
        switch (counter)
        {
        case 0:
            // first line after name is date
            // Display date
            (*logDisp) << "Date:    " << line << "\n";
            break;
        case 1:
            // line after date is time
            (*logDisp) << "Time:    " << line << "\n";
            break;
        default:
            switch (options)
            {
            case Anime:
            case Hentai:
            case Ero_Anime:
            case Series:
                if (counter == 2)
                    (*logDisp) << "Season:    " << line << "\n";
                else if (counter == 3)
                    (*logDisp) << "Episode:    " << line << "\n";
                else {
                    if (counter == 4)
                        (*logDisp) << "Details and Remarks:\n";
                    mt_field(line, logDisp);
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
                    mt_field(line, logDisp);
                }
                break;
            case Movies:
                if (counter == 2 && line != "") // if not empty
                    (*logDisp) << "Part Last seen:    " << line << "\n";
                else {
                    if (counter == 3)
                        (*logDisp) << "Details and Remarks:" << "\n";
                    mt_field(line, logDisp);
                }
            case Diary:
                mt_field(line, logDisp);
                // time and date are already printed + can't write Details and Remarks
            case Others:
                if (counter == 2)
                    (*logDisp) << "Details and Remarks:\n";
                mt_field(line, logDisp);
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
    wxString* list, std::string dest, std::string* listFP)
{
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
            index = line.find_last_of(SEP);
            listFP[i] = line.substr(index + 1);
            list[i++] = line.substr(0, index);
        }
    }
    break;
    case Entries:
    {
        int i = 0;
        for (auto& entry : std::filesystem::directory_iterator(dest))
            if (!entry.is_directory()) {
                std::string temp = entry.path().filename().string();
                list[i] = temp.substr(0, temp.length() - 4);
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
            if (line.find(SEP) != std::string::npos) {
                isGenN = 1;
                continue;
            }
            if (isGenN) {
                (*logDisp) << line << "\n--------------------\n";
                if ((line.find("Anime") == 0) ||
                    (line.find("Hentai") == 0) ||
                    (line.find("Ero-Anime") == 0) ||
                    (line.find("Series") == 0))
                    readFile(file, Anime, logDisp, 1);
                // the syntax is same for all four of 'em for now
                else if (line.find("Manga") == 0)
                    readFile(file, Manga, logDisp, 1);
                else if (line.find("Movies") == 0)
                    readFile(file, Movies, logDisp, 1);
                else if (line.find("Diary") == 0)
                    readFile(file, Diary, logDisp, 1);
                else
                    readFile(file, Others, logDisp, 1);
                (*logDisp) << "====================\n";
            }
            isGenN = 0;
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

std::optional<bool> readTrackerFile(std::ifstream& file, bool (&choices)[SET_NO])
{
    if (!file.is_open())
        return false;
    std::string tmp = "";
    char ch;
    bool isValid = false;
    for (char i = 0; i < SET_NO, getline(file, tmp); ++i) {
        ch = tmp.at(0);
        if (tmp.length() == 1 && ch >= '0' && ch <= '9')
            choices[i] = (bool)(ch - '0');
        else
            isValid = true;
    }

    if (isValid)
        return {};
    else
        return true;
}

void write_file(std::string& paf, std::string& data, std::string& xtra, bool isLog = false) {
    std::ifstream fileIN(paf);
    std::string tempFilePaf = paf + ".tmp";
    std::ofstream fileOUT(tempFilePaf);

    if (isLog)
        fileOUT << SEP << '\n';

    fileOUT << xtra << '\n';
    fileOUT << data << '\n' << SEP << '\n';

    if (!isLog)
    {
        std::string idk = "";
        getline(fileIN, idk);
    }

    {
        // copy from original to tmp
        std::string tmp = "", buff = "";
        /*
         * use getline and strings, tests show string + getline + same code below
         * complete in half the time taken as that of char* buffer and ofstream.write
         */
        while (getline(fileIN, tmp)) {
            if (buff.size() > (1024 * 70)) { // okay, 70kb I mean, how less can ur mem. be?, this may result in >200kb buffers
                fileOUT << buff << '\n';
                buff = "";
            }
            buff += (tmp + '\n');
        }
        fileOUT << buff.substr(0, buff.size() - 1); // delete the last \n
    }

    fileIN.close();
    fileOUT.close();

    std::filesystem::remove_all(paf); // remove original
    std::filesystem::rename(tempFilePaf, paf);
    // rename tmp to original
}


// write to all logs
void writeToal(std::string& data, std::string& genre) {
    std::string paf = USER_DATA + FSEP + "AllLogs.hentai";
    // write to user's data folder
    {
        std::ifstream fileR(paf);
        if (!fileR.is_open()) {
            reportErr("くそが! Can't open AllLogs.hentai ditch me", ("Can't open file: " + paf));
            return;
        }
    }

    write_file(paf, data, genre, true);
}


// write to last logs
void writeToll(std::string& data, std::string& genre) {
    std::string paf = USER_DATA + FSEP + "LastLogs.baka";
    // write to users data folder
    {
        std::ifstream fileR(paf);
        if (!fileR.is_open()) {
            reportErr("くそが! Can't open AllLogs.hentai ditch me", ("Can't open file: " + paf));
            return;
        }
    }

    write_file(paf, data, genre, true);
}

void writeFile(std::string paf, std::string& data, int option, std::string name)
{
    namespace fs = std::filesystem;
    if ((option & Create) == Create)
    {
        if (!fs::exists(paf))
        {
            std::ofstream file(paf);
            if (isspace(name))
            {
                reportErr("No name provided!", "お前はこんきれいってるか？");
                return;
            }
        }
    }
    if ((option & NQuit) == NQuit)
        return;
    if ((option & Add) == Add) {
        std::string genre = paf.substr(GV::consts::user_data_folder.length() + 1);
        genre = genre.substr(0, genre.find(FSEP));

        genre = genre + "\n" + name;

        std::thread wAllLog(writeToal, ref(data), ref(genre));
        std::thread wll(writeToll, ref(data), ref(genre));

        write_file(paf, data, name);

        wll.join();
        wAllLog.join();
    }
}


void writeFile(bool(&choices)[SET_NO], std::string&& paf)
{
    std::ofstream file(paf);

    for (char i = 0; i < SET_NO; i++)
    {
        file << choices[i] << '\n';
    }
}

template<typename Type_paf>
void indexData(int options, Type_paf paf)
{
    std::string buff = "";
    if ((options & _DEST) == _DEST)
    // destructive, destroy the previous record completely and 
    // recreate the file
    {
        std::ofstream fileOUT(paf); // the output file
        if ((options & G_IndexerAndData) == G_IndexerAndData)
        {
            std::string tmp = "";
            std::ifstream gen_name;     // file for gen_name.hentai
            paf.remove_filename();
            for (auto& gen : std::filesystem::directory_iterator(paf))
            {
                if (gen.is_directory()) {
                    gen_name.open((gen + FSEP + "gen_name.hentai"));
                    getline(gen_name, tmp); // the only line in the file
                    gen_name.close();
                    if (buff.size() > (1024 * 5)) {
                        fileOUT << buff;
                        buff = "";
                    }
                    buff += (tmp + SEP + gen.path().string() + '\n');
                }
            }
            fileOUT << buff.substr(0, buff.length() - 1); // remove the last \n
            fileOUT.close();
        }
        if ((options & E_IndexerAndData) == E_IndexerAndData)
        {
            std::string tmp = "";
            std::ifstream __entry;
            paf.remove_filename();
            for (auto& entry : std::filesystem::directory_iterator(paf)) {
                if (!entry.is_directory() && entry.extension() == ".baka") {
                    __entry.open(entry);
                    getline(__entry, tmp); // get the name in the log file (1st line)
                    __entry.close();
                    if (buff.size() > (1024 * 5)) {
                        fileOUT << buff;
                        buff = "";
                    }
                    buff += (tmp + SEP + entry.path().string() + '\n');
                }
            }
            fileOUT << buff.substr(0, buff.length() - 1); // remove the last \n
            fileOUT.close();
        }
        if ((options & Preferences) == Preferences) {
            for (int i = 0; i < SET_NO; ++i)
                buff += "0\n";
            fileOUT << buff.substr(0, buff.length() - 1);
            fileOUT.close();
        }
    }
    else if ((options & _CONST) == _CONST)
    // constructive, keep as much as possible of the previous file
    // then recreate it.
    {
        // htf do you do it?
        // therefore, reserved for later
    }
}
