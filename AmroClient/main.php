<?php

/* invoice_url options are:
 *    * certificado (Certificados)
 *    * index (Menu Principal - Default)
 *    * oc (Ordenes de Compra)
 */

 //echo "ACA: ".$_GET["invoice_url"];
 
if(!isset($_GET["invoice_url"]))
{
	$invoice_url = "pr";
}
else
{
	$invoice_url = $_GET["invoice_url"]; 
}
	
require_once("include/render.php");
$myRender = new Render($invoice_url);
$myRender->getPage();
$myRender->renderPage();

?>