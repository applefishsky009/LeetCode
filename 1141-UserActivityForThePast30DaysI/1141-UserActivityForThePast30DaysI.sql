Select activity_date as day, Count(Distinct user_id) as active_users
From Activity
Where activity_date Between '2019-06-28' AND '2019-07-27'
GROUP BY activity_date;