/**
 * 
 */

var server_url = "http://127.0.0.1:8080/?callback=?";
var clients;
var materials;
var ordencompras = null;

$(document).ready(function() {

	/*$("#parse_csv_button").click(function(){
		parseCSV();
	});	
	
	$("#delete_oc_button").click(function(){
		deleteOC();
	});	
	
	$("#get_oc_by_probeta_button").click(function(){
		getOCByProbeta();
	});	
	
	$("#get_oc_by_client_button").click(function(){
		getOCByClient();
	});	
	
	$("#get_oc_by_material_button").click(function(){
		getOCByMaterial();
	});	
	
	$("#get_all_oc_button").click(function(){
		getAllOC();
	});	
	
	$("#get_oc_by_oc_button").click(function(){
		getOCByOC();
	});*/
	getAllClients();
	getAllMaterials();
	
	$("#csvfile").change(function(e){
		  $in=$(this);
		  var file = $in.val();
		  parseCSV(file);		  
		});

	
	$("#search").click(function(){
		performSearch();
	});
	
});

function getAllClients()
{
	$.getJSON(server_url,
			{
				target: "Client",
				method: "GetClient",				
				email: "pmata@amro.com",
				password: "123"
			},
			function(data) {
				clients = data.clients;
				
				$("#option_cliente").append("<option value='0'>Todos</option>");
				for (var i=0; i < data.clients.length; i++) {
					var inner_html = "<option value='"+data.clients[i].id+"'>"+data.clients[i].name+"</option>";
					$("#option_cliente").append(inner_html);
				}	
			});
}

function getAllMaterials()
{
	$.getJSON(server_url,
			{
				target: "Material",
				method: "GetMaterial",				
				email: "pmata@amro.com",
				password: "123"
			},
			function(data) {
				materials = data.materials;
				
				$("#option_material").append("<option value='0'>Todos</option>");
				for (var i=0; i < data.materials.length; i++) {
					var inner_html = "<option value='"+data.materials[i].id+"'>"+data.materials[i].name+"</option>";
					$("#option_material").append(inner_html);
				}
			});
}

function clientNameSearch(id)
{
	for (var i = 0; i < clients.length; i++) 
		if (clients[i].id == id)
			return clients[i].name;
	
	return "Desconocido";
}

function materialNameSearch(id)
{
	for (var i = 0; i < materials.length; i++) 
		if (materials[i].id == id)
			return materials[i].name;
	
	return "Desconocido";
}

function performSearch() {
	var material_selection = $("#option_material option:selected").val();
	if (material_selection == 0)
		material_selection = "";
	else
		alert(material_selection);
	
	var client_selection = $("#option_cliente option:selected").val();
	if (client_selection == 0)
		client_selection = "";
	else 
		alert(client_selection);
	
	var probeta_selection = $("#protocolo").val();
	
	var order_selection;
	switch($("input[@name='oc_order']:checked").val()) {
	case 'by_oc':
		order_selection = "ordencompra";
		break;
	case 'by_client':
		order_selection = "client_id";
		break;
	case 'by_numprob':
		order_selection = "numprobeta";
		break;
	default:
		order_selection = "";
		break;
	}
	
	$("#ordercontrol").attr('disabled', 'disabled');
	
	$.getJSON(server_url,
			{
				target: "CSVParsing",
				method: "GetOC",
				email: "pmata@amro.com",
				password: "123",
				numprobeta: probeta_selection,
				client_id: client_selection,
				material_id: material_selection,
				order: order_selection
			},
			function(data) {
				ordencompras = data.lines;
				reorderOC();
				$("#ordercontrol").removeAttr('disabled');
			});
}

function reorderOC()
{
	if (ordencompras == null)
		return;
	
	switch($("input[@name='oc_order']:checked").val()) {
	case 'by_oc':
		orderByOC(ordencompras);
		break;
	case 'by_client':
		orderByClient(ordencompras);
		break;
	case 'by_numprob':
		orderByProbeta(ordencompras);
		break;
	default:
		break;
	}
}

