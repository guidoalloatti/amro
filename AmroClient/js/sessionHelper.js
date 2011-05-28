// Session Global Vars
function doGetSessionVars()
{

	// Remover Cookie: $.cookie("name", null);
	// Crear Cookie: $.cookie("name", "value");
	// Setear Datos Adicionales: $.cookie("name", "value", { path: '/administration', expires: 7 });

	var user = $.cookie("name");
	var pass = $.cookie("pass");
	
	//console.log("Buscando Usuario y Password y Seteando en Cookies: "+user+" | "+pass);
	//if(user != null && pass != null)
	//	return;
	//console.log("Usuario Global: "+globals.logedUser);
	//console.log("Password Global: "+globals.logedPass);	
	
	if(globals.logedUser == null && globals.logedPass == null)
	{
		http_request = new XMLHttpRequest();
		url = "ajax/doGetSessionVars.php";
		http_request.onreadystatechange = handle_session;
		http_request.open("GET", url, true);
		http_request.send(null);
	}
	else
	{
		console.log("Usuario y Password Seteados en globals: "+globals.logedUser+" | "+globals.logedPass);
	}
}
 
 function timeTrack()
 {
	console.log(".");
 }
 
 function handle_session()
 {
	if (http_request.readyState == 4) {
		if (http_request.status == 200){
			var json_data = http_request.responseText; 
			var session = eval("(" + json_data + ")");
			
			$.cookie("user", session.user);
			$.cookie("pass", session.pass);
			
			//globals.logedUser = session.user;
			//globals.logedPass = session.pass;

			//console.log("Buscando Usuario y Password y Seteando en globals: "+globals.logedUser+" | "+globals.logedPass);
			//return globals;
		} 
		else
			alert("Ocurrio un problema con la URL.");
		http_request = null;
	}
}