# Requirement
The content following is written in chinese,  
if there are errors displaying the characters,  
please install noto-fonts-cjk or other chinese fonts you prefer.  
  
# 個人資料
- 系級：化學系
- 學號：40742205S
- 姓名：賴勇典
  
# 前提
**我只有寫 hw0301, hw0302, hw0303, hw0304 & hw0306。**  

**以下為各檔案的介紹。**  

# hw0301.c
有 -e, -d, -k, -i, -o 選項，內容如下：  
-e, -d：加密\解密，必須擇一輸入，否則回傳-1。  
-k：金鑰檔，未提供則回傳-1。  
-i：要被加密的檔案，未提供則回傳-1。  
-o：輸出檔，如檔案已存在則會被複寫，未提供則回傳-1。  
範例： ./hw0301 -e -k key_file -i input_file -o cipher  
選項位置可對調。  

# hw0302.c
有 -a, -d 選項，內容如下：  
-a：預設，將路徑以字典序遞增排序。  
-d：將路徑以字典序遞減排序。  
範例：  
./hw0302 test.zip  
./hw0302 -d test.zip  
格式不正確會輸出幫助訊息：  
Usage: ./hw0305 [OPTION]...  
Example: ./hw0305 -d test.zip  
-a: default, the display order should be file name ASCII ascending order.  
-d: the display order should be file name ASCII descending order.  

# hw0303.c
有 -x, -y, -w, -h, -n, -i, -o 選項，沒圖很難解釋我就不多說了。  
-x, -y, -w, -h, -i 缺一則回傳-1。  

# hw0304.c
請照著我的步驟走：  
Enter the path of file:  
輸入遊戲存檔所在資料夾**全稱**，  
如：/home/user/JINJONG  
**~/JINJONG我試過會找不到**  
**最後可不打斜線，我會補**  
  
Enter the file to change (1 to 3, 0 to exit):  
這遊戲就三個存檔，看你要改哪個  
**請不要更動存檔名稱，會找不到**  

Choose an option to do:  
        0. Exit  
        1. Maximize attributes  
        2. Maximize items  
        3. Maximize arts  
        4. Change data by position of file (Don't use this option if you don't know WTF are you doing)  
Your choice:   
0 結束程式  
1 將人物能力值最大化(全部改成0x7FFF)  
2 獲取所有物品，且數值最大化(全部改成0x7FFF)  
3 挑選十種武功(最多就持有十種，我沒輒)，等級最大化(全部改成0x7FFF)  
武功對應值程式裡不提供，因為一次印出這麼多東西會讓人亂掉  
[武功參考網址](https://blog.xuite.net/dsl0817/blog/228046379)  
4 自己指定要修改的位元並輸入值(如果不知道自己ㄊㄇㄉ在改什麼，就別用)  
**有些輸入是要用十六進位的，會以(Hex)提示**  

# hw0305.c
我只寫出一個能寫入MIDI的header的程式...  

# hw0306.md
恩...沒啥好說  
  
**檔案結尾**