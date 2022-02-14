/*write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.
Your query should output a table with a single column for the title of each movie.
You may assume that there is only one person in the database with the name Johnny Depp.
You may assume that there is only one person in the database with the name Helena Bonham Carter.*/

SELECT DISTINCT title AS Temp FROM people JOIN stars ON people.id = stars.person_id JOIN movies ON stars.movie_id = movies.id WHERE
name = "Johnny Depp" OR name = "Helena Bonham Carter" GROUP BY title HAVING COUNT(title) > 1;