function orderByProbeta(lines)
{
	inner_html = '<li><span class="folder">Probetas</span><ul>';
	for (var i=0; i < lines.length; i++) {
		var same_probeta = true;
		var same_oc = true;
		var new_probeta = false;
		var new_oc = false;
				 	
		if (i == 0 || lines[i-1].numprobeta != lines[i].numprobeta) { 
		  inner_html += '<li class="closed"><span class="folder">' + lines[i].numprobeta + '</span><ul>';
		  new_probeta = true;
		}

		if ((i == 0 || lines[i-1].ordencompra != lines[i].ordencompra) || new_probeta) {
		  inner_html += '<li class="closed"><span class="folder">' + lines[i].ordencompra + '</span><ul>';
		  new_oc = true;
		}
		  
		if ((i == 0 || lines[i-1].material_id != lines[i].material_id) || new_oc)
		  inner_html += '<li class="closed"><span class="folder">'+ materialNameSearch(lines[i].material_id) + '</span>';
		  
		  inner_html += '<ul>';
		  inner_html += '<li><span class="file">Descripción ' + lines[i].description + '</span></li>';
		  inner_html += '<li><span class="file">Cliente ' + clientNameSearch(lines[i].client_id) + '</span></li>';
		  inner_html += '</ul>';		  
		  
		  if (i == (lines.length -1) || lines[i+1].numprobeta != lines[i].numprobeta)
			  same_probeta = false;
		  
		  if (i == (lines.length -1) || lines[i+1].ordencompra != lines[i].ordencompra || !same_probeta)
			  same_oc = false;			  
		
		  
		  if ((i == (lines.length -1) || lines[i+1].material_id != lines[i].material_id) || !same_oc)
			  inner_html += '</li>'; // Material  					  
		  
		  if (!same_oc) {
			  inner_html += '</ul>'; // Orden compra
		  	  inner_html += '</li>'; // Orden compra
		  }		  
		  
		  if (!same_probeta) {
			  inner_html += '</ul>'; // Probeta
		  	  inner_html += '</li>'; // Probetas
		  }
	  }		
	  inner_html += '</ul></li>'; // Ordenes de Compra
	  $("#example").html(inner_html);
	  $("#example").treeview();
}

function orderByClient(lines)
{
	inner_html = '<li><span class="folder">Clientes</span><ul>';
	for (var i=0; i < lines.length; i++) {
		var same_client = true;
		var same_probeta = true;
		var new_probeta = false;
		var new_client = false;
		
		  if (i == 0 || lines[i-1].client_id != lines[i].client_id) {
			  inner_html += '<li class="closed"><span class="folder">' + clientNameSearch(lines[i].client_id) + '</span><ul>';
			  new_client = true;
		  }
		  
		  if (i == 0 || lines[i-1].numprobeta != lines[i].numprobeta || new_client) {
			  inner_html += '<li class="closed"><span class="folder">' + lines[i].numprobeta + '</span><ul>';
			  new_probeta = true;
		  }
		  
		  if (i == 0 || lines[i-1].material_id != lines[i].material_id || new_probeta)
			  inner_html += '<li class="closed"><span class="folder">Material '+ materialNameSearch(lines[i].material_id) + '</span>';
		  
		  inner_html += '<ul>';
		  inner_html += '<li class="closed"><span class="folder">Orden Compra ' + lines[i].ordencompra + '</span>';
		  
		  inner_html += '<ul>';
		  inner_html += '<li><span class="file">Descripción ' + lines[i].description + '</span></li>';
		  inner_html += '<li><span class="file">Cliente ' + clientNameSearch(lines[i].client_id) + '</span></li>';
		  inner_html += '</ul>';
		  
		  inner_html += '</li>'; // orden compra
		  inner_html += '</ul>'; //orden compra
		
		  if (i == (lines.length -1) || lines[i+1].client_id != lines[i].client_id)
			  same_client = false;
		  
		  if (i == (lines.length -1) || lines[i+1].numprobeta != lines[i].numprobeta || !same_client)
			  same_probeta = false;		
		  
		  if (i == (lines.length -1) || lines[i+1].material_id != lines[i].material_id || !same_probeta)
			  inner_html += '</li>'; // Material  					  
		  
		  if (!same_probeta) { 
			  inner_html += '</ul>'; // Probeta
		  	  inner_html += '</li>'; // Probeta
		  }
		  
		  if (!same_client) {
			  inner_html += '</ul>'; // Cliente
		  	  inner_html += '</li>'; // Cliente
		  }
	  }		
	  inner_html += '</ul></li>'; // Clientes
	  $("#example").html(inner_html);
	  $("#example").treeview();
}

