<?php
echo '<section id="home">';
echo '<h2>Login: Please enter your login information below to sign in.</h2>';

//if (isset($_POST['submit'])) {
    echo '<form method="post" action="">';
    echo '<div class="form-group">';
    echo '<label class="control-label" for="username">Username: </label>';
    echo '<input type="text" id="username" name="username" class="form-control"/>';
    echo '<div id="fnFeedback"></div>';
    echo '</div>';
    
    echo '<div class="form-group">';
    echo '<label class="control-label" for="password">Password: </label>';
    echo '<input type="password" id="password" name="password" class="form-control"/>';
    echo '<div id="fnFeedback"></div>';
    echo '</div>';
    
    echo '<button class="btn btn-primary" name="submit" value="submit">Submit</button>';
    echo '</form>';

if(isset($_POST['submit'])) {
	$username = addslashes($_POST['username']);
	$passText = $_POST['password'];
	$salt = "Tr$52755875aGuacs32$"; 
	$password = hash('sha256', $salt.$passText.$username);
	$dblink = db_connect("user_data");
	$sql = "SELECT `auto_id` FROM `accounts` WHERE `auth_hash` = '$password'";
	$result = $dblink->query($sql) or 
		die("<p>Something went wrong with $sql<br>" . $dblink->error);
	if ($result->num_rows <= 0) {
		redirect("index.php?page=register&errMsg=invalidAuth");
	} else {
		$salt=microtime();
		$sid=hash('sha256', $salt.$password);
		$sql="UPDATE `accounts` set `session_id`='$sid' where `auth_hash`='$password'";
		$dblink->query($sql) or 
			die("<p>Something went wrong with $sql<br>" . $dblink->error);
		redirect("index.php?page=results&sid=$sid");
	}
	
}
echo '</section>';
?>
