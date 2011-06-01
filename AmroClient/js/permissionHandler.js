var server_url = globals.server_url; //"http://192.168.1.101:8080/?callback=?";
var user = $.cookie("user");
var pass = $.cookie("pass");
var users = {};
var userId = null;
var selectedUser = null;

$(document).ready(function() {	

	$("#ADMIN").change(function(){
		toogleAdmin();
	});

	$("#getUserPermissions").click(function(){
		getUsersPermissions();
	});

	$("#cannotChangeUser").click(function(){
		cannotChangeUser();
	});
	
	$("#canChangeUser").click(function(){
		canChangeUser();
	});
	
	$("#mark_all").click(function(){
		markAllCheckboxes();
	});
	
	$("#unmark_all").click(function(){
		unmarkAlCheckboxes()
	});

	$("#usuarios_dropdown").change(function(){
		selectedUserChanged();
		
		//console.log("Se cambio el usuario seleccionado");
	});
	
	$("#save_permissions").click(function(){
		savePermissions();
	});
	
	userId = $.getUrlVar('userid');
	
	//console.log(userId);
	
	//if(userId == undefined)
	//{
	//	console.log("El userid no esta defin��o");
	//	$("#option_usuarios").attr('disabled', true);
	//}
	
	//var gets = getUrlVars("userid");
	//console.log(userId);
	//html = '<select name="option_usuarios"><option value="1">Corcho</option><option value="2">Pepe</option><option value="3">Usuario 2</option></select><hr/>';
	//$("#usuarios_dropdown").html(html);
	
});

function savePermissions()
{
	if(selectedUser != null)
	{
		var permString = "";
		$('input:checkbox:checked').each(function(){
			permString += $(this).attr('id')+", ";
		});
		
		console.log("----------------- Actualizando Permisos -----------------");
		console.log(permString);
		console.log(selectedUser);
		console.log("---------------------------------------------------------");
		
		
		$.getJSON(server_url,
		{
			target: "User",
			method: "UpdatePrivileges",
			user_id: selectedUser.id,
			privileges: permString,
			email: user,
			password: pass
		},
		function(data) {
			if(data.success)
			{
				console.log(data);
			}
			else
			{
				console.log("La llamada realizada no fue existosa");
			}
		});
	}
	else
	{
		alert("Debe seleccionar un usuario para modificar sus permisos!");
	}
}

function toogleAdmin()
{
	if($("#ADMIN").is(':checked'))
	{
		markAllCheckboxes();
		disableAllCheckboxes();
		$("#ADMIN").attr('disabled', false);
	}
	else
	{
		enableAllCheckboxes();
	}
}

function selectedUserChanged()
{
	for(var i = 0; i < users.length; i++)
	{
		if(users[i].id == $("#option_usuarios").val())
			selectedUser = users[i];
			getUsersPermissions();
	}
}

function cannotChangeUser()
{
	$("#option_usuarios").attr('disabled', true);
}

function canChangeUser()
{
	$("#option_usuarios").attr('disabled', false);
}

function markAllCheckboxes()
{
	$("input[type='checkbox']:not([disabled='disabled'])").attr('checked', true);
}

function disableAllCheckboxes()
{
	$("input[type='checkbox']:not([disabled='disabled'])").attr('disabled', true);
}

function enableAllCheckboxes()
{
	$("input[type='checkbox']:not([disabled='disabled'])").attr('disabled', false);
}

function unmarkAlCheckboxes()
{
	$("input[type='checkbox']:not([enabled='disabled'])").attr('checked', false);
}

function getUsersPermissions()
{
	//console.log(selectedUser);
	
	unmarkAlCheckboxes();

	if(selectedUser != null)
	{
		for(var i = 0; i < selectedUser.privileges.length; i++)
		{
			$("#"+selectedUser.privileges[i]).attr('checked', true);
			if(selectedUser.privileges[i] == "ADMIN")
			{
				markAllCheckboxes();
			}
			//console.log(selectedUser.privileges[i]); //.permissions);
		}
	}
}

function getUsersDropdown()
{
	$.getJSON(server_url,
	{
		target: "User",
		method: "GetUser",
		email: user,	
		password: pass
	},
	function(data) {
		if (data.success == false)
			return;
		
		users = data.users;
		if(users.length > 0)
		{			
			var inner_html = 'Seleccionar Usuario: <select name="option_usuarios" id="option_usuarios"><option value="0">Seleccione...</option>';
			for(i = 0; i < users.length; i++)
			{
				if(users[i].id == userId)
				{
					console.log("Se selecciono el usuario: "+users[i].name);
					selectedUser = users[i];
				}
				inner_html += '<option value='+users[i].id+'>'+users[i].name+'</option>';
			}
			inner_html += "</select>";
			if(userId != undefined)
			{
				inner_html = "Usuario Seleccionado: <b>"+selectedUser.name+"</b>";
			}
			$("#usuarios_dropdown").html(inner_html);
		}
		
	});
}