<?php

session_start();
session_destroy();

echo '<p>You have been successfully logged out.</p><a href="../login.html">Return to login page.</a>';
sleep(1);
header("refresh:3; url=../login.html");		// Redirect to login page
exit();

?>