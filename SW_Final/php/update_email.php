<?php

	session_start();

	include "users.php";

	$user = new User($_SESSION["username"], $_SESSION["password"]);


	try {
		$user->setEmail($_POST["email"]);
	}
	catch(Exception $e) {
		echo $e->getMessage();
	}

	header("Location: ../blogs.html"); // Redirect browser
?>