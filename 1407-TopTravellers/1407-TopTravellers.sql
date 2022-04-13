Select u.name as name, IFNULL(SUM(r.distance), 0) as travelled_distance
From Users as u
Left Join Rides as r
On r.user_id = u.id
Group by r.user_id
Order By travelled_distance DESC, name ASC;