<?php

if(isset($_GET["module"]))
	$module = $_GET["module"];
else 
	$module = "default";
	
if($module == "cliente")
{

	$cliente_1 = array("nombre" => "Thorsa", 
					   "direccion" => "Amenabar 123");
	$cliente_2 = array("nombre" => "Rensor", 
					   "direccion" => "Pucherito 3223");
	$cliente_3 = array("nombre" => "Workfront", 
					   "direccion" => "Libertad 11235");
	$cliente_4 = array("nombre" => "Withmore", 
					   "direccion" => "Churco 9873");
	$clientes = array();
	$clientes[0] = $cliente_1;
	$clientes[1] = $cliente_2;
	$clientes[2] = $cliente_3;
	$clientes[3] = $cliente_4;

	//	var_dump($clientes);


	echo "<h3>Listado de Clientes</h3>";
	echo "<table><tr><td><table>";

	foreach($clientes as $cliente)
	{
		
		echo "<tr><td><a href='#'>".$cliente['nombre']." - ".$cliente["direccion"]."</a></td></tr>";
		
		//<input type='text' value='".$clientes['name']."' />";
			
	}

	echo "</table></table>";

}

?>