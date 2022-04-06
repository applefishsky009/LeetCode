Delete p1 
From Person p1, Person p2
Where p1.email = p2.email and p1.id > p2.id -- 不重复的也被保留，重复的删掉id大的