-- rlike
Select user_id, MAX(time_stamp) as last_stamp
From Logins
Where time_stamp rlike '^2020'
Group By user_id;