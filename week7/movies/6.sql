SELECT AVG(ratings.rating) FROM ratings
LEFT JOIN movies
ON movies.id = ratings.movie_id
WHERE movies.year = 2012;