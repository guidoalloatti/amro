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
				fakeLogin();
				//checkLogin()
			}
		else
			$("#error_box").html("<b>Atencion:</b> Usuario o password no especificados");
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
	$.getJSON("http://localhost:8080/?callback=?",
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
			
			window.location.replace("main.php?invoice_url=pr");
			
			//globals.logedUser = $("#user").val();
			//globals.logedPass = $("#pass").val();
			//console.log("http_request.readyState: "+http_request.readyState);
			//console.log("The Object: "+the_object);
			//console.log("Json Data: "+json_data);	
			//console.log("Usuario y Password Seteado en globals: "+globals.logedUser+" | "+globals.logedPass);
			
		} else {
			alert("Ocurrio un problema con la URL.");
		}
		http_request = null;
	}
}
