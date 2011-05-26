var selectedCA = null;
var selectedTT = null;

$(document).ready(function() {
	$("#link_tt").hide();
	$("#all_tt").hide();	
	
	$("#new_tt").hide();
	
	$("#selected_params").hide();
	
	
	//$("#tt_image").hide();
	

	
	$("#ca_selection").hide();
	$("#all_ca").hide();	

	$("#select_ca_button").click(function(event){
		inner_html = "<div style='height: 200px; overflow:auto;'>";
		inner_html += "<div id='current_ca_selected' style='max-height: 200px; overflow:auto;'>";
		inner_html += "</div>";
		inner_html += "<div id='current_tt_selected' style='max-height: 200px; overflow:auto;'>";
		inner_html += "</div>";
		inner_html += "<button id='link_tt_button'>Asociar</button>";					
		inner_html += "</div>";		
		
		$("#selected_params").html(inner_html);
		$("#link_tt").show("slow");		
		
		$("#link_tt_button").hide();
		$("#link_tt_button").click(function(event) {
			linkTT();
			event.preventDefault();
		});		
		
		event.preventDefault();
	});
});

function prepareTTAbm()
{
	prepareTT();
	prepareCA();
}

function selectTT(id)
{
	var tt = null;
	
	for (var i = 0; i < globals.currentTTermicos.length; i++) 
		if (globals.currentTTermicos[i].id == id)
			tt = globals.currentTTermicos[i];
	
	if (tt == null)
		return;
	
	var inner_html = "<table>";
	inner_html += "<caption>Tratamientos Térmico Seleccionado</caption>";
	inner_html += "<tr class='oc'><th class='oc'>ID</th><th class='oc'>Fecha</th><th class='oc'>Descripción</th><th class='oc'>Id</th><th class='oc'>Borrar</th><th class='oc'>Seleccionar</th></tr>";
	inner_html += "<tr class='even'>";
	inner_html += "<td class='oc'>"+tt.id+"</td>";
	inner_html += "<td>"+tt.date+"</td>";
	inner_html += "<td>"+tt.observations+"</td>";
	inner_html += "</tr>";
	inner_html += "</table><br/>";
	
	$("#current_tt_selected").html(inner_html);
	$("#selected_params").show("slow");		
	$("#current_tt_selected").show("slow");
	
	if ($("#current_ca_selected").html() != "")
		$("#link_tt_button").show("slow");
	
	selectedTT = tt;	
	
	var html = "<div style='align: center;'><img src='img/imagen_espectro.png' style='align: center; width: 400px; height: 300px;'></img></div>";
	$("#tt_viewer").html(html);
	$("#tt_viewer").show("slow");		
}

function deleteTT(id)
{
	$.getJSON(server_url,
			{
				target: "TTreatment",
				method: "DeleteTT",
				email: "pmata@amro.com",
				password: "123",
				id: id					
			},
			function(data) {
				if (data.success == true) {
					for (var i = 0; i < globals.currentTTermicos.length; i++) 
						if (globals.currentTTermicos[i].id == id)
							globals.currentTTermicos.splice(i, 1);
					
					showTTermicos(globals.currentTTermicos);
				} else
					alert("No se pudo borrar. Error en el servidor");					
			}
	);
			
} 

function showTTermicos(ttermicos)
{
	var inner_html = "<div style='max-height: 200px; overflow:auto;'>";
	inner_html += "<table>";
	inner_html += "<tr class='oc'><th class='oc'>ID</th><th class='oc'>Fecha</th><th class='oc'>Observaciones</th><th class='oc'>Borrar</th><th class='oc'>Seleccionar</th></tr>";
	
	for(var i=0; i < ttermicos.length; i++)
	{
		var line = "even";
		if( i%2 == 0 ) 
			line = "odd";
		
		inner_html += "<tr class='"+line+"'>";
		inner_html += "<td class='oc'>"+ttermicos[i].id+"</td>";
		inner_html += "<td>"+ttermicos[i].date+"</td>";
		inner_html += "<td>"+ttermicos[i].observations+"</td>";
		inner_html += "<td align='center'><button id='delete_tt' onclick='deleteTT("+ttermicos[i].id+"); event.preventDefault(); '>borrar</button></td>";
		inner_html += "<td align='center'><button id='selected_tt' onclick='selectTT("+ttermicos[i].id+"); event.preventDefault(); '>seleccionar</button></td>";
		inner_html += "</tr>";
	}
	
	inner_html += "</table>";
	inner_html += "</div>";
	$("#all_tt").html(inner_html);	
	$("#all_tt").show("slow");
	$("#ca_selection").show("slow");
	$("#tt_viewer").show("slow");
	$("#new_tt").show("slow");
}



