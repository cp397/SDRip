#ifndef GUI_H
#define GUI_H

/******************************************************************************
 * Struct for constructing menu options. Contains a text label, a flag to
 * enable or disable the menu option, and an action function pointer to
 * exectute if the menu option is selected (can be NULL for no action).
 *****************************************************************************/
typedef struct tagMenuOption {
    char *label;
    bool active;
    void (*action)(void);
} MenuOption;

/******************************************************************************
 * Creates a popup menu window on the screen with the specified menu options.
 *****************************************************************************/
class PopupMenu {
public:
    PopupMenu(MenuOption* menuOptions, int numOptions, int numRows, int numCols, int startY, int startX);
    virtual ~PopupMenu();
    int choose();
    void activate(int option);
    void deactivate(int option);
    void setLabel(int option, char* label);

    void redraw()              { wrefresh(m_window); }
    int getNumOptions()        { return m_numopts; }
    static int getNumLines()   { return LINES; }
    static int getNumCols()    { return COLS;  }
    static void initGraphics();
    static void stopGraphics();

private:
    void showOptions(int selected);
    
    WINDOW *m_window;
    MenuOption* m_list;
    int m_numopts;
    int m_rows;
    int m_cols;
    bool m_running;
};

#endif
