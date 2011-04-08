$(document).ready(function() {

	var html_code = "Codigo de retorno de la llamada: ";

	$("#validate_login_button").click(function(){
		validateLogin();
		renderHtml();
	});
	
	$("#ajax_validate_login_button").click(function(){
		ajaxValidate();
		renderHtml();
	});

	$("#get_user_button").click(function(){
		getUser();
		//renderHtml();
	});
	
	$("#insert_user_button").click(function(){
		insertUser();
		//renderHtml();
	});
	
	$("#insert_material_button").click(function(){
		insertMaterial();
		//renderHtml();
	});
	
	$("#get_material_button").click(function(){
		getMaterial();
		//renderHtml();
	});
	
	function getMaterial()
	{
		$.ajax({
			type: "GET",
			url: "http://192.168.1.100:8080/?",
			contentType: "application/json; charset=utf-8",
			dataType: "jsonp",
			data: {
				target: "Material",
				method: "GetMaterial",
				email: "pmata@amro.com",
				password: "123",
				},
				
			success: function(json) {
				alert(json.materials[0].mlimits.estriccion);
				//alert(json.users[1].email);
				//html_code += "Success: json.length = "+json.length;
			},
			error: function (XMLHttpRequest, textStatus, errorThrown) {
				alert("Error Ajax Call");
				//html_code += "Error json.length = "+json.length;
			}
		});
	}
	
	function insertMaterial()
	{
		$.ajax({
			type: "GET",
			url: "http://192.168.1.100:8080/?",
			contentType: "application/json; charset=utf-8",
			dataType: "jsonp",
			data: {
				target: "Material",
				method: "NewMaterial",
				chlimits: "c=12 mn=11 si=1.1 p=2.3 s=1.5 cr=4,1 ni=0 mo=0 cu=0 v=0,1 ce=0",
				mlimits: "tension_rotura=1 limite_fluencia=2.2 alargamiento=12 estriccion=22 resiliencia=0 dureza=0",
				name: "WCC",
				email: "pmata@amro.com",
				password: "123",
				},
				
			success: function(json) {
				alert(json.success);
				//alert(json.users[1].email);
				//html_code += "Success: json.length = "+json.length;
			},
			error: function (XMLHttpRequest, textStatus, errorThrown) {
				alert("Error Ajax Call");
				//html_code += "Error json.length = "+json.length;
			}
		});
	}
	
	
	function insertUser()
	{
		$.ajax({
			type: "GET",
			url: "http://192.168.1.100:8080/?",
			contentType: "application/json; charset=utf-8",
			dataType: "jsonp",
			data: {
				target: "User",
				method: "NewUser",
				name: "Guido",
				surname: "Alloatti",
				email: "galloatti2@amro.com",
				password: "123",
				signature: "NULL",
				},
				
			success: function(json) {
				alert(json.success);
				//alert(json.users[1].email);
				//html_code += "Success: json.length = "+json.length;
			},
			error: function (XMLHttpRequest, textStatus, errorThrown) {
				alert("Error Ajax Call");
				//html_code += "Error json.length = "+json.length;
			}
		});
	}
	
	
	function getUser()
	{
		$.getJSON("http://192.168.1.100:8080/?callback=?",
		{
			target: "User",
			method: "GetUset",
			email: "pmata@amro.com",
			password: "123",
		},
		function(data) {
			alert();
			
			//html_code += data;
			//console.log(data);			
		});
		
	}
	
	function validateLogin()
	{
		$.getJSON("http://192.168.1.100:8080/?callback=?",
		{
			target: "User",
			method: "Login",
			email: "pmata@amro.com",
			password: "123",
			//format: "json"
		},
		function(data) {
			alert("Function Data");
				html_code += data;
				console.log = data;			
		});
	}
	
	function ajaxValidate()
	{
		$.ajax({
    type: "GET",
    url: "http://192.168.1.100:8080/?",
    contentType: "application/json; charset=utf-8",
    dataType: "jsonp",
	data: {
		target: "User",
		method: "GetUser",
		email: "pmata@amro.com",
		password: "123"},
    success: function(json) {
		//alert(json.users[1].email);
		alert(json.success);
		
        //html_code += "Success: json.length = "+json.length;
    },
    error: function (XMLHttpRequest, textStatus, errorThrown) {
		html_code += "Error json.length = "+json.length;
    }
});
	}
	
	function renderHtml()
	{
		$("#html_change").replaceWith(html_code);
	}
	
	function dump(obj) {
    var out = '';
    for (var i in obj) {
        out += i + ": " + obj[i] + "\n";
    }

    alert(out);

    // or, if you wanted to avoid alerts...

    var pre = document.createElement('pre');
    pre.innerHTML = out;
    document.body.appendChild(pre)
}
	
});