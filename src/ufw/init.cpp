#include "init.h"

bool settings(bool* choices) {
    str paf = folderN + fsep + "Settings.baka";

    ifstream file(paf);
    if (!file.is_open()) {
        choices = nullptr;
        return false;
    }

    bool res = readTrackerFile(file, choices);

    choices = nullptr;
    return res;
}

void init(bool* choices) {


    fs::create_directory(folderN);
    {
        str paf = folderN + fsep + "Settings.baka";
        if (!fs::exists((paf))) {
            ofstream f(paf);
            f << 1 << endl;
            f << 0;
            f.close();
        }
        
        bool smth = settings(choices);
    }
    // idk if this works but does it improve the memory management (by destroying[or whatever it's called] the string var)
    {
        str paf = folderN + fsep + "LastLogs.baka";
        if (!fs::exists(paf)) {
            ofstream file(paf);
            // file << (char)1;
            file.close();
        }
    }
    {
        str paf = folderN + fsep + "AllLogs.hentai"; // 😅
        if (!fs::exists(paf)) {
            ofstream file(paf);
            // file << (char)1;
            file.close();
        }
    }

    if (choices[0]) {
        str paf = folderN + fsep;
        fs::create_directory((paf + "Anime"));
        fs::create_directory((paf + "Manga"));
        fs::create_directory((paf + "Movies"));
        fs::create_directory((paf + "BTS"));       // BTS is one of the best... fu if u don't like it, idc
        // fs::create_directory((pa + "BLACKPINK")); // hmm... I like BLACKPINK but not as much as BTS. Also fu if u don't like it, I still don't care
    }
    choices = nullptr;
}

bool createGen(const wxString& genName)
{
    std::string gen_name = std::string(genName.mb_str());

    if (isspace(gen_name) || gen_name.length() == 0) {
        wxMessageBox("Empty Genre Name", "You think I'm stupid");
        return false;
    }

    if (fs::exists((folderN + fsep + gen_name))) {
        wxMessageBox("Genre Already Exists", "-_-");
        return false;
    }

    fs::create_directory(folderN + fsep + gen_name);
    return true;
}

bool createEntry(const wxString& entryName, const wxString& genName)
{
    std::string entry_name = std::string(entryName.mb_str());
    std::string paf = folderN + fsep + std::string(genName.mb_str()) + fsep + entry_name + ".baka";

    if (isspace(entry_name) || entry_name.length() == 0) {
        wxMessageBox("Empty Entry Name", "You think I'm stupid");
        return false;
    }

    if (fs::exists(paf)) {
        wxMessageBox("Entry Already Exists", "-_-");
        return false;
    }

    ofstream file(paf);
    file.close();
    return true;
}
