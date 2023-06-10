# Requirement
The content following is written in chinese,  
if there are errors displaying the characters,  
please install noto-fonts-cjk or other chinese fonts you prefer.  
  
# 個人資料
- 系級：化學系
- 學號：40742205S
- 姓名：賴勇典
  
**以下是各程式的介紹**  
  
## fin01.c
如有違法輸入，一律輸出 help 資訊。  
-h 和 --help 不另行偵測。  
如程式出現問題，應該會得到 perror 輸出的錯誤訊息。  
順帶一提， n 過大可能導致最終比例跑掉，  
出現奇怪的結果。  
  
## schedule.c
add_job 會將 job 加在 head 之後，不會排序。
至於 schedule ...我盡力了。