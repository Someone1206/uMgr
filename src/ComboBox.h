#include "Bits.h"
#include "BaseWin.h"
#include <fstream>
#include <string>

class ComboBox
    :public BaseWin
{
private:
    /* data */
public:
    ComboBox(HWND parent, const Point& pos, const Size& _size, int id,
        int styles = CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
        int stylesEx = 0
    );

    void updateList(std::ifstream& indexFile, bool setFirstIndex = true);
    void setList(std::string* arr, size_t len);

    void setIndex(int i = 0) {
        SendMessage(this->hWnd, CB_SETCURSEL, i, 0);
    }
    ~ComboBox();
};

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
            (LPARAM)((TCHAR*)const_cast<char*>(str.substr(0, index).c_str())));
    }
    if (setFirstIndex)
        SendMessage(this->hWnd, CB_SETCURSEL, 0, 0);
}

void ComboBox::setList(std::string* arr, size_t len)
{
    for (int i = 0; i ++< len ;) // :>
    {
        SendMessage(this->hWnd, (UINT)CB_ADDSTRING, 0, 
            (LPARAM)((TCHAR*)const_cast<char*>(arr[i].c_str())));
    }
}

ComboBox::~ComboBox()
{
    /* do whatever */
}