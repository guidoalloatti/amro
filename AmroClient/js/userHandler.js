// Global Variables Definitions
var server_url = globals.server_url;
var user = $.cookie("user");
var pass = $.cookie("pass");

$(document).ready(function() {

	$("#guardar_usuario").click(function(){
		insertUsuario();
		event.preventDefault();
	});
	
	$("#signature_line").hide();
	
	$("#recargar_lista_usuarios").click(function(){
		getUserList();
		event.preventDefault();
	});
	
	$("#nuevo_usuario").click(function(){
		newUsuario();
		event.preventDefault();
	});
	
	$("#recargar_usuario").click(function(){
		reloadUser();
		event.preventDefault();
	});
	
	$("#actualizar_usuario").click(function(){
		updateUser();
		event.preventDefault();
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
	$( ".invisible" ).animate({"opacity": 1}, "slow");
	$("#usuario_seleccionado_name").html("Nuevo");
	$("#usuario_seleccionado_id").html("Usuario");	
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
	},
	function(data) {	
		if(data.success)
		{
			getUserList();
		}
		else
			alert("Hubo un problema al ejecutar el metodo NewUser");
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
		from_email: user,
		from_password: pass,
		name: $("#name").val(),
		surname: $("#surname").val(),
		email: $("#email").val(),
		password: $("#password").val(),
		signature: $("#signature").val(),
		user_id: $("#usuario_seleccionado_id").html()
	},
	function(data) {
		if(data.success)
		{
			if($("#email").val() == user && pass != $("#password").val())
			{
				//console.log("Se cambio en pass del usuario actual, se cambia el password de sesion");
				$.cookie("pass", $("#password").val());
				getUserList();
			}
		}
		else
		{
			alert("Hubo un problema al ejecutar el metodo UpdateUser");
			//console.log(data);
		}
	});
}

function getUserList()
{
	getUsers();
}

function getUser(id, name)
{
	$( ".invisible" ).animate({"opacity": 1}, "slow");

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
		if(data.success)
		{
			if(data.users.length > 1)
				alert("Error en la cantidad de usuarios, no se puede especificar el usuario seleccionado");
			else	
			{
				$("#name").val(data.users[0].name);
				$("#surname").val(data.users[0].surname);
				$("#email").val(data.users[0].email);
				if (data.users[0].signature != "") {
					$("#signature").attr("src", data.users[0].signature);
					$("#signature_line").show("slow");
				} else
					$("#signature_line").hide();
				
				$("#usuario_seleccionado_name").html(data.users[0].name);
				$("#usuario_seleccionado_id").html(data.users[0].id);
				$("#gestionarPermisosUsuario").html("<a href='main.php?invoice_url=pe&userid="+data.users[0].id+"'>Gestionar Permisos del Usuario</a>");
			}
		}
		else
			alert("Hubo un problema al ejecutar el metodo GetUser");
	});
}

function deleteUserConfirmation(name, id)
{
	if(confirm("Esta a punto de eliminar el usuario "+name))
	{
		deleteUser(id, name);
	}
}

function updateSignature(file, id)
{		
	$.getJSON(server_url,
	{	
		target: "User",
		method: "UpdateUser",
		from_email: user,
		from_password: pass,
		user_id: id,
		signature: globals.pathToCerts + id + "/" + file,
	},
	function(data) {
		if (data.success)
		{
			alert("Firma digital actualizada con éxito!");
			getUserList();	
		}
		else
		{
			alert("Hubo un problema al ejecutar el metodo UpdateUser");
			//console.log(data);
		}
	});
}

function uploadSignature(id)
{
	var html = "<form action='upload_signature.php' name='sig_popup' method='post' enctype='multipart/form-data' target='_blank' id='signatureUpload_"+id+"'><input type='file' name='file' id='signature_"+id+"'/> ";
	$("#subir_firma_"+id).html(html);
	
	$("#signature_"+id).change(function(e){
		  $in=$(this);
		  var file = $in.val();
		  $("#signatureUpload_"+id).attr("action", $("#signatureUpload_"+id).attr("action") + "?user=" + id);
		  $("#signatureUpload_"+id).submit();
	});	
	
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
		if (data.success == false) {
			alert("Error trayendo usuarios del servidor");
			return;
		}
		
		if (data.users.length == 0) 			
			newUsuario();
		
		
		var inner_html = "<table>";
		inner_html += "<tr bgcolor='#4797ED'>";
		inner_html += "<th class='rounded_start'>Usuario</th>";
		inner_html += "<th class='rounded_middle'>Subir Firma</th>";
		inner_html += "<th class='rounded_end'>Eliminar</th>";
		inner_html += "</tr>";
		
		for(i = 0; i < data.users.length; i++)
		{	
			inner_html += "<tr><td class='rounded_4'><a href='#' id='usuario_"+data.users[i].id+"' onclick='loadUser(\""+data.users[i].name+"\", \""+data.users[i].id+"\");'>"+data.users[i].name+"</a></td>";
			inner_html += "<td id='subir_firma_"+data.users[i].id+"' align='center'><button onclick='uploadSignature("+data.users[i].id+")'>Subir</button></td>";
			//inner_html += "<td align='center'><img src='img/delete.png' width='20' heigth='20' alt='Eliminar' title='Eliminar' onclick='deleteUserConfirmation(\""+data.users[i].name+"\", \""+data.users[i].id+"\");' /></td></tr>";
			inner_html += "<td align='center'><button style='background: #e82c2c;' onclick='deleteUserConfirmation(\""+data.users[i].name+"\", \""+data.users[i].id+"\");'>Borrar</button></td>";
		}		
		
		$("#usuario_list").html(inner_html);
		$("#usuarios_totales").html("Cantidad de Usuarios: "+data.users.length);
		$("#usuario_seleccionado").html("<h4>Ninguno...</h4>");
		
		globals.currentUsers = data.users;
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
		if (data.success == true) {
			console.log("Se elimino usuario "+name+" con id "+id);
			
			if (globals.currentUsers != null) {
				for (var i=0; i < globals.currentUsers; i++)
					if (globals.currentUsers[i].email == name &&
						globals.currentUsers[i].password == pass)
						if (globals.currentUsers[i].id == id)
							window.location = "main.php?invoice_url=logout";
			}
			
			getUserList();			
		} else if (data.permission != undefined) {
			alert("No se tiene permisos para realizar esta operación");
		} else
			alert("Error. Problemas con el servidor.");
		
		
	});
}

function reloadUser()
{
	getUser( $("#usuario_seleccionado_id").html(), $("#usuario_seleccionado_name").html() );
}

