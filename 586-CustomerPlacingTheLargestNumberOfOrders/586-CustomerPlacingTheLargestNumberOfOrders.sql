Select customer_number
From Orders
Group by customer_number
Order by Count(*) DESC
Limit 1;