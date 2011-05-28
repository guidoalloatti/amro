var server_url = globals.server_url;
var user = $.cookie("user");
var pass = $.cookie("pass");
var users;
var userId = null;
var selectedUser = null;

$(document).ready(function() {	

	$("#ADMIN").change(function(){
		if($("#ADMIN").is(':checked'))
		{
			markAllCheckboxes();
		}
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
	
	userId = $.getUrlVar('userid');
	
	//console.log(userId);
	
	getUsersDropdown();	

	//if(userId == undefined)
	//{
	//	console.log("El userid no esta definido");
	//	$("#option_usuarios").attr('disabled', true);
	//}
	
	//var gets = getUrlVars("userid");
	//console.log(userId);
	//html = '<select name="option_usuarios"><option value="1">Corcho</option><option value="2">Pepe</option><option value="3">Usuario 2</option></select><hr/>';
	//$("#usuarios_dropdown").html(html);
	
});


function selectedUserChanged()
{
	for(var i = 0; i < users.length; i++)
	{
		if(users[i].id == $("#option_usuarios").val())
			selectedUser = users[i];
			getUsersPermissions();
	}
	
	//console.log($("#option_usuarios").val());
	//console.log(users);
	//selectedUser = users.
	//console.log(selectedUser);
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

function unmarkAlCheckboxes()
{
	$("input[type='checkbox']:not([enabled='disabled'])").attr('checked', false);
}

function getUsersPermissions()
{
	unmarkAlCheckboxes();
	console.log(selectedUser.privileges);
	//ifselectedUser.privileges
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
		if(data.users.length > 0)
		{
			users = data.users;
			
			//var inner_html = "<table><tr><th>Usuario</th><th>Eliminar</th></tr><tr>"
			var inner_html = 'Seleccionar Usuario: <select name="option_usuarios" id="option_usuarios"><option value="0">Seleccione...</option>';
			for(i = 0; i < users.length; i++)
			{
				//console.log("data.users[i].id | userId\n"+data.users[i].id+" | "+userId);
				if(users[i].id == userId)
				{
					console.log("Se selecciono el usuario: "+users[i].name);
					selectedUser = users[i];
					//$("#option_usuarios").attr('selectedValue', users[i].id);
				}
					
				inner_html += '<option value='+users[i].id+'>'+users[i].name+'</option>';
				
				//inner_html += "<td><a href='#' id='usuario_"+data.users[i].id+"' onclick='loadUser(\""+data.users[i].name+"\", \""+data.users[i].id+"\");'>"+data.users[i].name+"</a></td>";
				//inner_html += "<td align='center'><img src='img/delete.png' width='20' heigth='20' alt='Eliminar' title='Eliminar' onclick='deleteUserConfirmation(\""+data.users[i].name+"\", \""+data.users[i].id+"\");' /></td></tr>";
			}
			inner_html += "</select>";
			
			if(userId != undefined)
				inner_html = "Usuario Seleccionado: <b>"+selectedUser.name+"</b>";

			$("#usuarios_dropdown").html(inner_html);
		}
	});
}