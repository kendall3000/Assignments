<?php
include("functions.php");
?>
<!DOCTYPE html>
<html lang="en">
	<head>
		<meta charset="utf-8">
		<meta http-equiv="X-UA-Compatible" content="IE=edge">
		<meta name="viewport" content="width=device-width, initial-scale=1">
		<meta name="description" content="">
		<meta name="author" content="">
		<link rel="icon" href="../images/dakota.png">
		<title>Kendall's Website</title>
		<link href="assets/css/bootstrap.min.css" rel="stylesheet">
		<link href="assets/css/bootstrap.css" rel="stylesheet">
		<link rel="stylesheet" href="assets/css/font-awesome.min.css">

		<link href="assets/css/owl.carousel.css" rel="stylesheet">
		<link href="assets/css/owl.theme.default.min.css"  rel="stylesheet">
		<link href="assets/css/style.css" rel="stylesheet">
		
	</head>
	
	
	<body id="page-top">
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
					<li class="hidden">
						<a href="#page-top"></a>
					</li>
				</div>
				<!-- /.navbar-collapse -->
				<?php
					include("navigation.php");
				?>
			</div>
			<!-- /.container-fluid -->
		</nav>

<!-- Header -->
		<header>
			<div class="container">
				<div class="slider-container">
					<div class="intro-text">
						<div class="intro-lead-in">Welcome To My Page!</div>
						<div class="intro-heading">It's Nice To Meet You</div>
						<a href="#about" class="page-scroll btn btn-xl">Let's Explore</a>
					</div>
				</div>
			</div>
		</header>
<?php
	if(!isset($_GET['page'])) // check to see if page is not set
		$page="home";
	else
		$page=$_GET['page'];
	switch($page){
		case "work":
			include("work.php");
			break;
		case "school":
			include("school.php");
			break;
		case "hobbies":
			include("hobbies.php");
			break;
		case "contact":
			include("contact.php");
			break;
		case "results":
			include("results.php");
			break;
		case "register":
			include("register.php");
			break;
		case "login":
			include("login.php");
			break;
		default: 
			include("home.php");
			break;
	};
?>
		<footer>
			<div class="container text-center">
				<p>Designed by <a href="http://moozthemes.com"><span>MOOZ</span>Themes.com</a></p>
			</div>
			<p id="back-top">
				<a href="#top"><i class="fa fa-angle-up"></i></a>
			</p>
		</footer>


		<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
		<script src="http://cdnjs.cloudflare.com/ajax/libs/jquery-easing/1.3/jquery.easing.min.js"></script>
		<script src="js/bootstrap.min.js"></script>
		<script src="js/owl.carousel.min.js"></script>
		<script src="js/cbpAnimatedHeader.js"></script>
		<script src="js/theme-scripts.js"></script>
		<!-- IE10 viewport hack for Surface/desktop Windows 8 bug -->
<!--		<script src="js/ie10-viewport-bug-workaround.js"></script>-->
		<script src="assets/js/add-content.js"></script>
	</body>
</html>