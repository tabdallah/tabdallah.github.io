<?php

	include "connect_db.php";		// Connect to the remote database

	// Query database for all user info in new_users table
	$data = array();

	$rows = $database->query("SELECT username FROM users");

	if($rows != FALSE) {
		foreach($rows as $row){
			$new_row = array('username'=>$row['username']);
			array_push($data, $new_row);
		}
	}
	else {
		//echo "<script type='text/javascript'> console.log('ERROR: Query returned nothing.') </script>";
	}

	// Encode data into JSON for easy Javascript passing & parsing
	$json_data = json_encode($data);
	echo $json_data;
?>