<?php
    include "users.php";

    session_start();
    
    try {
        // Create a user object
        $user = new User($_SESSION["username"], $_SESSION["password"]);
        $user->newPost($_POST["title"], $_POST["content"]);
    }
    catch(Exception $e) {
        echo $e->getMessage();
    }

    // Redirect user to blogs.html page so they can see their new blog
    header("Location: ../blogs.html");
?>
