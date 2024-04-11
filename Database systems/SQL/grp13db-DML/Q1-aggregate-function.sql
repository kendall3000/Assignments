-- Select total players and average weight per team, excluding teams with no players
SELECT team.team_id, team.team_name, COUNT(player.player_id) AS total_players, AVG(player.weight) AS avg_weight
FROM team
LEFT JOIN roster ON team.team_id = roster.team_id
LEFT JOIN roster_line ON roster.roster_id = roster_line.roster_id
LEFT JOIN player ON roster_line.player_id = player.player_id
WHERE player.player_id IS NOT NULL
GROUP BY team.team_id, team.team_name;


