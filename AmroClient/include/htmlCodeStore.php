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
		$html.= '</head><body>';
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
            case "pr":
                $html.='
					<title>Menu Principal</title>
					<meta content="menu" name="keywords">
					<link rel="icon" href="/favicon.gif" type="image/gif">
					';
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
        $html = "<hr/>Usuario Logueado: Guido (<a href='#'>Desloguear</a>) :: Logueado a las 12:20:35 :: <a href='main.php?invoice_url=pr'>Volver al Menu Principal</a><hr/>
            </body></html>";
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
        return file_get_contents("html/body/certificados.html");
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

	
	function getDefaults()
	{
		return file_get_contents("html/errors/not_found.html");
	}
	
	
}
