SELECT title FROM movies, people
JOIN stars ON (people.id=stars.person_id AND ratings.movie_id=stars.movie_id)
JOIN ratings ON movies.id=ratings.movie_id
WHERE name = "Chadwick Boseman"
ORDER BY rating DESC
LIMIT 5;