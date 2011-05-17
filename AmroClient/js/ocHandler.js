
$(document).ready(function() {
	loadOCPage();
	
	$("#cargar_ocs").click(function(){
		getAllOC();
	});
	
});

function loadOCPage()
{
	loadClients();
	loadMaterials();
	//loadOC();
}

function searchOC()
{
	alert("Buscando OC cliente "+$("#select_cliente").val()+
		  "\ncon el material "+$("#select_material").val()+
		  "\ny con orden de compra con valor "+$("#protocolo").val());
}

function loadClients()
{
	$.getJSON(server_url,
	{
		target: "Client",
		method: "GetClient",
		email: "pmata@amro.com",
		password: "123"
	},
	function(data) {
		var inner_html = "<select name='select_cliente' id='select_cliente'><option>Todos los Clientes</option>";
		for(i = 0; i < data.clients.length; i++)
		{
			inner_html += "<option>"+data.clients[i].name+"</option>";
		}
		inner_html += "</select>";	
			
		$("#clientes").replaceWith(inner_html);
		
		/*
		inner_html += "<td><a href='#' id='client_"+data.clients[i].id+"' onclick='loadClient(\""+data.clients[i].name+"\", \""+data.clients[i].id+"\");'>"+data.clients[i].name+"</a></td>";
		inner_html += "<td>"+data.clients[i].address+"</td>";
		inner_html += "<td align='center'><img src='img/edit.png' width='20' heigth='20' alt='Editar' title='Editar' /></td>";
		inner_html += "<td align='center'><img src='img/delete.png' width='20' heigth='20' alt='Eliminar' title='Eliminar' onclick='deleteClientConfirmation(\""+data.clients[i].name+"\", \""+data.clients[i].id+"\");' /></td></tr>";	
		$("#clientes_totales").html("Cantidad de Clientes: "+data.clients.length);
		$("#cliente_seleccionado").html("<h4>Ninguno...</h4>");
		*/
	});
}

function loadMaterials()
{
	$.getJSON(server_url,
	{
		target: "Material",
		method: "GetMaterial",
		email: "pmata@amro.com",
		password: "123"
	},
	function(data) {
		var inner_html = "<select name='select_material' id='select_material'><option>Todos los Materiales</option>";
		for(i = 0; i < data.materials.length; i++)
		{
			inner_html += "<option>"+data.materials[i].name+"</option>";
		}
		inner_html += "</select>";	
			
		$("#materiales").replaceWith(inner_html);
			
		//$("#clientes_totales").html("Cantidad de Clientes: "+data.clients.length);
		//$("#cliente_seleccionado").html("<h4>Ninguno...</h4>");
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
		var inner_html = "<tr class='oc'><th class='oc'>Orden de Compra</th><th class='oc'>Numero de Probeta</th><th class='oc'>Id Cliente</th><th class='oc'>Id Material</th><th class='oc'>Descripcion</th><th class='oc'>Id</th></tr>";
		for(var i=0; i < data.lines.length; i++)
		{
			var line = "even";
			if( i%2 == 0 ) 
			{
				line = "odd";
			}
				
			inner_html += "<tr class='"+line+"'>";
 			inner_html += "<td class='oc'>"+data.lines[i].ordencompra+"</td>";
			inner_html += "<td>"+data.lines[i].numprobeta+"</td>";
			inner_html += "<td>"+data.lines[i].client_id+"</td>";
			inner_html += "<td>"+data.lines[i].material_id+"</td>";
			inner_html += "<td>"+data.lines[i].description+"</td>";
			inner_html += "<td>"+data.lines[i].id+"</td>";
			inner_html += "<td><a href='main.php?invoice_url=ce&numprobeta="+data.lines[i].numprobeta+"&ordencompra="+data.lines[i].ordencompra+"'>Generar Certificado Para "+data.lines[i].numprobeta+"</a></td>";
			inner_html += "</tr>";
			
			//inner_html += data.lines[i].ordencompra+"\n";
			//inner_html += data.lines[i].numprobeta;
			
		}	
		$("#ordenes_compra").html(inner_html);
		console.log(data);
		//html_code += dump(data);
		//$("#html_change").replaceWith(html_code);				
	});
}	