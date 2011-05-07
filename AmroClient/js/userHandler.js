// Global Variables Definitions

$(document).ready(function() {

	getUserList();

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
		updateUsuario();
	});
	
	
});

// Funciones de Manejo de Usuarios
function newUsuario()
{
	$("#name").val("");
	$("#surname").val("");
	$("#signature").val("");
}
	
function loadUser(name, id)
{
	getUser(id, name);
}

function insertUsuario()
{
	$.getJSON("http://localhost:8080/?callback=?",
	{	
		target: "User",
		method: "NewUser",
		name: $("#name").val(),
		surname: $("#surname").val(),
		email: "pmata@amro.com",
		password: "123",
		signature: $("#signature").val(),
	},
	function(data) {
		alert("insertUser");
		getUserList();
	});
}

function updateUser()
{
	$.getJSON("http://localhost:8080/?callback=?",
	{
		target: "User",
		method: "UpdateUser",
		name: $("#name").val(),
		surname: $("surname").val(),
		email: "pmata@amro.com",
		password: "123",
		signature: $("#signature").val(),
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
	$.getJSON("http://localhost:8080/?callback=?",
	{
		target: "User",
		method: "GetUser",
		name: name,
		id: id,
		email: "pmata@amro.com",
		password: "123"
	},
	function(data) {
		if(data.users.length > 1)
			alert("Error en la cantidad de usuarios, no se puede especificar el usuario seleccionado");
		else	
		{
			$("#name").val(data.users[0].name);
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
	$.getJSON("http://localhost:8080/?callback=?",
	{
		target: "User",
		method: "GetUser",
		email: "pmata@amro.com",
		password: "123"
	},
	function(data) {
		var inner_html = "<table><tr><th>Usuario</th><th>Eliminar</th></tr><tr>"
		for(i = 0; i < data.users.length; i++)
		{	
			inner_html += "<td><a href='#' id='usuario_"+data.users[i].id+"' onclick='loadUser(\""+data.users[i].name+"\", \""+data.users[i].id+"\");'>"+data.users[i].name+"</a></td>";
			//inner_html += "<td>"+data.users[i].address+"</td>";
			inner_html += "<td align='center'><img src='img/delete.png' width='20' heigth='20' alt='Eliminar' title='Eliminar' onclick='deleteUserConfirmation(\""+data.users[i].name+"\", \""+data.users[i].id+"\");' /></td></tr>";
		}
		$("#usuario_list").html(inner_html);
		$("#usuarios_totales").html("Cantidad de Usuarios: "+data.users.length);
		$("#usuario_seleccionado").html("<h4>Ninguno...</h4>");
	});
}

function deleteUser(id, name)
{
	$.getJSON("http://localhost:8080/?callback=?",
	{
		target: "User",
		method: "DeleteUser",
		email: "pmata@amro.com",
		password: "123",
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
