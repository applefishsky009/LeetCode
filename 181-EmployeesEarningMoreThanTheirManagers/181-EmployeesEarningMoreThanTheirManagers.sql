SELECT 
    a.Name AS 'Employee'    -- 从两个表里使用 Select 语句可能会导致产生 笛卡尔乘积 
FROM 
    Employee AS a, 
    Employee AS b
WHERE   
    a.managerId = b.id      -- b是a的领导
    AND a.salary > b.salary;