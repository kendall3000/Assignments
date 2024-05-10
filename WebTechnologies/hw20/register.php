<?php
echo '<section id="home">';
echo '<h2>Register: Please fill out the following to create an account.</h2>';

if (isset($_POST['submit'])) {
    $username = addslashes($_POST['username']);
    $passText = $_POST['password'];
    $salt = "Tr$52755875aGuacs32$"; 
    $password = hash('sha256', $salt . $passText . $username);
    $dblink = db_connect("user_data");

    $sql = "SELECT `auto_id` FROM `accounts` WHERE `username` = '$username'";
    $result = $dblink->query($sql) or die("<p>Something went wrong with $sql<br>" . $dblink->error);

    if ($result->num_rows > 0) {
        redirect("index.php?page=register&errMsg=accountExists");
    } else {
        $sql = "INSERT INTO `accounts` (`username`, `auth_hash`) VALUES ('$username', '$password')";
        $dblink->query($sql) or die("<p>Something went wrong with $sql<br>" . $dblink->error);
        redirect("index.php?page=login");
    }
}

echo '<form method="post" action="">';
echo '<div class="form-group">';
echo '<label class="control-label" for="username">Username: </label>';
echo '<input type="text" id="username" name="username" class="form-control"/>';
echo '<div id="usernameFeedback"></div>';
echo '</div>';

echo '<div class="form-group">';
echo '<label class="control-label" for="password">Password: </label>';
echo '<input type="password" id="password" name="password" class="form-control"/>';
echo '<div id="passwordFeedback"></div>';
echo '</div>';

echo '<button class="btn btn-primary" name="submit" value="submit">Submit</button>';
echo '</form>';

echo '</section>';
?>

