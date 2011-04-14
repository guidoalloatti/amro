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
	
			/*
			$cliente_1 = array("nombre" => "Thorsa", "direccion" => "Amenabar 15324543");
			$cliente_2 = array("nombre" => "Rensor", "direccion" => "Pucherito 3223");
			$cliente_3 = array("nombre" => "Workfront", "direccion" => "Libertad 11235");
			$cliente_4 = array("nombre" => "Withmorfdsfggxdfe", "direccion" => "Churco 9873");
			$clientes = array();
			$clientes[0] = $cliente_1;
			$clientes[1] = $cliente_2;
			$clientes[2] = $cliente_3;
			$clientes[3] = $cliente_4;
			*/
			
			$this->html = "<h3>Listado de Clientes</h3>
			<table width='80%' border='0px'>
				<tr>
					<td width='35%' bgcolor='lightblue' id='client_list' >
						<table>
					";
	
			$this->html .= "	</td>
							</tr>
						</table>
					</td>
					<td bgcolor='lightgreen' width='75%'>
					<table >
						<tr>
							<td>
								<table>
									<tr>
										<td>
											Nombre:
										</td>
										<td>
											<input type='label' id='name' />
										</td>
										<td>
											Direccion:
										</td>
										<td>
											<input type='label' id='address' />
										</td>
									</tr>
									<tr>
										<td>
											Ciudad:
										</td>
										<td>
											<input type='label' id='city' />
										</td>
										<td>
											Codigo Postal:
										</td>
										<td>
											<input type='label' id='zip' />
										</td>
									</tr>
									<tr>
										<td>
											Pais:
										</td>
										<td>
											<input type='label' id='country' />
										</td>
										<td>
											Telefono:
										</td>
										<td>
											<input type='label' id='phone' />
										</td>
									</tr>
									<tr>
										<td>
											Fax:
										</td>
										<td>
											<input type='label' id='telefax' />
										</td>
										<td>
											Pagina Web:
										</td>
										<td>
											<input type='label' id='website' />
										</td>
									</tr>
									<tr>
										<td>
											Codigo de Identificacion:
										</td>
										<td>
											<input type='label' id='namecode' />
										</td>
										<td>
											Cantidad Maxima de Certificados:
										</td>
										<td>
											<input type='label' id='sequencedigits' />
										</td>
									</tr>
								</table>
							</td>
						</tr>
					</table>
					</td>	
				</tr>
			</table>
			<hr>
			<a href='#' id='guardar_cliente' >Guardar Cliente</a> ::
			<a href='#' id='eliminar_cliente'>Eliminar Cliente</a> ::
			<a href='#' id='recargar_cliente'>Regargar Cliente</a> ::
			<a href='#' id='nuevo_cliente'   >Nuevo Cliente</a>
			<hr/>";
		}
		
		return $this->html;
	}
}
?>