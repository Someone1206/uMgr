#pragma once
#include "Bits.h"
#include "BaseWin.h"

class ComboBox
    :public BaseWin
{
private:
    /* data */
public:
    ComboBox() = delete; // :>

    /// <summary>
    /// Constructor
    /// <param name="parent"> hwnd of parent</param>
    /// <param name="pos"> Position</param>
    /// <param name="size"> Size. Size.y = -1 if don't care</param>
    /// <param name="id"> ID for the window</param>
    /// <param name="styles"> styles: CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE</param>
    /// <param name="stylesEx"> extended styles. usually ignored</param>
    /// </summary>
    ComboBox(HWND parent, const Point& pos, const Size& _size, int id,
        int styles = CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, // :P
        int stylesEx = 0
    );

    /// <summary>
    /// <param name="indexFile"> ref. to the index file...</param>
    /// <param name="setFirstIndex"> true to set the active entry to 0</param>
    /// </summary>
    void updateList(std::ifstream& indexFile, bool setFirstIndex = true);

    /// <summary>
    /// <param name="indexFile"> ref. to the index file...</param>
    /// <param name="paf_arr"> str* for the paths of the gen/entry</param>
    /// <param name="setFirstIndex"> true to set the active entry to 0</param>
    /// </summary>
    void updateList_A(std::ifstream& indexFile, std::string* paf_arr, bool setFirstIndex = true);
    
    /// <summary>
    /// set the list to a str array on the heap
    /// <param name="arr"> str* to array to fill with</param>
    /// <param name="len"> length of the array</param>
    /// </summary>
    void setList(std::string* arr, size_t len);

    /// <summary>
    /// get the text label for an index
    /// <param name="index"> index, set to 0</param>
    /// </summary>
    std::string getTxt(int index = 0);



    // inline fns

    /// <summary>
    /// set the active selection which appears in the combobox
    /// <param name="i"> defaulted to 0, can be any int </param>
    /// </summary>
    void setIndex(int i = 0) 
    {
        SendMessage(this->hWnd, CB_SETCURSEL, i, 0);
    }
    
    /// <summary>
    /// clear indexes,
    /// <param name="index"> -1, for all/index no</param>
    /// </summary>
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