#include "fileIO.h"

// check if the string is empty or not
bool isspace(str& string1) {
    const char* c = string1.c_str();

    for (int i = 0; i < string1.length(); ++i)
        if (isspace(*c++)) {
            c = nullptr;
            return false;
        }
    c = nullptr;
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
 * <!-- GenIndexer.baka (G_IndexerAndData)-->
 *
 * <!!-- Names to display for the Genre  (I'll implement this later)  --!>
 * <-- some OS may not support Unicode in its filesystem (which OS is so damn outdated?)
 * or may show errors or stupid behaviours for some characters (I'm not trying to say that
 * English is great but I've seen some linux distros do that, Windows doesn't show any problems
 * its good -->
 *
 * <!-- EntryIndexer.baka -->
 *
 * <!!-- Names to display for the Entry  (this too will be implemented later or not at all)  --!>
 *
 * ******************************************************************************
 */

int entriesNGenres(str genre, bool isEntry)
{
    int i = 0;
    for (auto& gen : fs::directory_iterator(genre))
        if (gen.is_directory() == !isEntry)
            i++;
    return i;
}

void readFile(ifstream& file, ReadOptions options, wxTextCtrl* logDisp, int history, bool isLLog, bool clearAtS) {

    if (!file.is_open())
        int smth = wxMessageBox("Can't Open File!", "", wxOK | wxICON_ERROR);

    if (file.peek() == ifstream::traits_type::eof()) {
        logDisp->Clear();
        (*logDisp) << "No Logs Made";
        return;
    }

    str line = "";
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
                (*logDisp) << line << "\n";
                break;
            case Anime:
                if (counter == 2)
                    (*logDisp) << "Season:    " << line << "\n";
                else if (counter == 3)
                    (*logDisp) << "Episode:    " << line << "\n";
                else {
                    if (counter == 4)
                        (*logDisp) << "Details and Remarks:\n";
                    (*logDisp) << line << "\n";
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
                    (*logDisp) << line << "\n";
                }
                break;

            case Movies:
                if (counter == 2)
                    (*logDisp) << "Part Last seen:    " << line << "\n";
                else {
                    if (counter == 3)
                        (*logDisp) << "Details and Remarks:" << "\n";
                    (*logDisp) << line << "\n";
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

void readTrackerFile(ifstream& file, TrackerFileOptions tfo, wxTextCtrl* logDisp, int history,
    wxString* list, str dist, bool fullName, str* listFP) {

    if (logDisp != emptyText)
        logDisp->Clear();

    str line = "";

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
                        str temp = entry.path().filename().string();
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
                if (line.find((char)1) != str::npos) {
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

bool readTrackerFile(ifstream& file, bool* choices) {
    str validation;
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


void writeToal(str& data, str& genre) {
    str paf = folderN + fsep + "AllLogs.hentai";
    ifstream fileR(paf);
    if (!fileR.is_open()) {
        prl(fileR.is_open());
        prl("くそが! Can't open AllLogs.hentai ditch me");
        return;
    }
    str tempFilePaf = paf + ".temp";
    ofstream fileW(tempFilePaf);
    fileW << (char)1 << endl;
    {
        str temp = "";
        while (getline(fileR, temp))
            fileW << temp << endl;
    }

    fileR.close();
    fileW.close();
    {
        ofstream fileReW(paf);
        ifstream fileRe(tempFilePaf);

        fileReW << (char)1 << endl << genre << endl << data << endl;

        {
            str temp = "";
            while (getline(fileRe, temp))
                fileReW << temp << endl;
        }
    }
    fs::remove(tempFilePaf);
}

void writeToll(str& data, str& genre) {
    str paf = folderN + fsep + "LastLogs.baka";
    ifstream fileR(paf);
    if (!fileR.is_open()) {
        prl(fileR.is_open());
        prl("くそが! Can't open LastLogs.baka ditch me");
        return;
    }
    str tempFilePaf = paf + ".temp";

    ofstream fileW(tempFilePaf);

    fileW << (char)1 << endl;

    // write to temp file
    {
        str temp = "";
        while (getline(fileR, temp))
            fileW << temp << endl;
    }

    fileR.close();
    fileW.close();
    {
        ofstream fileReW(paf);
        ifstream fileRe(tempFilePaf);

        fileReW << (char)1 << endl << genre << endl << data << endl;

        int count = 0;
        str temp = "";
        char c = (char)1;

        while (getline(fileRe, temp) && count < 20) {
            if (temp.find(c) != str::npos)
                count++;
            fileReW << temp << endl;
        }

    }
    fs::remove(tempFilePaf);
}


// a really inefficient way of writing to the starting of file
void writeFile(str paf, str& data, int option, str name) {
    str genre = paf.substr(folderN.length() + 1);
    genre = genre.substr(0, genre.find(fsep));

    if ((option & Create) == Create)
    {
        if (!fs::exists(paf))
        {
            ofstream file(paf);
            if (isspace(name))
            {
                prl("No name provided");
                return;
            }
            file << name << endl << (char)1 << endl;
        }
    }
    if ((option & NQuit) == NQuit)
        return;
    if ((option & Add) == Add) {
        std::thread wAllLog(writeToal, ref(data), ref(genre));
        std::thread wll(writeToll, ref(data), ref(genre));

        ifstream fileR(paf);
        if (!fileR.is_open()) {
            prl(fileR.is_open());
            prl("Damn! Can't open a file, I am useless ditch me.");
            return;
        }

        str tempFilePaf = paf + ".temp", name = "";

        ofstream fileW(tempFilePaf);
        getline(fileR, name);
        // write to temp file
        {
            str temp = "";
            while (getline(fileR, temp))
                fileW << temp << endl;
        }
        fileR.close();
        fileW.close();

        // rewriting to the file again
        {
            ofstream fileReW(paf);
            ifstream fileR(tempFilePaf);
            fileReW << name << endl << (char)1 << endl;
            fileReW << data << endl;

            str temp = "";
            while (getline(fileR, temp))
                fileReW << temp << endl;
        }
        fs::remove(tempFilePaf);

        wll.join();
        wAllLog.join();
    }
}


// only for settings file
void writeFile(bool* choices, str paf) {
    ofstream file(paf);

    file << choices[0] << endl;
    file << choices[1];
}
