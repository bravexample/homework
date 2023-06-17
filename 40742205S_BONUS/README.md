# Requirement
The content following is written in chinese,  
if there are errors displaying the characters,  
please install noto-fonts-cjk or other chinese fonts you prefer.  
  
# 個人資料
- 系級：化學系
- 學號：40742205S
- 姓名：賴勇典

# Reference
https://invisible-island.net/ncurses/man/ncurses.3x.html#h3-Initialization  
https://invisible-island.net/ncurses/ncurses-intro.html#functions
  
# Ncurses
Ncurses 的意思是新的 curses (new curses) ，目的是為了延續已經停止開發的 curses 。  
Ncurses 的基本要素如下： 
- 螢幕 (screens)
當前終端機和文字介面的左上至右下的範圍，也就是使用者的可視區域。
- 視窗 (window)
資料結構，紀錄特定螢幕區域的內容。  
視窗是可以重疊和隱藏的，  
代表並非所有視窗中的資料都會輸出至螢幕。  
- 終端螢幕 (terminal screen)
代表使用者當前可以看到的內容。**不等於可視區域。**
  
## 基本常用函式
這裡只討論操作單個終端機或文字介面的常用情況。

- initscr()  
初始化 ncurses 的函式。若沒有特殊需求，通常是第一個被呼叫的 ncurses 函式。

- endwin()  
清除所有視窗，並重設當前終端機或文字介面。通常是最後一個被呼叫的 ncurses 函式。  
**在結束程式之前，務必呼叫此函式。**

- newwin(row, col, y, x)  
初始化一個視窗。 row 是橫排數， col 是縱排數，x 、 y 是視窗左上角的位置。  
**在 ncurses 的坐標系中，以使用者的角度看， x 向右越大， y 向下越大。**  
回傳 WINDOW * 。

- delwin(win)  
刪除特定視窗。

- erase() / werase(win)  
清除所有 / 特定視窗內容。  
實際做法為將視窗內容全部填入空白。

- move(y, x) / wmove(win, y, x)  
將游標移至螢幕 / 特定視窗的 (x, y) 座標。

- clrtoeol() / wclrtoeol(win)  
清除螢幕 / 特定視窗中游標所在的那一行。

- clrtobot() / wclrtobot(win)  
清除螢幕 / 特定視窗中以游標開始至螢幕 / 特定視窗結尾的內容。

- refresh() / wrefresh(win)  
更新所有 / 特定視窗的顯示內容。

- mvprintw(y, x, fmt) / mvwprintw(win, y, x, fmt)  
從螢幕 / 特定視窗中的 (x, y) 座標開始填入 fmt 內容。  
需要呼叫 refresh() / wrefresh(win) 刷新才會顯示。

- keypad(win, bool)  
利用 TRUE / FALSE 來允許 / 關閉特定視窗讀取鍵盤輸入。

- getch / wgetch(win)  
讀取字元輸入至螢幕 / 特定視窗內容。

- box(win, verch, horch)  
在特定視窗中，以 x 從 verch 開始共 verch 格， y 從 horch 開始共 horch 格劃出框線。  
若 verch 或 horch 為 0 則沿著視窗垂直 / 水平邊界畫線。

- attron(attr) / wattron(win, attr) / attroff(attr) / wattroff(win, attr)  
開啟或關閉螢幕 / 特定視窗的內容屬性。
  
**請看範例程式 bonus.c 。使用 make 指令即可編譯。**  
**請先看完註解再 ./bonus 。**