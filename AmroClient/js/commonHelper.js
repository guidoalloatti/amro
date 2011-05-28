
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
};

$(document).ready(function() {

	//SI.Files.stylizeAll();
	//SI.Files.stylizeById('test_file');
	
	$("#mark_all").click(function(){
		$("input[type='checkbox']:not([disabled='disabled'])").attr('checked', true);
	});
	
	$("#unmark_all").click(function(){
		$("input[type='checkbox']:not([enabled='disabled'])").attr('checked', false);
	});
});