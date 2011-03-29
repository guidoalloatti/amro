<?php

require_once("include/htmlCodeStore.php");

class Render
{
    private $includes;
    private $header;
    private $body;
    private $footer;
    private $pageInvoice;
    private $htmlCode;

    function __construct($pageInvoice)
    {
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
        switch($this->pageInvoice)
        {
            case "pr":
                $this->body = $this->htmlCode->getPrincipalBody();
                break;
            case "oc":
                $this->body = $this->htmlCode->getManageOCBody();
                break;
            case "ce":
                $this->body = $this->htmlCode->getCertificados();
                break;
			case "pe":
				$this->body = $this->htmlCode->getPermisos();
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
        echo $this->includes;
        echo $this->header;
        echo "<hr>";
        echo $this->body;
        echo "<hr>";
        echo $this->footer;
    }
}
