Select name, SUM(amount) as balance
From Transactions t
Left Join Users u
On t.account = u.account 
Group By t.account
Having balance > 10000;