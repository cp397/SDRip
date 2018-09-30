//#include "includes.h"
//
///******************************************************************************
// * Initialize curses and the app related curses data
// *****************************************************************************/
//void PopupMenu::initGraphics() {
//    //Initialize pdcurses
//    initscr();
//    start_color();
//
//    init_pair(1, COLOR_BLACK, COLOR_WHITE);
//    init_pair(2, COLOR_WHITE, COLOR_BLUE);
//    bkgd(COLOR_PAIR(1));
//    refresh();
//}
//
///******************************************************************************
// * Un-initialize curses
// *****************************************************************************/
//void PopupMenu::stopGraphics() {
//    endwin();    
//}
//
///******************************************************************************
// * Constructor - init ncurses/pdcurses and create the window for this menu
// *****************************************************************************/
//PopupMenu::PopupMenu(
//    MenuOption* menuOptions, 
//    int numOptions, 
//    int numRows, 
//    int numCols, 
//    int startY, 
//    int startX
//) : m_window(NULL), m_list(menuOptions), m_numopts(numOptions), m_rows(numRows), m_cols(numCols) {
//
//    //Create the popup window
//    m_window = newwin(numRows, numCols, startY, startX);
//    box(m_window, 0, 0);
//    wbkgd(m_window, COLOR_PAIR(2));
//    wrefresh(m_window);
//
//    //Configure input for the window
//    noecho();
//    keypad(m_window, TRUE);
//    curs_set(0);
//        
//    m_running = true;
//}
//
///******************************************************************************
// * Destructor - delete popup window and end ncurses/pdcurses
// *****************************************************************************/
//PopupMenu::~PopupMenu() {
//
//    //Erase the window
//    werase(m_window);
//    wbkgd(m_window, COLOR_PAIR(1));
//    wrefresh(m_window);
//    delwin(m_window);
//}
//
///******************************************************************************
// * Display each of the menu option labels in this popup menu's window
// *****************************************************************************/
//void PopupMenu::showOptions(int selected) {
//    char option[25];
//    
//    wattron(m_window, COLOR_PAIR(2));
//
//    for(int current=0; current<m_numopts; current++) {
//
//        if(current == selected) {
//            wattroff(m_window, A_INVIS);
//            wattron(m_window, A_STANDOUT);
//        } else if(current == 0) {
//            wattroff(m_window, A_INVIS);
//            wattroff(m_window, A_STANDOUT);
//        } else {
//            wattroff(m_window, A_STANDOUT);
//
//            if(m_list[current].active == false) {
//                wattron(m_window, A_INVIS);
//            } else {
//                wattroff(m_window, A_INVIS);
//            }
//        }
//        
//        sprintf(option, "%-10s", m_list[current]);
//        mvwprintw(m_window, 
//            current==0 ? current+1 : current+2, 
//            current==0 ? 2 : 4, 
//            "%s", option
//        );
//        wrefresh(m_window);
//    }
//}
//
///******************************************************************************
// * Run the popup menu and allow the user to scroll through the options and
// * select one of the options.  Run any action function included with the 
// * menu opton and then return the option number that was selected
// *****************************************************************************/
//int PopupMenu::choose()
//{
//    int input    = 0;
//    int selected = 1;
//
//    showOptions(selected);
//    wrefresh(m_window);
//
//    //Run this menu popup until the user presses the 'q' key or quits
//    //from within the menu (if the user included such a menu option)
//    while(m_running == true && (input = wgetch(m_window)) != 'q') {
//
//        //Redraw the menu as the user moves through the options
//        switch(input) {
//
//            //Scroll up to the previous active menu option
//            case KEY_UP:
//                
//                //Move to the previous menu item with wraparound
//                selected--;
//                selected = (selected<1) ? m_numopts-1 : selected;
//
//                //Keep searching for an active menu option if the current
//                //one is inactive
//                while(m_list[selected].active == false) {
//                    selected--;
//                    selected = (selected<1) ? m_numopts-1 : selected;
//                }
//
//                break;
//                
//            //Scroll down to the next active menu option
//            case KEY_DOWN:
//                
//                //Move to the next menu item with wraparound
//                selected++;
//                selected = (selected>m_numopts-1) ? 1 : selected;
//
//                //Keep searching for an active menu option if the current
//                //one is inactive
//                while(m_list[selected].active == false) {
//                    selected++;
//                    selected = (selected>m_numopts-1) ? 1 : selected;
//                }
//                break;
//
//            //Select an option
//            case'\n':
//                if(m_list[selected].action != NULL) m_list[selected].action();
//                else  m_running = false;
//                break;
//        }
//        showOptions(selected);
//        wrefresh(m_window);
//    }
//    
//    return selected;
//}    
//
///******************************************************************************
// * Activate the specified menu option
// *****************************************************************************/
//void PopupMenu::activate(int option) {
//    if(option>=0 && option<m_numopts) m_list[option].active = true;
//}
//
///******************************************************************************
// * Deactive the specified menu option
// *****************************************************************************/
//void PopupMenu::deactivate(int option) {
//    if(option>=0 && option<m_numopts) m_list[option].active = false;
//}
//
///******************************************************************************
// * Change the label of one of the menu options
// *****************************************************************************/
//void PopupMenu::setLabel(int option, char* label) {
//    if(option>=0 && option<m_numopts) m_list[option].label = label;
//}
//
