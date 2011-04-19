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

			$this->html = "<h3>Listado de Clientes <div id='clientes_totales'>Cantidad de Clientes: 0</div></h3>
			<table width='90%' height='300px' border='0px'>
				<tr>
					<td width='20%' bgcolor='#BBBBBB' id='client_list' VALIGN='top'>
						<table>
					";
	
			$this->html .= "	</td>
							</tr>
						</table>
					</td>
					<td bgcolor='lightgray' width='80%' VALIGN='top'>
						<table bgcolor='#BBBBBB'>
							<tr>
								<td><h3>Cliente Seleccionado:</h3></td>
								<td align='right' id='cliente_seleccionado_name'></td>
								<td id='cliente_seleccionado_id'></td>
							</tr>
						</table>
						<table><hr noshade/></table>					
					<table>
						<tr>
							<td>
								<table>
									<tr>
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
											<input type='label' id='seqdigits' />
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
			<a href='#' id='actualizar_cliente' >Modificar Cliente</a> ::
			<!-- <a href='#' id='eliminar_cliente'>Eliminar Cliente</a> :: -->
			<a href='#' id='recargar_cliente'>Regargar Cliente</a> ::
			<a href='#' id='recargar_lista_clientes'>Regargar Lista de Clientes</a> ::
			<a href='#' id='nuevo_cliente'>Nuevo Cliente</a><br/>
			<div id='html_code'></div>";
		}
		
		return $this->html;
	}
}
?>