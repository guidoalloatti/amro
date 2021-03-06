var server_url = globals.server_url;
var user = $.cookie("user");
var pass = $.cookie("pass");


$(document).ready(function() {

	$("#selectedCA").hide();
	$("#addCA").hide();
	$("#allMA").hide();
	$("#all_oc").hide();
	$("#oc_details").hide();
	$("#showSave").hide();
	$("#image_watch").hide();	
	$("#ttermico_selected").hide();
	$("#ttermico_selected").parent().hide();
	$("#show_ttermico_asoc").hide();
	$("#view_certs_button").hide();
	$("#loadCAImage").hide();

	
	
	$("#view_certs_button").click(function(event){
		window.location = "main.php?invoice_url=cm"; 
		event.preventDefault();
	});
	
	$("#checkMAExistence").click(function(event){
		getMA();
		event.preventDefault();
	});	
	
	$("#create_tt_button").click(function(event){
		window.location = "main.php?invoice_url=abm&module=ttermico"; 
		event.preventDefault();
	});
	
	$("#checkCAExistence").click(function(event){
		getCA();
		event.preventDefault();
	});

	$("#ver_detalles").click(function(event){
		getOCDetails(showDetails);
		event.preventDefault();
	});
	
	$("#cambiar_ocb").click(function(event){
		cambiarOC();
		event.preventDefault();
	});
	
	//$("#submitCA").hide();
	
	$("#_file").change(function(e){
	  $in=$(this);
	  var file = $in.val();
	  //uploadCAFile(file);	
	  $("#form_file").val(file);
	  $("#submitCA").submit();
	});	
	
	$("#submitCAButton").click(function(event){
		$("#_file").click();
		event.preventDefault();
	});
	
	$("#ttloader").change(function(e){
		  $in=$(this);
		  var file = $in.val();
		  var inner_html = '<div id="image_div" style="height: 300px; overflow:auto;"><img src="'+file+'"></div>';
		  $("#image_watch").html(inner_html);
		  $("#image_watch").show("slow");
		});
	
	$('#formElem').children(':nth-child(3)').find(':input:not(button)').each(function(){
		var $this 		= $(this);
		$this.change(function(event){
			checkMASaveOpportunity();
			event.preventDefault();
		});
	});	
});

function loadAllClients()
{	
	if(globals.currentClients != null && globals.currentClients.length > 0)
		return;
	
	
	$.getJSON(server_url,
	{
		target: "Client",
		method: "GetClient",
		email: user,      	// "pmata@amro.com",
		password: pass		// "123"
	},
	function(data) {
		if(data.success == true)
		{
			globals.currentClients = data.clients;
			//showClients(data.clients);
		}
		else
		{
			alert("No se pudieron cargar los clientes. Error con el servidor");
		}
	});
}

function loadAllMaterials()
{
	if(globals.currentMaterials != null && globals.currentMaterials.length > 0)
		return;
	
	$.getJSON(server_url,
	{
		target: "Material",
		method: "GetMaterial",
		email: user,      // "pmata@amro.com",
		password: pass,	  // "123",
	},
	function(data) {
		if(data.success == true)
		{
			globals.currentMaterials = data.materials;
			//showMaterials(data.materials);
		}
		else
		{
			alert("No se pudieron cargar los materiales. Error con el servidor");
		}
	});
}

function loadAllUsers()
{
	if(globals.currentUsers != null && globals.currentUsers.length > 0)
		return;
	
	$.getJSON(server_url,
	{
		target: "User",
		method: "GetUser",
		email: user,      	// "pmata@amro.com",
		password: pass, 	// "123"
	},
	function(data) {
		if(data.success == true)
		{
			globals.currentUsers = data.users;
			showReviewers(data.users);
			showApprovers(data.users);
		}
		else
		{
			alert("No se pudieron cargar los usuarios. Error con el servidor");
		}
	});
}

function showReviewers(users)
{		
	var inner_html = "<option value='0'>Seleccionar</option>";
	for(i = 0; i < users.length; i++)
	{
		inner_html += "<option value='"+users[i].id+"'>"+users[i].name+ " " +users[i].surname+"</option>";
	}
	inner_html += "</select>";	
	$("#select_reviewer").html(inner_html);
}

