<?php

/* invoice_url options are:
 *    * certificado (Certificados)
 *    * index (Menu Principal - Default)
 *    * oc (Ordenes de Compra)
 */

/*
echo "User: ".$_SESSION['user']."<br/>
	  Pass: ".$_SESSION['pass']."<br/>
	  Invoice: ".$_GET["invoice_url"]."<br/>";
	var_dump($_SESSION);
*/

$testLogin = false;

if(!isset($_SESSION))
	session_start();

if($testLogin)
{
	//echo "Seteando loginVars";
	$time = time();
	$_SESSION['user'] = "pmata@amro.com";
	$_SESSION['pass'] = "123";
	$_SESSION['lastLoginDate'][$_GET['user']] = $time;
}
	

if( ($_SESSION['user'] === null || 
	  $_SESSION['pass'] === null) &&
	  $_GET["invoice_url"] != "lo")
{

	echo "Se debe loguear para poder ingresar al sistema.<br/><a href='main.php?invoice_url=lo'>Ir al login</a>";
}
else
{
	if(!isset($_GET["invoice_url"]))
		$invoice_url = "pr";
	else
		$invoice_url = $_GET["invoice_url"]; 

	if(!isset($_GET["module"]))
		$module = "default";
	else
		$module = $_GET["module"];

	require_once("include/render.php");
	$myRender = new Render($invoice_url, $module);
	$myRender->getPage();
	$myRender->renderPage();
}
?>