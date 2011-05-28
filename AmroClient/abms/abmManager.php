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
			case "ttermico":
				$this->getAbmTtermicoHtml();
				break;
			default:
				echo "No se encontro el ABM";
				break;
		}
		return $this->html;
	}
	
	function getAbmMaterialHtml()
	{
		$this->html = "<body onload='materialStart();'> <h3>Listado de Materiales <div id='materiales_totales'>Cantidad de Materiales: 0</div></h3>
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
								<td><table><tr>
									<td>Nombre:</td>
									<td><input type='label' id='name' /></td>
								</tr></table></td>
								</tr>
								<tr>
									<th><b>Material Quimico</b></th>
									<th><b>Maximo</b></th>
									<th><b>Minimo</b></th>
									<th><b>Material Quimico</b></th>
									<th><b>Maximo</b></th>
									<th><b>Minimo</b></th>
								</tr>
								<tr>
									<td align='right'>% Carbono:</td>
									<td><input type='label' id='carbono_max' size='2'/></td>
									<td><input type='label' id='carbono_min' size='2'/></td>
									<td align='right'>% Cromo:</td>
									<td><input type='label' id='cromo_max' size='2'/></td>
									<td><input type='label' id='cromo_min' size='2'/></td>
								</tr>
								<tr>
									<td align='right'>% Manganeso:</td>
									<td><input type='label' id='manganeso_max' size='2'/></td>
									<td><input type='label' id='manganeso_min' size='2'/></td>
									<td align='right'>% Silicio:</td>
									<td><input type='label' id='silicio_max' size='2'/></td>
									<td><input type='label' id='silicio_min' size='2'/></td>
								</tr>
								<tr>
									<td align='right'>% Fosforo:</td>
									<td><input type='label' id='fosforo_max' size='2'/></td>
									<td><input type='label' id='fosforo_min' size='2'/></td>
									<td align='right'>% Azufre:</td>
									<td><input type='label' id='azufre_max' size='2'/></td>
									<td><input type='label' id='azufre_min' size='2'/></td>
								</tr>
								<tr>
									<td align='right'>% Niquel:</td>
									<td><input type='label' id='niquel_max' size='2'/></td>
									<td><input type='label' id='niquel_min' size='2'/></td>
									<td align='right'>% Molibdeno:</td>
									<td><input type='label' id='molibdeno_max' size='2'/></td>
									<td><input type='label' id='molibdeno_min' size='2'/></td>
								</tr>
								<tr>
									<td align='right'>% Cobre:</td>
									<td><input type='label' id='cobre_max' size='2'/></td>
									<td><input type='label' id='cobre_min' size='2'/></td>
									<td align='right'>% Vanadio:</td>
									<td><input type='label' id='vanadio_max' size='2'/></td>
									<td><input type='label' id='vanadio_min' size='2'/></td>
								</tr>
								<tr>
									<td align='right'>C.E.:</td>
									<td><input type='label' id='ce_max' size='2'/></td>
									<td><input type='label' id='ce_min' size='2'/></td>
								<tr>
										
								</tr>
								<tr>
									<th><b>Propiedad Mecanica</b></th>
									<th><b>Maximo</b></th>
									<th><b>Minimo</b></th>
									<th><b>Propiedad Mecanica</b></th>
									<th><b>Maximo</b></th>
									<th><b>Minimo</b></th>
									
									</tr>
								<tr>
									<td align='right'>Tension de Rotura (Mpa):</td>
									<td ><input type='label' id='tension_rotura_max' size='2'/></td>
									<td><input type='label' id='tension_rotura_min' size='2'/></td>
									<td align='right'>Limite de Fluencia (Mpa):</td>
									<td><input type='label' id='limite_fluencia_max' size='2'/></td>
									<td><input type='label' id='limite_fluencia_min' size='2'/></td>
								</tr>
								<tr>
									<td align='right'>Alargamiento (%):</td>
									<td><input type='label' id='alargamiento_max' size='2'/></td>
									<td><input type='label' id='alargamiento_min' size='2'/></td>
									<td align='right'>Estriccion (%):</td>
									<td><input type='label' id='estriccion_max' size='2'/></td>
									<td><input type='label' id='estriccion_min' size='2'/></td>
								</tr>
								<tr>
									<td align='right'>Resiliencia (J) Charpy A:</td>
									<td><input type='label' id='resiliencia_max' size='2'/></td>
									<td><input type='label' id='resiliencia_min' size='2'/></td>
									<td align='right'>Dureza (Hb) 10/3000:</td>
									<td><input type='label' id='dureza_max' size='2'/></td>
									<td><input type='label' id='dureza_min' size='2'/></td>
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
		$this->html = "<body onload='userStart();'> <h3>Listado de Usuarios <div id='usuarios_totales'>Cantidad de Usuarios: 0</div></h3>
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
									<td>Nombre:</td>
									<td><input type='label' id='name' /></td>
								</tr>
								<tr>
									<td>Apellido:</td>
									<td><input type='label' id='surname' /></td>
								</tr>		
								<tr>
									<td>Email:</td>
									<td><input type='label' id='email' /></td>
								</tr>
								<tr>
									<td>Password:</td>
									<td><input type='label' id='password' /></td>
								</tr>
								<tr>
									<td>Firma:</td>
									<td><input type='file' id='signature' /></td>
								</tr>	
								<tr>
									<td><a href='main.php?invoice_url=pe&userid=1'>Gestionar Permisos del Usuario</a></td>
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
		
		$this->html = "<body onload='clientStart();'> <h3>Listado de Clientes <div id='clientes_totales'>Cantidad de Clientes: 0</div></h3>
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

	function getAbmTtermicoHtml()
	{
		$this->html = "<body onload='tratamientoTermicoStart();'> <h3>Carga y visualización de Tratamientos Termicos y asociación con Análisis Químicos realizados </h3>
		<table id='abm_tt'>
			<tr>
				<td width='420px' id='all_tt_cell'>
					<table width='420px'>
						<tr>
							<td>
								<p id='all_tt_title' align='center'>
									<label style='font-weight:bold;'>Tratamientos Térmicos</label>
								</p>
							</td>
						</tr>
						<tr id='show_tt' width='400px'>
							<td>
								<p id='all_tt'></p>
							</td>
						</tr>
						<tr width='420px'>
							<td>
								<p id='ca_selection'>
									<button id='select_ca_button'>Asociar con Análisis Químico</button>
									<button style='float: right;' id='new_tt_button'>Ingresar Nuevo T. Térmico</button>
								</p>
							</td>				
						</tr>
					</table>
				</td>
				
				<td width='430px' id='link_tt_cell'>
					<table  width='430px'>
						<tr>
							<td>
								<p id='link_tt_title' align='center'>
									<label style='font-weight:bold;'>Asociar Análisis Químico</label>
								</p>
							</td>
						</tr>
						<tr>
							<td>
								<p id='all_ca'></p>
							</td>
						</tr>
						<tr>
							<td>
								<p id='selected_params' align='center'></p>
							</td>
						</tr>
					</table>
				</td>			
				
				<td width='420px' id='new_tt_cell'>
					<table width='420px'>
						<tr>
							<td>
								<p align='center' id='new_tt_title'>
									<label style='font-weight:bold;'>Nuevo Tratamiento Térmico</label>
								</p>
							</td>
						</tr>
						<tr>
							<td>
								<p id='new_tt_date'>
									<label>Ingrese una fecha*:</label><br/>
									<label>dd</label><input type='text' id='tt_day' size='2'/><label>/ mm</label><input id='tt_month' type='text' size='2'/><label>/ yyyy</label><input id='tt_year' type='text' size='2'/><br/>
									* Si no ingresa nada se tomará la fecha de hoy.
								</p>
								<p id='new_tt_image'>
									<label>Seleccione una nueva imagen:</label><input id='tt_image_path' type='file'/>
								</p>
								<p id='new_tt_obs'><label>Ingrese observación:</label><textarea id='tt_obs' cols='20' rows='5'></textarea></p>
								<p id='new_tt_submit' align='center'><button onclick='newTT(); event.preventDefault();'>Crear</button></p>
							</td>
						</tr>						
					</table>
				</td>
				
				<td width='420px' id='tt_viewer_cell'>
					<table  width='420px'>
						<tr>
							<td>
								<p id='tt_viewer_title' align='center'></p>
							</td>
						</tr>
						<tr>
							<td>
								<p id='tt_viewer_img' align='center'></p>
							</td>
						</tr>
						<tr>
							<td>
								<p id='tt_viewer_obs' align='center'></p>
							</td>
						</tr>
					</table>
				</td>			
			</tr>
		</table>
		";
	}
	
}
?>