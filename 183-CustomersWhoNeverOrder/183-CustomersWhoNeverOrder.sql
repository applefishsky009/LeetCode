Select Customers.name as 'Customers'
from Customers
Where Customers.id not in (
    Select CustomerId from Orders
);