function orderByOC(lines)
{
	inner_html = '<li><span class="folder">Ordenes de Compra</span><ul>';
	for (var i=0; i < lines.length; i++) {
		var same_oc = true;
		var same_probeta = true;
		var new_probeta = false;
		var new_oc = false;
		
		  if (i == 0 || lines[i-1].ordencompra != lines[i].ordencompra) {
			  inner_html += '<li class="closed"><span class="folder">' + lines[i].ordencompra + '</span><ul>';
			  new_oc = true;
		  }
	  
		  if (i == 0 || lines[i-1].numprobeta != lines[i].numprobeta || new_oc) {
			  inner_html += '<li class="closed"><span class="folder">'+ lines[i].numprobeta + '</span><ul>';
			  new_probeta = true;
		  }
		  
		  if (i == 0 || lines[i-1].material_id != lines[i].material_id || new_probeta)
			  inner_html += '<li class="closed"><span class="folder">' + materialNameSearch(lines[i].material_id) + '</span><ul>';
		  
		  inner_html += '<ul>';
		  inner_html += '<li><span class="file">Descripción ' + lines[i].description + '</span></li>';
		  inner_html += '<li><span class="file">Cliente ' + clientNameSearch(lines[i].client_id) + '</span></li>';
		  inner_html += '</ul>';
		  
		  if (i == (lines.length -1) || lines[i+1].ordencompra != lines[i].ordencompra)
			  same_oc = false;
		  
		  if (i == (lines.length -1) || lines[i+1].numprobeta != lines[i].numprobeta || !same_oc)
			  same_probeta = false;		
		  
		  if (i == (lines.length -1) || lines[i+1].material_id != lines[i].material_id || !same_probeta) {
			  inner_html += '</ul>'; // Material
			  inner_html += '</li>'; // Material			  
		  }
		  
		  if (!same_probeta) {
			  inner_html += '</ul>'; // probeta
			  inner_html += '</li>'; // probeta  					  
		  }		  
		  
		  if (!same_oc) {
			  inner_html += '</ul>'; // Orden compra
		  	  inner_html += '</li>'; // Orden compra
		  }
	  }		
	  inner_html += '</ul></li>'; // Ordenes de Compra
	  $("#example").html(inner_html);
	  $("#example").treeview();	
}

function parseCSV(file)
{
	var shortname = file.match(/[^\/\\]+$/);
		
	$.getJSON("http://localhost:8080/?callback=?",
	{
		target: "CSVParsing",
		method: "ParseCSV",
		email: "pmata@amro.com",
		password: "123",
		filepath: "/home/pmata/amro/"+ shortname
	},
	function(data) {
		if (data.errors == 'undefined')
			return;
		
		inner_html = '<li><span class="folder">Errores</span><ul>';
		for (var v in data.errors) {
			inner_html += '<li class="closed"><span class="folder">Linea: ' + v + '</span><ul>';
			inner_html += '<li><span class="file">' + data.errors[v] + '</span></li></ul>';
		}
		inner_html += '</ul></li>'; // Errores
		
		$("#parsingreport").html(inner_html);
		$("#parsingreport").treeview();	
	});
}	

function deleteOC()
{
	$.getJSON("http://localhost:8080/?callback=?",
	{
		target: "CSVParsing",
		method: "DeleteOC",
		email: "pmata@amro.com",
		password: "123",
		id: "4"
	},
	function(data) {
		
	});
}


	