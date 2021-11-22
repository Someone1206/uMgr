#include "ComboBox.h"
#include <fstream>
#include <string>

ComboBox::ComboBox(HWND parent, const Point& pos, const Size& _size, int id, int styles, int stylesEx)
    :BaseWin(parent, pos, _size, id, GetModuleHandle(nullptr))
{
    if (size.y == -1)
        size.y = 0x10000; // :> irdc
    hWnd = CreateWindowEx(
        stylesEx,
        "comBoBOX", "",
        styles,
        Position.x, Position.y,
        size.x, size.y,
        this->Parent, (HMENU)ID, this->hInst, nullptr
    );

    Show();
}

void ComboBox::updateList(std::ifstream& indexFile, bool setFirstIndex) {
    std::string str = "";
    int index = 0;
    while (getline(indexFile, str))
    {
        if (str == "")
            continue;
        index = str.find_last_of(BaseWin::SEP);
        SendMessage(this->hWnd, (UINT)CB_ADDSTRING, 0,
            (LPARAM)(const_cast<char*>(str.substr(0, index).c_str())));
    }
    if (setFirstIndex)
        SendMessage(this->hWnd, CB_SETCURSEL, 0, 0);
}

void ComboBox::updateList_A(std::ifstream& indexFile, std::string*& paf_arr, bool setFirstIndex, int initPafStr)
{
    std::string paths = "";
    int len = 0;
    {
        std::string str = "";
        int index = 0;
        while (getline(indexFile, str))
        {
            if (str == "")
                continue;
            index = str.find_last_of(BaseWin::SEP);
            SendMessage(this->hWnd, (UINT)CB_ADDSTRING, 0,
                (LPARAM)((TCHAR*)const_cast<char*>(str.substr(0, index).c_str())));
            len++;
            paths += (str.substr(index + 1) + '\n');
        }
    }

    if (setFirstIndex)
        this->setIndex(0);

    unsigned int n_at = 0;
    if(initPafStr == CB_INIT_PAF)
    {
        paf_arr = new std::string[len];
        for (unsigned int i = 0; i < len; i++) {
            n_at = paths.find_first_of('\n');
            paf_arr[i] = paths.substr(0, n_at);
            paths = paths.substr(n_at + 1);
        }
    }
#ifndef NDEBUG
    std::string tmpStr = "";
    for (int j = -1; ++j < len;)
    {
        tmpStr += paf_arr[j] + '\n';
    }
    MessageBox(this->hWnd, tmpStr.c_str(), "やったね！", MB_OKCANCEL | MB_ICONINFORMATION);
#endif
}

void ComboBox::setList(std::string* arr, size_t len)
{
    for (int i = -1; ++i < len;)
    {
        SendMessage(this->hWnd, (UINT)CB_ADDSTRING, 0,
            (LPARAM)((TCHAR*)const_cast<char*>(arr[i].c_str())));
    }
}

std::string ComboBox::getTxt(int index)
{
    int len = SendMessage(this->hWnd, CB_GETLBTEXTLEN, index, 0);
    //TCHAR txt[len + 1];
    TCHAR* txt = new TCHAR(len + 1);
    SendMessage(this->hWnd, CB_GETLBTEXT, index, (LPARAM)txt);
#ifndef NDEBUG
    MessageBox(nullptr, txt, "lll", MB_OKCANCEL);
#endif
    return std::string(txt);
}