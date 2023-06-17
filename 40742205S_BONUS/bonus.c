// a program for ncurses demo
#include <ncurses.h>

#define WINDOW_ROW 40
#define WINDOW_COL 40
#define WINDOW_BEGIN_X 0
#define WINDOW_BEGIN_Y 0

void options_init(WINDOW *win);
void set_options(WINDOW *win);

int main() {
    initscr(); // 初始化 ncurses

    WINDOW *window = newwin(WINDOW_ROW, WINDOW_COL, WINDOW_BEGIN_Y, WINDOW_BEGIN_X); // 建立新視窗

    mvwprintw(window, WINDOW_ROW / 2, (WINDOW_COL / 2) - 5, "Press a key"); // 在指定的視窗的指定位置加入字串
    
    wrefresh(window); // 刷新視窗中顯示的內容
    
    keypad(window, TRUE); // 允許視窗讀取鍵盤輸入
    
    wgetch(window); // 讀取一個輸入字元傳入指定的視窗
    
    werase(window); // 清除螢幕內容
    
    mvwprintw(window, WINDOW_ROW / 2, (WINDOW_COL / 2) - 9, "Press a key again"); // 在指定的視窗的指定位置加入字串

    wrefresh(window); // 刷新視窗中顯示的內容
    
    wgetch(window); // 讀取一個輸入字元傳入指定的視窗
    
    delwin(window); // 刪除視窗
    
    window = newwin(WINDOW_ROW, WINDOW_COL, WINDOW_BEGIN_Y, WINDOW_BEGIN_X); // 建立新視窗
    
    box(window, 1, 0); // 在視窗中畫出邊界
    
    wattron(window, A_REVERSE); // 開啟反白屬性
    
    mvwprintw(window, WINDOW_ROW / 2, (WINDOW_COL / 2) - 5, "Press a key"); // 在指定的視窗的指定位置加入字串
    
    wattroff(window, A_REVERSE); // 關閉反白屬性

    wrefresh(window); // 刷新視窗中顯示的內容
    
    wgetch(window); // 讀取一個輸入字元傳入指定的視窗

    wclrtoeol(window); // 清除視窗中游標那一行
    
    mvwprintw(window, WINDOW_ROW / 2, (WINDOW_COL / 2) - 9, "Press a key again"); // 在指定的視窗的指定位置加入字串

    wrefresh(window); // 刷新視窗中顯示的內容
    
    wgetch(window); // 讀取一個輸入字元傳入指定的視窗
    
    wmove(window, 0, 0); // 移動游標至視窗中的相對座標

    wclrtobot(window); // 清除游標至視窗底部的所有資料

    mvwprintw(window, WINDOW_ROW / 2, (WINDOW_COL / 2) - 5, "Press a key"); // 在指定的視窗的指定位置加入字串

    wrefresh(window); // 刷新視窗中顯示的內容

    wgetch(window); // 讀取一個輸入字元傳入指定的視窗

    delwin(window); // 刪除視窗

    window = newwin(WINDOW_ROW, WINDOW_COL, WINDOW_BEGIN_Y, WINDOW_BEGIN_X); // 建立新視窗

    options_init(window); // 從卡坦島修改的範例，方向鍵移動選項， enter 鍵選擇， q 鍵退出

    endwin(); // 終止所有視窗
    
    return 0;
}

void options_init(WINDOW *win) {
    box(win, 0, 0);
    mvwprintw(win, 0, 2, "OPTIONS");
    set_options(win);
    wrefresh(win);
}

void set_options(WINDOW *win) {
    int row, col;
    getmaxyx(win, row, col);
    keypad(win, true);

    char *NPC_num[4] = {
        "Number of NPC      2",
        "Number of NPC      3",
        "Number of NPC      4",
        "Number of NPC      5"
    };

    char *options[2] = {NPC_num[1], "Level of NPC    Easy"};

    for (int choice = 0, highlight = 0; choice != 'q';) {
        for(int i = 0; i < 2; i++) {
            if(i == highlight) {
                wattron(win, A_REVERSE);
            }
            mvwprintw(win, (row / 2) + i, (col / 2) - 10, options[i]);
            wattroff(win, A_REVERSE);
        }
        choice = wgetch(win);
        switch(choice) {
            case KEY_UP:
                if(highlight == 0) {
                    highlight = 1;
                }
                else {
                    highlight--;
                }
                break;
            case KEY_DOWN:
                if(highlight == 1) {
                    highlight = 0;
                }
                else {
                    highlight++;
                }
                break;
            case '\n': {
                switch (highlight) {
                    case 0: {
                        int index_of_NPC_num = 1;
                        for (int input = 0; input != '\n';) {
                            mvwprintw(win, (row / 2) + 2, (col / 2) - 16, "                               ");
                            for(int i = 0; i < 4; i++) {
                                if(i == index_of_NPC_num) {
                                    wattron(win, A_REVERSE);
                                }
                                mvwprintw(win, (row / 2) + i, (col / 2) - 10, NPC_num[i]);
                                wattroff(win, A_REVERSE);
                            }
                            input = wgetch(win);
                            switch (input) {
                                case KEY_UP:
                                    if (index_of_NPC_num <= 0)
                                        index_of_NPC_num = 3;
                                    else
                                        index_of_NPC_num--;
                                    break;
                                case KEY_DOWN:
                                    if (index_of_NPC_num >= 3)
                                        index_of_NPC_num = 0;
                                    else
                                        index_of_NPC_num++;
                                    break;
                                default:    
                                    break;
                            }
                        }
                        mvwprintw(win, (row / 2) + 2, (col / 2) - 10, "                    ");
                        mvwprintw(win, (row / 2) + 3, (col / 2) - 10, "                    ");
                        options[0] = NPC_num[index_of_NPC_num];
                    }
                        break;
                    case 1:
                        mvwprintw(win, (row / 2) + 2, (col / 2) - 16, "Haha, I didn't do other levels.");
                        break;
                }
            }
                break;
            default:
                break;
        }
    }
}