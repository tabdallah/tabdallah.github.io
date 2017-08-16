<?php
	include "users.php";

	session_start();

	if (isset($_SESSION["username"])==0)
	{
		$username = $_POST["username"];	// Get username from input box
	}
	else
	{
		$username = $_SESSION["username"];
	}
	
	// Try to get the specified users blog contents
	try {
		// Create a user object to allow for loading of a blog		
		$user = new Guest();
		$user->getBlog($user->getID($username), $username);
	}
	catch(Exception $e) {
		echo $e->getMessage();
	}
?>