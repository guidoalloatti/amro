var server_url = "http://localhost:8080/?callback=?";

$(document).ready(function() {

	//getUserList();
	
	$("#ver_detalles").click(function(){
		verDetallesOC();
	});
	
	$("#cambiar_ocb").click(function(){
		cambiarOC();
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

function verDetallesOC()
{
	var inner_html = "<p> Ver como poner detalles </p>";
	$("#ver_detalles").after(inner_html);
}

function cambiarOC()
{
	inner_html = "<p><div style='height: 120px; overflow: auto;'>";
	inner_html = "<table>";
	inner_html = "<tr class='oc'><th class='oc'>Orden de Compra</th><th class='oc'>Numero de Probeta</th><th class='oc'>Id Cliente</th><th class='oc'>Id Material</th><th class='oc'>Descripcion</th><th class='oc'>Id</th><th class='oc'>Generar Certificado</th></tr>";
	for(var i=0; i < allOrders.length; i++)
	{
		var line = "even";
		if( i%2 == 0 ) 
		{
			line = "odd";
		}
		
		inner_html += "<tr class='"+line+"'>";
		inner_html += "<td class='oc'>"+data.lines[i].ordencompra+"</td>";
		inner_html += "<td>"+allOrders[i].numprobeta+"</td>";
		inner_html += "<td>"+allOrders[i].client_id+"</td>";
		inner_html += "<td>"+allOrders[i].material_id+"</td>";
		inner_html += "<td>"+allOrders[i].description+"</td>";
		inner_html += "<td>"+allOrders[i].id+"</td>";
		inner_html += "<td align='center'><a href='main.php?invoice_url=ce&numprobeta="+allOrders[i].numprobeta+"&ordencompra="+data.lines[i].ordencompra+"'><img src='img/create.gif' alt='Generar Certificadop para Probeta Numero"+allOrders[i].numprobeta+"' width='25px'/></a></td>";
		//inner_html += "<td><a href='main.php?invoice_url=ce&numprobeta="+data.lines[i].numprobeta+"&ordencompra="+data.lines[i].ordencompra+"'>Generar Certificado Para "+data.lines[i].numprobeta+"</a></td>";
		inner_html += "</tr>";
	}
	inner_html = "</table>";
	inner_html += "</div></p>";
	
	$("#cambiar_ocb").after(inner_html);
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
	for (var i=0; i < allOrders.length; i++) {
		if (allOrders[i].id = vars.id)
			oc = allOrders[i];
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
