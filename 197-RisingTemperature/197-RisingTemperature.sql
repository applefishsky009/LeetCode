Select w1.id As id
From Weather w1, Weather w2
Where DateDiff(w1.recordDate, w2.recordDate) = 1
And w1.Temperature > w2.Temperature;