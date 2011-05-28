var user = $.cookie("user");
var pass = $.cookie("pass");

$(document).ready(function() {

	$("#cargar_certs").click(function(){
		getAllCerts();
	});	
	
});

function loadCertPage()
{
	if(user == null || pass == null)
		doGetSessionVars();
	loadClients();
	loadMaterials();
	loadUsers();
	getAllCerts();
}

function searchCert()
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
		case "l":
			searchByMaterial();
			break;
		case "u":
			searchByUser();
			break;
		case "f":
			searchByDate();
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
function filterClient(filter)
{	
	if (globals.currentCerts == null || globals.currentCerts.length == 0)
		return;
	
	var certs = new Array();
	
	if (filter == 0) {
		certs = globals.currentCerts;	
	} else {	
		for (var i=0; i < globals.currentCerts.length; i++) 
			if (globals.currentCerts[i].client_id == filter)
				certs.push(globals.currentCerts[i]);
	}
	
	showCerts(certs);
}


function showClients(clients)
{		
	var inner_html = "<select name='select_cliente' id='select_cliente'><option value='0'>Todos los Clientes</option>";
	for(i = 0; i < clients.length; i++)
	{
		inner_html += "<option value='"+clients[i].id+"'>"+clients[i].name+"</option>";
	}
	inner_html += "</select>";	
	$("#clientes").replaceWith(inner_html);
	$("#select_cliente").change(function(e){
		$in=$(this);
		var value = $in.val();
		filterClient(value);
	});
}

