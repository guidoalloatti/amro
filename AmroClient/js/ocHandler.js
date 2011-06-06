var server_url = globals.server_url;
var user = $.cookie("user");
var pass = $.cookie("pass");

$(document).ready(function() {

	$("#show_all_oc_button").click(function(){
		getAllOC();
	});
	
	$("#new_oc_button").click(function(){
		startNewOC();
	});
	
	$("#new_oc_submit").click(function(){
		insertOC();
	});
	
	$("#parsing_cell").hide();
	
	$("#new_oc_cell").hide();
	
	$("#csvfile").change(function(e){
	  $in=$(this);
	  var file = $in.val();
	  //parseCSV(file);		  
	});
});

function uploadCSV()
{
	//console.log($("#formUploadCSV"));
	//console.log($("#csvfile").val());
	//console.log("Pedro");	
	parseCSV($("#csvfile").val());	
}

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
		default:
			alert("Seleccionar parámetro para filtrar la búsqueda");
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
	
	if (filter == 0)
		showOrders(orders, " de Todos Los Clientes");
	else
		showOrders(orders, " con cliente " + clientNameSearch(filter));
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
	
	if (filter == 0)
		showOrders(orders, " de Todos Los Materiales");
	else
		showOrders(orders, " con material " + materialNameSearch(filter));
}

function deleteOC(id)
{
	$.getJSON(server_url,
			{
				target: "CSVParsing",
				method: "DeleteOC",
				email: user,		//"pmata@amro.com",
				password: pass,		//"123"
				id: id
			},
			function(data) {
				if(data.success == true)
				{
					var order;
					
					for (var i = 0; i < globals.currentOrders; i++ )
						if (globals.currentOrders[i].id == id) {
							order = globals.currentOrders[i];
							globals.currentOrders = globals.currentOrders.splice(i, 1);
						}	
					
					$("#ordenes_compra td").each(function() {
						if ($(this).html() == id)
							$(this).parent().remove();
					});					
					
					//globals.currentClients = data.clients;
					//showOrders(globals.currentOrders, "");
				} else if (data.permissions != undefined) {
					alert("Error! No tiene permisos para realizar la operacion");
				} else
				{
					alert("No se pudp borrar la orden de compra. Error con el servidor");
				}
			});
}

function showOrders(orders, title)
{
	var inner_html = "<div style='float: left; height: 350px; width: 100%; overflow: auto'><table><tr class='oc'><th class='oc'>Orden de Compra</th><th class='oc'>Numero de Probeta</th><th class='oc'>Cliente</th><th class='oc'>Material</th><th class='oc'>Descripcion</th><th class='oc'>Id</th><th class='oc'>Borrar</th><th class='oc'>Generar Certificado</th></tr>";
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
		inner_html += "<td><button style='background: #e82c2c;' onclick='deleteOC("+orders[i].id+");'>Borrar</button></td>";
		inner_html += "<td align='center'><a href='main.php?invoice_url=ce&numprobeta="+orders[i].numprobeta+"&ordencompra="+orders[i].ordencompra+"&id="+orders[i].id+"&material="+orders[i].material_id+"&client="+orders[i].client_id+"&desc="+encodeURIComponent(orders[i].description)+"'><button>Generar</button></a></td>";
		inner_html += "</tr>";
	}
	inner_html += "</table>";
	$("#all_oc_title label").html("Ordenes de Compra"+title);
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
		if(data.success == true)
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
		if(data.success == true)
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
		$("#all_oc_title label").html("Ordenes de Compra");
		return;
	}
	loading("ordenes_compra", true);

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
			$("#all_oc_title label").html("Ordenes de Compra");
			return;
		}	
			
		showOrders(data.lines, " con Nº " + $("#orden_compra").val());
	});
}

function searchOCByProbeta()
{
	if($("#protocolo").val() == "")
	{
		inner_html = "No se definio el valor de busqueda por protocolo.";
		$("#ordenes_compra").html(inner_html);
		$("#all_oc_title label").html("Ordenes de Compra");
		return;
	}
	loading("ordenes_compra", true);

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
			$("#all_oc_title label").html("Ordenes de Compra");
			return;
		}	
			
		showOrders(data.lines, " con Nº de Probeta " + $("#protocolo").val());
	});
}
	
