<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Contact Form</title>
    <!-- Bootstrap core CSS -->
    <link href="assets/css/bootstrap.min.css" rel="stylesheet">
    <link rel="stylesheet" href="assets/css/font-awesome.min.css">
    <!-- Custom styles for this template -->
    <link href="assets/css/style.css" rel="stylesheet">
</head>
<body>

<!-- Navigation -->
<nav class="navbar navbar-default navbar-fixed-top .navbar-default.navbar-shrink">
    <div class="container">
        <!-- Brand and toggle get grouped for better mobile display -->
        <div class="navbar-header page-scroll">
            <button type="button" class="navbar-toggle" data-toggle="collapse" data-target="#bs-example-navbar-collapse-1">
                <span class="sr-only">Toggle navigation</span>
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
            </button>
            <a class="navbar-brand page-scroll" href="#page-top"><img src="../images/Projectile.png" alt="Kendall's Website" class="logo-image"><p>Kendall's Website</p></a>
        </div>
       
        <div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
            <ul class="nav navbar-nav navbar-right">
                <li class="hidden">
                    <a href="#page-top"></a>
                </li>
                <li>
                    <a class="page-scroll" href="indexnew.html">Home</a>
                </li>
                <li>
                    <a class="page-scroll" href="work.html">Work</a>
                </li>
                <li>
                    <a class="page-scroll" href="school.html">School</a>
                </li>
                <li>
                    <a class="page-scroll" href="hobbies.html">Hobbies</a>
                </li>
                <li>
                    <a class="page-scroll" href="contact.php">Contact</a>
                </li>
            </ul>
        </div>
        
    </div>
    
</nav>

<!-- Header -->
<header>
    <div class="container">
        <div class="slider-container">
            <div class="intro-text">
                <div class="intro-lead-in">Welcome To My Page!</div>
                <div class="intro-heading">It's Nice To Meet You</div>
                <a href="#" class="page-scroll btn btn-xl">Let's Explore</a>
            </div>
        </div>
    </div>
</header>
	

