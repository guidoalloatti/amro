<?php

/*
if( $_GET['key'] == "" || 
	$_GET['key'] != 'amroKey' ||
	$_GET['pass'] == "" ||
	$_GET['user'] == "")
{
	exit;
}
*/

session_start();

$user = $_GET['user'];
$pass = $_GET['pass'];
$time = time();

$_SESSION['user'] = $user;
$_SESSION['pass'] = $pass;
$_SESSION['lastLoginDate'][$_GET['user']] = $time;

//print_r($_SESSION);

echo '{"user":'.json_encode($user).', "pass":'.json_encode($pass).', "login_date":'.json_encode($time).'}';

?>