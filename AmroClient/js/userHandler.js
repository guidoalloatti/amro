// Global Variables Definitions
var server_url = "http://192.168.1.101:8080/?callback=?"; // globals.server_url; // 
var user = $.cookie("user");
var pass = $.cookie("pass");


$(document).ready(function() {

	$("#guardar_usuario").click(function(){
		insertUsuario();
	});
	
	$("#recargar_lista_usuarios").click(function(){
		getUsuarioList();
	});
	
	$("#nuevo_usuario").click(function(){
		newUsuario();
	});
	
	$("#recargar_usuario").click(function(){
		reloadUsuario();
	});
	
	$("#actualizar_usuario").click(function(){
		updateUser();
	});
	
	
});

function userStart()
{
	if(user == null || pass == null)
		doGetSessionVars();
	getUserList();
}

// Funciones de Manejo de Usuarios
function newUsuario()
{
	$("#name").val("");
	$("#surname").val("");
	$("#signature").val("");
	$("#email").val("");
	$("#password").val("");
}
	
function loadUser(name, id)
{
	getUser(id, name);
}

function insertUsuario()
{
	$.getJSON(server_url,
	{	
		target: "User",
		method: "NewUser",
		password: $("#password").val(),
		email: $("#email").val(),
		signature: $("#signature").val(),
		name: $("#name").val(),
		surname: $("#surname").val(),
		signature: $("#signature").val(),
	},
	function(data) {
		getUserList();
	});
}

function updateUser()
{
	if($("#usuario_seleccionado_id").html() == "")
	{
		alert("No esta definido el id del usuario.");
		return;
	}
	
	$.getJSON(server_url,
	{
		target: "User",
		method: "UpdateUser",
		name: $("#name").val(),
		surname: $("#surname").val(),
		email: $("#email").val(),
		password: $("#password").val(),
		signature: $("#signature").val(),
		id: $("#usuario_seleccionado_id").html(),
	},
	function(data) {
	});
}

function getUserList()
{
	getUsers();
}

function getUser(id, name)
{
	$.getJSON(server_url,
	{
		target: "User",
		method: "GetUser",
		name: name,
		id: id,
		email: user, 			// "pmata@amro.com",
		password: pass, 		// "123"
	},
	function(data) {
		if(data.users.length > 1)
			alert("Error en la cantidad de usuarios, no se puede especificar el usuario seleccionado");
		else	
		{
			$("#name").val(data.users[0].name);
			$("#surname").val(data.users[0].surname);
			$("#email").val(data.users[0].email);
			$("#signature").val(data.users[0].signature);
			$("#usuario_seleccionado_name").html(data.users[0].name);
			$("#usuario_seleccionado_id").html(data.users[0].id);
		}	
	});
}

function deleteUserConfirmation(name, id)
{
	if(confirm("Esta a punto de eliminar el usuario "+name))
	{
		deleteUser(id, name);
	}
}

function getUsers()
{
	$.getJSON(server_url,
	{
		target: "User",
		method: "GetUser",
		email: user, 			// "pmata@amro.com",
		password: pass, 		// "123"
	},
	function(data) {
		var inner_html = "<table><tr><th>Usuario</th><th>Eliminar</th></tr><tr>"
		for(i = 0; i < data.users.length; i++)
		{	
			inner_html += "<td><a href='#' id='usuario_"+data.users[i].id+"' onclick='loadUser(\""+data.users[i].name+"\", \""+data.users[i].id+"\");'>"+data.users[i].name+"</a></td>";
			inner_html += "<td align='center'><img src='img/delete.png' width='20' heigth='20' alt='Eliminar' title='Eliminar' onclick='deleteUserConfirmation(\""+data.users[i].name+"\", \""+data.users[i].id+"\");' /></td></tr>";
		}
		$("#usuario_list").html(inner_html);
		$("#usuarios_totales").html("Cantidad de Usuarios: "+data.users.length);
		$("#usuario_seleccionado").html("<h4>Ninguno...</h4>");
	});
}

function deleteUser(id, name)
{
	$.getJSON(server_url,
	{
		target: "User",
		method: "DeleteUser",
		email: user, 			// "pmata@amro.com",
		password: pass,			// "123",
		id: id,
	},
	function(data) {
		console.log("Se elimino usuario "+name+" con id "+id);
		getUserList();
	});
}

function reloadUser()
{
	getUser( $("#usuario_seleccionado_id").html(), $("#usuario_seleccionado_name").html() );
}

