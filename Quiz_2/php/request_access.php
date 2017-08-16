<?php

// Get login info from Javascript
$username = $_POST["username"];
$password  = $_POST["password"];

// Read usernames and passwords from midterm_users.json file
$users_JSON = file_get_contents('users.json');	// Read JSON file
$users = json_decode($users_JSON, true);				// Convert JSON to array

// Add new user to end of existing array
$new_user = array("username"=>$username, "password"=>$password);
array_push($users, $new_user);

// Encode as JSON and overwrite existing file
$users_JSON_new = json_encode($users);
if(file_put_contents('users.json', $users_JSON_new) == FALSE) {
	echo "<p>Failed to write data to JSON file.</p>";
}


echo '<p>Access requested.</p><a href="../login.html">Go to login page.</a>';
header("refresh:3; url=../login.html"); 			// Redirect back to login page
exit();

?>