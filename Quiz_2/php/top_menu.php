<?php

if (session_status() == PHP_SESSION_NONE) {
    session_start();
}

// Check if user is logged and has a right to access
if (isset($_SESSION["username"]))
{
	echo '
		<div class="container">
			<div class="navbar-header">
				<button type="button" class="navbar-toggle" data-toggle="collapse" data-target="#myNavbar">
					<span class="icon-bar"></span>                        
				</button>
				<a class="navbar-brand" href="index.html">SW Quiz 2</a>
			</div>
			
			<div class="collapse navbar-collapse" id="myNavbar">
				<ul class="nav navbar-nav">
					<li><a href="members.html">Members Page</a></li>
				</ul>
				<ul class="nav navbar-nav navbar-right">
					<li><a href="request_access.html">Sign up</a></li>
					<li><a href="./php/logout.php"><span class="glyphicon glyphicon-log-out"></span> Logout</a></li>
				</ul>
			</div>
		</div>
	';
}
else {
	echo '
		<div class="container">
			<div class="navbar-header">
				<button type="button" class="navbar-toggle" data-toggle="collapse" data-target="#myNavbar">
					<span class="icon-bar"></span>                        
				</button>
				<a class="navbar-brand" href="index.html">SW Quiz 2</a>
			</div>
			
			<div class="collapse navbar-collapse" id="myNavbar">
				<ul class="nav navbar-nav navbar-right">
					<li><a href="request_access.html">Sign up</a></li>
					<li><a href="login.html"><span class="glyphicon glyphicon-log-in"></span> Login</a></li>
				</ul>
			</div>
		</div>
	';
}
?>