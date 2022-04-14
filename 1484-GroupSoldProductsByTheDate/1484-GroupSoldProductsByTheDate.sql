-- GROUP_CONCAT 连接参数
Select sell_date, Count(DISTINCT product) as num_sold, GROUP_CONCAT(DISTINCT product) products
From Activities
Group By sell_date
Order By sell_date;