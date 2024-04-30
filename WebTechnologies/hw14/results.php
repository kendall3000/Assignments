<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="../images/dakota.png">
    <title>Form Submission Results</title>
    <!-- Bootstrap core CSS -->
    <link href="assets/css/bootstrap.min.css" rel="stylesheet">
    <link rel="stylesheet" href="assets/css/font-awesome.min.css">
    <!-- Custom styles for this template -->
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
            </div>
            <!-- Collect the nav links, forms, and other content for toggling -->
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
            <!-- /.navbar-collapse -->
        </div>
        <!-- /.container-fluid -->
    </nav>

    <!-- Header -->
    <header>
        <div class="container">
            <div class="slider-container">
                <div class="intro-text">
                    <div class="intro-lead-in">Form Submission Results</div>
                    <div class="intro-heading">Thank you for your submission!</div>
                </div>
            </div>
        </div>
    </header>

    <!-- Display Form Submission Results -->
    <section id="form-results" class="bg-light-gray">
        <div class="container">
            <div class="row">
                <div class="col-lg-12 text-center">
                    <h2 class="section-heading">Form Data</h2>
                    <hr class="primary">
                </div>
            </div>
            <div class="row">
                <div class="col-lg-8 col-lg-offset-2 text-center">
                    <?php
                    if (isset($_GET['submit'])) {
                        echo "<p>First Name: " . $_GET['firstname'] . "</p>";
                        echo "<p>Last Name: " . $_GET['lastname'] . "</p>";
                        echo "<p>Email: " . $_GET['email'] . "</p>";
                        echo "<p>Phone: " . $_GET['phone'] . "</p>";
                        echo "<p>Username: " . $_GET['username'] . "</p>";
                        echo "<p>Password: " . $_GET['password'] . "</p>";
                        echo "<p>Comments: " . $_GET['comments'] . "</p>";
                    } else {
                        echo "<p>Error: Form data was not submitted.</p>";
                    }
                    ?>
                </div>
            </div>
        </div>
    </section>
	

    <!-- Footer -->
    <footer>
        <div class="container text-center">
            <p>Designed by <a href="http://moozthemes.com"><span>MOOZ</span>Themes.com</a></p>
        </div>
    </footer>

    <!-- JavaScript includes -->
    <script src="assets/js/event-listener.js"></script>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
    <script src="http://cdnjs.cloudflare.com/ajax/libs/jquery-easing/1.3/jquery.easing.min.js"></script>
    <script src="js/bootstrap.min.js"></script>
    <script src="js/owl.carousel.min.js"></script>
    <script src="js/cbpAnimatedHeader.js"></script>
    <script src="js/theme-scripts.js"></script>
</body>
</html>



