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
	loadClients();
	loadMaterials();
	getAllOC();
}

function searchOC()
{
	var selected_search = $("input[@name='filtro']:checked").val();
	
	switch(selected_search)
	{
		case "o":
			searchByOC();
			break;
		case "p":
			searchByProbeta();
			break;
		case "c":
			searchByClient();
			break;
		case "m":
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

function showClients(clients)
{		
	var inner_html = "<select name='select_cliente' id='select_cliente'><option>Todos los Clientes</option>";
	for(i = 0; i < clients.length; i++)
	{
		inner_html += "<option>"+clients[i].name+"</option>";
	}
	inner_html += "</select>";	
	$("#clientes").replaceWith(inner_html);
}

function loadClients()
{
	if(globals.currentClients != null && globals.currentClients.length > 0)
		showClients(globals.currentClients);
	
	$.getJSON(server_url,
	{
		target: "Client",
		method: "GetClient",
		email: "pmata@amro.com",
		password: "123"
	},
	function(data) {
		if(data.success == true && data.clients.length > 0)
		{
			globals.currentClients = data.clients;
			showClients(data.clients);
		}
		else
		{
			alert("No se pudieron cargar los clientes. Error con el servidor");
		}
	});
}

function showMaterials(materials)
{		
	var inner_html = "<select name='select_material' id='select_material'><option>Todos los Materiales</option>";
	for(i = 0; i < materials.length; i++)
	{
		inner_html += "<option>"+materials[i].name+"</option>";
	}
	inner_html += "</select>";	
	$("#materiales").replaceWith(inner_html);
}

function loadMaterials()
{
	if(globals.currentMaterials != null && globals.currentMaterials.length > 0)
		showClients(globals.currentMaterials);
	
	$.getJSON(server_url,
	{
		target: "Material",
		method: "GetMaterial",
		email: "pmata@amro.com",
		password: "123"
	},
	function(data) {
		if(data.success == true && data.materials.length > 0)
		{
			globals.currentMaterials = data.materials;
			showMaterials(data.materials);
		}
		else
		{
			alert("No se pudieron cargar los materiales. Error con el servidor");
		}
	});
}

function searchByOC()
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
		email: "pmata@amro.com",
		password: "123",
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
			
		var inner_html = "<tr class='oc'><th class='oc'>Orden de Compra</th><th class='oc'>Numero de Probeta</th><th class='oc'>Id Cliente</th><th class='oc'>Id Material</th><th class='oc'>Descripcion</th><th class='oc'>Id</th><th class='oc'>Generar Certificado</th></tr>";
		for(var i=0; i < data.lines.length; i++)
		{
			var line = "even";
			if( i%2 == 0 ) 
				line = "odd";

			inner_html += "<tr class='"+line+"'>";
 			inner_html += "<td class='oc'>"+data.lines[i].ordencompra+"</td>";
			inner_html += "<td>"+data.lines[i].numprobeta+"</td>";
			inner_html += "<td>"+clientNameSearch(data.lines[i].client_id)+"</td>";
			inner_html += "<td>"+materialNameSearch(data.lines[i].material_id)+"</td>";
			inner_html += "<td>"+data.lines[i].description+"</td>";
			inner_html += "<td>"+data.lines[i].id+"</td>";
			inner_html += "<td align='center'><a href='main.php?invoice_url=ce&numprobeta="+data.lines[i].numprobeta+"&ordencompra="+data.lines[i].ordencompra+"&id="+data.lines[i].id+"&material="+data.lines[i].material_id+"&client="+data.lines[i].client_id+"&desc="+encodeURIComponent(data.lines[i].description)+"'><img src='img/create.gif' alt='Generar Certificadop para Probeta Numero"+data.lines[i].numprobeta+"' width='25px'/></a></td>";
			inner_html += "</tr>";
		}	
		$("#ordenes_compra").html(inner_html);
	});
}

function searchByProbeta()
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
		email: "pmata@amro.com",
		password: "123",
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
			
		var inner_html = "<tr class='oc'><th class='oc'>Orden de Compra</th><th class='oc'>Numero de Probeta</th><th class='oc'>Id Cliente</th><th class='oc'>Id Material</th><th class='oc'>Descripcion</th><th class='oc'>Id</th><th class='oc'>Generar Certificado</th></tr>";
		for(var i=0; i < data.lines.length; i++)
		{
			var line = "even";
			if( i%2 == 0 ) 
				line = "odd";

			inner_html += "<tr class='"+line+"'>";
 			inner_html += "<td class='oc'>"+data.lines[i].ordencompra+"</td>";
			inner_html += "<td>"+data.lines[i].numprobeta+"</td>";
			inner_html += "<td>"+clientNameSearch(data.lines[i].client_id)+"</td>";
			inner_html += "<td>"+materialNameSearch(data.lines[i].material_id)+"</td>";
			inner_html += "<td>"+data.lines[i].description+"</td>";
			inner_html += "<td>"+data.lines[i].id+"</td>";
			inner_html += "<td align='center'><a href='main.php?invoice_url=ce&numprobeta="+data.lines[i].numprobeta+"&ordencompra="+data.lines[i].ordencompra+"&id="+data.lines[i].id+"&material="+data.lines[i].material_id+"&client="+data.lines[i].client_id+"&desc="+encodeURIComponent(data.lines[i].description)+"'><img src='img/create.gif' alt='Generar Certificadop para Probeta Numero"+data.lines[i].numprobeta+"' width='25px'/></a></td>";
			inner_html += "</tr>";
		}	
		$("#ordenes_compra").html(inner_html);
	});
}
	
function getAllOC()
{
	$.getJSON(globals.server_url,
	{
		target: "CSVParsing",
		method: "GetOC",
		email: "pmata@amro.com",
		password: "123",
		order: "ordencompra"
	},
	function(data) {
		var inner_html = "<tr class='oc'><th class='oc'>Orden de Compra</th><th class='oc'>Numero de Probeta</th><th class='oc'>Id Cliente</th><th class='oc'>Id Material</th><th class='oc'>Descripcion</th><th class='oc'>Id</th><th class='oc'>Generar Certificado</th></tr>";
		for(var i=0; i < data.lines.length; i++)
		{
			var line = "even";
			if( i%2 == 0 ) 
			{
				line = "odd";
			}
				
			inner_html += "<tr class='"+line+"'>";
 			inner_html += "<td class='oc'>"+data.lines[i].ordencompra+"</td>";
			inner_html += "<td>"+data.lines[i].numprobeta+"</td>";
			inner_html += "<td>"+clientNameSearch(data.lines[i].client_id)+"</td>";
			inner_html += "<td>"+materialNameSearch(data.lines[i].material_id)+"</td>";
			inner_html += "<td>"+data.lines[i].description+"</td>";
			inner_html += "<td>"+data.lines[i].id+"</td>";
			inner_html += "<td align='center'><a href='main.php?invoice_url=ce&numprobeta="+data.lines[i].numprobeta+"&ordencompra="+data.lines[i].ordencompra+"&id="+data.lines[i].id+"&material="+data.lines[i].material_id+"&client="+data.lines[i].client_id+"&desc="+encodeURIComponent(data.lines[i].description)+"'><img src='img/create.gif' alt='Generar Certificadop para Probeta Numero"+data.lines[i].numprobeta+"' width='25px'/></a></td>";
			inner_html += "</tr>";
		}	
		$("#ordenes_compra").html(inner_html);
				
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
		email: "pmata@amro.com",
		password: "123",
		//filepath: "/home/pmata/amro/"+ shortname
		filepath: "/home/guido/Escritorio/"+ shortname
		
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



