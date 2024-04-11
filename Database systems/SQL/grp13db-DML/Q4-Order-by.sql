-- Select statement with an order by clause
SELECT
    player_id, player_fname, player_lname,height
FROM player
ORDER BY player_lname ASC, player_fname ASC;