function showApprovers(users)
{		
	var inner_html = "<option value='0'>Seleccionar</option>";
	for(i = 0; i < users.length; i++)
	{
		inner_html += "<option value='"+users[i].id+"'>"+users[i].name+ " " +users[i].surname+"</option>";
	}
	inner_html += "</select>";	
	$("#select_approver").html(inner_html);
}

function getUrlVars()
{
    var vars = [], hash;
    var hashes = window.location.href.slice(window.location.href.indexOf('?') + 1).split('&');
    for(var i = 0; i < hashes.length; i++)
    {
        hash = hashes[i].split('=');
        vars.push(hash[0]);
        vars[hash[0]] = hash[1];
    }
    return vars;
}

function showDetails(lines)
{
	if (lines.length < 1)
	{
		var inner_html = "No se encontro ninguna orden de compra con valor de protocolo "+$("#orden_compra").val();
		$("#oc_details").html(inner_html);
		return;
	}
	
	var inner_html = "<div><table><tr class='oc'><th class='oc'>Orden de Compra</th><th class='oc'>Numero de Probeta</th><th class='oc'>Cliente</th><th class='oc'>Material</th><th class='oc'>Descripcion</th><th class='oc'>Id</th></tr>";
	inner_html += "<tr class='odd'>";
		inner_html += "<td class='oc'>"+lines[0].ordencompra+"</td>";
	inner_html += "<td>"+lines[0].numprobeta+"</td>";
	inner_html += "<td>"+clientNameSearch(lines[0].client_id)+"</td>";
	inner_html += "<td>"+materialNameSearch(lines[0].material_id)+"</td>";
	inner_html += "<td>"+lines[0].description+"</td>";
	inner_html += "<td>"+lines[0].id+"</td>";
	inner_html += "</tr>";
	inner_html += "</table></div>";

	$("#oc_details").html(inner_html);
	$("#oc_details").show("slow");
}

function getOCDetails(callback)
{
	var vars = getUrlVars();
	
	if (vars.id == undefined) {
		alert("Primero debe seleccionar una orden de compra");
		return;
	}
	
	$.getJSON(globals.server_url,
			{
				target: "CSVParsing",
				method: "GetOC",
				email: user,      	// "pmata@amro.com",
				password: pass,     // "123",
				id: vars.id,
				order: "ordencompra"
			},
			function(data) {
				if (data.success == false)
					return new Array();
				
				callback(data.lines);
			}
	);			
}

function cambiarOC()
{
	if (globals.currentOrders == null)
		getOCs();
	else
		drawOC();	
}

