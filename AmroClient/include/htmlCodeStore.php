<?php

class htmlCodeStore {

    public $pageInvoice;
    
    function __construct($page_invoice)
    {
        $this->pageInvoice = $page_invoice;
    }

	/* All Pages Commons */
    function getIncludes()
    {
        $html = '
            <!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
			"http://www.w3.org/TR/html4/loose.dtd">
            <html>
                <head>
                    <script src="js/jquery-1.5.1.min.js" type="text/javascript"></script>
                    <script src="js/jquery-ui-1.8.11.custom.min.js" type="text/javascript"></script>
                    <script src="js/slideHelper.js" type="text/javascript"></script>
                    <script src="js/menuHelper.js" type="text/javascript"></script>
                    <script src="js/jquery.treeview.js" type="text/javascript"></script>
                    <script src="js/commonHelper.js" type="text/javascript"></script>

                    <link href="css/slideStyle.css" rel="stylesheet" type="text/css">
                    <link href="css/screen.css" rel="stylesheet" type="text/css">
                    <link href="css/jquery.treeview.css" rel="stylesheet" type="text/css">
                    <link href="css/menu.buttons.css" rel="stylesheet" type="text/css">
            ';
			
		$html .= $this->getTitles();
		
		$html.= '</head><body>';
		return $html;

	}
			
	function getTitles()
	{
		switch ($this->pageInvoice)
		{
			case "ce":
				$html.='
					<title>Creacion de Certificados</title>
					<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
					<meta content="certificados" name="keywords">
					<link rel="icon" href="/favicon.gif" type="image/gif">
					';
				break;
			case "oc":
				$html.='
					<title>Administracion de Ordenes de Compra</title>
					<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
					<meta content="compra" name="keywords">
					<link rel="icon" href="/favicon.gif" type="image/gif">
					<script>
						$(document).ready(function(){
							$("#example").treeview();
						});
					</script>';
				break;
			case "pe":
				$html.='
					<title>Gestionar Permisos de Usuarios</title>
					<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
					<meta content="permisos" name="keywords">
					<link rel="icon" href="/favicon.gif" type="image/gif">
					';
			case "pr":
				$html.='
					<title>Menu Principal</title>
					<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
					<meta content="menu" name="keywords">
					<link rel="icon" href="/favicon.gif" type="image/gif">
					';
			default:
				$html.='
					<title>Pagina no Encontrada</title>
					<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
					<meta content="not_found" name="keywords">
					<link rel="icon" href="/favicon.gif" type="image/gif">
					';
				break;
		}
		return $html;
    }

    function getHeader()
    {
		switch ($this->pageInvoice)
		{
			case "oc":
				$pageDescription = "Gestión de Ordenes de Compra";
				break;
			default:
				$pageDescription = $this->pageInvoice;
				break;
		}
		
        $html = "
				<img src='img/amro_header_2.png' alt='Header' />
                <h2>Sistema de Gestion de Certificados :: ".$pageDescription."</h2>";
        return $html;
    }

    function getFooter()
    {
        $html = "Usuario Logueado: Guido :: Logueado a las 12:20:35 :: <a href='main.php?invoice_url=pr'>Volver al Menu Principal</a><hr/>
            </body></html>";
        return $html;
    }

	/* Start of Pages Html */
    function getPrincipalBody()
    {
        $html = "
            <h1>Menu Principal</h1>
            <table>
                <tr>
                    <td>
                        <button class='green' id='btn_green'>
                            <span>Generar Certificado</span>
                        </button>
                    </td>
                </tr>
                <tr>
                    <td>
                        <button class='red' id='btn_red'>
                            <span>Administrar Ordenes de Compra</span>
                        </button>
                    </td>
                </tr>
                <tr>
                    <td>
                        <button class='gray' id='btn_gray'>
                            <span>Configuracion del Sistema</span>
                        </button>
                    </td>
                </tr>
                <tr>
                    <td>
                        <button class='blue' id='btn_blue'>
                            <span>Administrar Abm</span>
                        </button>
                    </td>
                </tr>
				 <tr>
                    <td>
                        <button class='yellow' id='btn_yellow'>
                            <span>Gestionar Permisos de Usuarios</span>
                        </button>
                    </td>
                </tr>
				<tr>
                    <td>
                        <button class='orange' id='btn_orange'>
                            <span>Ir al Menu Principal</span>
                        </button>
                    </td>
                </tr>
            </table>";
        return $html;
    }

