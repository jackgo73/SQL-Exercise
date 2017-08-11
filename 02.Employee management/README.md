# SQL Exercises/Employee management

## Relational Schema

`Oracle12c`

![Computer-store-db](img/Employees.png)

```sql
 CREATE TABLE Departments (
   Code INTEGER PRIMARY KEY NOT NULL,
   Name CLOB NOT NULL ,
   Budget REAL NOT NULL 
 );
 
 CREATE TABLE Employees (
   SSN INTEGER PRIMARY KEY NOT NULL,
   Name CLOB NOT NULL ,
   LastName CLOB NOT NULL ,
   Department INTEGER NOT NULL , 
   CONSTRAINT fk_Departments_Code FOREIGN KEY(Department) 
   REFERENCES Departments(Code)
 );
```

## Sample Dataset
```sql
INSERT INTO Departments(Code,Name,Budget) VALUES(14,'IT',65000);
INSERT INTO Departments(Code,Name,Budget) VALUES(37,'Accounting',15000);
INSERT INTO Departments(Code,Name,Budget) VALUES(59,'Human Resources',240000);
INSERT INTO Departments(Code,Name,Budget) VALUES(77,'Research',55000);

INSERT INTO Employees(SSN,Name,LastName,Department) VALUES('123234877','Michael','Rogers',14);
INSERT INTO Employees(SSN,Name,LastName,Department) VALUES('152934485','Anand','Manikutty',14);
INSERT INTO Employees(SSN,Name,LastName,Department) VALUES('222364883','Carol','Smith',37);
INSERT INTO Employees(SSN,Name,LastName,Department) VALUES('326587417','Joe','Stevens',37);
INSERT INTO Employees(SSN,Name,LastName,Department) VALUES('332154719','Mary-Anne','Foster',14);
INSERT INTO Employees(SSN,Name,LastName,Department) VALUES('332569843','George','O''Donnell',77);
INSERT INTO Employees(SSN,Name,LastName,Department) VALUES('546523478','John','Doe',59);
INSERT INTO Employees(SSN,Name,LastName,Department) VALUES('631231482','David','Smith',77);
INSERT INTO Employees(SSN,Name,LastName,Department) VALUES('654873219','Zacary','Efron',59);
INSERT INTO Employees(SSN,Name,LastName,Department) VALUES('745685214','Eric','Goldsmith',59);
INSERT INTO Employees(SSN,Name,LastName,Department) VALUES('845657245','Elizabeth','Doe',14);
INSERT INTO Employees(SSN,Name,LastName,Department) VALUES('845657246','Kumar','Swamy',14);
```

## Exercises

1 Select the last name of all employees.

```sql
SELECT LastName FROM Employees;
```

2 Select the last name of all employees, without duplicates.

```sql
SELECT DISTINCT TO_CHAR(LastName) FROM Employees;
```

3 Select all the data of employees whose last name is "Smith".

```sql
SELECT * FROM Employees WHERE TO_CHAR(lastname)='Smith';

SELECT * FROM Employees WHERE dbms_lob.compare(lastname, 'Smith') = 0;
```

4 Select all the data of employees whose last name is "Smith" or "Doe".

```sql
SELECT * FROM Employees WHERE TO_CHAR(lastname)='Smith' OR TO_CHAR(lastname)='Doe';
```

5 Select all the data of employees that work in department 14.

```sql
SELECT * FROM Employees WHERE Department = 14;
```

6 Select all the data of employees that work in department 37 or department 77.

```sql
SELECT * FROM Employees WHERE Department = 37 OR Department = 77;

SELECT * FROM Employees WHERE Department IN (37, 77);
```

7 Select all the data of employees whose last name begins with an "S".

```sql
SELECT * FROM Employees WHERE lastname like 'S%';
```

8 Select the sum of all the departments' budgets.

```sql
SELECT SUM(budget) FROM departments;
```

9 Select the number of employees in each department (you only need to show the department code and the number of employees).

```sql
SELECT department,COUNT(*) FROM employees GROUP BY department; 
```

10 Select all the data of employees, including each employee's department's data.

```sql
SELECT SSN,
       E          . NAME AS Name_E,
       LastName,
       D          . NAME AS Name_D,
       Department,
       Code,
       Budget
  FROM Employees E
 INNER JOIN Departments D
    ON E.Department = D.Code;

```

11 Select the name and last name of each employee, along with the name and budget of the employee's department.

```sql
SELECT E.NAME AS Employees_Name,
       E.LastName AS Employees_LastName,
       D.NAME AS Departments_Name,
       D.Budget AS Departments_Budget
  FROM Employees E
  LEFT JOIN Departments D
    ON E.Department = D.Code;

```

12 Select the name and last name of employees working for departments with a budget greater than $60,000.

```sql
-- 不要使用left join .. on .. and budget > 60000 ，否则不合条件的行会当做null拼接到后面。
SELECT E.NAME AS Employees_Name, E.LastName AS Employees_LastName, D.Budget
  FROM Employees E
 INNER JOIN Departments D
    ON E.Department = D.Code
   AND D.Budget > 60000;

SELECT E.NAME AS Employees_Name, E.LastName AS Employees_LastName, D.Budget
  FROM Employees E
 INNER JOIN Departments D
    ON E.Department = D.Code
 WHERE D.Budget > 60000;

SELECT name, lastname
  FROM employees
 WHERE department IN (SELECT code FROM departments WHERE budget > 60000);
```

13 Select the departments with a budget larger than the average budget of all the departments.

```sql
select *
  from departments
 where budget > (select avg(budget) from departments);
```

14 Select the names of departments with more than two employees.

```sql
-- where 子句的作用是在对查询结果进行分组前，将不符合where条件的行去掉，即在分组之前过滤数据，条件中不能包含聚组函数，使用where条件显示特定的行。
-- having 子句的作用是筛选满足条件的组，即在分组之后过滤数据，条件中经常包含聚组函数，使用having 条件显示特定的组，也可以使用多个分组标准进行分组。

SELECT Name
  FROM Departments
 WHERE Code IN (SELECT Department
                  FROM Employees
                 GROUP BY Department
                HAVING COUNT(*) > 2);

SELECT Departments.Name
  FROM Employees
 INNER JOIN Departments
    ON Department = Code
 GROUP BY Departments.Name
HAVING COUNT(*) > 2;
```

15 Select the name and last name of employees working for departments with second lowest budget.

```sql
SELECT NAME, LastName
  FROM Employees
 WHERE department =
       (SELECT code
          FROM (SELECT code, DENSE_RANK() OVER(ORDER BY budget ASC) rnk
                  FROM departments)
         WHERE rnk = 2)
```

16 Add a new department called "Quality Assurance", with a budget of $40,000 and departmental code 11. Add an employee called "Mary Moore" in that department, with SSN 847-21-9811.

```sql
INSERT INTO departments VALUES (11, 'Quality Assurance', 40000);

INSERT INTO employees VALUES (847219811, 'Mary', 'Moore', 11);
```

17 Reduce the budget of all departments by 10%.

```sql
UPDATE departments SET budget = budget * 0.9
```

18 Reassign all employees from the Research department (code 77) to the IT department (code 14).

```sql
UPDATE employees SET department = 14 WHERE department = 77;
```

19 Delete from the table all employees in the IT department (code 14).

```sql
DELETE FROM employees WHERE department = 14
```

20 Delete from the table all employees who work in departments with a budget greater than or equal to $60,000.

```sql
DELETE FROM employees
 WHERE department IN (select code from departments where budget >= 60000);
```

21 Delete from the table all employees.

```sql
DELETE FROM employees;
```

