// Global Variables Definitions
var server_url = globals.server_url;
var user = $.cookie("user");
var pass = $.cookie("pass");


// On Ready
$(document).ready(function() {
	
	$("#guardar_cliente").click(function(){
		insertClient();
		event.preventDefault();
	});
	
	$("#recargar_lista_clientes").click(function(){
		getClientList();
		event.preventDefault();
	});
	
	$("#nuevo_cliente").click(function(){
		newClient();
		event.preventDefault();
	});
	
	$("#recargar_cliente").click(function(){
		reloadClient();
		event.preventDefault();
	});
	
	$("#actualizar_cliente").click(function(){
		updateClient();
		event.preventDefault();
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

	$( ".invisible" ).animate({"opacity": 1}, "slow");
	$("#cliente_seleccionado_name").html("Nuevo");
	$("#cliente_seleccionado_id").html("Cliente");	
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
		email: user,
		password: pass
	},
	function(data) {	
		if(!data.success)
			alert("No se pudo correr el metodo NewClient correctamente");
		else
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
		name: $("#name").val(),
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
		email: user,
		password: pass
	},
	function(data) {
		if(!data.success)
			alert("No se pudo correr el metodo UpdateClient correctamente");
		else
			getClientList();
	});
}

function getClientList()
{
	getClients();
}

function getClient(id, name)
{

	$( ".invisible" ).animate({"opacity": 1}, "slow");
	
	$.getJSON(server_url,
	{
		target: "Client",
		method: "GetClient",
		name: name,
		id: id,
		email: user,
		password: pass
	},
	function(data) {
		if(!data.success)
			alert("No se pudo correr el metodo GetClient correctamente");
		else
		{
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
				
				//$("#cliente_seleccionado_name").html("<td class='rounded_4'>Nombre: <b>"+data.clients[0].name+"</b></td>");
				//$("#cliente_seleccionado_id").html("<td class='rounded_4'>Id: <b>"+data.clients[0].id+"</b></td>");
				
			}	
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
		email: user,
		password: pass
	},
	function(data) {	
		if(!data.success)
			alert("No se pudo correr el metodo GetClient correctamente");
		else
		{
			if (data.clients.length == 0)
				newClient();
			
			var inner_html = "<table><tr bgcolor='#4797ED'><th class='rounded_start'>Cliente</th><th class='rounded_middle'>Direccion</th><th class='rounded_end'>Eliminar</th></tr>";
			for(i = 0; i < data.clients.length; i++)
			{	
				inner_html += "<tr><td class='rounded_4'> > <a href='#' id='client_"+data.clients[i].id+"' onclick='loadClient(\""+data.clients[i].name+"\", \""+data.clients[i].id+"\");'>"+data.clients[i].name+"</a></td>";
				inner_html += "<td>"+data.clients[i].address+"</td>";
				//inner_html += "<td align='center'><img src='img/delete.png' width='20' heigth='20' alt='Eliminar' title='Eliminar' onclick='deleteClientConfirmation(\""+data.clients[i].name+"\", \""+data.clients[i].id+"\");' /></td></tr>";
				inner_html += "<td align='center'><button style='background: #e82c2c;' onclick='deleteClientConfirmation(\""+data.clients[i].name+"\", \""+data.clients[i].id+"\");'>Borrar</button></td>";
			}
			$("#client_list").html(inner_html);		
			$("#clientes_totales").html("Cantidad de Clientes: "+data.clients.length);
			$("#cliente_seleccionado").html("Ninguno...");
		}
	});
}

function deleteClient(id, name)
{
	$.getJSON(server_url,
	{
		target: "Client",
		method: "DeleteClient",
		email: user,
		password: pass,
		id: id
	},
	function(data) {	
		if(!data.success)
			alert("No se pudo correr el metodo DeleteClient correctamente");
		else
			getClientList();
	});
}

function reloadClient()
{	
	getClient( $("#cliente_seleccionado_id").html(), $("#cliente_seleccionado_name").html() );
}