Select s.product_id, p.product_name
From Sales as s 
Left Join Product as p
On s.product_id = p.product_id
Group by s.product_id
Having MIN(sale_date) >= '2019-01-01'
And MAX(sale_date) <= '2019-03-31';