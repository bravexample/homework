# Requirement
The content following is written in chinese,  
if there are errors displaying the characters,  
please install noto-fonts-cjk or other chinese fonts you prefer.  
  
# 個人資料
- 系級：化學系
- 學號：40742205S
- 姓名：賴勇典
  
# 前提
**hw0201 我直接將函式內容寫進標頭檔，沒有額外的來源檔，**  
題目敘述裡沒有特別要求，我想應該是沒問題的。  
**我只有寫 hw0201, hw0202, hw0203。**  
  
**以下為各檔案的介紹。**  
  
# matrix.h
- 結構宣告：  
typedef struct _sMatrix {  
    int32_t row;  
    int32_t column;  
    int32_t **data;  
} sMatrix;  
- matrix_init：  
只要 m 或 n 為零，回傳 -1 。
- matrix_free：  
若 pA 為空，回傳 -1 。
- matrix_set：  
執行 pM->data[m][n] = value; 。  
m 或 n 超出 pM 範圍就回傳 -1 。
- matrix_print：  
若 pM 為空，函式回傳。（ void 你還指望我回三小，哭阿紀老）
- matrix_add：  
只要 pB 與 pC 大小不相等或為零，回傳 -1 。
- matrix_multiply：  
只要 pB->column 與 pC->row 不相等或為零，回傳 -1 。
- matrix_transpose：  
若 pA 為空，回傳 -1 。
- matrix_det：  
若 pA 或 pAns 為空或 pA 不是方陣，回傳 -1 。

# hw0202
宣告了路徑最大長度與資料夾內檔案的最大個數：  
#define PATH_MAX 4096  
#define FILE_MAX 4096  
**請不要超限**  
**此程式不會印出 . 與 .. 資料夾。**  
  
# hw0203
輸出格式如下：
"%d %s %s:%s %s\n", 記數, book_id, chapter, verse, text  
（對，除了記數都是 %s ，你沒看錯）  
  
  

**檔案至此結束，感謝您的閱讀。**