function generateCertificate()
{	
	var vars = getUrlVars();
	
	var quimicos = 	"c="+$("#_c").val()+"+"+
	"mn="+$("#_mn").val()+"+"+
	"si="+$("#_si").val()+"+"+
	"p="+$("#_p").val()+"+"+
	"s="+$("#_s").val()+"+"+
	"cr="+$("#_cr").val()+"+"+
	"ni="+$("#_ni").val()+"+"+
	"mo="+$("#_mo").val()+"+"+
	"cu="+$("#_cu").val()+"+"+
	"v="+$("#_v").val()+"-"+"+"+
	"ce="+$("#_ce").val();	

	var mecanicos = "tension_rotura="+$("#tension_rotura").val()+"+"+
	"limite_fluencia="+$("#limite_fluencia").val()+"+"+
	"alargamiento="+$("#alargamiento").val()+"+"+
	"estriccion="+$("#estriccion").val()+"+"+
	"resiliencia="+$("#resiliencia").val()+"+"+
	"dureza="+$("#dureza").val();
	
	var description = decodeURIComponent(vars.desc);
	
	var reviewer = $("#select_reviewer").val();
	var approver = $("#select_approver").val();
	
	var observations = $("#observations").val();
	
	var ttreatment = $("#ttermico_selected").val();

	$.getJSON(server_url,
	{	
		target: "Certificate",
		method: "NewCertificate",
		identificacion: vars.numprobeta,
		protn: vars.numprobeta,
		email: user,      	// "pmata@amro.com",
		password: pass,     // "123",
		ordencompra: vars.ordencompra,
		chemicalanalysis: quimicos,
		mechanicalanalysis: mecanicos,
		approver_id: approver,
		reviewer_id: reviewer,
		material_id: vars.material,
		client_id: vars.client,
		description: description,
		observations: observations,
		ttreatment_id: ttreatment
	},
	function(data) {
		if (data.success == true) {
			alert("El certificado se generó con éxito");
			
			$("#view_certs_button").show("slow");	
		} else if (data.permissions != undefined)
			alert("No tiene permisos para realizar la operación");
		else if (data.client_id != undefined)
			alert("No se puede generar el certificado. El cliente con id " + vars.client + " no existe.");
		else if (data.ttermico_id != undefined)
			alert("No se puede generar el certificado. El Tratamiento Térmico con id " + ttreatment + " no existe.");
		else if (data.material_id != undefined)
			alert("No se puede generar el certificado. El Material con id " + material_id + " no existe.");
		else if (data.approver_id != undefined)
			alert("No se puede generar el certificado. El usuario que aprueba con id " + approver_id + " no existe.");
		else if (data.reviewer_id != undefined)
			alert("No se puede generar el certificado. El usuario que revisa con id " + reviewer_id + " no existe.");
		else if (data.error != undefined)
			alert("No se puede generar el certificado. Mal formato en los valores químicos y mecánicos pasados.");
		else
			alert("Fallo en la generación de certificado");
	});	
}

function getOCs()
{	
	loading("all_oc", true);

	$.getJSON(globals.server_url,
	{
		target: "CSVParsing",
		method: "GetOC",
		email: user,      		// "pmata@amro.com",
		password: pass,      	// "123",
		order: "ordencompra"
	},
	function(data) {
		if (data.success == true) {
			globals.currentOrders = data.lines;
			drawOC();
		}
		else
			alert("No se pudieron cargar las ordenes de compra. Error con el servidor");
	});
}

function drawOC()
{
	inner_html = "<div style='max-height: 275px; overflow: auto;'>";
	inner_html += "<table>";
	inner_html += "<tr class='oc'><th class='oc'>Orden de Compra</th><th class='oc'>Numero de Probeta</th><th class='oc'>Cliente</th><th class='oc'>Material</th><th class='oc'>Descripcion</th><th class='oc'>Id</th><th class='oc'>Generar Certificado</th></tr>";
	
	if (globals.currentOrders == null)
		return;
	
	//alert(globals.currentOrders.length);
	
	for(var i=0; i < globals.currentOrders.length; i++)
	{
		var line = "even";
		if( i%2 == 0 ) 
		{
			line = "odd";
		}
		
		inner_html += "<tr class='"+line+"'>";
		inner_html += "<td class='oc'>"+globals.currentOrders[i].ordencompra+"</td>";
		inner_html += "<td>"+globals.currentOrders[i].numprobeta+"</td>";
		inner_html += "<td>"+clientNameSearch(globals.currentOrders[i].client_id)+"</td>";
		inner_html += "<td>"+materialNameSearch(globals.currentOrders[i].material_id)+"</td>";
		inner_html += "<td>"+globals.currentOrders[i].description+"</td>";
		inner_html += "<td>"+globals.currentOrders[i].id+"</td>";
		inner_html += "<td align='center'><a href='main.php?invoice_url=ce&numprobeta="+globals.currentOrders[i].numprobeta+"&ordencompra="+globals.currentOrders[i].ordencompra+"&id="+globals.currentOrders[i].id+"&material="+globals.currentOrders[i].material_id+"&client="+globals.currentOrders[i].client_id+"&desc="+encodeURIComponent(globals.currentOrders[i].description)+"'><button>Generar</button></a></td>";
		inner_html += "</tr>";
	}
	
	inner_html += "</table>";
	inner_html += "</div>";
	
	$("#all_oc").html(inner_html);
	$("#all_oc").show("slow");
}

