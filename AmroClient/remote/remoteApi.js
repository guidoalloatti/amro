var html_code = "Codigo de retorno de la llamada ---> ";

$(document).ready(function() {

	$("#validate_login_button").click(function(){
		validateLogin();
	});
	
	$("#ajax_validate_login_button").click(function(){
		ajaxValidate();
	});

	$("#get_user_button").click(function(){
		getUser();
	});
	
	$("#get_client_button").click(function(){
		getClient();
	});
	
	$("#insert_user_button").click(function(){
		insertUser();
	});
	
	$("#insert_client_button").click(function(){
		insertClient();
	});
	
	$("#insert_material_button").click(function(){
		insertMaterial();
	});
	
	$("#get_material_button").click(function(){
		getMaterial();
	});
	
	$("#delete_material_button").click(function(){
		deleteMaterial();
	});
	
	$("#delete_user_button").click(function(){
		deleteUser();
	});
	
	$("#delete_client_button").click(function(){
		deleteClient();
	});	
	
	$("#update_material_button").click(function(){
		updateMaterial();
	});
	
	$("#update_user_button").click(function(){
		updateUser();
	});
	
	$("#update_client_button").click(function(){
		updateClient();
	});	
		
	$("#load_ma_button").click(function(){
		loadMA();
	});
	
	$("#delete_ma_button").click(function(){
		deleteMA();
	});	
		
	$("#get_all_ma_button").click(function(){
		getAllMA();
	});
	
	$("#get_ma_by_date_button").click(function(){
		getMAByDate();
	});		
	
	$("#parse_ca_button").click(function(){
		parseCA();
	});
	
	$("#delete_ca_button").click(function(){
		deleteCA();
	});	
		
	$("#check_all_ca_button").click(function(){
		checkAllCA();
	});
	
	$("#check_ca_by_date_button").click(function(){
		checkCAByDate();
	});

	$("#check_ca_by_probeta_button").click(function(){
		checkCAByProbeta();
	});	
	
	$("#check_ca_by_material_button").click(function(){
		checkCAByMaterial();
	});	

	$("#parse_csv_button").click(function(){
		parseCSV();
	});	
	
	$("#delete_oc_button").click(function(){
		deleteOC();
	});	
	
	$("#get_oc_by_probeta_button").click(function(){
		getOCByProbeta();
	});	
	
	$("#get_oc_by_client_button").click(function(){
		getOCByClient();
	});	
	
	$("#get_oc_by_material_button").click(function(){
		getOCByMaterial();
	});	
	
	$("#get_all_oc_button").click(function(){
		getAllOC();
	});	
	
	$("#get_oc_by_oc_button").click(function(){
		getOCByOC();
	});	
	
	function insertClient()
	{
		$.getJSON("http://localhost:8080/?callback=?",
		{
			target: "Client",
			method: "NewClient",
			name: "Thorsa",
			address: "Juan Pindoncho 123",
			city: "Rosario",
			zip: "2000",
			country: "Argentina",
			phone: "+(54) 156-111111",
			website: "www.amro.com",
			telefax: "1111111",
			seqdigits: "3", // Esto especifica cu�ntos d�gitos va a usar para los n�meros de probeta. Ej. AR425 --> 3
			code: "AR", // Codigo del n�mero de probeta, si alg�n otro cliente tiene el c�digo, tira error.
			email: "pmata@amro.com",
			password: "123",
			signature: "NULL"
		},
		function(data) {
			html_code += dump(data);
			$("#html_change").replaceWith(html_code);				
		});
	}
	
	function updateClient()
	{
		$.getJSON("http://localhost:8080/?callback=?",
		{
			target: "Client",
			method: "UpdateClient",
			name: "Thorsa",
			address: "Juan Pindoncho 123",
			city: "Rosario",
			zip: "2000",
			country: "Argentina",
			phone: "+(54) 156-111111",
			website: "www.amro.com",
			telefax: "1111111",
			seqdigits: "3", // Esto especifica cu�ntos d�gitos va a usar para los n�meros de probeta. Ej. AR425 --> 3
			code: "FB", // Codigo del n�mero de probeta, si alg�n otro cliente tiene el c�digo, tira error.
			email: "pmata@amro.com",
			password: "123",
			signature: "NULL",
			id: "5"
		},
		function(data) {
			html_code += dump(data);
			$("#html_change").replaceWith(html_code);				
		});
	}
		
	function getClient()
	{
		$.getJSON("http://localhost:8080/?callback=?",
		{
			target: "Client",
			method: "GetClient",
			email: "pmata@amro.com",
			password: "123"
		},
		function(data) {
			html_code += dump(data);
			$("#html_change").replaceWith(html_code);				
		});
		
	}
	
	function deleteClient()
	{
		$.getJSON("http://localhost:8080/?callback=?",
		{
			target: "Client",
			method: "DeleteClient",
			email: "pmata@amro.com",
			password: "123",
			id: "4"
		},
		function(data) {
			html_code += dump(data);
			$("#html_change").replaceWith(html_code);				
		});
		
	}
	
	function getMaterial()
	{
		$.getJSON("http://localhost:8080/?callback=?",
		{
			target: "Material",
			method: "GetMaterial",
			email: "pmata@amro.com",
			password: "123"
		},
		function(data) {
			html_code += dump(data);
			$("#html_change").replaceWith(html_code);				
		});
	}	
	
	function insertMaterial()
	{
		$.getJSON("http://localhost:8080/?callback=?",
		{
			target: "Material",
			method: "NewMaterial",
			email: "pmata@amro.com",
			password: "123",
			chlimits: "c=12-0+mn=11-0+si=1.1-0+p=2.3-0+s=1.5-1+cr=4-2,1+ni=0+mo=0+cu=0+v=0,1+ce=0",
			mlimits: "tension_rotura=1-0+limite_fluencia=2.2-1.6+alargamiento=12+estriccion=22+resiliencia=0+dureza=0",
			name: "WCB"			
		},
		function(data) {
			html_code += dump(data);
			$("#html_change").replaceWith(html_code);				
		});
	}	
	
	function updateMaterial()
	{
		$.getJSON("http://localhost:8080/?callback=?",
		{
			target: "Material",
			method: "UpdateMaterial",
			email: "pmata@amro.com",
			password: "123",
			chlimits: "c=52-0+mn=11-0+si=1.1-0+p=2.3-0+s=1.5-1+cr=4-2,1+ni=0+mo=0+cu=0+v=0,1+ce=0",
			mlimits: "tension_rotura=1-0+limite_fluencia=2.2-1.6+alargamiento=12+estriccion=22+resiliencia=0+dureza=0",
			name: "WCB",
			id: "5"			
		},
		function(data) {
			html_code += dump(data);
			$("#html_change").replaceWith(html_code);				
		});
	}	
	
	function deleteMaterial()
	{
		$.getJSON("http://localhost:8080/?callback=?",
		{
			target: "Material",
			method: "DeleteMaterial",
			email: "pmata@amro.com",
			password: "123",
			id: "3"
		},
		function(data) {
			html_code += dump(data);
			$("#html_change").replaceWith(html_code);				
		});
	}	
	
	function insertUser()
	{
		$.getJSON("http://localhost:8080/?callback=?",
		{
			target: "User",
			method: "NewUser",
			name: "Guido",
			surname: "Alloatti",
			email: "galloatti2@amro.com",
			password: "123",
			signature: "NULL"
		},
		function(data) {
			html_code += dump(data);
			$("#html_change").replaceWith(html_code);				
		});
	}
			
	function updateUser()
	{
		$.getJSON("http://localhost:8080/?callback=?",
		{
			target: "User",
			method: "UpdateUser",
			name: "Guidolo",
			surname: "Alloatti",
			email: "galloatti2@amro.com",
			password: "123",
			signature: "NULL"
		},
		function(data) {
			html_code += dump(data);
			$("#html_change").replaceWith(html_code);				
		});
	}
	
	function getUser()
	{
		$.getJSON("http://localhost:8080/?callback=?",
		{
			target: "User",
			method: "GetUser",
			email: "pmata@amro.com",
			password: "123",
		},
		function(data) {
			html_code += dump(data);
			$("#html_change").replaceWith(html_code);				
		});
		
	}
	
	function deleteUser()
	{
		$.getJSON("http://localhost:8080/?callback=?",
		{
			target: "User",
			method: "DeleteUser",
			// Quien lo esta borrando
			email: "pmata@amro.com",
			password: "123",
			// A quien se borra
			id: "6"
		},
		function(data) {
			html_code += dump(data);
			$("#html_change").replaceWith(html_code);				
		});
		
	}	
	
	function validateLogin()
	{
		$.getJSON("http://localhost:8080/?callback=?",
		{
			target: "User",
			method: "Login",
			email: "pmata@amro.com",
			password: "123",
			//format: "json"
		},
		function(data) {			
			html_code += dump(data);
			$("#html_change").replaceWith(html_code);									
		});
	}	
	
	function loadMA()
	{
		$.getJSON("http://localhost:8080/?callback=?",
		{
			target: "Analysis",
			method: "LoadMA",
			email: "pmata@amro.com",
			password: "123",
			mechanicalanalysis: "tension_rotura=1+limite_fluencia=2.2+alargamiento=12+estriccion=22+resiliencia=0+dureza=0",
			material_id: "4",				
		},
		function(data) {
			html_code += dump(data) + "\n" + "Puede responder tambi�n con un 'material_id: xx' queriendo decir que el fallo estuvo en que no existe el material especifico";
			$("#html_change").replaceWith(html_code);				
		});
	}	
	
	function deleteMA()
	{
		$.getJSON("http://localhost:8080/?callback=?",
		{
			target: "Analysis",
			method: "DeleteMA",
			email: "pmata@amro.com",
			password: "123",
			id: "1",
		},
		function(data) {
			html_code += dump(data);
			$("#html_change").replaceWith(html_code);				
		});
	}	
	
	function getAllMA()
	{
		$.getJSON("http://localhost:8080/?callback=?",
		{
			target: "Analysis",
			method: "GetMA",
			email: "pmata@amro.com",
			password: "123"							
		},
		function(data) {
			html_code += dump(data);
			$("#html_change").replaceWith(html_code);				
		});
	}	
	
	function getMAByDate()
	{
		$.getJSON("http://localhost:8080/?callback=?",
		{
			target: "Analysis",
			method: "GetMA",
			email: "pmata@amro.com",
			password: "123",
			year: "2011",
			month: "4",
			day: "12"
		},
		function(data) {
			html_code += dump(data);
			$("#html_change").replaceWith(html_code);				
		});
	}
	
	function parseCA()
	{
		$.getJSON("http://localhost:8080/?callback=?",
		{
			target: "Analysis",
			method: "ParseCA",
			email: "pmata@amro.com",
			password: "123",
			filepath: "/home/pmata/amro/analisis20110412.csv"
		},
		function(data) {
			html_code += dump(data);
			$("#html_change").replaceWith(html_code);				
		});
	}	
	
	function deleteCA()
	{
		$.getJSON("http://localhost:8080/?callback=?",
		{
			target: "Analysis",
			method: "DeleteCA",
			email: "pmata@amro.com",
			password: "123",
			id: "3"
		},
		function(data) {
			html_code += dump(data);
			$("#html_change").replaceWith(html_code);				
		});
	}	
	
	function checkCAByDate()
	{
		$.getJSON("http://localhost:8080/?callback=?",
		{
			target: "Analysis",
			method: "CheckCA",
			email: "pmata@amro.com",
			password: "123",
			year: "2010",
			month: "8",
			day: "30"
		},
		function(data) {
			html_code += dump(data);
			$("#html_change").replaceWith(html_code);				
		});
	}
	
	function checkCAByProbeta()
	{
		$.getJSON("http://localhost:8080/?callback=?",
		{
			target: "Analysis",
			method: "CheckCA",
			email: "pmata@amro.com",
			password: "123",
			numprobeta: "AR1068",
		},
		function(data) {
			html_code += dump(data);
			$("#html_change").replaceWith(html_code);				
		});
	}	
	
	function checkAllCA()
	{
		$.getJSON("http://localhost:8080/?callback=?",
		{
			target: "Analysis",
			method: "CheckCA",
			email: "pmata@amro.com",
			password: "123"			
		},
		function(data) {
			html_code += dump(data);
			$("#html_change").replaceWith(html_code);				
		});
	}	
	
	function checkCAByMaterial()
	{
		$.getJSON("http://localhost:8080/?callback=?",
		{
			target: "Analysis",
			method: "CheckCA",
			email: "pmata@amro.com",
			password: "123",
			material_id: "5",
		},
		function(data) {
			html_code += dump(data);
			$("#html_change").replaceWith(html_code);				
		});
	}	
	
	function parseCSV()
	{
		$.getJSON("http://localhost:8080/?callback=?",
		{
			target: "CSVParsing",
			method: "ParseCSV",
			email: "pmata@amro.com",
			password: "123",
			filepath: "/disco/Amro/files/ordencompra20110412.csv"
		},
		function(data) {
			html_code += dump(data);
			$("#html_change").replaceWith(html_code);				
		});
	}	
	
	function deleteOC()
	{
		$.getJSON("http://localhost:8080/?callback=?",
		{
			target: "CSVParsing",
			method: "DeleteOC",
			email: "pmata@amro.com",
			password: "123",
			id: "4"
		},
		function(data) {
			html_code += dump(data);
			$("#html_change").replaceWith(html_code);				
		});
	}	
	
	function getAllOC()
	{
		$.getJSON("http://localhost:8080/?callback=?",
		{
			target: "CSVParsing",
			method: "GetOC",
			email: "pmata@amro.com",
			password: "123"
		},
		function(data) {
			html_code += dump(data);
			$("#html_change").replaceWith(html_code);				
		});
	}	
	
	function getOCByOC()
	{
		$.getJSON("http://localhost:8080/?callback=?",
		{
			target: "CSVParsing",
			method: "GetOC",
			email: "pmata@amro.com",
			password: "123",
			ordencompra: "7924"
		},
		function(data) {
			html_code += dump(data);
			$("#html_change").replaceWith(html_code);				
		});
	}	
	
	function getOCByMaterial()
	{
		$.getJSON("http://localhost:8080/?callback=?",
		{
			target: "CSVParsing",
			method: "GetOC",
			email: "pmata@amro.com",
			password: "123",
			material_id: "5",
		},
		function(data) {
			html_code += dump(data);
			$("#html_change").replaceWith(html_code);				
		});
	}	
	
	function getOCByClient()
	{
		$.getJSON("http://localhost:8080/?callback=?",
		{
			target: "CSVParsing",
			method: "GetOC",
			email: "pmata@amro.com",
			password: "123",
			client_id: "5",
		},
		function(data) {
			html_code += dump(data);
			$("#html_change").replaceWith(html_code);				
		});
	}	
	
	function getOCByProbeta()
	{
		$.getJSON("http://localhost:8080/?callback=?",
		{
			target: "CSVParsing",
			method: "GetOC",
			email: "pmata@amro.com",
			password: "123",
			numprobeta: "AR1068",
		},
		function(data) {
			html_code += dump(data);
			$("#html_change").replaceWith(html_code);				
		});
	}	
	
	function renderHtml()
	{
		$("#html_change").replaceWith(html_code);
	}
	
	var pre = document.createElement('pre');
	document.body.appendChild(pre);
	
	function dump2(obj, indent) {
		var out = '';
		for (var i in obj) {
			if (typeof obj[i] == 'object') {
				out += indent + i + ": " + "\n" + dump2(obj[i], indent + "\t");										
			} else
				out += indent + i + ": " + obj[i] + "\n";
		}
			return out;
	}	
	
	function dump(obj) {
		out = dump2(obj, "");

		// or, if you wanted to avoid alerts...

		pre.innerHTML = out;
	}
	
});