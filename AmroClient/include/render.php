<?php

require_once("include/htmlCodeStore.php");
require_once("abms/abmManager.php");

class Render
{
    private $includes;
    private $header;
    private $body;
    private $footer;
    private $pageInvoice;
    private $htmlCode;
	private $module;
	
    function __construct($pageInvoice, $module=null)
    {
		$this->module = $module;
        $this->pageInvoice = $pageInvoice;
        $this->htmlCode = new htmlCodeStore($pageInvoice);
    }

    private function getIncludes()
    {
        $this->includes = $this->htmlCode->getIncludes();
    }

    private function getHeader()
    {
        $this->header = $this->htmlCode->getHeader();
    }

    private function getFooter()
    {
        $this->footer = $this->htmlCode->getFooter();
    }

    private function getBody()
    {
		$this->body = $this->htmlCode->getBody();
		
        switch($this->pageInvoice)
        {
            case "pr":
                $this->body = $this->htmlCode->getPrincipalBody();
                break;
            case "oc":
                $this->body = $this->htmlCode->getManageOCBody();
                break;
            case "cm":
                $this->body = $this->htmlCode->getManageCertBody();
                break;
            case "ce":
                $this->body = $this->htmlCode->getCertificados();
                break;
			case "pe":
				$this->body = $this->htmlCode->getPermisos();
                break;
            case "ab":
                $this->body = $this->htmlCode->getAbms();
                break;
			case "abm":
				$abmManager = new abmManager();
				$this->body = $abmManager->getAbmHtml();
				break;
			case "lo":
				$this->body = $this->htmlCode->getLoginBody();
				break;
			case "logout":
				$this->body = $this->htmlCode->doLogoutBody();
				break;
            default:
				$this->body = $this->htmlCode->getDefaults();
                break;
        }
    }

    public function getPage()
    {
        $this->getIncludes();
        $this->getHeader();
        $this->getBody();
        $this->getFooter();
    }

    public function renderPage()
    {
        echo $this->includes . $this->header . $this->body . $this->footer;
    }
}