function uploadCAFile(file)
{
	var shortname = file.match(/[^\/\\]+$/);
	$("#loadCAImage").show();
	$.getJSON(globals.server_url,
			{
				target: "Analysis",
				method: "ParseCA",
				email: user,      	// "pmata@amro.com",
				password: pass,     // "123",
				filepath: globals.pathToCAUpload + file,		//"/home/pmata/amro/"+shortname
			},
			function(data) {
				$("#loadCAImage").hide();
				if (data.success == true) {
					alert("Archivo parseado exitósamente");
					$("#addCA").hide("slow");
				} else
					alert("Error parseado archivo");
				
			});
}

function getCA()
{
	var vars = getUrlVars();
	
	if (vars.numprobeta == undefined) {
		alert("Elija una orden de compra con su respectivo Nº de probeta para poder realizar la busqueda");
		return;
	}
	
	$.getJSON(globals.server_url,
			{
				target: "Analysis",
				method: "CheckCA",
				email: user,      	// "pmata@amro.com",
				password: pass,     // "123",
				numprobeta: vars.numprobeta
			},
			function(data) {
				if (data.success == true) {
					if(data.CAnalysis.length > 0)
					{				
						inner_html = "<div style='max-height: 150px; overflow: auto;'>";
						inner_html += "<table>";
						inner_html += "<tr class='oc'><th class='oc'>Numero de Probeta</th><th class='oc'>Material</th><th class='oc'>Fecha</th><th class='oc'>Id</th><th class='oc'>Seleccionar</th></tr>";
						
						globals.currentCA = data.CAnalysis;
						
						for(var i=0; i < data.CAnalysis.length; i++)
						{
							var line = "even";
							if( i%2 == 0 ) 
								line = "odd";
							
							inner_html += "<tr class='"+line+"'>";
							inner_html += "<td class='oc'>"+data.CAnalysis[i].numprobeta+"</td>";
							inner_html += "<td>"+materialNameSearch(data.CAnalysis[i].material_id)+"</td>";
							inner_html += "<td>"+data.CAnalysis[i].date+"</td>";
							inner_html += "<td>"+data.CAnalysis[i].id+"</td>";
							inner_html += "<td align='center'><button id='selected_ca' onclick='loadCAValues("+data.CAnalysis[i].id+"); event.preventDefault(); '>seleccionar</button></td>";
							inner_html += "</tr>";
						}
						
						inner_html += "</table>";
						inner_html += "</div>";
						$("#selectedCA").html(inner_html);					
						$("#selectedCA").show("slow");
					}
					else
					{						
						$("#addCA").show("slow");
					}
				}
				else
				{
					alert("Error de Consulta con el Servidor.");
				}
					
			});
}

function loadCAValues(id)
{
	if (globals.currentCA == null) {
		getCA();
		return;
	}
		
	for (var i=0; i < globals.currentCA.length; i++) {
		if (globals.currentCA[i].id == id) {
			$("#_c").val(globals.currentCA[i].chemicalanalysis.c[0]);
			$("#_mn").val(globals.currentCA[i].chemicalanalysis.mn[0]);
			$("#_si").val(globals.currentCA[i].chemicalanalysis.si[0]);
			$("#_p").val(globals.currentCA[i].chemicalanalysis.p[0]);
			$("#_s").val(globals.currentCA[i].chemicalanalysis.s[0]);
			$("#_cr").val(globals.currentCA[i].chemicalanalysis.cr[0]);
			$("#_ni").val(globals.currentCA[i].chemicalanalysis.ni[0]);
			$("#_mo").val(globals.currentCA[i].chemicalanalysis.mo[0]);
			$("#_cu").val(globals.currentCA[i].chemicalanalysis.cu[0]);
			$("#_v").val(globals.currentCA[i].chemicalanalysis.v[0]);
			$("#_ce").val(globals.currentCA[i].chemicalanalysis.ce[0]);
			
			if (globals.currentCA[i].ttreatment_id)
				loadTTfromCA(globals.currentCA[i].ttreatment_id);
		}		
	}
	
	return false;
}

