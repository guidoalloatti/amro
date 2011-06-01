// Setting Globals
var http_request;
var url;
var pass;
var user;
var key;

$(document).ready(function() {
	$("#loginButton").click(function(){
		if(checkValues())
			{
				//fakeLogin();
				checkLogin();
			}
		else
			$("#error_box").html("<b>Atencion:</b> Usuario o password no especificados");
	});
	
	$("#new_user_table").hide();
	$("#new_user_button").click(function(){
		newUserForm();
	});
	
	$("#new_user_submit").click(function(){
		newUser();
	});
});

function checkValues()
{
	var canLogin = true;
	if( $("#user").val() == "" || $("#pass").val() == "" )
		canLogin = false;
	return canLogin;
}

function fakeLogin()
{
	globals.logedUser = $("#user").val();
	globals.logedPass = $("#pass").val();
	window.location.replace("main.php?invoice_url=pr");
}

function checkLogin()
{
	$.getJSON(globals.server_url, 		//"http://localhost:8080/?callback=?",
	{
		target: "User",
		method: "Login",
		email: $("#user").val(),
		password: $("#pass").val(),
	},
	function(data) {
		if(data.success)
		{
			$("#error_box").html("Login <b>Correcto</b>!");
			doLogin( "amroKey", $("#user").val(), $("#pass").val() );
		}
		else
		{
			$("#error_box").html("Login <b>Incorrecto</b>!!");			
		}
		//html_code += dump(data);
		//$("#html_change").replaceWith(html_code);			
		//$("#error_box").html("Haciendo Login!"+html_code);
		//console.log(data);
	});
}	

function setAjaxVars()
{
	http_request = new XMLHttpRequest();
	pass = $("#pass").val();
	user = $("#user").val();
	key	 = "amroKey";
	url = "ajax/doLogin.php?key="+key+"&user="+user+"&pass="+pass;
}

function doLogin(user, pass, key)
{
	setAjaxVars();
	http_request.onreadystatechange = handle_json;
	http_request.open("GET", url, true);
	http_request.send(null);
}
 
 function handle_json()
 {
	if (http_request.readyState == 4) {
		if (http_request.status == 200){
			var json_data = http_request.responseText; 
			var the_object = eval("(" + json_data + ")");
			
			
			//globals.logedUser = $("#user").val();
			//globals.logedPass = $("#pass").val();
			console.log("http_request.readyState: "+http_request.readyState);
			console.log("The Object: "+the_object);
			console.log("Json Data: "+json_data);	
			console.log("Usuario y Password Seteado en globals: "+globals.logedUser+" | "+globals.logedPass);
			
			$.cookie("user", $("#user").val());
			$.cookie("pass", $("#pass").val());

			window.location.replace("main.php?invoice_url=pr");
			
		} else {
			alert("Ocurrio un problema con la URL.");
		}
		http_request = null;
	}
}
 
function newUserForm()
{
	var inner_html = "<table>";
	inner_html += "<tr><td><label>Nombre:</label></td><td><input type='text' placeholder='Juan' id='new_user_name' style='text-align:center;' /></td></tr>";
	inner_html += "<tr><td><label>Apellido:</label></td><td><input type='text' placeholder='Perez' id='new_user_surname' style='text-align:center;' /></td></tr>";
	inner_html += "<tr><td><label>email:</label></td><td><input type='text' placeholder='juanperez@amro.com.ar' id='new_user_email' style='text-align:center;' /></td></tr>";
	inner_html += "<tr><td><label>Contraseña:</label></td><td><input type='password' placeholder='xjfwaz90d' id='new_user_pass' style='text-align:center;' /></td></tr>";

	inner_html += "</table>";
	
	$("#new_user_fields").html(inner_html);	
	$("#new_user_table").show("slow");	
}

function newUser()
{	
	var mail = $("#new_user_email").val();
	var password = $("#new_user_pass").val();
	
	if (mail == "" || password == "") {
		alert("Ni el mail ni la contraseña pueden ser vacios");
		return;	
	}		
	
	$.getJSON(globals.server_url,
	{	
		target: "User",
		method: "NewUser",
		password: password,
		email: mail,
		name: $("#new_user_name").val(),
		surname: $("#new_user_surname").val()
	},
	function(data) {
		if (data.success == true) {
			alert("Usuario " + mail + " creado!\nRecuerde que cada usuario en el sistema será\nidentificado con su dirección única de mail.");
			window.location = "main.php?invoice_url=lo";
		} else if (data.user != undefined)
			alert("Error creando usuario! El usuario con mail " + mail + " ya existe.");
		else if (data.email != undefined)
			alert("Error! El formato del mail no es valido.");
		else
			alert("Error creando usuario. Problemas en el servidor.\nIntente nuevamente.");
	});
}
