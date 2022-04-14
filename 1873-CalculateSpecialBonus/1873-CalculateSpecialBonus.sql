-- case when then else end
Select employee_id, 
Case When 
    Mod(employee_id, 2) = 1 And name not rlike '^M' Then salary Else 0 End as bonus
From Employees
Order By employee_id;