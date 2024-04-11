-- Two queries of your choice with comments:
-- Query 1: List unique combinations of player names and their positions (limit to 5 players with different positions)
-- Generate random lineup
SELECT DISTINCT
    CONCAT(player_fname, ' ', player_lname) AS player_full_name,
    player_position
FROM
    player
LIMIT 5;