function loadClients()
{
	if(globals.currentClients != null && globals.currentClients.length > 0)
		showClients(globals.currentClients);
	
	$.getJSON(server_url,
	{
		target: "Client",
		method: "GetClient",
		email: user,
		password: pass,
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

function filterUser(filter)
{	
	if (globals.currentCerts == null || globals.currentCerts.length == 0)
		return;
	
	var certs = new Array();
	
	if (filter == 0) {
		certs = globals.currentCerts;	
	} else {	
		for (var i=0; i < globals.currentCerts.length; i++) 
			if (globals.currentCerts[i].performer_id == filter)
				certs.push(globals.currentCerts[i]);
	}
	
	showCerts(certs);
}

function showUsers(users)
{		
	var inner_html = "<select name='select_usuario' id='select_usuario'><option value='0'>Todos los Usuarios</option>";
	for(i = 0; i < users.length; i++)
	{
		inner_html += "<option value='"+users[i].id+"'>"+users[i].name + " " + users[i].surname +"</option>";
	}
	inner_html += "</select>";	
	$("#usuarios").replaceWith(inner_html);
	$("#select_usuario").change(function(e){
		$in=$(this);
		var value = $in.val();
		filterUser(value);
	});
}

function loadUsers()
{
	if(globals.currentUsers != null && globals.currentUsers.length > 0)
		showUsers(globals.currentUsers);
	
	$.getJSON(server_url,
	{
		target: "User",
		method: "GetUser",
		email: user,
		password: pass,
	},
	function(data) {
		if(data.success == true && data.users.length > 0)
		{
			globals.currentUsers = data.users;
			showUsers(data.users);
		}
		else
		{
			alert("No se pudieron cargar los usuarios. Error con el servidor");
		}
	});
}

function filterMaterial(filter)
{	
	if (globals.currentCerts == null || globals.currentCerts.length == 0)
		return;
	
	var certs = new Array();
	
	if (filter == 0) {
		certs = globals.currentCerts;	
	} else {	
		for (var i=0; i < globals.currentCerts.length; i++) 
			if (globals.currentCerts[i].material_id == filter)
				certs.push(globals.currentCerts[i]);
	}
	
	showCerts(certs);
}

function showMaterials(materials)
{		
	var inner_html = "<select name='select_material' id='select_material'><option value='0'>Todos los Materiales</option>";
	for(i = 0; i < materials.length; i++)
	{
		inner_html += "<option value='"+materials[i].id+"'>"+materials[i].name+"</option>";
	}
	inner_html += "</select>";	
	$("#materiales").replaceWith(inner_html);
	$("#select_material").change(function(e){
		$in=$(this);
		var value = $in.val();
		filterMaterial(value);
	});
}

function loadMaterials()
{
	if(globals.currentMaterials != null && globals.currentMaterials.length > 0)
		showMaterials(globals.currentMaterials);
	
	$.getJSON(server_url,
	{
		target: "Material",
		method: "GetMaterial",
		email: user,
		password: pass,
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

function showCerts(certs)
{
	var inner_html = "<tr class='oc'><th class='oc'>ID</th><th class='oc'>ProtN</th><th class='oc'>Numero de Probeta</th><th class='oc'>Cliente</th><th class='oc'>Material</th><th class='oc'>Creador</th><th class='oc'>Orden Compra</th><th class='oc'>Fecha</th><th class='oc'>Ver Certificado</th></tr>";
	for(var i=0; i < certs.length; i++)
	{
		var line = "even";
		if( i%2 == 0 ) 
		{
			line = "odd";
		}
			
		inner_html += "<tr class='"+line+"'>";
		inner_html += "<td class='oc'>"+certs[i].id+"</td>";
		inner_html += "<td>"+certs[i].protn+"</td>";
		inner_html += "<td>"+certs[i].numprobeta+"</td>";
		inner_html += "<td>"+clientNameSearch(certs[i].client_id)+"</td>";
		inner_html += "<td>"+materialNameSearch(certs[i].material_id)+"</td>";
		inner_html += "<td>"+userNameSearch(certs[i].performer_id)+"</td>";
		inner_html += "<td>"+certs[i].ordencompra+"</td>";
		inner_html += "<td>"+certs[i].date+"</td>";
		inner_html += "<td align='center'><a href='file://" + certs[i].certificatepath + "'><img src='img/create.gif' alt='Ver Certificado "+certs[i].protn+"' width='25px'/></a></td>";
		inner_html += "</tr>";
	}	
	$("#certificados").html(inner_html);
}

function searchByOC()
{
	if($("#cert_orden_compra").val() == "")
	{
		inner_html = "No se definio el valor de busqueda por orden de compra.";
		$("#certificados").html(inner_html);
		return;
	}
	$.getJSON(globals.server_url,
	{
		target: "Certificate",
		method: "GetCertificate",
		email: user,
		password: pass,
		ordencompra: $("#cert_orden_compra").val(),
		order: "id"
	},
	function(data) {
		if(data.certificates.length < 1)
		{
			inner_html = "No se encontro ningun certificado con orden de compra "+$("#cert_orden_compra").val();
			$("#certificados").html(inner_html);
			return;
		}	
			
		showCerts(data.certificates);
	});
}

function searchByDate()
{
	var dateRegex = /^\d?\d$/;
	var yearDateRegex = /^\d{4}$/;
	
	if($("#cert_dia").val() == "" || $("#cert_mes").val() == "" || $("#cert_year").val() == "")
	{
		inner_html = "No se definio el valor de busqueda por fecha.";
		$("#certificados").html(inner_html);
		return;
	}
	
	if(!dateRegex.test($("#cert_dia").val()) || !dateRegex.test($("#cert_mes").val()) || !yearDateRegex.test($("#cert_year").val()))
	{
		inner_html = "El formato de fecha ingresado para la busqueda es incorrecto.";
		$("#certificados").html(inner_html);
		return;
	}
	
	$.getJSON(globals.server_url,
	{
		target: "Certificate",
		method: "GetCertificate",
		email: user,
		password: pass,
		day: $("#cert_dia").val(),
		month: $("#cert_mes").val(),
		year: $("#cert_year").val(),
		order: "id"
	},
	function(data) {
		if(data.certificates.length < 1)
		{
			inner_html = "No se encontro ningun certificado con fecha "+$("#cert_dia").val()+"/"+ $("#cert_mes").val()+"/"+$("#cert_year").val();
			$("#certificados").html(inner_html);
			return;
		}	
			
		showCerts(data.certificates);
	});
}

function searchByProtN()
{
	if($("#cert_protn").val() == "")
	{
		inner_html = "No se definio el valor de busqueda por ProtN.";
		$("#certificados").html(inner_html);
		return;
	}
	$.getJSON(globals.server_url,
	{
		target: "Certificate",
		method: "GetCertificate",
		email: user,
		password: pass,
		protn: $("#cert_protn").val(),
		order: "id"
	},
	function(data) {
		if(data.certificates.length < 1)
		{
			inner_html = "No se encontro ningún certificado con valor protn "+$("#cert_protn").val();
			$("#certificados").html(inner_html);
			return;
		}	
			
		showCerts(data.certificates);
	});
}



function searchByProbeta()
{
	if($("#cert_numprob").val() == "")
	{
		inner_html = "No se definio el valor de busqueda por número de probeta.";
		$("#certificados").html(inner_html);
		return;
	}
	$.getJSON(globals.server_url,
	{
		target: "Certificate",
		method: "GetCertificate",
		email: user,
		password: pass,
		numprobeta: $("#cert_numprob").val(),
		order: "id"
	},
	function(data) {
		if(data.certificates.length < 1)
		{
			inner_html = "No se encontro ningun certificado con numero de probeta "+$("#cert_numprob").val();
			$("#certificados").html(inner_html);
			return;
		}	
			
		showCerts(data.certificates);
	});
}
	
function getAllCerts()
{
	$.getJSON(globals.server_url,
	{
		target: "Certificate",
		method: "GetCertificate",
		email: user,
		password: pass,
		order: "id"
	},
	function(data) {
		/*var inner_html = "<tr class='oc'><th class='oc'>ID</th><th class='oc'>ProtN</th><th class='oc'>Numero de Probeta</th><th class='oc'>Cliente</th><th class='oc'>Material</th><th class='oc'>Creador</th><th class='oc'>Orden Compra</th><th class='oc'>Fecha</th><th class='oc'>Ver Certificado</th></tr>";
		for(var i=0; i < data.certificates.length; i++)
		{
			var line = "even";
			if( i%2 == 0 ) 
			{
				line = "odd";
			}
				
			inner_html += "<tr class='"+line+"'>";
 			inner_html += "<td class='oc'>"+data.certificates[i].id+"</td>";
			inner_html += "<td>"+data.certificates[i].protn+"</td>";
			inner_html += "<td>"+data.certificates[i].numprobeta+"</td>";
			inner_html += "<td>"+clientNameSearch(data.certificates[i].client_id)+"</td>";
			inner_html += "<td>"+materialNameSearch(data.certificates[i].material_id)+"</td>";
			inner_html += "<td>"+userNameSearch(data.certificates[i].performer_id)+"</td>";
			inner_html += "<td>"+data.certificates[i].ordencompra+"</td>";
			inner_html += "<td>"+data.certificates[i].date+"</td>";
			inner_html += "<td align='center'><a href='file://" + data.certificates[i].certificatepath + "'><img src='img/create.gif' alt='Ver Certificado "+data.certificates[i].protn+"' width='25px'/></a></td>";
			inner_html += "</tr>";
		}	
		$("#certificados").html(inner_html);*/
		if (data.success == true && data.certificates.length > 0) {
			showCerts(data.certificates);	
			globals.currentCerts = data.certificates;
		}
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

function userNameSearch(id)
{
	if (globals.currentUsers == null)
		return "Desconocido";
	
	for (var i = 0; i < globals.currentUsers.length; i++) 
		if (globals.currentUsers[i].id == id)
			return globals.currentUsers[i].name + " " + globals.currentUsers[i].surname;
	
	return "Desconocido";
}

	



