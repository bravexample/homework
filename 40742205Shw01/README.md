# Requirement
The content following is written in chinese,  
if there are errors displaying the characters,  
please install noto-fonts-cjk or other chinese fonts you prefer.  
  
# 個人資料
- 系級：化學系
- 學號：40742205S
- 姓名：賴勇典
  
# 前提
需要提供標頭檔的作業，包括 potato ball ，**我都直接將函式內容寫進標頭檔，沒有額外的來源檔，**  
題目敘述裡沒有要求，我想應該是沒問題的。  
再來，為避免嫌疑，我寫的程式沒有使用 string.h ，僅在 hw0104.c 中使用 mystring.h 。  
關於 oop.h ，**我保證沒有修改結構體與函式宣告**，僅修改＼增加以下內容：  
- 將 #pragma once 改成 #ifndef/#endif
- include stdio.h
- include stdlib.h
- include time.h
- 實作函式內容
  
**以下為各檔案的介紹。**  
  
# mystring.h
- mystrchr、mystrrchr：  
傳入空指標會直接回傳 0 ，'\0' 也被視為字串內容。
- mystrspn、mystrstr：  
只要其中一個指標為 NULL 就會回傳 0 。
- mystrcspn：  
const char *s 若為 NULL 就會回傳 0 ，  
const char *reject 若為 NULL 會執行 reject = ""; 。
- mystrpbrk：  
const char *s 若為 NULL 就會回傳 0 ，  
const char *accept 若為 NULL 會回傳 (char *)s; 。
- mystrtok：  
const char *delim 若為 NULL 就會回傳 0 ，  
使用 char *mystrtok_ptr 和 char *mystrtok_save 儲存資料，  
**請不要重複宣告或使用他們**
  
# insert.h
char **ppResult 為 NULL 會回傳 -1 ，  
const char *pStr1 與 const char *pStr2 皆為 NULL 時會回傳 -1 ，  
int32_t location 大於 pStr1 的長度時也會回傳 -1 。  
若 pStr1 或 pStr2 之一為 0 會指派 "" 。
  
# abacus.h
- abacus_init：  
使用 calloc 。
- abacus_set：  
傳入空指標或字串長度超過 255 就會回傳 -1 。
- abacus_add：  
傳入空指標會回傳 -1 ，  
溢位時會進位，若超過 255 也會回傳 -1 。
- abacus_del：
不會改變 sAbacus.number ，  
如 123 - 123 ， sAbacus.number = 3 ，儲存的值為 0 。  
若結果為負數會回傳 -1 。
- abacus_print：  
不會印出開頭的 0 ，若 pUpperRod 與 pLowerRod 皆為 0 則會印出 0 。
  
# hw0104.c
沒什麼好說的，就 JSON Reader 。
  
# oop.h
我沒有做任何錯誤處理，傳入空指標保證 segmentation fault 。  
**可以的話請不要做這種事。**
  

  
**感謝您的閱讀。**