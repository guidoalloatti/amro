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
        $html = file_get_contents("html/header/includes.html");
		$html .= $this->getTitles();
		switch ($this->pageInvoice)
        {
        	case "oc":
        		$html .= "</head><body onload='loadOCPage();'>";
        		break;
        	case "ce":
        		$html .= "</head><body onload='loadCert();'>";
        		break;
        	default:
        		$html .= '</head><body>';
        		break;
        }		
		return $html;
	}

    function getTitles()
    {
        $html = '<meta http-equiv="Content-Type" content="text/html; charset=utf-8">';
        switch ($this->pageInvoice)
        {
            case "ce":
                $html.='
					<title>Creacion de Certificados</title>
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
					<meta content="permisos" name="keywords">
					<link rel="icon" href="/favicon.gif" type="image/gif">
					';
                break;
            case "pr":
                $html.='
					<title>Menu Principal</title>
					<meta content="menu" name="keywords">
					<link rel="icon" href="/favicon.gif" type="image/gif">
					';
                break;
			case "ab":
				$html.='
					<title>Altas, Bajas y Modificaciones</title>
					<meta content="menu" name="keywords">
					<link rel="icon" href="/favicon.gif" type="image/gif">
					';
					break;
			case "abm":
				$html.='
					<title>Altas, Bajas y Modificaciones</title>
					<meta content="menu" name="keywords">
					<link rel="icon" href="/favicon.gif" type="image/gif">
					';
					break;
            default:
                $html.='
					<title>Pagina no Encontrada</title>
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
                <hr><h2>Sistema de Gestion de Certificados :: ".$pageDescription."</h2><hr>";
        return $html;
    }

    function getFooter()
    {
		$lastLoginTimestamp = $_SESSION['lastLoginDate'][$_SESSION['user']];
		$logedTimestamp = time() - $_SESSION['lastLoginDate'][$_SESSION['user']];
		
		$lastLoginDate = date("H:i:s d/m", $lastLoginTimestamp);
		
		$logedDateHours = floor($logedTimestamp/3600);
		$logedDateMinutes = round(($logedTimestamp%3600)/60);
		
		$usuarioLogueadoMensaje = "Usuario Logueado: <b>".$_SESSION['user']."</b> (<a href='main.php?invoice_url=logout'>Desloguear</a>)"; 
		$sesionActivaMensaje =  "Sesion Activa por ".$logedDateHours." horas y ".$logedDateMinutes." minutos";
		$sesionEmpezadaMensaje = "Logueado a las ".$lastLoginDate;
		
		
		if($_SESSION['user'] === null || $_SESSION['pass'] === null)
			$html = "<hr/><b>Ningun</b> Usuario Logueado<hr/></body></html>";
		else	
			$html = "<hr/>$usuarioLogueadoMensaje :: $sesionEmpezadaMensaje :: $sesionActivaMensaje :: <a href='main.php?invoice_url=pr'>Volver al Menu Principal</a><hr/></body></html>";
        return $html;
    }

    /* Start of Pages Html */
    function getPrincipalBody()
    {
        return file_get_contents("html/body/principal.html");
    }

    function getManageOCBody()
    {
        return file_get_contents("html/body/orden_compra.html");
    }

    function getCertificados()
    {
		//var_dump($_GET);
		//echo "<p>Generar Certificado para la orden de compra con numero de probeta: ".$_GET['numprobeta']."</p>";
        //return file_get_contents("html/body/certificados.html");
		
		$html = '
		
		<div id="slide">
        <!-- <h1>Creación de Certificado</h1> -->
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

					<p>Generando Certificado para la Orden de Compra: '.$_GET["ordencompra"].'</p>
					<p>y con Numero de Probeta: '.$_GET["numprobeta"].'</p>
					
					<br/>
					<button style="display: block;" id="ver_detalles">Ver detalles de la Orden de Compra</button>
					<p id="oc_details"></p>
					
					<button style="display: block;" id="cambiar_ocb">Seleccionar otra Orden de Compra </button> 
					<p id="all_oc"></p>
					
            </fieldset>
            <fieldset class="step">
                <legend>2. Análisis Químico <legend_comments>Realizado en el espectrómetro, marca SPECTROMAXX, SP-08000777, nº 124621-08</legend_comments></legend>
                    <p>
					<label for="_c">% C</label><input type="text" id="_c" name="_c" placeholder="Porcentaje de Carbono" autocomplete="OFF" />
                    <label for="_mn">&nbsp;&nbsp;% Mn</label><input type="text" id="_mn" name="_mn" placeholder="Porcentaje de Manganeso" autocomplete="OFF" />
					</p>
                    
					<p>
					<label for="_si">% Si</label><input type="text" id="_si" name="_si" placeholder="Porcentaje de Silicio" autocomplete="OFF" />
                    <label for="_p">&nbsp;&nbsp;% P</label><input type="text" id="_p" name="_p" placeholder="Porcentaje de Fósforo" autocomplete="OFF" />
					</p>
                    
					<p>
					<label for="_s">% S</label><input type="text" id="_s" name="_s" placeholder="Porcentaje de Azufre" autocomplete="OFF" />
                    <label for="_cr">&nbsp;&nbsp;% Cr</label><input type="text" id="_cr" name="_cr" placeholder="Porcentaje de Cromo" autocomplete="OFF" />
					</p>
					
                    <p>
					<label for="_ni">% Ni</label><input type="text" id="_ni" name="_ni" placeholder="Porcentaje de Níquel" autocomplete="OFF" />
                    <label for="_mo">&nbsp;&nbsp;% Mo</label><input type="text" id="_mo" name="_mo" placeholder="Porcentaje de Molibdeno" autocomplete="OFF" />
					</p>
                    
					<p>
					<label for="_cu">% Cu</label><input type="text" id="_cu" name="_cu" placeholder="Porcentaje de Cobre" autocomplete="OFF" />
                    <label for="_v">&nbsp;&nbsp;% V</label><input type="text" id="_v" name="_v" placeholder="Porcentaje de Vanadio" autocomplete="OFF" />
					</p>
					
					<p><label for="_ce">C.E.</label><input type="text" id="_ce" name="_ce" placeholder="Ingrese el C.E." autocomplete="OFF" /></p>
                    
					<p><button id="checkCAExistence">Chequear Existencia de Analisis Quimico</button></p>
					<p id="addCA"><label for="_file">Suba un nuevo archivo:</label><input id="_file" type="file"/></p>
                                             
                    <p id="selectedCA"></p>
            
			</fieldset>
            <fieldset class="step">
                <legend>3. Análisis Mecánico <legend_comments>Realizado en una máquina universal de ensayos AMSLER, serie nº 9449, capacidad máxima 15 t, según lo especificado en la norma ASTM A 370</legend_comments></legend>
                    <p><label for="tension_rotura">Tensión de Rotura (Mpa)</label><input type="text" id="tension_rotura" name="tension_rotura" placeholder="Ingrese la Tensión de Rotura" autocomplete="OFF" /></p>
                    <p><label for="limite_fluencia">Límite de Fluencia (Mpa)</label><input type="text" id="limite_fluencia" name="limite_fluencia" placeholder="Ingrese el Límite de Fluencia" autocomplete="OFF" /></p>
                    <p><label for="alargamiento">Alargamiento (%)</label><input type="text" id="alargamiento" name="alargamiento" placeholder="Ingrese el porcentaje de Alargamiento" autocomplete="OFF" /></p>
                    <p><label for="estricción">Estricción (%)</label><input type="text" id="estriccion" name="estricción" placeholder="Ingrese el porcentaje de Estricción" autocomplete="OFF" /></p>
                    <p><label for="resiliencia">Resiliencia (J) Charpy A</label><input type="text" id="resiliencia" name="resiliencia" placeholder="Ingrese Resiliencia (J) Charpy A" autocomplete="OFF" /></p>
                    <p><label for="dureza">Dureza (Hb) 10/3000</label><input type="text" id="dureza" name="dureza" placeholder="Ingrese la Dureza (Hb) 10/3000" autocomplete="OFF" /></p>
                    
                    <p id="showSave"></p>                    
                    
                    <p><button id="checkMAExistence">Buscar Análisis Mecánico ya cargado</button></p>
                    <p id="allMA"></p>
            </fieldset>
            <fieldset class="step">
                <legend>4. Cargar la Imagen</legend>
                    <p><input type="text" id="ttermico_selected"/></p>
                    <p id="show_ttermico_asoc"></p>                  
                    <table width="810px" id="abm_tt">
                    	<tr>                    		
                    		<td>
                    		<table width="300px">
								<tr>
									<td>
										<p style="width: 300px;" id="all_tt_title" align="center">
											<label style="float:center; font-weight:bold;">Otros Tratamientos Térmicos</label>
										</p>
									</td>
								</tr>
								<tr id="show_tt" width="300px">
									<td width="300px">
		                    			<p style="width: 300px;" id="all_tt"></p>
		                    		</td> 
								</tr>
								<tr width="300px">
									<td align="center">
										<p align="center" style="width: 300px;" id="ca_selection">
											<button style="float:center;" id="create_tt_button">Crear Nuevo T. Térmico</button>
										</p>
									</td>				
								</tr>
							</table>
							</td>
                    		<td>
                    			<table  width="480px">
									<tr>
										<td>
											<p style="width: 480px;" id="tt_viewer_title" align="center"></p>
										</td>
									</tr>
									<tr>
										<td>
											<p style="width: 480px;" id="tt_viewer_img" align="center"></p>
										</td>
									</tr>
									<tr>
										<td>
											<p style="width: 480px;" id="tt_viewer_obs" align="center"></p>
										</td>
									</tr>
								</table>                    		
                    		</td>
                    	</tr>
                    </table>

            </fieldset>
            <fieldset class="step">
                <legend>Confirmación de generación de Certificado</legend>
                <p>Una vez que todos los campos de una solapa estén
                correctamente cargadas se marcará dicha solapa con un
                ícono verde.
                Un ícono rojo en una solapa significa que algún campo
                falta o no ha sido completado correctamente.
                En este último paso se confirman todos los anteriores
                y se genera el certificado.</p>
                <p><label for="observations">Observaciones</label><input type="text" id="observations" name="observations" placeholder="Ingrese alguna observación" autocomplete="OFF" /></p>
                <p><label for="reviewer" id="reviewer">Revisa</label><select name="select_reviewer" id="select_reviewer"><option value="0">Seleccionar</option></select></p>
                <p><label for="approver" id="approver">Aprueba</label><select name="select_approver" id="select_approver"><option value="0">Seleccionar</option></select></p>
                <p class="submit"><button id="registerButton" type="submit">Generar Certificado!</button></p>
            </fieldset>
            <fieldset class="step"></fieldset>            
        </form>
    </div>
</div>
</div>';

	return $html;
		
    }
	
	function getPermisos()
	{
		return file_get_contents("html/body/permisos.html");
	}

    function getAbms()
    {
        return file_get_contents("html/body/abms.html");
    }

	function getBody()
	{
		switch($this->pageInvoice)
		{
			case "pr":
				$html_page_name = "principal.html";
				break;
			case "oc":
				$html_page_name = ".html";
				break;
			case "ce":
				$this->body = $this->getCertificados();
				break;
			case "pe":
				$this->body = $this->getPermisos();
				break;
			case "ab":
				$this->body = $this->getAbms();
				break;
			default:
				$this->body = $this->getDefaults();
				break;
		}
	}

	function getLoginBody()
	{
		return file_get_contents("html/body/mainlogin.html");
	}
	
	function doLogoutBody()
	{
		session_destroy();
		unset($_SESSION['lastLoginDate'][$_SESSION['user']]);
		unset($_SESSION['user']);
		unset($_SESSION['pass']);
		
		return file_get_contents("html/body/logout.html");
	}
	
	function getDefaults()
	{
		return file_get_contents("html/errors/not_found.html");
	}
	
	
}
