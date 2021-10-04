#include "init.h"
#include <fstream>
#include "fileIO.h"


bool settings(bool* choices) {
    std::string paf = GV::consts::c_app_data + GV::consts::fsep + "Settings.baka";

    std::ifstream file(paf);
    if (!file.is_open()) {
        choices = nullptr;
        return false;
    }

    bool res = readTrackerFile(file, choices);

    choices = nullptr;
    return res;
}

void init(bool* choices)
{

    GV::consts::user_data_folder = "uMgrData";

    fs::create_directory(GV::consts::user_data_folder); //
    fs::create_directory(GV::consts::c_app_data);       //

    {
        std::string paf = GV::consts::c_app_data + GV::consts::fsep + "Settings.baka";
        if (!fs::exists((paf))) {
                std::ofstream f(paf);
        f << 1 << std::endl;
            f << 0;
            f.close();
        }
        bool smth = settings(choices);
    }
    // idk if this works but does it improve the memory management (by destroying[or whatever it's called] the string var)

    {
        std::string paf = GV::consts::user_data_folder + GV::consts::fsep + "LastLogs.baka";
        if (!fs::exists(paf)) {
            std::ofstream file(paf);
            // file << (char)1;
            file.close();
        }
    }
    {
        std::string paf = GV::consts::user_data_folder + GV::consts::fsep + "AllLogs.hentai"; // 😅
        if (!fs::exists(paf)) {
            std::ofstream file(paf);
            // file << (char)1;
            file.close();
        }
    }

    if (choices[0]) {
        std::string paf = GV::consts::user_data_folder + GV::consts::fsep;
        fs::create_directory((paf + "Anime"));
        fs::create_directory((paf + "Manga"));
        fs::create_directory((paf + "Movies"));
        // fs::create_directory((paf + "BTS"));       // BTS is one of the best... fu if u don't like it, idc
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

    if (fs::exists((GV::consts::user_data_folder + GV::consts::fsep + gen_name))) {
        wxMessageBox("Genre Already Exists", "-_-");
        return false;
    }

    fs::create_directory(GV::consts::user_data_folder + GV::consts::fsep + gen_name);
    return true;
}

bool createEntry(const wxString& entryName, const wxString& genName)
{
    std::string entry_name = std::string(entryName.mb_str());
    std::string paf = GV::consts::user_data_folder + GV::consts::fsep + std::string(genName.mb_str()) + GV::consts::fsep 
        + entry_name + ".baka";

    if (isspace(entry_name) || entry_name.length() == 0) {
        wxMessageBox("Empty Entry Name", "You think I'm stupid");
        return false;
    }

    if (fs::exists(paf)) {
        wxMessageBox("Entry Already Exists", "-_-");
        return false;
    }

    std::ofstream file(paf);
    file.close();
    return true;
}