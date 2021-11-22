#pragma once
#include "Bits.h"
#include "BaseWin.h"


#define CB_INIT_PAF     0xff
#define CB_NO_INIT      0x80
#define CB_NORMAL       CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE


class ComboBox
    :public BaseWin
{
private:
    /* data */
public:
    ComboBox() = delete; // :>

    /// <summary>
    /// Constructor
    /// </summary>
    /// <param name="parent">: hwnd of parent</param>
    /// <param name="pos">: Position</param>
    /// <param name="size">: Size. Size.y = -1 if don't care</param>
    /// <param name="id">: ID for the window</param>
    /// <param name="styles">: styles: CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE</param>
    /// <param name="stylesEx">: extended styles. usually ignored</param>
    ComboBox(HWND parent, const Point& pos, const Size& _size, int id,
        int styles = CB_NORMAL, // :P
        int stylesEx = 0
    );

    /// <summary>
    /// update the list but without updation in paths array
    /// </summary>
    /// <param name="indexFile">: ref. to the index file...</param>
    /// <param name="setFirstIndex">: true to set the active entry to 0</param>
    void updateList(std::ifstream& indexFile, bool setFirstIndex = true);

    /// <summary>
    /// Updates the list according to the index files supplied and updates the path array
    /// </summary>
    /// <param name="indexFile">: ref. to the index file...</param>
    /// <param name="paf_arr">: str* for the paths of the gen/entry</param>
    /// <param name="setFirstIndex">: true to set the active entry to 0</param>
    /// <param name="initPafStr">: CB_INIT_PAF to initialise the string array, CB_NO_INIT to not init it</param>
    void updateList_A(std::ifstream& indexFile, std::string*& paf_arr, bool setFirstIndex = true, int initPafStr = 1);
    
    /// <summary>
    /// set the list to a str array on the heap
    /// </summary>
    /// <param name="arr">: str* to array to fill with</param>
    /// <param name="len">: length of the array</param>
    void setList(std::string* arr, size_t len);

    /// <summary>
    /// get the text label for an index
    /// </summary>
    /// <param name="index">: index, set to 0</param>
    /// <returns>The text at the given index</returns>
    std::string getTxt(int index = 0);



    // inline fns

    /// <summary>
    /// set the active selection which appears in the combobox
    /// </summary>
    /// <param name="i">: defaulted to 0, can be any int </param>
    void setIndex(int i = 0) 
    {
        SendMessage(this->hWnd, CB_SETCURSEL, i, 0);
    }

    /// <summary>
    /// Get the selected index
    /// </summary>
    /// <returns>Returns the selected index</returns>
    unsigned int getIndex() {
        return SendMessage(this->hWnd, CB_GETCURSEL, 0, 0);
    }

    void Add(const char* txt) {
        SendMessage(this->hWnd, CB_ADDSTRING, 0, (LPARAM)txt);
    }
    
    /// <summary>
    /// clear indexes,
    /// </summary>
    /// <param name="index"> -1, for all/index no</param>
    void Clear(int index = -1)
    {
        if (index < 0)
        {
            SendMessage(this->hWnd, CB_RESETCONTENT, 0, 0);
            return;
        }
        SendMessage(this->hWnd, CB_DELETESTRING, index, 0);
    }

    ~ComboBox() { /* do whatever */ }
};