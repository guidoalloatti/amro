// Global Variables Definitions
//var server_url = "http://192.168.1.101:8080/?callback=?";
var server_url = globals.server_url; //"http://localhost:8080/?callback=?";
var user = $.cookie("user");
var pass = $.cookie("pass");


// On Ready
$(document).ready(function() {

	$("#guardar_cliente").click(function(){
		insertClient();
	});
	
	$("#recargar_lista_clientes").click(function(){
		getClientList();
	});
	
	$("#nuevo_cliente").click(function(){
		newClient();
	});
	
	$("#recargar_cliente").click(function(){
		reloadClient();
	});
	
	$("#actualizar_cliente").click(function(){
		updateClient();
	});

});

 function clientStart()
 {
	if(user == null || pass == null)
		doGetSessionVars();
	getClientList();
}

// Funciones de Manejo de Clientes
function newClient()
{
	$("#name").val("");
	$("#address").val("");
	$("#city").val("");
	$("#zip").val("");
	$("#country").val("");
	$("#phone").val("");
	$("#website").val("");
	$("#telefax").val("");
	$("#seqdigits").val("");
	$("#namecode").val("");
}
	
function loadClient(name, id)
{
	getClient(id, name);
}

function insertClient()
{
	$.getJSON(server_url,
	{	
		target: "Client",
		method: "NewClient",
		name: $("#name").val(),
		address: $("#address").val(),
		city: $("#city").val(),
		zip: $("#zip").val(),
		country: $("#country").val(),
		phone: $("#phone").val(),
		website: $("#website").val(),
		telefax: $("#telefax").val(),
		seqdigits: $("#seqdigits").val(), 					// Esto especifica cu�ntos d�gitos va a usar para los n�meros de probeta. Ej. AR425 --> 3
		code: $("#namecode").val(), 						// Codigo del n�mero de probeta, si alg�n otro cliente tiene el c�digo, tira error.
		email: user,										// "pmata@amro.com",
		password: pass, 									// "123",
	},
	function(data) {
		getClientList();
	});
}

function updateClient()
{
	if($("#cliente_seleccionado_id").html() == "")
	{
		alert("No esta definido el id del cliente.");
		return;
	}
	
	$.getJSON(server_url,
	{
		target: "Client",
		method: "UpdateClient",
		name: encodeURIComponent($("#name").val()),
		address: $("#address").val(),
		city: $("#city").val(),
		zip: $("#zip").val(),
		country: $("#country").val(),
		phone: $("#phone").val(),
		website: $("#website").val(),
		telefax: $("#telefax").val(),
		seqdigits: $("#seqdigits").val(),
		code: $("#namecode").val(),
		id: $("#cliente_seleccionado_id").html(),
		email: user, 								//"pmata@amro.com",
		password: pass, 							//"123",
	},
	function(data) {
		getClientList();
	});
}

function getClientList()
{
	//console.log("getClientList"+user+pass);
	getClients();
}

function getClient(id, name)
{
	$.getJSON(server_url,
	{
		target: "Client",
		method: "GetClient",
		name: name,
		id: id,
		email: user, 							//"pmata@amro.com",
		password: pass, 						//"123"
	},
	function(data) {
		if(data.clients.length > 1)
			alert("Error en la cantidad de clientes, no se puede especificar el cliente seleccionado");
		else	
		{
			$("#name").val(data.clients[0].name);
			$("#namecode").val(data.clients[0].code);
			$("#address").val(data.clients[0].address);
			$("#city").val(data.clients[0].city);
			$("#zip").val(data.clients[0].zip);
			$("#country").val(data.clients[0].country);
			$("#phone").val(data.clients[0].phone);
			$("#website").val(data.clients[0].website);
			$("#telefax").val(data.clients[0].telefax);
			$("#seqdigits").val(data.clients[0].seqdigits);
			$("#cliente_seleccionado_name").html(data.clients[0].name);
			$("#cliente_seleccionado_id").html(data.clients[0].id);
		}	
	});
}

function deleteClientConfirmation(name, id)
{
	if(confirm("Esta a punto de eliminar el cliente "+name))
	{
		//console.log("Se eliminara el cliente "+name);
		deleteClient(id, name);
	}
}

function getClients()
{

	$.getJSON(server_url,
	{
		target: "Client",
		method: "GetClient",
		email: user, 				//"pmata@amro.com",
		password: pass, 			//"123"
	},
	function(data) {
		var inner_html = "<table><tr><th>Cliente</th><th>Direccion</th><!--<th>Editar</th>--><th>Eliminar</th></tr><tr>"
		
		for(i = 0; i < data.clients.length; i++)
		{	
			inner_html += "<td><a href='#' id='client_"+data.clients[i].id+"' onclick='loadClient(\""+data.clients[i].name+"\", \""+data.clients[i].id+"\");'>"+data.clients[i].name+"</a></td>";
			inner_html += "<td>"+data.clients[i].address+"</td>";
			//inner_html += "<td align='center'><img src='img/edit.png' width='20' heigth='20' alt='Editar' title='Editar' /></td>";
			inner_html += "<td align='center'><img src='img/delete.png' width='20' heigth='20' alt='Eliminar' title='Eliminar' onclick='deleteClientConfirmation(\""+data.clients[i].name+"\", \""+data.clients[i].id+"\");' /></td></tr>";
		}
		$("#client_list").html(inner_html);		
		$("#clientes_totales").html("Cantidad de Clientes: "+data.clients.length);
		$("#cliente_seleccionado").html("<h4>Ninguno...</h4>");

	});
}

function deleteClient(id, name)
{
	$.getJSON(server_url,
	{
		target: "Client",
		method: "DeleteClient",
		email: user,				// "pmata@amro.com",
		password: pass, 			// "123",
		id: id,
	},
	function(data) {
		getClientList();
		//console.log("Se elimino cliente "+name+" con id "+id);
	});
}

function reloadClient()
{
	getClient( $("#cliente_seleccionado_id").html(), $("#cliente_seleccionado_name").html() );
}

