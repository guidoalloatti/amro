<?php

class abmManager
{	
	public $html;
	
	function __construct()
	{
	}

	function getClienteAbm()
	{
	
		if(isset($_GET["module"]))
			$module = $_GET["module"];
		else 
			$module = "default";
			
		if($module == "cliente")
		{

			$cliente_1 = array("nombre" => "Thorsa", "direccion" => "Amenabar 123");
			$cliente_2 = array("nombre" => "Rensor", "direccion" => "Pucherito 3223");
			$cliente_3 = array("nombre" => "Workfront", "direccion" => "Libertad 11235");
			$cliente_4 = array("nombre" => "Withmore", "direccion" => "Churco 9873");
			$clientes = array();
			$clientes[0] = $cliente_1;
			$clientes[1] = $cliente_2;
			$clientes[2] = $cliente_3;
			$clientes[3] = $cliente_4;

			$this->html = "<h3>Listado de Clientes</h3>
			<table width='60%' border='0px'>
				<tr>
					<td width='25%' bgcolor='lightblue'>
						<table >
							<tr>
								<td>";

			foreach($clientes as $cliente)
			{
				$this->html .= "<tr><td><a href='#'>".$cliente['nombre']."</td><td>".$cliente["direccion"]."</td></a></td>
							   <td><img src='img/new.png' width='20' heigth='20' alt='Nuevo' /></td>
							   <td><img src='img/edit.png' width='20' heigth='20' alt='Editar' /></td>
							   <td><img src='img/delete.png' width='20' heigth='20' alt='Eliminar'/></td></tr>";
			}
			
			$this->html .= "	</td>
							</tr>
						</table>
					
					</td>
					<td bgcolor='lightgreen' width='75%'>
					<table >
						<tr>
							<td>
								Ponela bien careta
							</td>
						</tr>
					</table>
					</td>	
				</tr>
			</table>
			<hr>
			<a href='#' id='guardar_cliente' >Guardar Cliente</a> ::
			<a href='#' id='eliminar_cliente'>Eliminar Cliente</a> ::
			<a href='#' id='nuevo_cliente'   >Nuevo Cliente</a>
			<hr/>";
		}
		
		return $this->html;
	}
}
?>