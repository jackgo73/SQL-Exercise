# SQL Exercises/Movie theatres

## Relational Schema

`Oracle12c`

![Computer-store-db](img/Sql_movie_theaters.png)

```sql
 CREATE TABLE Movies (
   Code INTEGER PRIMARY KEY,
   Title VARCHAR(255) NOT NULL,
   Rating VARCHAR(255) 
 );
 
 CREATE TABLE MovieTheaters (
   Code INTEGER PRIMARY KEY,
   Name VARCHAR(255) NOT NULL,
   Movie INTEGER,  
     FOREIGN KEY (Movie) REFERENCES Movies(Code)
 ) ;
```

## Sample Dataset
```sql
 INSERT INTO Movies(Code,Title,Rating) VALUES(9,'Citizen King','G');
 INSERT INTO Movies(Code,Title,Rating) VALUES(1,'Citizen Kane','PG');
 INSERT INTO Movies(Code,Title,Rating) VALUES(2,'Singin'' in the Rain','G');
 INSERT INTO Movies(Code,Title,Rating) VALUES(3,'The Wizard of Oz','G');
 INSERT INTO Movies(Code,Title,Rating) VALUES(4,'The Quiet Man',NULL);
 INSERT INTO Movies(Code,Title,Rating) VALUES(5,'North by Northwest',NULL);
 INSERT INTO Movies(Code,Title,Rating) VALUES(6,'The Last Tango in Paris','NC-17');
 INSERT INTO Movies(Code,Title,Rating) VALUES(7,'Some Like it Hot','PG-13');
 INSERT INTO Movies(Code,Title,Rating) VALUES(8,'A Night at the Opera',NULL);
 
 INSERT INTO MovieTheaters(Code,Name,Movie) VALUES(1,'Odeon',5);
 INSERT INTO MovieTheaters(Code,Name,Movie) VALUES(2,'Imperial',1);
 INSERT INTO MovieTheaters(Code,Name,Movie) VALUES(3,'Majestic',NULL);
 INSERT INTO MovieTheaters(Code,Name,Movie) VALUES(4,'Royale',6);
 INSERT INTO MovieTheaters(Code,Name,Movie) VALUES(5,'Paraiso',3);
 INSERT INTO MovieTheaters(Code,Name,Movie) VALUES(6,'Nickelodeon',NULL);
```

## Exercises

1 Show all unrated movies.

```sql
SELECT * FROM movies WHERE rating IS NULL;
```

2 Select all movie theaters that are not currently showing a movie.

```sql
SELECT * FROM MovieTheaters WHERE Movie IS NULL;
```

3 Select all data from all movie theaters and, additionally, the data from the movie that is being shown in the theater (if one is being shown).

```sql
SELECT *
FROM MovieTheaters
LEFT JOIN Movies
ON MovieTheaters.Movie = Movies.Code;
```

4 Select all data from all movies and, if that movie is being shown in a theater, show the data from the theater.

```sql
SELECT *
FROM movies
LEFT JOIN movietheaters
ON movietheaters.movie = movies.code;
```

5 Show the titles of movies not currently being shown in any theaters.

```sql
SELECT *
FROM movies
WHERE code NOT IN
  ( SELECT movie FROM movietheaters WHERE movie IS NOT NULL
  );

SELECT Movies.Title
FROM MovieTheaters
RIGHT JOIN Movies
ON MovieTheaters.Movie     = Movies.Code
WHERE MovieTheaters.Movie IS NULL;
```

6 Add the unrated movie "One, Two, Three".

```sql
INSERT INTO Movies(Title,Rating) VALUES('One, Two, Three',NULL);
```

7 Set the rating of all unrated movies to "G".

```sql
UPDATE Movies SET Rating='G' WHERE Rating IS NULL;
```

8 Remove movie theaters projecting movies rated "NC-17".

```sql
 DELETE FROM MovieTheaters WHERE Movie IN
   (SELECT Code FROM Movies WHERE Rating = 'NC-17');
```

