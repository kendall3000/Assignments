<?php
echo '<div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">';
echo '<ul class="nav navbar-nav navbar-right">';
if(!isset($_GET['page'])) // check to see if page is not set
	$page="home";
else
	$page=$_GET['page'];
//home
if($page=="home")
	echo '<li class="active"><a class="page-scroll" href="index.php">Home</a></li>';
else
	echo'<li><a class="page-scroll" href="index.php">Home</a></li>';
//work
if($page=="work")	
	echo '<li class="active"><a class="page-scroll" href="index.php?page=work">Work</a></li>';
else
	echo '<li><a class="page-scroll" href="index.php?page=work">Work</a></li>';
//school
if($page=="school")
	echo'<li class="active"><a class="page-scroll" href="index.php?page=school">School</a></li>';
else
	echo '<li><a class="page-scroll" href="index.php?page=school">School</a></li>';
//hobbies
if($page=="hobbies")
	echo '<li class="active"><a class="page-scroll" href="index.php?page=hobbies">Hobbies</a></li>';
else
	echo '<li><a class="page-scroll" href="index.php?page=hobbies">Hobbies</a></li>';

if($page=="contact")
	echo'<li class="active"><a class="page-scroll" href="index.php?page=contact">Contact</a></li>';
else
	echo'<li><a class="page-scroll" href="index.php?page=contact">Contact</a></li>';

echo '</ul>';
echo '</div>';
?>
