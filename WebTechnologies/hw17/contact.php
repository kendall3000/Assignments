<section id="home">
	
    <?php
	session_start();
  	if(!isset($_POST['submit'])) 
	{
		echo '<form method="post" action="index.php?page=contact" id="mainForm" style="padding:20px;margin=20px">';
		
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
		
        $comments = addslashes($_POST['comments']);
		$_SESSION['comments']=$comments;
		
		if($errors!=NULL)
			header("Location: contact.php?errMsg=$errors");
		// ODBC String
		$dbUserName = "webuser";
		$dbPassword = "m).[6Ou7S3s_Z@yH";
		$host = "localhost";
		$db = "contact_data";
		$dblink = new mysqli($host, $dbUserName, $dbPassword, $db);

		if ($dblink->connect_error) {
			die("Connection failed: " . $dblink->connect_error);
		}

		$sql = "INSERT INTO contact_info (`first_name`,`last_name`,`email`,`phone`,`user_name`,`password`,`comment`) VALUES ('$firstname', '$lastname', '$email', '$phone', '$username', '$password', '$comments')";
		$dblink->query($sql) or die("Something went wrong with: $sql" . $dblink->error);

		echo '<h2>Your data was successfully submitted.</h2>';
		$dblink->close();
	}
    ?>
</section>



<!-- jQuery -->
<script src="https://ajax.googleapis.com/ajax/libs/jquery/1"></script>
<script src="assets/js/event-listener.js"></script>  