function showMA(mas)
{
	inner_html = "<div style='max-height: 150px; overflow: auto;'>";
	inner_html += "<table>";
	inner_html += "<tr class='oc'><th class='oc'>Fecha</th><th class='oc'>Material</th><th class='oc'>Id</th><th class='oc'>Borrar</th><th class='oc'>Seleccionar</th></tr>";
	
	//globals.currentMA = data.MAnalysis;
	
	for(var i=0; i < mas.length; i++)
	{
		var line = "even";
		if( i%2 == 0 ) 
			line = "odd";
		
		inner_html += "<tr class='"+line+"'>";
		inner_html += "<td class='oc'>"+mas[i].date+"</td>";
		inner_html += "<td>"+materialNameSearch(mas[i].material_id)+"</td>";
		inner_html += "<td>"+mas[i].id+"</td>";
		inner_html += "<td align='center'><button style='background: #e82c2c;' id='delete_ma' onclick='deleteMA("+mas[i].id+"); event.preventDefault(); '>borrar</button></td>";
		inner_html += "<td align='center'><button id='selected_ma' onclick='loadMAValues("+mas[i].id+"); event.preventDefault(); '>seleccionar</button></td>";
		inner_html += "</tr>";
	}
	
	inner_html += "</table>";
	inner_html += "</div>";
	$("#allMA").html(inner_html);					
	$("#allMA").show("slow");
	
}

function deleteMA(id)
{
	$.getJSON(globals.server_url,
			{
				target: "Analysis",
				method: "DeleteMA",
				email: user,      	// "pmata@amro.com",
				password: pass,     // "123",
				id: id
			},
			function(data) {
				if (data.success == true) {
					getMA();
				} else {
					alert("No se pudo borrar el análisis mecánico. Error en el servidor.");
				}
			}
	);
}

function getMA()
{
	var vars = getUrlVars();
	
	$.getJSON(globals.server_url,
			{
				target: "Analysis",
				method: "GetMA",
				email: user,      	// "pmata@amro.com",
				password: pass,     // "123",
				order: "id"
			},
			function(data) {
				if (data.success == true) {
					
					if(data.MAnalysis.length > 0)
					{		
						globals.currentMA = data.MAnalysis;
						showMA(globals.currentMA);						
					}				
				}
				else
				{
					alert("Error de Consulta con el Servidor.");
				}
					
			});
}

function loadMAValues(id)
{
	if (globals.currentMA == null) {
		getMA();
		return;
	}	

	for (var i=0; i < globals.currentMA.length; i++) {
		if (globals.currentMA[i].id == id) {
			$("#tension_rotura").val(globals.currentMA[i].mechanicalanalysis.tension_rotura[0]);
			$("#limite_fluencia").val(globals.currentMA[i].mechanicalanalysis.limite_fluencia[0]);
			$("#alargamiento").val(globals.currentMA[i].mechanicalanalysis.alargamiento[0]);
			$("#estriccion").val(globals.currentMA[i].mechanicalanalysis.estriccion[0]);
			$("#resiliencia").val(globals.currentMA[i].mechanicalanalysis.resiliencia[0]);
			$("#dureza").val(globals.currentMA[i].mechanicalanalysis.dureza[0]);
		}		
	}
	
	return false;
}

function loadMA()
{
	var mecanico = "tension_rotura="+$("#tension_rotura").val()+"+"+
	"limite_fluencia="+$("#limite_fluencia").val()+"+"+
	"alargamiento="+$("#alargamiento").val()+"+"+
	"estriccion="+$("#estriccion").val()+"+"+
	"resiliencia="+$("#resiliencia").val()+"+"+
	"dureza="+$("#dureza").val(); 
		
	var vars = getUrlVars(); 	
	var material = vars.material;
	
	$.getJSON(globals.server_url,	{
		target: "Analysis",
		method: "LoadMA",
		email: user,      	// "pmata@amro.com",
		password: pass,     // "123",
		mechanicalanalysis: mecanico,
		material_id: material				
	},
	function(data) {
		if (data.success == true) {
			alert("Análisis Mecánico guardado con éxito.");
			getMA();
		} else
			alert("Fallo guardando nuevo Análisis Mecánico");
	});
}	

