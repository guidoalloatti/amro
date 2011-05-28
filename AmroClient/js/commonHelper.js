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
	pathToCerts: "files/certificados/",
};


$(document).ready(function() {	
	// Cuidado con lo que se pone aca, se carga SIEMPRE!!!
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