var globals = {
	currentOrders: null,
	server_url: "http://localhost:8080/?callback=?",
	currentCA: null,
	currentMaterials: null,
	currentClients: null,
	currentOC: null,
	currentMA: null,
	currentUsers: null,
	currentTTermicos: null,
	currentUsers: null,
	currentCerts: null,
	logedUser: null,
	logedPass: null,
	pathToUpload: "../AmroClient/files/uploads/",
	pathToCerts: "../AmroClient/certificados/img/"
};

function loadError()
{
	alert("Error! No se puede comunicar con el servidor. Chequee su conexión.");
}

$(document).ready(function() {	
	// Cuidado con lo que se pone aca, se carga SIEMPRE!!!
	$.ajaxSetup({timeout: 15000, error: loadError, async: false});	
});

// Read a page's GET URL variables and return them as an associative array.
$.extend({
  getUrlVars: function(){
    var vars = [], hash;
    var hashes = window.location.href.slice(window.location.href.indexOf('?') + 1).split('&');
    for(var i = 0; i < hashes.length; i++)
    {
      hash = hashes[i].split('=');
      vars.push(hash[0]);
      vars[hash[0]] = hash[1];
    }
    return vars;
  },
  getUrlVar: function(name){
    return $.getUrlVars()[name];
  }
});

function loading(object, show)
{
	var inner_html = "<div width='100%' height='100%' align='center'>";
	inner_html += "<img src='img/ajax-loader2.gif'/>";
	inner_html += "</div>";
	
	$("#"+object).html(inner_html);
	
	if (show)
		$("#"+object).show("slow");
}

