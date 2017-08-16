<?php

if (session_status() == PHP_SESSION_NONE) {
    session_start();
}

// Check if user is logged and has a right to access
if (isset($_SESSION["username"]))
{
	// Access granted
}
else {
	header("refresh:3; url=../index.html");	// Redirect to home page
	echo '<p>Access denied.</p><a href="../login.html">Go to login page.</a>';
	exit();
}
?>