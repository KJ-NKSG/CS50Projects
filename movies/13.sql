/*write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.
Your query should output a table with a single column for the name of each person.
There may be multiple people named Kevin Bacon in the database. Be sure to only select the Kevin Bacon born in 1958.
Kevin Bacon himself should not be included in the resulting list.*/

SELECT name FROM movies JOIN stars ON movies.id = stars.movie_id JOIN people ON stars.person_id = people.id
WHERE movie_id IN (SELECT movie_id FROM movies JOIN stars ON movies.id = stars.movie_id JOIN
people ON stars.person_id = people.id WHERE name = "Kevin Bacon" and birth = 1958) GROUP BY name HAVING name <> "Kevin Bacon";