function prepareTT()
{
	if(globals.currentTTermicos != null && globals.currentTTermicos.length > 0)
		showTTermicos(globals.currentTTermicos);
	
	$.getJSON(server_url,
	{
		target: "TTreatment",
		method: "GetTT",
		email: "pmata@amro.com",
		password: "123"
	},
	function(data) {
		if(data.success == true && data.tts.length > 0)
		{
			globals.currentTTermicos = data.tts;
			showTTermicos(data.tts);
		}
		else
		{
			alert("No se pudieron cargar los tratamientos térmicos. Error con el servidor");
		}
	});
}

function selectCA(id)
{
	var ca = null;
	
	for (var i = 0; i < globals.currentCA.length; i++) 
		if (globals.currentCA[i].id == id)
			ca = globals.currentCA[i];	
	
	if (ca == null)
		return;
	
	var inner_html = "<table>";
	inner_html += "<caption>Análisis Químico Seleccionado</caption>";
	inner_html += "<tr class='oc'><th class='oc'>Numero de Probeta</th><th class='oc'>Material</th><th class='oc'>Fecha</th><th class='oc'>Id</th>";
	inner_html += "<tr class='odd'>";
	inner_html += "<td class='oc'>"+ca.numprobeta+"</td>";
	inner_html += "<td>"+materialNameSearch(ca.material_id)+"</td>";
	inner_html += "<td>"+ca.date+"</td>";
	inner_html += "<td>"+ca.id+"</td>";
	inner_html += "</tr>";
	inner_html += "</table><br/>";
	
	$("#current_ca_selected").html(inner_html);	
	$("#selected_params").show("slow");		

	$("#current_ca_selected").show("slow");
	
	if ($("#current_tt_selected").html() != "")
		$("#link_tt_button").show("slow");
	
	selectedCA = ca;
}

function prepareCA()
{
	if(globals.currentCA != null && globals.currentCA.length > 0)
		showCA(globals.currentCA);
	
	$.getJSON(server_url,
	{
		target: "Analysis",
		method: "CheckCA",
		email: "pmata@amro.com",
		password: "123"
	},
	function(data) {
		if (data.success == true) {
			if(data.CAnalysis.length > 0)
			{				
				var inner_html = "<div style='max-height: 200px; overflow: auto;'>";
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
					inner_html += "<td align='center'><button id='selected_ca' onclick='selectCA("+data.CAnalysis[i].id+"); event.preventDefault(); '>seleccionar</button></td>";
					inner_html += "</tr>";
				}
				
				inner_html += "</table></div>";
				$("#all_ca").html(inner_html);
				$("#all_ca").show("slow");
			}			
		}
		else
		{
			alert("Error de Consulta con el Servidor.");
		}
	});
}

function linkTT()
{
	if (selectedCA == null) {
		alert("Por favor, seleccionar un análisis químico.");
		return;
	}
	
	if (selectedTT == null) {
		alert("Por favor, seleccionar un tratamiento térmico.");
		return;
	}
	
	$.getJSON(server_url,
			{
				target: "Analysis",
				method: "AttachTT",
				email: "pmata@amro.com",
				password: "123",
				ttreatment_id: selectedTT.id,
				id: selectedCA.id
			},
			function(data) {
				if (data.success == true)
					alert("La operación se realizó con éxito");
				else
					alert("La operación falló, error en el servidor");
			}
		);		
}