<section id="home">
	
    <?php
	session_start();
  	if(!isset($_POST['submit'])) 
	{
		echo '<form method="post" action="contact.php" id="mainForm" style="padding:20px;margin=20px">';
		
		//validation for firstname
		
		if(isset($_GET['errMsg']) && strstr($_GET['errMsg'],"firstNameNull")){
			$firstname = $_POST['firstname'];
			echo' <div id="firstNameDiv" class="form-group has-error">';
			echo' <label class="control-label" for="firstname">First Name: </label>';
			echo' <input type="text" id="firstname" name="firstname" class="form-control"/>';
			// Check if first name is empty or contains invalid characters
			echo '<div id="fnFeedback">First Name must contain only alphabetical characters, hyphens, or apostrophes. It cannot be blank.</div>';
			echo '</div>';
		}
		else// there is no error, check for previously submitted data
		{
			if(isset($_SESSION['firstname'])){ // form loaded with previous data
				echo '<div id="firstNameDiv" class="form-group has-success">';
				echo '<label class="control-label" for="firstname">First Name: </label>';
				echo '<input type="text" id="firstname" name="firstname" class="form-control" value="'.$_SESSION['firstname'].'"/>';
				echo '<div id="fnFeedback"></div>';
				echo '</div>';
			}
			else // form loaded with no data
			{
				echo' <div id="firstNameDiv" class="form-group">';
				echo' <label class="control-label" for="firstname">First Name: </label>';
				echo' <input type="text" id="firstname" name="firstname" class="form-control">';
				echo' <div id="fnFeedback"></div>';
				echo' </div>';
			}
		}
		
		//validation for lastname	
		if(isset($_GET['errMsg']) && strstr($_GET['errMsg'],"lastNameNull")){
			echo '<div class="form-group has-error">';
			echo '<label class="control-label" for="lastname">Last Name: </label>';
			echo '<input type="text" id="lastname" name="lastname" class="form-control"/>';
			echo '<div id="lnFeedback">Name must contain only alphabetical characters, hyphens, or apostrophes. Last name cannot be blank!</div>';
			echo '</div>';
		}
		else
		{
			
			if(isset($_SESSION['lastname'])){ // form loaded with previous data
				echo '<div class="form-group has-success">';
				echo '<label class="control-label" for="lastname">Last Name: </label>';
				echo '<input type="text" id="lastname" name="lastname" class="form-control" value="'.$_SESSION['lastname'].'"/>';
				echo '<div id="lnFeedback"></div>';
				echo '</div>';
			}
			else // form loaded with no data
			{
				echo' <div class="form-group">';
				echo' <label class="control-label" for="lastname">Last Name: </label>';
				echo' <input type="text" id="lastname" name="lastname" class="form-control">';
				echo' <div id="lnFeedback"></div>';
				echo' </div>';
			}
		}
		
		//validation for email	  
		if(isset($_GET['errMsg']) && strstr($_GET['errMsg'],"emailNull")){
			echo '<div class="form-group has-error">';
			echo '<label class="control-label" for="email">Email: </label>';
			echo '<input type="text" id="email" name="email" class="form-control"/>';
			echo '<div id="eFeedback">Email must be formatted correctly! Email cannot be blank!</div>';
			echo '</div>';
		}
		else
		{
			if(isset($_SESSION['email'])){ // form loaded with previous data
				echo '<div class="form-group has-success">';
				echo '<label class="control-label" for="email">Email: </label>';
				echo '<input type="text" id="email" name="email" class="form-control" value="'.$_SESSION['email'].'"/>';
				echo '<div id="eFeedback"></div>';
				echo '</div>';
			}
			else // form loaded with no data
			{
				echo' <div class="form-group">';
				echo' <label class="control-label" for="email">Email: </label>';
				echo' <input type="text" id="email" name="email" class="form-control">';
				echo' <div id="eFeedback"></div>';
				echo' </div>';
			}
		}
		
		//validation for phone
		if(isset($_GET['errMsg']) && strstr($_GET['errMsg'],"phoneNull")){
			echo '<div class="form-group has-error">';
			echo '<label class="control-label" for="phone">Phone: </label>';
			echo '<input type="text" id="phone" name="phone" class="form-control"/>';       
			echo '<div id="phoneFeedback">Phone number must be exactly 10 digits and cannot be empty!</div>';
			echo '</div>';
		}
		else
		{
			if(isset($_SESSION['phone'])){ // form loaded with previous data
				echo '<div class="form-group has-success">';
				echo '<label class="control-label" for="phone">Phone: </label>';
				echo '<input type="text" id="phone" name="phone" class="form-control" value="'.$_SESSION['phone'].'"/>';
				echo '<div id="phoneFeedback"></div>';
				echo '</div>';
			}
			else // form loaded with no data
			{
				echo' <div class="form-group">';
				echo' <label class="control-label" for="phone">Phone: </label>';
				echo' <input type="text" id="phone" name="phone" class="form-control">';
				echo' <div id="phoneFeedback"></div>';
				echo' </div>';
			}
		}
		
		//validation for username
		if(isset($_GET['errMsg']) && strstr($_GET['errMsg'],"userNull")){		 
			echo '<div class="form-group has-error">';
			echo '<label class="control-label" for="username">Create a username: </label>';
			echo '<input type="text" id="username" name="username" class="form-control"/>';       
			echo '<div id="userFeedback">Must contain at least 6 characters and username cannot be blank!</div>';
			echo '</div>';
		}
		else
		{
			if(isset($_SESSION['username'])){ // form loaded with previous data
				echo '<div class="form-group has-success">';
				echo '<label class="control-label" for="username">Create a username:: </label>';
				echo '<input type="text" id="username" name="username" class="form-control" value="'.$_SESSION['username'].'"/>';
				echo '<div id="userFeedback"></div>';
				echo '</div>';
			}
			else // form loaded with no data
			{
				echo' <div class="form-group">';
				echo' <label class="control-label" for="email">Create a username:: </label>';
				echo' <input type="text" id="username" name="username" class="form-control">';
				echo' <div id="userFeedback"></div>';
				echo' </div>';
			}
		}
		
		//validation for password
		if(isset($_GET['errMsg']) && strstr($_GET['errMsg'],"passwordNull")){		 
			echo '<div class="form-group has-error">';
			echo '<label class="control-label" for="password">Create a password: </label>';     
			echo '<input type="password" class="form-control" id="password" name="password"/>';
			echo '<div id="pwFeedback">Must contain at least 6 characters and password cannot be blank!</div>';
			echo '</div>';
		}
		else
		{
			if(isset($_SESSION['password'])){ // form loaded with previous data
				echo '<div class="form-group has-success">';
				echo '<label class="control-label" for="password">Create a password: </label>';
				echo '<input type="password" id="password" name="password" class="form-control" value="'.$_SESSION['password'].'"/>';
				echo '<div id="pwFeedback"></div>';
				echo '</div>';
			}
			else // form loaded with no data
			{
				echo' <div class="form-group">';
				echo' <label class="control-label" for="password">Create a password: </label>';
				echo' <input type="password" id="password" name="password" class="form-control">';
				echo' <div id="pwFeedback"></div>';
				echo' </div>';
			}
		}
		
	
		if(isset($_SESSION['comments'])){ // form loaded with previous data
				echo '<div class="form-group has-success">';
				echo '<label class="control-label" for="comments">Comments: </label>';
				echo '<input type="text" id="comments" name="comments" class="form-control" value="'.$_SESSION['comments'].'"/>';
				echo '<div id="cFeedback"></div>';
				echo '</div>';
			}
			else // form loaded with no data
			{
				echo' <div class="form-group">';
				echo '<label for="comments" class="control-label">Comments: </label>';
				echo '<textarea id="comments" name="comments" class="form-control"></textarea>';  
				echo '<div id="cFeedback"></div>';
				echo' </div>';
		}
				 
		echo '<div class="form-group"> ';
		echo '<button class="btn btn-primary" type="submit" value="sign up!" name="submit" />Submit</button>';
		echo '</div>';    
		echo '</form>';
    }
	else
	{
		$errors="";
		$firstname = $_POST['firstname'];
		if($firstname==NULL || !preg_match('/^[A-Za-z\'-]+$/', $firstname))
			$errors="firstNameNull";
		else
			$_SESSION['firstname']=$firstname;
		
        $lastname = $_POST['lastname'];
		if($lastname==NULL || !preg_match('/^[A-Za-z\'-]+$/', $lastname))
			$errors.="lastNameNull";
		else
			$_SESSION['lastname']=$lastname;
		
        $email = $_POST['email'];
		if($email==NULL || !filter_var($email, FILTER_VALIDATE_EMAIL))
			$errors.="emailNull";
		else
			$_SESSION['email']=$email;
		
        $phone = $_POST['phone'];
		if($phone==NULL || !preg_match('/^\d{10}$/', $phone))
			$errors.="phoneNull";
		else
			$_SESSION['phone']=$phone;
		
        $username = $_POST['username'];
		if($username==NULL || strlen($username) < 6)
			$errors.="userNull";
		else
			$_SESSION['username']=$username;
		
        $password = $_POST['password'];
		if($password==NULL || strlen($password) < 6)
			$errors.="passwordNull";
		else
			$_SESSION['password']=$password;
		
        $comments = $_POST['comments'];
		$_SESSION['comments']=$comments;
		
		if($errors!=NULL)
			header("Location: contact.php?errMsg=$errors");
		
		echo "<h2>Submitted Data: </h2>"; 
		echo '<p>First Name: '.$_POST['firstname'].'</p>';
		echo '<p>Last Name: '.$_POST['lastname']. '</p>';
		echo '<p>Email: '.$_POST['email']. '</p>';
		echo '<p>Phone: '.$_POST['phone'].'</p>';
		echo '<p>Username: '.$_POST['username'].'</p>';
		echo '<p>Password: '.$_POST['password'].'</p>';
		echo '<p>Comments: '.$_POST ['comments'].'</p>';
		if ($_POST[' username'] =="admin"){
			echo '<h2>Welcome to the admin dashboard</h2>';
		}
	}
    ?>
</section>

<!-- FOOTER -->
<footer id="footer">
    <div class="container">
        <div class="row">
            <div class="col-md-4 col-sm-6">
                <div class="footer-info">
                    
                </div>
            </div>
            <div class="col-md-4 col-sm-6">
                <div class="footer-info">
                   
                </div>
            </div>
            <div class="col-md-4 col-sm-12">
                <div class="footer-info newsletter-form">
                    
                </div>
            </div>
        </div>
    </div>
</footer>

<p id="back-top">
    <a href="#top"><i class="fa fa-angle-up"></i></a>
</p>

<footer>
    <div class="container text-center">
        <p>Designed by <a href="http://moozthemes.com"><span>MOOZ</span>Themes.com</a></p>
    </div>
</footer>

<!-- jQuery -->
<script src="https://ajax.googleapis.com/ajax/libs/jquery/1"></script>
<script src="assets/js/event-listener.js"></script>  
