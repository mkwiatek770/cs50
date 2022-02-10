WITH common_movies AS (
    SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = 'Johnny Depp')
    INTERSECT
    SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = 'Helena Bonham Carter')
)
SELECT title FROM movies
WHERE id IN common_movies;
