-- 去重，排序，多个group
Select date_id, make_name, COUNT(DISTINCT(lead_id)) as unique_leads, COUNT(DISTINCT(partner_id)) as unique_partners
From DailySales
Group By date_id, make_name
Order By date_id;