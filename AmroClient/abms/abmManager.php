<?php

class abmManager
{	
	public $html;
	public $module;
	
	function __construct()
	{
		if(isset($_GET["module"]))
			$this->module = $_GET["module"];
		else 
			$this->module = "default";
	}

	function getAbmHtml()
	{
		switch ($this->module)
		{
			case "cliente":
				$this->getAbmClienteHtml();
				break;
			case "usuario":
				$this->getAbmUsuarioHtml();
				break;
			case "material":
				$this->getAbmMaterialHtml();
				break;
			default:
				echo "No se encontro el ABM";
				break;
		}
		return $this->html;
	}
	
	
	function getAbmMaterialHtml()
	{
		$this->html = "<h3>Listado de Materiales <div id='materiales_totales'>Cantidad de Materiales: 0</div></h3>
		<table width='90%' height='300px' border='0px'>
			<tr>
				<td width='20%' bgcolor='#BBBBBB' id='material_list' VALIGN='top'>
					<table>
					</td>
						</tr>
					</table>
				</td>
				<td bgcolor='lightgray' width='80%' VALIGN='top'>
					<table bgcolor='#BBBBBB'>
						<tr>
							<td><h3>Material Seleccionado:</h3></td>
							<td align='right' id='material_seleccionado_name'></td>
							<td id='material_seleccionado_id'></td>
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
								</tr>
								<tr><td><b>Quimicas</b></td></tr>
								<tr>
									<td>
										% Carbono:
									</td>
									<td>
										<input type='label' id='carbono' />
									</td>
									<td>
										% Cromo:
									</td>
									<td>
										<input type='label' id='cromo' />
									</td>
								</tr>
								<tr>
									<td>
										% Manganeso:
									</td>
									<td>
										<input type='label' id='manganeso' />
									</td>
									<td>
										% Silicio:
									</td>
									<td>
										<input type='label' id='silicio' />
									</td>
								</tr>
								<tr>
									<td>
										% Fosforo:
									</td>
									<td>
										<input type='label' id='fosforo' />
									</td>
									<td>
										% Azufre:
									</td>
									<td>
										<input type='label' id='azufre' />
									</td>
								</tr>
								<tr>
									<td>
										% Niquel:
									</td>
									<td>
										<input type='label' id='niquel' />
									</td>
									<td>
										% Molibdeno:
									</td>
									<td>
										<input type='label' id='molibdeno' />
									</td>
								</tr>
								<tr>
									<td>
										% Cobre:
									</td>
									<td>
										<input type='label' id='cobre' />
									</td>
									<td>
										% Vanadio:
									</td>
									<td>
										<input type='label' id='vanadio' />
									</td>
								</tr>
								<tr>
									<td>
										C.E.:
									</td>
									<td>
										<input type='label' id='ce' />
									</td>
								<tr>
										
								</tr>
								<tr><td><b>Mecanicas</b></td></tr>
								<tr>
									<td>
										Tension de Rotura (Mpa):
									</td>
									<td>
										<input type='label' id='tension_rotura' />
									</td>
									<td>
										Limite de Fluencia (Mpa):
									</td>
									<td>
										<input type='label' id='limite_fluencia' />
									</td>
								</tr>
								<tr>
									<td>
										Alargamiento (%):
									</td>
									<td>
										<input type='label' id='alargamiento' />
									</td>
									<td>
										Estriccion (%):
									</td>
									<td>
										<input type='label' id='estriccion' />
									</td>
								</tr>
								<tr>
									<td>
										Resiliencia (J) Charpy A:
									</td>
									<td>
										<input type='label' id='resiliencia' />
									</td>
									<td>
										Dureza (Hb) 10/3000:
									</td>
									<td>
										<input type='label' id='dureza' />
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
		<a href='#' id='guardar_material' >Guardar Material</a> ::
		<a href='#' id='actualizar_material' >Modificar Material</a> ::
		<!-- <a href='#' id='eliminar_material'>Eliminar Materia</a> :: -->
		<a href='#' id='recargar_material'>Regargar Material</a> ::
		<a href='#' id='recargar_lista_materiales'>Regargar Lista de Materiales</a> ::
		<a href='#' id='nuevo_material'>Nuevo Material</a><br/>
		<div id='html_code'></div>";
	}	
	
	function getAbmUsuarioHtml()
	{	
		$this->html = "<h3>Listado de Usuarios <div id='usuarios_totales'>Cantidad de Usuarios: 0</div></h3>
		<table width='90%' height='300px' border='0px'>
			<tr>
				<td width='20%' bgcolor='#BBBBBB' id='usuario_list' VALIGN='top'>
					<table>
					</td>
						</tr>
					</table>
				</td>
				<td bgcolor='lightgray' width='80%' VALIGN='top'>
					<table bgcolor='#BBBBBB'>
						<tr>
							<td><h3>Usuario Seleccionado:</h3></td>
							<td align='right' id='usuario_seleccionado_name'></td>
							<td id='usuario_seleccionado_id'></td>
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
								</tr>
								<tr>
									<td>
										Apellido:
									</td>
									<td>
										<input type='label' id='surname' />
									</td>
								</tr>
								<tr>
									<td>
										Firma:
									</td>
									<td>
										<textarea id='signature'></textarea>
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
		<a href='#' id='guardar_usuario' >Guardar Usuario</a> ::
		<a href='#' id='actualizar_usuario' >Modificar Usuario</a> ::
		<a href='#' id='recargar_usuario'>Regargar Usuario</a> ::
		<a href='#' id='recargar_lista_usuarios'>Regargar Lista de Usuarios</a> ::
		<a href='#' id='nuevo_usuario'>Nuevo Usuario</a><br/>
		<div id='html_code'></div>";
	}
	
	function getAbmClienteHtml()
	{
		
		$this->html = "<h3>Listado de Clientes <div id='clientes_totales'>Cantidad de Clientes: 0</div></h3>
		<table width='90%' height='300px' border='0px'>
			<tr>
				<td width='20%' bgcolor='#BBBBBB' id='client_list' VALIGN='top'>
					<table>
					</td>
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
	
}
?>