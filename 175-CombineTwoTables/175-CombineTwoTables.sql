Select firstname, lastname, city, state 
from Person left join Address           -- out join
on Person.personId = Address.personId   -- on 关键字用来连接表