WITH bacon_movies AS (
    SELECT movie_id FROM stars JOIN people ON stars.person_id=people.id WHERE name = 'Kevin Bacon' AND birth = 1958
)
SELECT name FROM people
JOIN stars ON people.id=stars.person_id
WHERE movie_id IN bacon_movies
EXCEPT
SELECT 'Kevin Bacon';