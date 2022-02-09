SELECT name FROM people, movies
JOIN stars ON (people.id=stars.person_id AND movies.id=stars.movie_id)
WHERE title = "Toy Story";