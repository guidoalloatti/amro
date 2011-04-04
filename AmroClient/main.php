<?php

/* invoice_url options are:
 *    * certificado (Certificados)
 *    * index (Menu Principal - Default)
 *    * oc (Ordenes de Compra)
 */

if(!isset($_GET["invoice_url"]))
{
	$invoice_url = "pr";
}
else
{
	$invoice_url = $_GET["invoice_url"]; 
}

if(!isset($_GET["module"]))
{
	$module = "default";
}
else
{
	$module = $_GET["module"]; 
}

require_once("include/render.php");
$myRender = new Render($invoice_url, $module);
$myRender->getPage();
$myRender->renderPage();

?>