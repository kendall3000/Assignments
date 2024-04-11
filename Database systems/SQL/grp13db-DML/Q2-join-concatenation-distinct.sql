-- Select distinct player names along with their jersey numbers and team names
SELECT DISTINCT 
    CONCAT(player.player_fname, ' ', player.player_lname) AS player_name,
    player.jersey_number,
    team.team_name
FROM player
JOIN roster_line ON player.player_id = roster_line.player_id
JOIN roster ON roster_line.roster_id = roster.roster_id
JOIN team ON roster.team_id = team.team_id;
