Update Salary
Set 
    sex = Case sex
        When 'm' Then 'f'
        Else 'm'
    End;