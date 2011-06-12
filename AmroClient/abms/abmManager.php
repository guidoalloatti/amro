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
		$this->html = "<body id='abm_body' onload='materialStart();'> 
		<!--
		<h3>Listado de Materiales <div id='materiales_totales'>Cantidad de Materiales: 0</div></h3>
		-->
		<table width='90%' height='300px' border='0px'>
			<tr>
				<td width='25%' id='material_list' VALIGN='top'>
				<div style='height:300px; overflow:auto;'>
					<table>
					</td>
						</tr>
					</table>
					</div>
				</td>
				<td width='80%' VALIGN='top' class='invisible'>
					<table>
						<tr>
							<!-- <td><h3>Material Seleccionado:</h3></td> 
							<td align='right' id='material_seleccionado_name'></td>
							<td id='material_seleccionado_id'></td> -->
							
							<td align='right' id='material_seleccionado_name' class='rounded_4'>Ninguno</td>
							<td id='material_seleccionado_id'  align='right' class='rounded_4'>Sin Definir</td>
							
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
									<td><label>Nombre:</label></td>
									<td><input type='label' id='name' /></td>
								</tr></table></td>
								</tr>
								<tr>
									<th><b>Composicion Quimica</b></th>
									<th><b>Maximo</b></th>
									<th><b>Minimo</b></th>
									<th><b>Composicion Quimica</b></th>
									<th><b>Maximo</b></th>
									<th><b>Minimo</b></th>
								</tr>
								<tr>
									<td align='right'><label>% Carbono:</label></td>
									<td><input type='label' id='carbono_max' size='2'/></td>
									<td><input type='label' id='carbono_min' size='2'/></td>
									<td align='right'><label>% Cromo:</label></td>
									<td><input type='label' id='cromo_max' size='2'/></td>
									<td><input type='label' id='cromo_min' size='2'/></td>
								</tr>
								<tr>
									<td align='right'><label>% Manganeso:</label></td>
									<td><input type='label' id='manganeso_max' size='2'/></td>
									<td><input type='label' id='manganeso_min' size='2'/></td>
									<td align='right'><label>% Silicio:</label></td>
									<td><input type='label' id='silicio_max' size='2'/></td>
									<td><input type='label' id='silicio_min' size='2'/></td>
								</tr>
								<tr>
									<td align='right'><label>% Fosforo:</label></td>
									<td><input type='label' id='fosforo_max' size='2'/></td>
									<td><input type='label' id='fosforo_min' size='2'/></td>
									<td align='right'><label>% Azufre:</label></td>
									<td><input type='label' id='azufre_max' size='2'/></td>
									<td><input type='label' id='azufre_min' size='2'/></td>
								</tr>
								<tr>
									<td align='right'><label>% Niquel:</label></td>
									<td><input type='label' id='niquel_max' size='2'/></td>
									<td><input type='label' id='niquel_min' size='2'/></td>
									<td align='right'><label>% Molibdeno:</label></td>
									<td><input type='label' id='molibdeno_max' size='2'/></td>
									<td><input type='label' id='molibdeno_min' size='2'/></td>
								</tr>
								<tr>
									<td align='right'><label>% Cobre:</label></td>
									<td><input type='label' id='cobre_max' size='2'/></td>
									<td><input type='label' id='cobre_min' size='2'/></td>
									<td align='right'><label>% Vanadio:</label></td>
									<td><input type='label' id='vanadio_max' size='2'/></td>
									<td><input type='label' id='vanadio_min' size='2'/></td>
								</tr>
								<tr>
									<td align='right'><label>C.E.:</label></td>
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
									<td align='right'><label>Tension de Rotura (Mpa):</label></td>
									<td ><input type='label' id='tension_rotura_max' size='2'/></td>
									<td><input type='label' id='tension_rotura_min' size='2'/></td>
									<td align='right'><label>Limite de Fluencia (Mpa):</label></td>
									<td><input type='label' id='limite_fluencia_max' size='2'/></td>
									<td><input type='label' id='limite_fluencia_min' size='2'/></td>
								</tr>
								<tr>
									<td align='right'><label>Alargamiento (%):</label></td>
									<td><input type='label' id='alargamiento_max' size='2'/></td>
									<td><input type='label' id='alargamiento_min' size='2'/></td>
									<td align='right'><label>Estriccion (%):</label></td>
									<td><input type='label' id='estriccion_max' size='2'/></td>
									<td><input type='label' id='estriccion_min' size='2'/></td>
								</tr>
								<tr>
									<td align='right'><label>Resiliencia (J) Charpy A:</label></td>
									<td><input type='label' id='resiliencia_max' size='2'/></td>
									<td><input type='label' id='resiliencia_min' size='2'/></td>
									<td align='right'><label>Dureza (Hb) 10/3000:</label></td>
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
		<button id='guardar_material' >Guardar Material</button> ::
		<button id='actualizar_material' >Modificar Material</button> ::
		<!-- <button id='eliminar_material'>Eliminar Materia</button> :: -->
		<button id='recargar_material'>Recargar Material</button> ::
		<button id='recargar_lista_materiales'>Recargar Lista de Materiales</button> ::
		<button id='nuevo_material'>Nuevo Material</button><br/>
		<div id='html_code'></div>";
	}	
	
	function getAbmUsuarioHtml()
	{	
		$this->html = "<body id='abm_body' onload='userStart();'> 
		<!-- <h3>Listado de Usuarios <div id='usuarios_totales'>Cantidad de Usuarios: 0</div></h3>-->
		<table width='90%' height='300px' border='0px'>
			<tr>
				<td width='25%' id='usuario_list' VALIGN='top'>
				<div style='height:300px; overflow:auto;'>
					<table>
					</td>
						</tr>
					</table>
					</div>
				</td>
				<td class='invisible' width='70%' VALIGN='top'>
					<table>
						<tr>
							<!-- <td><h3>Usuario Seleccionado:</h3></td> -->
							<td align='right' id='usuario_seleccionado_name' class='rounded_4'>Ninguno</td>
							<td id='usuario_seleccionado_id'  align='right' class='rounded_4'>Sin Definir</td>
							
							<!-- <td align='right' id='usuario_seleccionado_name'></td>
							<td id='usuario_seleccionado_id'></td>-->
						</tr>
					</table>
					<table><hr noshade/></table>					
				<table>
					<tr>
						<td>
							<table>
								<tr>
									<td><label>Nombre:</label></td>
									<td><input type='label' id='name' /></td>
								</tr>
								<tr>
									<td><label>Apellido:</label></td>
									<td><input type='label' id='surname' /></td>
								</tr>		
								<tr>
									<td><label>Email:</label></td>
									<td><input type='label' id='email' /></td>
								</tr>
								<tr>
									<td><label>Password:</label></td>
									<td><input type='password' id='password' /></td>
								</tr>
								<tr id='signature_line'>
									<td><label>Firma:</label></td>
									<td>
										<img id='signature' width='100px' height='100px'/>									
									</td>
								</tr>	
								<tr>
									<td><div id='gestionarPermisosUsuario'></div> 
								</td>
									<!-- <a href='main.php?invoice_url=pe&userid=1'>Gestionar Permisos del Usuario</a> -->
								</tr>
								
							</table>
						</td>
					</tr>
				</table>
				</td>	
			</tr>
		</table>
		<hr>
		<button id='guardar_usuario' >Guardar Usuario</button> ::
		<button id='actualizar_usuario' >Modificar Usuario</button> ::
		<button id='recargar_usuario'>Recargar Usuario</button> ::
		<button id='recargar_lista_usuarios'>Recargar Lista de Usuarios</button> ::
		<button id='nuevo_usuario'>Nuevo Usuario</button><br/>
		<div id='html_code'></div>";
	}
	
	function getAbmClienteHtml()
	{	
		$this->html = "<body id='abm_body' onload='clientStart();'>
		<table width='95%' height='300px' border='0px'>
			<!-- 
			<tr>
				<td id='clientes_totales'>Cantidad de Clientes: 0
						<div id='clientes_totales'>Cantidad de Clientes: 0</div>s 
				</td>
			</tr>
			-->
			<tr>
				<td width='30%' id='client_list' VALIGN='top'>
					<div style='height:300px overflow:auto;'>
					<!--
					<table>
						</td>
						</tr>
					</table>
					-->
					</div>
				</td>
				<td  width='65%' VALIGN='top' class='invisible' id='client_details'>
					<table>
						<tr>
							<!-- <td class='rounded_2'><b>Cliente Seleccionado<b></td> -->
							<td align='right' id='cliente_seleccionado_name' class='rounded_4'>Ninguno</td>
							<td id='cliente_seleccionado_id'  align='right' class='rounded_4'>c</td>
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
										<label>Nombre:</label>
									</td>
									<td>
										<input type='label' id='name' />
									</td>
									<td>
										<label>Direccion:</label>
									</td>
									<td>
										<input type='label' id='address' />
									</td>
								</tr>
								<tr>
									<td>
										<label>Ciudad:</label>
									</td>
									<td>
										<input type='label' id='city' />
									</td>
									<td>
										<label>Codigo Postal:</label>
									</td>
									<td>
										<input type='label' id='zip' />
									</td>
								</tr>
								<tr>
									<td>
										<label>Pais:</label>
									</td>
									<td>
										<input type='label' id='country' />
									</td>
									<td>
										<label>Telefono:</label>
									</td>
									<td>
										<input type='label' id='phone' />
									</td>
								</tr>
								<tr>
									<td>
										<label>Fax:</label>
									</td>
									<td>
										<input type='label' id='telefax' />
									</td>
									<td>
										<label>Pagina Web:</label>
									</td>
									<td>
										<input type='label' id='website' />
									</td>
								</tr>
								<tr>
									<td>
										<label>Codigo de Identificacion:</label>
									</td>
									<td>
										<input type='label' id='namecode' />
									</td>
									<td>
										<label>Cantidad Dígitos por Código:</label>
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
		<button id='guardar_cliente' >Guardar Cliente</button> ::
		<button href='#' id='actualizar_cliente' >Modificar Cliente</button> ::
		<!-- <a href='#' id='eliminar_cliente'>Eliminar Cliente</button> :: -->
		<button href='#' id='recargar_cliente'>Recargar Cliente</button> ::
		<button href='#' id='recargar_lista_clientes'>Recargar Lista de Clientes</button> ::
		<button href='#' id='nuevo_cliente'>Nuevo Cliente</button><br/>
		<div id='html_code'></div>";
	}

	function getAbmTtermicoHtml()
	{
		$this->html = "<body onload='tratamientoTermicoStart();'> <h3>Carga y visualización de Tratamientos Termicos y asociación con Análisis Químicos realizados </h3>
		<table id='abm_tt'>
			<tr>
				<td width='420px' id='all_tt_cell' style='vertical-align:top;'>
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
				
				<td width='430px' id='link_tt_cell' style='vertical-align:top;'>
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
				
				<td width='420px' id='new_tt_cell' style='vertical-align:top;'>
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
									<input type='text' placeholder='dd' id='tt_day' style='text-align:center;' size='1'/><input placeholder='mm' style='text-align:center;' id='tt_month' type='text' size='1'/><input placeholder='yyyy' style='text-align:center;' id='tt_year' type='text' size='1'/><br/>
									* Si no ingresa nada se tomará la fecha de hoy.
								</p>
									<form action='upload_ttfile.php' method='post' enctype='multipart/form-data' target='_blank' id='ttImageUpload'>
										<p id='new_tt_image'>									
											<label for='tt_image_path'>Seleccione una nueva imagen:</label><input id='tt_image_file' name='file' type='file'/>
										</p>
									</form>								
								
								<p id='new_tt_obs'><label>Ingrese observación:</label><textarea id='tt_obs' cols='20' rows='5'></textarea></p>
								<p id='new_tt_submit' align='center'><button onclick='newTT(); event.preventDefault();'>Crear</button></p>
							</td>
						</tr>						
					</table>
				</td>
				
				<td width='420px' id='tt_viewer_cell' style='vertical-align:top;'>
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