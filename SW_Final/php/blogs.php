<?php
	include "users.php";

	session_start();

	// Check if user is logged in or a guest
	try {
		if (isset($_SESSION["username"])==0)
		{
			// Create a guest - will populate the display with the data required for pulling existing blogs
			$user = new Guest();
			$user->generatePage();
		}
		else
		{
			// Create a registered user
			$user = new User($_SESSION["username"], $_SESSION["password"]);
			$user->generatePage();
		}			
	}
	catch(Exception $e) {
		echo $e->getMessage();
	}	
?>