    function getManageOCBody()
    {
        $html = '
		<h3><u>Filtrar por los siguientes parametros</u></h3>
			
			Numero de Protocolo: <input id="protocolo" />
			
			Cliente:<select name="option_cliente">
				<option value="0">Todos</option>
				<option value="1">Thorsa</option>
				<option value="2">Cliente 2</option>
				<option value="3">Cliente 3</option>
			</select>
			
			Material:<select name="option_material">
				<option value="0">Todos</option>
				<option value="1">Material 1</option>
				<option value="2">Material 2</option>
				<option value="3">Material 3</option>
			</select>
			
			<input type="button" id="search" value="Buscar" />

			<br/><hr>
              <ul id="example" class="filetree">
              <li><span class="folder">Ordenes de Compra</span>
                <ul>
                    <li><span class="folder">Orden de Compra 1</span>
                        <ul>
                            <li><span class="file">Material WC</span></li>
                        </ul>
                    </li>
                    <li><span class="folder">Orden de Compra 2</span>
                        <ul>
                            <li><span class="folder">Material WC</span>
                                <ul>
                                    <li><span class="file">Detalles 1</span></li>
                                    <li><span class="file">Detalles 2</span></li>
                                </ul>
                            </li>
                            <li><span class="file">Material AC</span></li>
                        </ul>
                    </li>
                    <li class="closed"><span class="folder">Orden de Compra 3 (closed at start)</span>
                        <ul>
                            <li><span class="file">Material WC</span></li>
                        </ul>
                    </li>
                    <li><span class="folder">Orden de Compra 4</span></li>
                    </ul></ul>
					<br/><hr>Subir Ordenes de Compra:<input type="file" />
					';
					
					
					
        return $html;
    }

