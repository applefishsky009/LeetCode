-- 正则表达式或包含字符串
Select *
From Patients
-- Where conditions REGEXP '(^DIAB1| DIAB1)';
-- WHERE conditions LIKE "DIAB1%" OR INSTR(conditions, " DIAB1");
WHERE conditions rlike '^DIAB1|.*\\sDIAB1';