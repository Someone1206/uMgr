#include "fileIO.h"
#include <thread>

bool isspace(std::string& string1)
{
    const char* c = string1.c_str();
    int count = 0;
    for (int i = 0; i < string1.length(); ++i) {
        if (isspace(*c++)) {
            count++;
        }
    }
    c = nullptr;
    if (count == string1.length())
        return true;
    return false;
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
 * <!-- Anime:  distinguished by file names-->
 * <name>
 * (char)1
 * <date>
 * <time>
 * <season>  ...optional
 * <episode> ...optional
 * <details> ...optional
 * (char)1
 *
 * <!-- Manga:  distinguished by file names-->
 * <name>
 * (char)1
 * <date>
 * <time>
 * <chapter> ...optional
 * <page>    ...optional
 * <details> ...optional
 * (char)1
 *
 * <!-- Movies:  distinguished by file names-->
 * <name>
 * (char)1
 * <date>
 * <time>
 * <part>    ...optional
 * <details> ...optional
 * (char)1
 *
 *
 * <!-- Tracker File Formats -->
 *
 *
 * <!-- Settings.baka (G_Set)-->
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
    for (auto& gen : fs::directory_iterator(genre))
        if (gen.is_directory() == !isEntry)
            i++;
    return i;
}

void mt_Field(std::string& data, wxTextCtrl* logDisp)
{
    if (data == "")
    {
        logDisp->SetDefaultStyle(wxTextAttr(wxNullColour, wxColor(200, 200, 255)));
        (*logDisp) << data << '\n';
        logDisp->SetDefaultStyle(wxTextAttr(wxNullColour));
        return;
    }
    (*logDisp) << data << '\n';
}

