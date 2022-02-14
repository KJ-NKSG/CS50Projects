/*write a SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0.
Your query should output a table with a single column for the name of each person.

SELECT name FROM people WHERE id IN
(SELECT person_id FROM directors WHERE movie_id IN
(SELECT id FROM movies WHERE id IN (SELECT movie_id FROM ratings where rating >= 9.0))); */

SELECT DISTINCT name FROM ratings JOIN movies ON ratings.movie_id = movies.id JOIN directors ON movies.id = directors.movie_id JOIN people ON directors.person_id = people.id WHERE rating >= 9.0;


