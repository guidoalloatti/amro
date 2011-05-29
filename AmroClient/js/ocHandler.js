var server_url = globals.server_url;
var user = $.cookie("user");
var pass = $.cookie("pass");

$(document).ready(function() {

	$("#cargar_ocs").click(function(){
		getAllOC();
	});
	
	$("#csvfile").change(function(e){
	  $in=$(this);
	  var file = $in.val();
	  parseCSV(file);		  
	});
});

function loadOCPage()
{
	
	if(user == null || pass == null)
		doGetSessionVars();
	loadOCClients();
	loadOCMaterials();
	getAllOC();	
}

function searchOC()
{
	var selected_search = $("input[@name='filtro']:checked").val();
	
	switch(selected_search)
	{
		case "o":
			searchOCByOC();
			break;
		case "p":
			searchOCByProbeta();
			break;
		case "c":
			searchOCByClient();
			break;
		case "m":
			searchOCByMaterial();
			break;
		default:
			getAllOC();
			break;
	}
	
	//console.log($("input[@name='filtro']:checked").val());
	//console.log($("#filtro_orden_compra:checked").val());
	//if($("#filtro_orden_compra").val());
	/*
	alert("Buscando OC cliente "+$("#select_cliente").val()+
		  "\ncon el material "+$("#select_material").val()+
		  "\ny con orden de compra con valor "+$("#protocolo").val());
	*/
}

function filterOCClient(filter)
{	
	if (globals.currentOrders == null || globals.currentOrders.length == 0)
		return;
	
	var orders = new Array();
	
	if (filter == 0) {
		orders = globals.currentOrders;	
	} else {	
		for (var i=0; i < globals.currentOrders.length; i++) 
			if (globals.currentOrders[i].client_id == filter)
				orders.push(globals.currentOrders[i]);
	}
	
	showOrders(orders);
}

function filterOCMaterial(filter)
{	
	if (globals.currentOrders == null || globals.currentOrders.length == 0)
		return;
	
	var orders = new Array();
	
	if (filter == 0) {
		orders = globals.currentOrders;	
	} else {	
		for (var i=0; i < globals.currentOrders.length; i++) 
			if (globals.currentOrders[i].material_id == filter)
				orders.push(globals.currentOrders[i]);
	}
	
	showOrders(orders);
}

function showOrders(orders)
{
	var inner_html = "<tr class='oc'><th class='oc'>Orden de Compra</th><th class='oc'>Numero de Probeta</th><th class='oc'>Cliente</th><th class='oc'>Material</th><th class='oc'>Descripcion</th><th class='oc'>Id</th><th class='oc'>Generar Certificado</th></tr>";
	for(var i=0; i < orders.length; i++)
	{
		var line = "even";
		if( i%2 == 0 ) 
			line = "odd";

		inner_html += "<tr class='"+line+"'>";
			inner_html += "<td class='oc'>"+orders[i].ordencompra+"</td>";
		inner_html += "<td>"+orders[i].numprobeta+"</td>";
		inner_html += "<td>"+clientNameSearch(orders[i].client_id)+"</td>";
		inner_html += "<td>"+materialNameSearch(orders[i].material_id)+"</td>";
		inner_html += "<td>"+orders[i].description+"</td>";
		inner_html += "<td>"+orders[i].id+"</td>";
		inner_html += "<td align='center'><a href='main.php?invoice_url=ce&numprobeta="+orders[i].numprobeta+"&ordencompra="+orders[i].ordencompra+"&id="+orders[i].id+"&material="+orders[i].material_id+"&client="+orders[i].client_id+"&desc="+encodeURIComponent(orders[i].description)+"'><button>Generar</button></a></td>";
		inner_html += "</tr>";
	}	
	$("#ordenes_compra").html(inner_html);
}

function showClientsByOC(clients)
{		
	var inner_html = "<select name='select_cliente' id='oc_select_cliente'><option value='0'>Todos los Clientes</option>";
	for(i = 0; i < clients.length; i++)
	{
		inner_html += "<option value='"+clients[i].id+"'>"+clients[i].name+"</option>";
	}
	inner_html += "</select>";	
	$("#clientes").replaceWith(inner_html);
	$("#oc_select_cliente").change(function(e){
		$in=$(this);
		var value = $in.val();
		filterOCClient(value);
	});	
}

function loadOCClients()
{
	if(globals.currentClients != null && globals.currentClients.length > 0)
		showClients(globals.currentClients);
	
	$.getJSON(server_url,
	{
		target: "Client",
		method: "GetClient",
		email: user,		//"pmata@amro.com",
		password: pass,		//"123"
	},
	function(data) {
		if(data.success == true && data.clients.length > 0)
		{
			globals.currentClients = data.clients;
			showClientsByOC(data.clients);
		}
		else
		{
			alert("No se pudieron cargar los clientes. Error con el servidor");
		}
	});
}

