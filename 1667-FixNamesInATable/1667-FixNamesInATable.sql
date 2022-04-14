--  字符串拼接，大小写转化， 字符分割
Select user_id as user_id,
CONCAT(Upper(Left(name, 1)), Lower(Right(name, length(name) - 1))) as name
From Users
Order By user_id;