SELECT distinct(people.name) FROM people
INNER JOIN stars ON stars.person_id = people.id
INNER JOIN movies on movies.id = stars.movie_id
WHERE NOT (people.name = "Kevin Bacon" AND people.birth = 1958) AND movies.id IN
(SELECT movies.id FROM people
INNER JOIN stars ON stars.person_id = people.id
INNER JOIN movies ON movies.id = stars.movie_id
WHERE people.name = "Kevin Bacon" AND people.birth = 1958);
