#include "GV.h"

namespace GV
{
    namespace consts
    {
        char fsep = std::filesystem::path::preferred_separator;
        std::filesystem::path uPaf;
        std::string uName = getU_F_name();
        std::string c_app_data = "uMgr_A_Data";
        std::string user_data_folder;
    } // namespace consts
} // namespace GV

std::string GV::getU_F_name()
{
#if _WIN32
    TCHAR userPaf[MAX_PATH];
    SHGetFolderPath(nullptr, CSIDL_PROFILE, nullptr, 0, userPaf);
    GV::consts::uPaf = userPaf;
    int index = 0;
    for (int i = 0; i < GV::consts::uPaf.string().length(); i++)
    {
        std::string temp = GV::consts::uPaf.string();
        if (temp.at(i) == GV::consts::fsep)
            index = i;
    }
    return GV::consts::uPaf.string().substr(index + 1);
#endif // _WIN32
}
