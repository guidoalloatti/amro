var server_url = "http://localhost:8080/?callback=?";

$(document).ready(function() {

	$("#ver_detalles").click(function(event){
		getOCDetails();
		event.preventDefault();
	});
	
	$("#cambiar_ocb").click(function(event){
		cambiarOC();
		event.preventDefault();
	});
	
	$("#upload_file").click(function(event){
		//uploadCAFile();
		getCA();
		event.preventDefault();
	});
});

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

function getOCDetails()
{
	var vars = getUrlVars();
		
	$.getJSON(globals.server_url,
			{
				target: "CSVParsing",
				method: "GetOC",
				email: "pmata@amro.com",
				password: "123",
				id: vars.id,
				order: "ordencompra"
			},
			function(data) {
				if(data.lines.length < 1)
				{
					inner_html = "No se encontro ninguna orden de compra con valor de protocolo "+$("#orden_compra").val();
					$("#ordenes_compra").html(inner_html);
					return;
				}	
					
				var inner_html = "<table><tr class='oc'><th class='oc'>Orden de Compra</th><th class='oc'>Numero de Probeta</th><th class='oc'>Id Cliente</th><th class='oc'>Id Material</th><th class='oc'>Descripcion</th><th class='oc'>Id</th></tr>";
				inner_html += "<tr class='odd'>";
	 			inner_html += "<td class='oc'>"+data.lines[0].ordencompra+"</td>";
				inner_html += "<td>"+data.lines[0].numprobeta+"</td>";
				inner_html += "<td>"+data.lines[0].client_id+"</td>";
				inner_html += "<td>"+data.lines[0].material_id+"</td>";
				inner_html += "<td>"+data.lines[0].description+"</td>";
				inner_html += "<td>"+data.lines[0].id+"</td>";
				//inner_html += "<td align='center'><a href='main.php?invoice_url=ce&numprobeta="+data.lines[i].numprobeta+"&ordencompra="+data.lines[i].ordencompra+"&id="+data.lines[i].id+"'><img src='img/create.gif' alt='Generar Certificadop para Probeta Numero"+data.lines[i].numprobeta+"' width='25px'/></a></td>";
				inner_html += "</tr>";
				inner_html += "</table>";
	
				$("#oc_details").html(inner_html);
				//$("#oc_details").animate({ visibility:'visible' }, 100, function() {});
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

function markSelected(probeta)
{
	alert(probeta);
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
	
	alert(vars.ordencompra);
	
	/*var oc = null;
	for (var i=0; i < globals.allOrders.length; i++) {
		if (globals.allOrders[i].id = vars.id)
			oc = globals.allOrders[i];
	}*/
	
	alert("asñdjflañsjdflñkasjdflñasdjflsjd");
	
	$.getJSON(server_url,
	{	
		target: "Certificate",
		method: "NewCertificate",
		protn: vars.numprobeta,
		email: "pmata@amro.com",
		password: "123",
		ordencompra: vars.ordencompra,
		chemicalanalysis: quimicos,
		mechanicalanalysis: mecanicos,
		approver_id: "1",
		reviewer_id: "1",
		material_id: "1",
		client_id: "4"
	},
	function(data) {
		//getUserList();
		alert(data);
	});	
}

function getOCs()
{
	$.getJSON(globals.server_url,
	{
		target: "CSVParsing",
		method: "GetOC",
		email: "pmata@amro.com",
		password: "123",
		order: "ordencompra"
	},
	function(data) {
		globals.currentOrders = data.lines;
		drawOC();
	});
}

function drawOC()
{
	inner_html = "<div style='height: 150px; overflow: auto;'>";
	inner_html += "<table>";
	inner_html += "<tr class='oc'><th class='oc'>Orden de Compra</th><th class='oc'>Numero de Probeta</th><th class='oc'>Id Cliente</th><th class='oc'>Id Material</th><th class='oc'>Descripcion</th><th class='oc'>Id</th><th class='oc'>Generar Certificado</th></tr>";
	
	if (globals.currentOrders == null)
		return;
	
	alert(globals.currentOrders.length);
	
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
		inner_html += "<td>"+globals.currentOrders[i].client_id+"</td>";
		inner_html += "<td>"+globals.currentOrders[i].material_id+"</td>";
		inner_html += "<td>"+globals.currentOrders[i].description+"</td>";
		inner_html += "<td>"+globals.currentOrders[i].id+"</td>";
		inner_html += "<td align='center'><a href='main.php?invoice_url=ce&numprobeta="+globals.currentOrders[i].numprobeta+"&ordencompra="+globals.currentOrders[i].ordencompra+"&id="+globals.currentOrders[i].id+"'><img src='img/create.gif' alt='Generar Certificadop para Probeta Numero "+globals.currentOrders[i].numprobeta+"' width='25px'/></a></td>";
		inner_html += "</tr>";
	}
	
	inner_html += "</table>";
	inner_html += "</div>";
	
	$("#all_oc").html(inner_html);
}

function uploadCAFile()
{
	$.getJSON(globals.server_url,
			{
				target: "Analysis",
				method: "ParseCA",
				email: "pmata@amro.com",
				password: "123",
				filepath: "/home/pmata/amro/analisis20110412.csv"
			},
			function(data) {
			});
}

function getCA()
{
	var vars = getUrlVars();
	
	$.getJSON(globals.server_url,
			{
				target: "Analysis",
				method: "CheckCA",
				email: "pmata@amro.com",
				password: "123",
				numprobeta: vars.numprobeta
			},
			function(data) {
				if (data.success == true) {
					inner_html = "<div style='height: 150px; overflow: auto;'>";
					inner_html += "<table>";
					inner_html += "<tr class='oc'><th class='oc'>Numero de Probeta</th><th class='oc'>Id Material</th><th class='oc'>Fecha</th><th class='oc'>Id</th><th class='oc'>Seleccionar</th></tr>";
					
					globals.currentCA = data.CAnalysis;
					
					for(var i=0; i < data.CAnalysis.length; i++)
					{
						var line = "even";
						if( i%2 == 0 ) 
						{
							line = "odd";
						}
						
						inner_html += "<tr class='"+line+"'>";
						inner_html += "<td class='oc'>"+data.CAnalysis[i].numprobeta+"</td>";
						inner_html += "<td>"+data.CAnalysis[i].material_id+"</td>";
						inner_html += "<td>"+data.CAnalysis[i].date+"</td>";
						inner_html += "<td>"+data.CAnalysis[i].id+"</td>";
						inner_html += "<td align='center'><button id='selected_ca' onclick='loadCAValues("+data.CAnalysis[i].id+");'>seleccionar</button></td>";
						inner_html += "</tr>";
					}
					
					inner_html += "</table>";
					inner_html += "</div>";
					$("#asdf").html(inner_html);					
				}
				
					
			});
}

function loadCAValues(id)
{
	if (globals.currentCA == null) {
		alert("dasdf");
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
		}		
	}
	
	return false;
}