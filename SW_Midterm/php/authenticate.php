<?php

// Create a session if there isn't one already
if (session_status() == PHP_SESSION_NONE) {
	session_start();
}

// Get login info from Javascript
$username = $_POST["username"];
$password  = $_POST["password"];
$remember = isset($_POST["remember"]);

// Read usernames and passwords from midterm_users.json file
$users_JSON = file_get_contents('users.json');	// Read JSON file
$users = json_decode($users_JSON, true);				// Convert JSON to array

// Check each entry in the users array to see if the username and password match
foreach($users as $user) {
	if(($username == $user['username']) && ($password == $user['password'])){
		// Login successful
		$_SESSION["username"] = $username;
		$_SESSION["password"] = $password; 
		echo "<strong>Welcome Member!</strong>";
		header("Location: ../members.html"); 	// Redirect to members page
		exit();
	}
}

echo '<p>Invalid login info.</p><a href="../login.html">Return to login page.</a>';
header("refresh:3; url=../login.html"); 			// Redirect back to login page
exit();

?>