-- 行转列, 列转行用Union, Select 后面是值+键的形式
SELECT product_id, 'store1' store, store1 price
FROM Products
WHERE store1 IS NOT NULL
Union All
SELECT product_id, 'store2' store, store2 price
FROM Products
WHERE store2 IS NOT NULL
Union All
SELECT product_id, 'store3' store, store3 price
FROM Products
WHERE store3 IS NOT NULL;