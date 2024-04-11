-- Select players with average points per game above the overall average
SELECT 
    player.player_id,
    CONCAT(player.player_fname, ' ', player.player_lname) AS player_name,
    AVG(stats.field_goals + stats.threepoint_field_goals * 3 + stats.free_throws) AS avg_ppg
FROM player
JOIN player_per_game_stats stats ON player.player_id = stats.player_id
GROUP BY player.player_id
HAVING AVG(stats.field_goals + stats.threepoint_field_goals * 3 + stats.free_throws) > (
    -- Subquery to calculate overall average points per game
    SELECT AVG(stats.field_goals + stats.threepoint_field_goals * 3 + stats.free_throws)
    FROM player_per_game_stats stats
);
