-- 多键group, 加减
Select e.event_day as day, e.emp_id as emp_id, (SUM(e.out_time) - SUM(e.in_time)) as total_time
From Employees as e
Group by e.event_day, e.emp_id