function startNewOC() {
	var inner_html = "<table>";
	inner_html += "<tr><td><label>Nº de Orden de Compra:</label></td><td><input type='text' placeholder='ej. 2564' id='oc_number' style='text-align:center;' /></td></tr>";
	inner_html += "<tr><td><label>Número de Probeta:</label></td><td><input type='text' placeholder='ej. ar1245, N3658' id='oc_probeta' style='text-align:center;'/></td></tr>";
	inner_html += "<tr><td><label>Elegir cliente:</label></td><td>";

	var clients = globals.currentClients;
	inner_html += "<select name='select_cliente' id='new_oc_cliente'><option value='0'>Todos los Clientes</option>";
	for(i = 0; i < clients.length; i++)
	{
		inner_html += "<option value='"+clients[i].id+"'>"+clients[i].name+"</option>";
	}
	inner_html += "</select></td></tr>";
	
	inner_html += "<tr><td><label>Elegir material:</label></td><td>";

	var materials = globals.currentMaterials;
	inner_html += "<select name='select_material' id='new_oc_material'><option value='0'>Todos los Materiales</option>";
	for(i = 0; i < materials.length; i++)
	{
		inner_html += "<option value='"+materials[i].id+"'>"+materials[i].name+"</option>";
	}
	inner_html += "</select></td></tr>";	
		
	inner_html += "<tr><td><label>Ingrese descripción:</label></td><td><input type='text' placeholder='ej. 3-TAPA E-4''300 RJ' id='oc_desc' style='text-align:center;'/></td></tr>";
	inner_html += "</table>";
	
	$("#new_oc_fields").html(inner_html);	
	$("#new_oc_cell").show("slow");	
}

function insertOC()
{
	var orden = $("#oc_number").val();
	if (orden == "") {
		alert("Ingrese número de orden de compra.");
		return;
	}
	
	var probeta = $("#oc_probeta").val();
	if (probeta == "") {
		alert("Ingrese un número de probeta.");
		return;
	}	
	
	var client = $("#new_oc_cliente").val();
	if (client == 0) {
		alert("Ingrese un cliente.");
		return;
	}
	
	var material = $("#new_oc_material").val();
	if (material == 0) {
		alert("Ingrese un material.");
		return;
	}
	
	var descripcion = $("#oc_desc").val();
	if (descripcion == "") {
		alert("Ingrese un descripcion.");
		return;
	}	
	
	$.getJSON(globals.server_url,
			{
				target: "CSVParsing",
				method: "NewOC",
				email: user,			//"pmata@amro.com",
				password: pass,			//"123",
				ordencompra: orden,
				material_id: material,
				client_id: client,
				description: descripcion,
				numprobeta: probeta
			},
			function(data) {
				if (data.success == true) {
					alert("La operación se realizó con éxito!");
					getAllOC();					
				} else if (data.probeta != undefined) {
					alert("Error! El formato del número de probeta " + orden + " no es valido.");
				} else if (data.permissions != undefined){
					alert("Error! Usted no tiene permisos para realizar la operación.");
				} else {
					alert("Error! Verifique los datos ingresados y que la orden de compra\n con los datos ingresados no exista.");
				}			
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
		if (data.success == true) {
			showOrders(data.lines, "");
				
			globals.currentOrders = data.lines;
			//alert(globals.currentOrders.length);
		}else
			alert("No se pudieron cargar las ordenes de compra. Error con el servidor.");
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
	$("#new_oc_cell").hide();
	var shortname = file.match(/[^\/\\]+$/);
	$.getJSON(server_url,
	{
		target: "CSVParsing",
		method: "ParseCSV",
		email: user,		//"pmata@amro.com",
		password: pass,		//"123",
		filepath: globals.pathToCSVUpload+shortname,	//"/home/guido/Escritorio/"+ shortname
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
		$("#parsing_cell").show("slow");
	});
}	



