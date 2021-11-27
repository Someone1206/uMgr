#include "init.h"
#include "fileIO.h"

bool settings(bool(&choices)[SET_NO])
{
    std::string paf = PREF_FOLDER + FSEP + PREF_FILE;

    std::ifstream file(paf);
    if (!file.is_open()) {
        return false;
    }

    std::optional<bool> res = readTrackerFile(file, choices);

    return res.value();
}

void init(bool(&choices)[SET_NO])
{
    {
        std::string paf = aFolder + FSEP + "pafs.hentai";
        std::ifstream paf_file(paf);
        getline(paf_file, uFolder);
    }

    std::filesystem::create_directories(aFolder);

    {
        std::string paf = PREF_FOLDER + FSEP + PREF_FILE;
        if (!std::filesystem::exists((paf))) {
            std::ofstream f(paf);
            f << 1 << std::endl;
            f << 0;
            f.close();
        }
        bool smth = settings(choices);
    }
    // idk if this works but does it improve the memory management (by destroying[or whatever it's called] the string var)

    {
        std::string paf = uFolder + FSEP + "LastLogs.baka";
        if (!std::filesystem::exists(paf)) {
            std::ofstream file(paf);
            // file << (char)1;
            file.close();
        }
    }
    {
        std::string paf = uFolder + FSEP + "AllLogs.hentai"; // 😅
        if (!std::filesystem::exists(paf)) {
            std::ofstream file(paf);
            // file << (char)1;
            file.close();
        }
    }

    if (choices[0]) {
        std::string paf = uFolder + FSEP;
        std::filesystem::create_directory((paf + "Anime"));
        std::filesystem::create_directory((paf + "Manga"));
        std::filesystem::create_directory((paf + "Movies"));
        // fs::create_directory((paf + "BTS"));       // BTS is one of the best... fu if u don't like it, idc
        // fs::create_directory((pa + "BLACKPINK")); // hmm... I like BLACKPINK but not as much as BTS. Also fu if u don't like it, I still don't care
    }
}


bool createGen(const wxString& genName)
{
    std::string gen_name = std::string(genName.mb_str());

    if (isspace(gen_name) || gen_name.length() == 0) {
        wxMessageBox("Empty Genre Name", "You think I'm stupid");
        return false;
    }

    if (std::filesystem::exists((uFolder + FSEP + gen_name))) {
        wxMessageBox("Genre Already Exists", "-_-");
        return false;
    }

    std::filesystem::create_directory(uFolder + FSEP + gen_name);
    return true;
}

bool createEntry(const wxString& entryName, const wxString& genName)
{
    std::string entry_name = std::string(entryName.mb_str());
    std::string paf = uFolder + FSEP + std::string(genName.mb_str()) + FSEP 
        + entry_name + ".baka";

    if (isspace(entry_name) || entry_name.length() == 0) {
        wxMessageBox("Empty Entry Name", "You think I'm stupid");
        return false;
    }

    if (std::filesystem::exists(paf)) {
        wxMessageBox("Entry Already Exists", "-_-");
        return false;
    }

    std::string idk = "";
    writeFile(paf, idk, Create, entry_name);
    return true;
}


inline std::string getFrameTitle()
{
    std::ifstream file((PREF_FOLDER + FSEP + TIT_FILE));
    std::string str = "uMgr";
    if (file && file.eof()) // if file opens & !mt, can be spc
        getline(file, str);
    return str;
}