    function getCertificados()
    {
        $html = '
	        <div id="slide">
		        <h1>Creación de Certificado</h1>
		        <div id="navigation" style="display: none;">
				    <ul>
                        <li><a href="#">1. Orden de Compra</a></li>
                        <li><a href="#">2. Análisis Químico</a></li>
                        <li><a href="#">3. Análisis Mecánico</a></li>
                        <li><a href="#">4. Cargar Imagen</a></li>
                        <li><a href="#">5. Generar Certificado</a></li>
				    </ul>
			    </div>

		<div id="wrapper">
			<div id="steps">
				<form id="formElem" name="formElem" action="" method="post">
					<fieldset class="step">
						<legend>1. Orden de Compra</legend>
							<p><label for="nro_colada">Nro. de Colada</label><input id="nro_colada" name="nro_colada" /></p>
							<p><label for="fecha">Fecha</label><input id="fecha" name="fecha" /></p>
							<p><label for="material">Material</label><select id="material" name="material">
								<option value="material_1" selected="">Material 1</option>
								<option value="material_2" selected="">Material 2</option>
								<option value="material_3" selected="">Material 3</option>
								<option value="material_4" selected="">Material 4</option>
								<option value="material_5" selected="">Material 5</option>
								<option value="material_6" selected="">Material 6</option>
								<option value="material_7" selected="">Material 7</option>
								<option value="material_8" selected="">Material 8</option>
							</select></p>
							<p><label for="cliente">Cliente</label><select id="cliente" name="cliente">
								<option value="cliente_1" selected="">Cliente 1</option>
								<option value="cliente_2" selected="">Cliente 2</option>
								<option value="cliente_3" selected="">Cliente 3</option>
								<option value="cliente_4" selected="">Cliente 4</option>
								<option value="cliente_5" selected="">Cliente 5</option>
								<option value="cliente_6" selected="">Cliente 6</option>
								<option value="cliente_7" selected="">Cliente 7</option>
								<option value="cliente_8" selected="">Cliente 8</option>
							</select></p>
							<p><label for="descripcion">Descripcion</label><textarea rows="2" cols="30" id="descripcion" name="descripcion"placeholder="Ingrese aqui la descripción" autocomplete="OFF"></textarea></p>
							<p><label for="observaciones">Observaciones</label><textarea rows="2" cols="30" id="observaciones" name="observaciones"placeholder="Ingrese aqui las observaciones" autocomplete="OFF"></textarea></p>
							<p><label for="sip">SIP</label><input id="sip" name="sip" /></p>
							<p><label for="nro_oc">Nro. de Orden de Compra</label><input id="nro_oc" name="nro_oc" /></p>
					</fieldset>
					<fieldset class="step">
						<legend>2. Análisis Químico</legend>
						<p>Realizado en el espectrómetro, marca SPECTROMAXX, SP-08000777, nº 124621-08</p>
							<p><label for="_c">% C</label><input type="text" id="_c" name="_c" placeholder="Porcentaje de Carbono" autocomplete="OFF" /></p>
							<p><label for="_mn">% Mn</label><input type="text" id="_mn" name="_mn" placeholder="Porcentaje de Manganeso" autocomplete="OFF" /></p>
							<p><label for="_si">% Si</label><input type="text" id="_si" name="_si" placeholder="Porcentaje de Silicio" autocomplete="OFF" /></p>
							<p><label for="_p">% P</label><input type="text" id="_p" name="_p" placeholder="Porcentaje de Fósforo" autocomplete="OFF" /></p>
							<p><label for="_s">% S</label><input type="text" id="_s" name="_s" placeholder="Porcentaje de Azufre" autocomplete="OFF" /></p>
							<p><label for="_cr">% Cr</label><input type="text" id="_cr" name="_cr" placeholder="Porcentaje de Cromo" autocomplete="OFF" /></p>
							<p><label for="_ni">% Ni</label><input type="text" id="_ni" name="_ni" placeholder="Porcentaje de Níquel" autocomplete="OFF" /></p>
							<p><label for="_mo">% Mo</label><input type="text" id="_mo" name="_mo" placeholder="Porcentaje de Molibdeno" autocomplete="OFF" /></p>
							<p><label for="_cu">% Cu</label><input type="text" id="_cu" name="_cu" placeholder="Porcentaje de Cobre" autocomplete="OFF" /></p>
							<p><label for="_v">% V</label><input type="text" id="_v" name="_v" placeholder="Porcentaje de Vanadio" autocomplete="OFF" /></p>
							<p><label for="_ce">C.E.</label><input type="text" id="_ce" name="_ce" placeholder="Ingrese el C.E." autocomplete="OFF" /></p>
					</fieldset>
					<fieldset class="step">
						<legend>3. Análisis Mecánico</legend>
						<p>Realizado en una máquina universal de ensayos AMSLER, serie nº 9449, capacidad máxima 15 t, según lo especificado en la norma ASTM A 370</p>
							<p><label for="tension_rotura">Tensión de Rotura (Mpa)</label><input type="text" id="tension_rotura" name="tension_rotura" placeholder="Ingrese la Tensión de Rotura" autocomplete="OFF" /></p>
							<p><label for="limite_fluencia">Límite de Fluencia (Mpa)</label><input type="text" id="limite_fluencia" name="limite_fluencia" placeholder="Ingrese el Límite de Fluencia" autocomplete="OFF" /></p>
							<p><label for="alargamiento">Alargamiento (%)</label><input type="text" id="alargamiento" name="alargamiento" placeholder="Ingrese el porcentaje de Alargamiento" autocomplete="OFF" /></p>
							<p><label for="estricción">Estricción (%)</label><input type="text" id="estricción" name="estricción" placeholder="Ingrese el porcentaje de Estricción" autocomplete="OFF" /></p>
							<p><label for="resiliencia">Resiliencia (J) Charpy A</label><input type="text" id="resiliencia" name="resiliencia" placeholder="Ingrese Resiliencia (J) Charpy A" autocomplete="OFF" /></p>
							<p><label for="dureza">Dureza (Hb) 10/3000</label><input type="text" id="dureza" name="dureza" placeholder="Ingrese la Dureza (Hb) 10/3000" autocomplete="OFF" /></p>
					</fieldset>
					<fieldset class="step">
						<legend>4. Cargar la Imagen</legend>
							<p>Imagen....</p>
							
					</fieldset>
					<fieldset class="step"></fieldset>
					<fieldset class="step">
						<legend>Confirmación de generación de Certificado</legend>
						<p>Una vez que todos los campos de una solapa estén
						correctamente cargadas se marcará dicha solapa con un
						ícono verde.
						Un ícono rojo en una solapa significa que algún campo
						falta o no ha sido completado correctamente.
						En este último paso se confirman todos los anteriores
						y se genera el certificado.</p>
						<p class="submit"><button id="registerButton" type="submit">Generar Certificado!</button></p>
					</fieldset>
				</form>
			</div>
		</div>
	    </div>';
        return $html;
    }
	
