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
	currentCerts: null
	logedUser: null,
	logedPass: null,
};


$(document).ready(function() {	
	
	//doGetSessionVars();
	
	$("#mark_all").click(function(){
		$("input[type='checkbox']:not([disabled='disabled'])").attr('checked', true);
	});
	
	$("#unmark_all").click(function(){
		$("input[type='checkbox']:not([enabled='disabled'])").attr('checked', false);
	});
});