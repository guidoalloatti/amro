<?php

session_start();

$user = $_SESSION['user'];
$pass = $_SESSION['pass'];

//echo $user;
//echo $pass;

echo '{"user":'.json_encode($user).', "pass":'.json_encode($pass).'}';

?>