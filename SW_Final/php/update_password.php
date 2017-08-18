<?php

	session_start();

	include "users.php";

	$user = new User($_SESSION["username"], $_SESSION["password"]);


	try {
		$user->setPassword($_POST["password"]);
	}
	catch(Exception $e) {
		echo $e->getMessage();
	}

	header("Location: ../blogs.html"); // Redirect browser
?>