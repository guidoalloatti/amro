var globals = {
		currentOrders: null,
		server_url: "http://localhost:8080/?callback=?",
		currentCA: null
};

$(document).ready(function() {
	$("#mark_all").click(function(){
		$("input[type='checkbox']:not([disabled='disabled'])").attr('checked', true);
	});
	
	$("#unmark_all").click(function(){
		$("input[type='checkbox']:not([enabled='disabled'])").attr('checked', false);
	});
});