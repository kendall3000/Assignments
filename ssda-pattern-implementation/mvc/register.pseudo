// get registration information from the user
$username = $_POST['username'];
$pw1 = $_POST['password1'];
$pw2 = $_POST['password2'];

// validate 
if ($pw1 != $pw2 || !valid($pw1) || !valid($username))
    return redirectBack(400);

// hash password
$pwHash = hash($pw1);

$title = "<title>Welcome $username</title>";

// initialize database
$db = getDatabase('myHost', 'mypassword', 'myDb');
$table = "users";

// create user
$success = $db->query("INSERT INTO $table (username, password) 
    VALUES ($username, $pwHash);");

if(!$success)
    return redirectBack(500);

// set up opening tag 
if(getCurrentSeason() == 'summer');
    $h1Style = '<h1 style="color: RED">';
else
    $h1Style = '<h1 style="color: BLUE">';

echo "<html>
            <head>
                $title
            </head>
            <body>
                $h1Style
                    Welcome $username
                </h1>
            </body>
        </html>";
