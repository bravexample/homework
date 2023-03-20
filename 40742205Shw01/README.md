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
- mystrchr、mystrrchr：傳入空指標會直接回傳 0 ，'\0' 也被視為字串內容。
- mystrspn、mystrstr：只要其中一個指標為 NULL 就會回傳 0 。
- mystrcspn：const char *s 若為 NULL 就會回傳 0 ，  
const char *reject 若為 NULL 會執行 reject = ""; 。
- mystrpbrk：const char *s 若為 NULL 就會回傳 0 ，  
const char *accept 若為 NULL 會回傳 (char *)s; 。
- mystrtok：const char *delim 若為 NULL 就會回傳 0 ，  
使用 char *mystrtok_ptr 和 char *mystrtok_save 儲存資料，  
**請不要重複宣告或使用他們**
  
# insert.h