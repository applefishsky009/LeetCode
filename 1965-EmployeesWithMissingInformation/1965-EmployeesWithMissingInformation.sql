-- union all 联合多表 group by 按照id分组 having 条件筛选 order by 升序排序 Select employee_id
From (
    Select employee_id From Employees
    Union ALL 
    Select employee_id From Salaries
) as ans
Group By employee_id
Having count(employee_id) = 1
Order By employee_id;