function checkMASaveOpportunity() 
{
	var filled = true;
	$('#formElem').children(':nth-child(3)').find(':input:not(button)').each(function(){
		var $this 		= $(this);
		var valueLength = jQuery.trim($this.val()).length;

		if(valueLength == '')
			filled = false;			 
	});
	
	if (filled) {
		inner_html = '<button id="SaveMA" onclick="loadMA(); event.preventDefault();">Guardar el nuevo Análisis Mecánico</button>';
		$("#showSave").html(inner_html);
		$("#showSave").show("slow");
	}
}

function selectTR(id)
{
	//alert("asd");
	$("#ttermico_selected").val(id);
}

function showTT(ttermicos)
{
	var inner_html = "<div align='center' style='height: 300px; overflow:auto;'>";
	inner_html += "<table style='width:280px;'>";
	inner_html += "<tr class='oc'><th class='oc'>ID</th><th class='oc'>Fecha</th><th class='oc'>Seleccionar</th></tr>";
	
	for(var i=0; i < ttermicos.length; i++)
	{
		var line = "even";
		if( i%2 == 0 ) 
			line = "odd";
		
		inner_html += "<tr class='"+line+"'>";
		inner_html += "<td class='oc'>"+ttermicos[i].id+"</td>";
		inner_html += "<td>"+ttermicos[i].date+"</td>";
		//inner_html += "<td>"+ttermicos[i].observations+"</td>";
		inner_html += "<td align='center'><button float='center' id='view_tt' onclick='viewTT("+ttermicos[i].id+"); selectTR("+ttermicos[i].id+"); event.preventDefault(); '>seleccionar</button></td>";
		inner_html += "</tr>";
	}
	
	inner_html += "</table>";
	inner_html += "</div>";
	$("#all_tt").html(inner_html);
	$("#all_tt_title").show("slow");
	$("#all_tt").show("slow");
	$("#ca_selection").show("slow");
	//$("#new_tt").show("slow");
}

function getTT()
{
	if(globals.currentTTermicos != null && globals.currentTTermicos.length > 0)
		showTTermicos(globals.currentTTermicos);
	
	$.getJSON(server_url,
	{
		target: "TTreatment",
		method: "GetTT",
		email: user,      	// "pmata@amro.com",
		password: pass,		// "123"
	},
	function(data) {
		if(data.success == true)
		{
			globals.currentTTermicos = data.tts;
			showTT(data.tts);
		}
		else
		{
			alert("No se pudieron cargar los tratamientos térmicos. Error con el servidor");
		}
	});
}

function showSelectedTT(tt)
{
	var inner_html = "<div align='center'>";
	inner_html += "<table style='width:280px;'><caption style='font-weight:bold;'>Tratamiento Térmico Asociado a Análisis Químico Seleccionado</caption>";
	inner_html += "<tr class='oc'><th class='oc'>ID</th><th class='oc'>Fecha</th><th class='oc'>Seleccionar</th></tr>";
	
	inner_html += "<tr class='odd'>";
	inner_html += "<td class='oc'>"+tt.id+"</td>";
	inner_html += "<td>"+tt.date+"</td>";
	inner_html += "<td align='center'><button float='center' id='view_tt' onclick='viewTT("+tt.id+"); selectTR("+tt.id+"); event.preventDefault(); '>seleccionar</button></td>";
	inner_html += "</tr>";
		
	inner_html += "</table>";
	inner_html += "</div>";
	
	$("#show_ttermico_asoc").html(inner_html);	
	$("#show_ttermico_asoc").show("slow");
}

function loadTTfromCA(id)
{
	if(globals.currentTTermicos != null && globals.currentTTermicos.length > 0) {
		for (var i = 0;  i < globals.currentTTermicos.length; i++)
			if (globals.currentTTermicos[i].id == id)
				showSelectedTT(globals.currentTTermicos[i]);
		
		return;
	}
		
	
	$.getJSON(server_url,
	{
		target: "TTreatment",
		method: "GetTT",
		email: user,      	// "pmata@amro.com",
		password: pass,     //  "123",
		id: id
	},
	function(data) {
		if(data.success == true && data.tts.length == 1)
		{
			showSelectedTT(data.tts[0]);
		}		
	});
}

