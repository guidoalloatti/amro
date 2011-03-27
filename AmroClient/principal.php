<?php

require_once("include/render.php");
$myRender = new Render("index");
$myRender->getPage();
$myRender->renderPage();

?>