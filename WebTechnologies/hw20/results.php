<script src="assets/js/jquery-3.5.1.js"></script>
<?php
if (isset($_REQUEST['sid'])&& $_REQUEST['sid']!=''){
	$sid=addslashes($_REQUEST['sid']);
	$dblink=db_connect("user_data");
	$sql="select `auto_id` from `accounts` where `session_id`='$sid'";
	$result=$dblink->query($sql) or 
		die("<p>Something went wrong with $sql<br>" .$dblink->error);
	if($result->num_rows<=0)
		redirect("index.php?page=login&errMsg=InvalidSid");
	echo '<section id="home">';
	echo '<table class="table table-stripped">';
	echo '<thead>';
	echo '<tr>';
	echo '<th>First Name</th>';
	echo '<th>Last Name</th>';
	echo '<th>Email</th>';
	echo '<th>Phone</th>';
	echo '<th>Comments</th>';
	echo '</tr>';
	echo '</thead>';
	echo '<tbody id="results">';
	echo '</tbody>';
	echo '</table>';
	echo '</section>';
}
else{
	redirect("index.php?page=login&errMsg=NullSid");
}
?>
<script>
	function refresh_data(){
		$.ajax({
			type: 'post',
			url: 'https://ec2-18-204-195-168.compute-1.amazonaws.com/hw19/query_contacts.php',
			success: function(data){
				$('#results').html(data);
			}
		});
	}
setInterval(function(){refresh_data();}, 500);
</script>