function showMaterialsByOC(materials)
{		
	var inner_html = "<select name='select_material' id='oc_select_material'><option value='0'>Todos los Materiales</option>";
	for(i = 0; i < materials.length; i++)
	{
		inner_html += "<option value='"+materials[i].id+"'>"+materials[i].name+"</option>";
	}
	inner_html += "</select>";	
	$("#materiales").replaceWith(inner_html);
	$("#oc_select_material").change(function(e){
		$in=$(this);
		var value = $in.val();
		filterOCMaterial(value);
	});	
}

function loadOCMaterials()
{
	if(globals.currentMaterials != null && globals.currentMaterials.length > 0)
		showMaterials(globals.currentMaterials);
	
	$.getJSON(server_url,
	{
		target: "Material",
		method: "GetMaterial",
		email: user,		//"pmata@amro.com",
		password: pass,		//"123"
	},
	function(data) {
		if(data.success == true && data.materials.length > 0)
		{
			globals.currentMaterials = data.materials;
			showMaterialsByOC(data.materials);
		}
		else
		{
			alert("No se pudieron cargar los materiales. Error con el servidor");
		}
	});
}

function searchOCByOC()
{
	if($("#orden_compra").val() == "")
	{
		inner_html = "No se definio el valor de busqueda por orden de compra.";
		$("#ordenes_compra").html(inner_html);
		return;
	}
	$.getJSON(globals.server_url,
	{
		target: "CSVParsing",
		method: "GetOC",
		email: user,		//"pmata@amro.com",
		password: pass,		//"123",
		ordencompra: $("#orden_compra").val(),
		order: "ordencompra"
	},
	function(data) {
		if(data.lines.length < 1)
		{
			inner_html = "No se encontro ninguna orden de compra con valor "+$("#orden_compra").val();
			$("#ordenes_compra").html(inner_html);
			return;
		}	
			
		showOrders(data.lines);
	});
}

function searchOCByProbeta()
{
	if($("#protocolo").val() == "")
	{
		inner_html = "No se definio el valor de busqueda por protocolo.";
		$("#ordenes_compra").html(inner_html);
		return;
	}
	$.getJSON(globals.server_url,
	{
		target: "CSVParsing",
		method: "GetOC",
		email: user,			//"pmata@amro.com",
		password: pass,			//"123",
		numprobeta: $("#protocolo").val(),
		order: "numprobeta"
	},
	function(data) {
		if(data.lines.length < 1)
		{
			inner_html = "No se encontro ninguna orden de compra con valor de protocolo "+$("#orden_compra").val();
			$("#ordenes_compra").html(inner_html);
			return;
		}	
			
		showOrders(data.lines);
	});
}
	

	
function getAllOC()
{
	
	loading("ordenes_compra", true);
	$.getJSON(globals.server_url,
	{
		target: "CSVParsing",
		method: "GetOC",
		email: user,			//"pmata@amro.com",
		password: pass,			//"123",
		order: "ordencompra",	
	},
	function(data) {
		showOrders(data.lines);
				
		globals.currentOrders = data.lines;
		//alert(globals.currentOrders.length);
	});
}	

function clientNameSearch(id)
{
	if (globals.currentClients == null)
		return "Desconocido";
	
	for (var i = 0; i < globals.currentClients.length; i++) 
		if (globals.currentClients[i].id == id)
			return globals.currentClients[i].name;
	
	return "Desconocido";
}

function materialNameSearch(id)
{
	if (globals.currentMaterials == null)
		return "Desconocido";
	
	for (var i = 0; i < globals.currentMaterials.length; i++) 
		if (globals.currentMaterials[i].id == id)
			return globals.currentMaterials[i].name;
	
	return "Desconocido";
}

function parseCSV(file)
{
	var shortname = file.match(/[^\/\\]+$/);
	$.getJSON("http://localhost:8080/?callback=?",
	{
		target: "CSVParsing",
		method: "ParseCSV",
		email: user,		//"pmata@amro.com",
		password: pass,		//"123",
		filepath: globals.pathToUpload+shortname,	//"/home/guido/Escritorio/"+ shortname
	},
	function(data) {
		if (data.errors == 'undefined')
			return;
		inner_html = '<li><span class="folder">Errores</span><ul>';
		for (var v in data.errors) {
			inner_html += '<li class="closed"><span class="folder">Linea: ' + v + '</span><ul>';
			inner_html += '<li><span class="file">' + data.errors[v] + '</span></li></ul>';
		}
		inner_html += '</ul></li>';
		$("#parsingreport").html(inner_html);
		$("#parsingreport").treeview();	
	});
}	



