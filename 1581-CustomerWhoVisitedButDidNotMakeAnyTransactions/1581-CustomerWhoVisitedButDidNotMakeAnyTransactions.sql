Select DISTINCT customer_id, Count(customer_id) as count_no_trans
From Visits
Where visit_id not in (
    Select DISTINCT visit_id
    From Transactions
)
Group By customer_id;