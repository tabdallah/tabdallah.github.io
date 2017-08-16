<?php
	session_start();

    // Now process data and request access
    include "users.php";
    $user = new User($_POST["username"], $_POST["password"], $_POST["email"]);
    try {
        $user->requestAccess();    
    }
    catch(Exception $e) {
        echo $e->getMessage();

        echo '<br><a href="../request_access.html">Return to request access page.</a>';
        sleep(1);
        header("refresh:3; url=../request_access.html");     // Redirect to login page
        exit();
    }

    header("Location: ../login.html");
?>