void readFile(std::ifstream& file, ReadOptions options, wxTextCtrl* logDisp, int history, bool isLLog, bool clearAtS) {

    if (!file.is_open())
        int smth = wxMessageBox("Can't Open File!", "", wxOK | wxICON_ERROR);

    if (file.peek() == std::ifstream::traits_type::eof()) {
        logDisp->Clear();
        (*logDisp) << "No Logs Made";
        return;
    }

    std::string line = "";
    int counter = 0;
    bool hasContent = false;

    if (clearAtS)
        logDisp->Clear();

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
    */
    // if history is 0, print all -> -1, else print the number of logs from first and add 1 to it
    getline(file, line);
    (*logDisp) << "Name:    " << line << "\n";

    while (getline(file, line) && ((bool)history)) {
        if (line.find((char)1) != std::string::npos)
        {
            if (isLLog)
                return;
            counter = 0;
            history--;
            continue;
        }
        switch (counter) {
        case 0:
            // prl("Date:" << "\t\t" << line << '\n');
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
    wxString* list, std::string dist, bool fullName, std::string* listFP) {

    if (logDisp != emptyText)
        logDisp->Clear();

    std::string line = "";

    switch (tfo) {
    case G_IndexerAndData:
    case E_IndexerAndData:
    {
        int i = 1;
        for (auto& gen : fs::directory_iterator(dist))
            if (gen.is_directory())
                list[i++] = gen.path().filename().string();
    }
    break;
    case Entries:
    {
        int i = 0;
        for (auto& entry : fs::directory_iterator(dist))
            if (!entry.is_directory()) {
                if (!fullName) {
                    std::string temp = entry.path().filename().string();
                    list[i] = temp.substr(0, temp.length() - 5);
                }
                listFP[i] = entry.path().string();
                i++;
            }
    }
    break;
    case LogList:
    {
        if (!file.is_open()) {
            int res = wxMessageBox("Can't open log file", "", wxOK | wxICON_ERROR);
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
        int sheesh = wxMessageBox("Damn it!", "We've (rather I have) encountered some problems while parsing the source code. "
            "The devs have made some problems. You can edit the src yourself, or wait for it to be fixed by the dev or cry (the best option)",
            wxOK | wxICON_ERROR);
    }
    }
    if (logDisp != emptyText)
        logDisp->SetInsertionPoint(0);
}

bool readTrackerFile(std::ifstream& file, bool* choices) {
    std::string validation;
    char c, i = 0;

    while (getline(file, validation) && i < 2) {
        c = validation.at(0);
        if (validation == "")
            choices[i] = 1;
        else if ((c >= '0' || c <= '9') && validation.length() == 1) {
            choices[i] = (bool)(c - '0');
        }
        else
            return false;
        i++;
    }


    choices = nullptr;

    return true;
}


void writeToal(std::string& data, std::string& genre) {
    using f_I = std::ifstream;
    using f_O = std::ofstream;

    std::string paf = GV::consts::user_data_folder + GV::consts::fsep + "AllLogs.hentai";
    // write to user's data folder

    f_I fileR(paf);
    if (!fileR.is_open()) {
        wxMessageBox("くそが! Can't open AllLogs.hentai ditch me", ("Can't open file: "  + paf), wxICON_ERROR | wxOK);
        return; // https://youtu.be/HCHuptVDGKg
    }
    std::string tempFilePaf = paf + ".temp";
    f_O fileW(tempFilePaf);
    fileW << (char)1 << std::endl;
    {
        std::string temp = "";
        while (getline(fileR, temp))
            fileW << temp << std::endl;
    }

    fileR.close();
    fileW.close();
    {
        f_O fileReW(paf);
        f_I fileRe(tempFilePaf);

        fileReW << (char)1 << std::endl << genre << std::endl << data << std::endl;

        {
            std::string temp = "";
            while (getline(fileRe, temp))
                fileReW << temp << std::endl;
        }
    }
    fs::remove(tempFilePaf);
}

void writeToll(std::string& data, std::string& genre) {
    using f_I = std::ifstream;
    using f_O = std::ofstream;

    std::string paf = GV::consts::user_data_folder + GV::consts::fsep + "LastLogs.baka";
    // write to users data folder

    f_I fileR(paf);
    if (!fileR.is_open()) {
        wxMessageBox("くそが! Can't open AllLogs.hentai ditch me", ("Can't open file: " + paf), wxICON_ERROR | wxOK);
        return;
    }
    std::string tempFilePaf = paf + ".temp";

    f_O fileW(tempFilePaf);

    fileW << (char)1 << std::endl;

    // write to temp file
    {
        std::string temp = "";
        while (getline(fileR, temp))
            fileW << temp << std::endl;
    }

    fileR.close();
    fileW.close();
    {
        f_O fileReW(paf);
        f_I fileRe(tempFilePaf);

        fileReW << (char)1 << std::endl << genre << std::endl << data << std::endl;

        int count = 0;
        std::string temp = "";
        char c = (char)1;

        while (getline(fileRe, temp) && count < 20) {
            if (temp.find(c) != std::string::npos)
                count++;
            fileReW << temp << std::endl;
        }

    }
    fs::remove(tempFilePaf);
}


// a really inefficient way of writing to the starting of file
void writeFile(std::string paf, std::string& data, int option, std::string name) {
    using f_I = std::ifstream;
    using f_O = std::ofstream;

    std::string genre = paf.substr(GV::consts::user_data_folder.length() + 1);
    genre = genre.substr(0, genre.find(GV::consts::fsep));

    if ((option & Create) == Create)
    {
        if (!fs::exists(paf))
        {
            f_O file(paf);
            if (isspace(name))
            {
                wxMessageBox("No name provided!", "きみはこんきれいってるか？", wxICON_ERROR | wxOK);
                return;
            }
            file << name << std::endl << (char)1 << std::endl;
        }
    }
    if ((option & NQuit) == NQuit)
        return;
    if ((option & Add) == Add) {
        std::thread wAllLog(writeToal, ref(data), ref(genre));
        std::thread wll(writeToll, ref(data), ref(genre));

        f_I fileR(paf);
        if (!fileR.is_open()) {
            wxMessageBox("Damn! Can't open a file, I am useless ditch me.", "😥😥😥😥😥", wxICON_ERROR | wxOK);
            return;
        }

        std::string tempFilePaf = paf + ".temp", name = "";

        f_O fileW(tempFilePaf);
        getline(fileR, name);
        // write to temp file
        {
            std::string temp = "";
            while (getline(fileR, temp))
                fileW << temp << std::endl;
        }
        fileR.close();
        fileW.close();

        // rewriting to the file again
        {
            f_O fileReW(paf);
            f_I fileR(tempFilePaf);
            fileReW << name << std::endl << (char)1 << std::endl;
            fileReW << data << std::endl;

            std::string temp = "";
            while (getline(fileR, temp))
                fileReW << temp << std::endl;
        }
        fs::remove(tempFilePaf);

        wll.join();
        wAllLog.join();
    }
}


// only for settings file
void writeFile(bool* choices, std::string paf) {
    std::ofstream file(paf);

    file << choices[0] << std::endl;
    file << choices[1];
}
