<?php
	include "users.php";
	$user = new User($_POST["username"], $_POST["password"]);

	try {
		$user->login();
	}
	catch(Exception $e) {
		echo $e->getMessage();
		echo '<br><a href="../login.html">Return to login page.</a>';
		sleep(1);
		header("refresh:3; url=../login.html");		// Redirect to login page
		exit();
	}
?>