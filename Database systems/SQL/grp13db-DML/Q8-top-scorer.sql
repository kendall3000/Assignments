-- Query 8: Top 5 Players with Total Points in a Specific Season and Different Positions
SELECT
    player.player_id,
    player.player_fname,
    player.player_lname,
    player.player_position,
    SUM(player_per_game_stats.field_goals + player_per_game_stats.threepoint_field_goals + player_per_game_stats.free_throws) AS total_points
FROM
    player
JOIN
    player_per_game_stats ON player.player_id = player_per_game_stats.player_id
JOIN
    game ON player_per_game_stats.game_id = game.game_id
WHERE
    game.season_id = 4 -- 4, 5, or 6
GROUP BY
    player.player_id, player.player_fname, player.player_lname, player.player_position
ORDER BY
    total_points DESC
LIMIT 5;
