# Write your MySQL query statement below
Select s.name
From SalesPerson s
Where s.sales_id not in (
Select o.sales_id
From Orders o
Left Join Company c
On o.com_id = c.com_id
Where c.name = 'RED'
)

# Select s.name
# From SalesPerson s
# Where s.sales_id not in (
# Select o.sales_id
# From Orders o
# Where o.com_id in (
# Select c.com_id
# From Company c
# Where c.name = 'RED'
# )
# )