	function getPermisos()
	{
		$html = '
			Usuario:
			<select name="option_usuarios">
				<option value="1">Admin</option>
				<option value="2">Pepe</option>
				<option value="3">Usuario 2</option>
			</select><hr/>
			
			<table width="750px" border="0" cellpadding="15" cellspacing="15">
				<tr>
					<td width="250px" style="border: 2px" bgcolor="lightyellow">
						<h3><u>Permisos de Usuario</u></h3>
							<h5>Crear Usuario <input type="checkbox"  name="create_user" id="create_user_checkbox" value="0">
							<br/>Listar Usuarios <input type="checkbox"  name="list_user" id="list_user_checkbox" value="0">
							<br/>Eliminar Usuarios <input type="checkbox"  name="delete_user" id="delete_user_checkbox" value="0">
							<br/>Modificar Usuarios <input type="checkbox"  name="edit_user" id="edit_user_checkbox" value="0">
						</h5>
					</td>
					<td width="250px" style="border: 2px" bgcolor="lightgreen">
						<h3><u>Permisos de Clientes</u></h3>
							<h5>Crear Cliente <input type="checkbox"  name="create_client" id="create_client_checkbox" value="0">
							<br/>Listar Clientes <input type="checkbox"  name="list_client" id="list_client_checkbox" value="0">
							<br/>Eliminar Clientes <input type="checkbox"  name="delete_client" id="delete_client_checkbox" value="0">
							<br/>Modificar Clientes <input type="checkbox"  name="edit_client" id="edit_client_checkbox" value="0">
						</h5>
					</td>
					<td width="250px" style="border: 2px" bgcolor="lightgray">
						<h3><u>Permisos de Ordenes de Compras</u></h3>
							<h5>Crear Orden de Compra <input type="checkbox"  name="create_oc" id="create_oc_checkbox" value="0">
							<br/>Listar Orden de Compra <input type="checkbox"  name="list_oc" id="list_oc_checkbox" value="0">
							<br/>Eliminar Orden de Compra <input type="checkbox"  name="delete_oc" id="delete_oc_checkbox" value="0">
							<br/>Modificar Orden de Compra <input type="checkbox"  name="edit_oc" id="edit_oc_checkbox" value="0">
						</h5>
					</td>
				</tr>
					<td width="250px" style="border: 2px" bgcolor="lightcyan">
						<h3><u>Permisos de Materiales</u></h3>
							<h5>Crear Material <input type="checkbox"  name="create_user" id="create_user_checkbox" value="0">
							<br/>Listar Material <input type="checkbox"  name="list_user" id="list_user_checkbox" value="0">
							<br/>Eliminar Material <input type="checkbox"  name="delete_user" id="delete_user_checkbox" value="0">
							<br/>Modificar Material <input type="checkbox"  name="edit_user" id="edit_user_checkbox" value="0">
						</h5>
					</td>
					<td width="250px" style="border: 2px" bgcolor="lightblue">
						<h3><u>Permisos de Certificados</u></h3>
							<h5>Crear Certificados <input type="checkbox"  name="create_certificate" id="create_certificate_checkbox" value="0">
							<br/>Listar Certificados <input type="checkbox"  name="list_certificate" id="list_certificate_checkbox" value="0">
							<br/>Eliminar Certificados <input type="checkbox"  name="delete_certificate" id="delete_certificate_checkbox" value="0">
							<br/>Modificar Certificados <input type="checkbox"  name="edit_certificate" id="edit_certificate_checkbox" value="0">
						</h5>
					</td>
					<td width="250px" style="border: 2px" bgcolor="#ff66ff">
						<h3><u>Permisos de Configuraciones</u></h3>
							<h5>Opcion 1 <input type="checkbox"  name="" id="" value="0">
							<br/>Opcion 2 <input type="checkbox"  name="" id="" value="0">
							<br/>Opcion 3 <input type="checkbox"  name="" id="" value="0">
							<br/>Opcion 4 <input type="checkbox"  name="" id="" value="0">
						</h5>
					</td>
			</table>
			<hr/>
			<!--
			<input type="button" id="mark_all" value="Asignar todos los permisos" /> :: 
			-->
			<a href="#" id="mark_all" >Marcar todos los permisos</a> ::
			<a href="#" id="unmark_all" >Desmarcar todos los permisos</a> ::
			<a href="#" id="recargar" >Recargar Permisos</a> ::
			<a href="main.php?invoice_url=pe&save=true" id="guardar" >Guardar Cambios</a>';
		return $html;
	
	}
    
	function getDefaults()
	{
		$html = "Pagina No Encontrada... Lo sentimos...";
		return $html;
	}
	
	
}
