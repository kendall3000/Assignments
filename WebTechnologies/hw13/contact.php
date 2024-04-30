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
    if(isset($_POST['submit'])) {
        // Display submitted data
        $firstname = $_POST['firstname'];
        $lastname = $_POST['lastname'];
        $email = $_POST['email'];
        $phone = $_POST['phone'];
        $username = $_POST['username'];
        $password = $_POST['password'];
        $comments = $_POST['comments'];

        echo "<h2>Submitted Data:</h2>";
        echo "<p>First Name: $firstname</p>";
        echo "<p>Last Name: $lastname</p>";
        echo "<p>Email: $email</p>";
        echo "<p>Phone: $phone</p>";
        echo "<p>Username: $username</p>";
        echo "<p>Password: $password</p>";
        echo "<p>Comments: $comments</p>";
    } else {
        // Display form
    ?>

    <form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>" id="mainForm" style="padding:20px;margin:20px" onsubmit="return validateForm()">
        <div id="firstNameDiv" class="form-group">
            <label for="firstname">First Name:</label>
            <input type="text" id="firstname" name="firstname" class="form-control"/>
            <div id="fnFeedback"></div>
        </div>
        <div class="form-group">
            <label for="lastname">Last Name:</label>
            <input type="text" id="lastname" name="lastname" class="form-control"/>
            <div id="lnFeedback"></div>
        </div>
        <div class="form-group">
            <label for="email">Email:</label>
            <input type="text" id="email" name="email" class="form-control"/>
            <div id="emFeedback"></div>
        </div>
        <div class="form-group">
            <label for="phone">Phone:</label>
            <input type="text" id="phone" name="phone" class="form-control"/>
            <div id="pFeedback"></div>
        </div>
        <div class="form-group">
            <label for="username">Create a username:</label>
            <input type="text" id="username" name="username" class="form-control"/>
            <div id="usFeedback"></div>
        </div>
        <div class="form-group">
            <label for="password">Create a password:</label>
            <input type="password" class="form-control" id="password" name="password"/>
            <div id="pwFeedback"></div>
        </div>
        <div class="form-group">
            <label for="comments">Comments:</label>
            <textarea id="comments" name="comments" class="form-control"></textarea>
            <div id="unFeedback"></div>
        </div>
        <div class="form-group">
            <input type="submit" value="Sign up!" name="submit"/>
        </div>
    </form>
    <?php
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
<script src="https://ajax.googleapis.com/ajax/libs/jquery/1
