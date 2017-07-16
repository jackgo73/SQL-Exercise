# SQL Exercises/The computer store

## Relational Schema

![Computer-store-db](img/Computer-store-db.png)

Please note the datatypes given are SQLite datatypes.

PK and FK stand for primary key and foreign key respectively.

```sql
CREATE TABLE Manufacturers (
    Code          integer PRIMARY KEY,
    Name          text
);


CREATE TABLE Products (
    Code          integer PRIMARY KEY,
    Name          text,
    Price         real,
    Manufacturer  integer REFERENCES Manufacturers (Code)
);


```

## Generated Data
```sql
INSERT INTO Manufacturers values ( generate_series(1,10000), md5(random()::text));

INSERT INTO Products values ( 
    generate_series(1,100000), 
    md5(random()::text),
    random()::real*10000,
    (random()*10000)::integer
);

```

## Exercises

1. Select the names of all the products in the store.

```sql
SELECT * FROM Products;
```

2. Select the names and the prices of all the products in the store.

```sql
SELECT Name, Price FROM Products;
```


3. Select the name of the products with a price less than or equal to $200.

```sql
SELECT Name FROM Products WHERE Price<=200;
```

4. Select all the products with a price between $60 and $120.

```sql
SELECT * FROM Products WHERE Price<=120 AND Price>=60;

SELECT * FROM Products WHERE Price BETWEEN 60 AND 120;
```

5. Select the name and price in cents (i.e., the price must be multiplied by 100).

```sql
SELECT Name, Price * 100 FROM Products;
 

SELECT Name, Price * 100 AS PriceCents FROM Products;
```

6. Compute the average price of all the products.

```sql
SELECT AVG(Price) FROM Products;
```

7. Compute the average price of all products with manufacturer code equal to 2.

```sql
SELECT AVG(Price) FROM Products WHERE Manufacturer=2;
```

8. Compute the number of products with a price larger than or equal to $180.

```sql
SELECT count(*) FROM Products WHERE Price >= 180;
```

9. Select the name and price of all products with a price larger than or equal to $180, and sort first by price (in descending order), and then by name (in ascending order).

```sql
SELECT Name, Price FROM Products WHERE Price >= 180 ORDER BY Price DESC, Name ASC;
```

10. Select all the data from the products, including all the data for each product's manufacturer.

```sql
SELECT * FROM Products, Manufacturers WHERE Products.Manufacturer = Manufacturers.Code;

SELECT * FROM Products INNER JOIN Manufacturers ON Products.Manufacturer = Manufacturers.Code;
```

11. Select the product name, price, and manufacturer name of all the products.

```sql
SELECT Products.Name, Price, Manufacturers.Name
  FROM Products, Manufacturers
  WHERE Products.Manufacturer = Manufacturers.Code;

SELECT Products.Name, Price, Manufacturers.Name 
  FROM Products INNER JOIN Manufacturers 
  ON Products.Manufacturer = Manufacturers.Code;
```

12. Select the average price of each manufacturer's products, showing only the manufacturer's code.

```sql
SELECT AVG(Price), Manufacturer FROM Products GROUP BY Manufacturer;
```

13. Select the average price of each manufacturer's products, showing the manufacturer's name.

```sql
SELECT AVG(Price), Manufacturers.Name
  FROM Products, Manufacturers
  WHERE Products.Manufacturer = Manufacturers.Code
  GROUP BY Manufacturers.Name;

SELECT AVG(Price), Manufacturers.Name 
  FROM Products INNER JOIN Manufacturers 
  ON Products.Manufacturer = Manufacturers.Code
  GROUP BY Manufacturers.Name;
```

14. Select the names of manufacturer whose products have an average price larger than or equal to $150.

```sql
 /* Without INNER JOIN */
SELECT AVG(Price), Manufacturers.Name
  FROM Products, Manufacturers
  WHERE Products.Manufacturer = Manufacturers.Code
  GROUP BY Manufacturers.Name
  HAVING AVG(Price) >= 150;

/* HAVING与WHERE不同： WHERE会在应用GROUP BY之前过滤个体行，而HAVING过滤由 GROUP BY创建的分组行。 */

SELECT AVG(Price), Manufacturers.Name
  FROM Products, Manufacturers
  WHERE Products.Manufacturer = Manufacturers.Code
  GROUP BY Manufacturers.Name
  HAVING AVG(Price) >= 150;
```


15. Select the name and price of the cheapest product.

```
SELECT Name, Price FROM Products ORDER BY Price ASC LIMIT 1;

SELECT Name, Price FROM Products WHERE Price=(SELECT MIN(Price) FROM Products);
```

16. Select the name of each manufacturer along with the name and price of its most expensive product.

这个我在stackoverflow上问了一个问题
https://stackoverflow.com/questions/45126123/use-groupy-by-to-get-the-name-and-price-of-its-most-expensive-product

```
SELECT Manufacturers.Name AS ManufacturersName, MAX(Price)
  FROM Products, Manufacturers
  WHERE Products.Manufacturer = Manufacturers.Code
  GROUP BY Manufacturers.Name;

SELECT manufacturersname, max, Products.Name 
FROM 
  (
    SELECT Manufacturers.Name AS ManufacturersName, MAX(Price)
      FROM Products, Manufacturers
      WHERE Products.Manufacturer = Manufacturers.Code
      GROUP BY Manufacturers.Name
  ) AS subtable, Products
WHERE subtable.max=Products.Price;


SELECT A.Name, A.Price, F.Name
  FROM Products A INNER JOIN Manufacturers F
  ON A.Manufacturer = F.Code
  AND A.Price =
    (
      SELECT MAX(A.Price)
        FROM Products A
        WHERE A.Manufacturer = F.Code
    );
```

