<?php

function db_connect($db){
	$dbUserName = "webuser";
	$dbPassword = "m).[6Ou7S3s_Z@yH";
	$host = "localhost";
	$dblink = new mysqli($host, $dbUserName, $dbPassword, $db);
	return $dblink;
}

function redirect ( $uri )
{?>
	<script type="text/javascript">
	document.location.href="<?php echo $uri; ?>";
	</script>
<?php die;	
}


?>
