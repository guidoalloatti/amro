// Global Variables Definitions
//var server_url = "http://192.168.1.101:8080/?callback=?";
//var server_url = server_url;
var server_url = "http://localhost:8080/?callback=?";
var user = $.cookie("user");
var pass = $.cookie("pass");

$(document).ready(function() {

	$("#guardar_material").click(function(){
		insertMaterial();
	});
	
	$("#recargar_lista_materiales").click(function(){
		getMaterialList();
	});
	
	$("#nuevo_material").click(function(){
		newMaterial();
	});
	
	$("#recargar_material").click(function(){
		reloadMaterial();
	});
	
	$("#actualizar_material").click(function(){
		updateMaterial();
	});
	
});

function materialStart()
{
	if(user == null || pass == null)
		doGetSessionVars();
	getMaterialList();
}

// Funciones de Manejo de Clientes
function newMaterial()
{
	$("#name").val("");
	
	$("#carbono_max").val("");
	$("#cromo_max").val("");
	$("#manganeso_max").val("");
	$("#silicio_max").val("");
	$("#fosforo_max").val("");
	$("#azufre_max").val("");
	$("#niquel_max").val("");
	$("#molibdeno_max").val("");
	$("#cobre_max").val("");
	$("#vanadio_max").val("");
	$("#ce_max").val("");
	
	$("#carbono_min").val("");
	$("#cromo_min").val("");
	$("#manganeso_min").val("");
	$("#silicio_min").val("");
	$("#fosforo_min").val("");
	$("#azufre_min").val("");
	$("#niquel_min").val("");
	$("#molibdeno_min").val("");
	$("#cobre_min").val("");
	$("#vanadio_min").val("");
	$("#ce_min").val("");
	
	$("#tension_rotura_max").val("");
	$("#limite_fluencia_max").val("");
	$("#alargamiento_max").val("");
	$("#estriccion_max").val("");
	$("#resiliencia_max").val("");
	$("#dureza_max").val("");
	
	$("#tension_rotura_min").val("");
	$("#limite_fluencia_min").val("");
	$("#alargamiento_min").val("");
	$("#estriccion_min").val("");
	$("#resiliencia_min").val("");
	$("#dureza_min").val("");
}
	
function loadMaterial(name, id)
{
	getMaterial(id, name);
}

function insertMaterial()
{
	
	var quimicos = 	"c="+$("#carbono_max").val()+"-"+$("#carbono_min").val()+"+"+
					"mn="+$("#manganeso_max").val()+"-"+$("#manganeso_min").val()+"+"+
					"si="+$("#silicio_max").val()+"-"+$("#silicio_min").val()+"+"+
					"p="+$("#fosforo_max").val()+"-"+$("#fosforo_min").val()+"+"+
					"s="+$("#azufre_max").val()+"-"+$("#azufre_min").val()+"+"+
					"cr="+$("#cromo_max").val()+"-"+$("#cromo_min").val()+"+"+
					"ni="+$("#niquel_max").val()+"-"+$("#niquel_min").val()+"+"+
					"mo="+$("#molibdeno_max").val()+"-"+$("#molibdeno_min").val()+"+"+
					"cu="+$("#cobre_max").val()+"-"+$("#cobre_min").val()+"+"+
					"v="+$("#vanadio_max").val()+"-"+$("#vanadio_min").val()+"+"+
					"ce="+$("#ce_max").val()+"-"+$("#ce_min").val();	

	var mecanicos = "tension_rotura="+$("#tension_rotura_max").val()+"-"+$("#tension_rotura_min").val()+"+"+
					"limite_fluencia="+$("#limite_fluencia_max").val()+"-"+$("#limite_fluencia_min").val()+"+"+
					"alargamiento="+$("#alargamiento_max").val()+"-"+$("#alargamiento_min").val()+"+"+
					"estriccion="+$("#estriccion_max").val()+"-"+$("#estriccion_min").val()+"+"+
					"resiliencia="+$("#resiliencia_max").val()+"-"+$("#resiliencia_min").val()+"+"+
					"dureza="+$("#dureza_max").val()+"-"+$("#dureza_min").val();
					
	$.getJSON(server_url,
	{	
		target: "Material",
		method: "NewMaterial",
		name: $("#name").val(),
		chlimits: quimicos,
		mlimits: mecanicos,
		email: user, 			// "pmata@amro.com",
		password: pass,			// "123",
		//id: id,
	},
	function(data) {
		getMaterialList();
		newMaterial();
	});
}

function updateMaterial()
{

	if($("#material_seleccionado_id").html() == "")
	{
		alert("No esta definido el id del material.");
		return;
	}

	var quimicos = 	"c="+$("#carbono_max").val()+"-"+$("#carbono_min").val()+"+"+
					"mn="+$("#manganeso_max").val()+"-"+$("#manganeso_min").val()+"+"+
					"si="+$("#silicio_max").val()+"-"+$("#silicio_min").val()+"+"+
					"p="+$("#fosforo_max").val()+"-"+$("#fosforo_min").val()+"+"+
					"s="+$("#azufre_max").val()+"-"+$("#azufre_min").val()+"+"+
					"cr="+$("#cromo_max").val()+"-"+$("#cromo_min").val()+"+"+
					"ni="+$("#niquel_max").val()+"-"+$("#niquel_min").val()+"+"+
					"mo="+$("#molibdeno_max").val()+"-"+$("#molibdeno_min").val()+"+"+
					"cu="+$("#cobre_max").val()+"-"+$("#cobre_min").val()+"+"+
					"v="+$("#vanadio_max").val()+"-"+$("#vanadio_min").val()+"+"+
					"ce="+$("#ce_max").val()+"-"+$("#ce_min").val();	

	var mecanicos = "tension_rotura="+$("#tension_rotura_max").val()+"-"+$("#tension_rotura_min").val()+"+"+
					"limite_fluencia="+$("#limite_fluencia_max").val()+"-"+$("#limite_fluencia_min").val()+"+"+
					"alargamiento="+$("#alargamiento_max").val()+"-"+$("#alargamiento_min").val()+"+"+
					"estriccion="+$("#estriccion_max").val()+"-"+$("#estriccion_min").val()+"+"+
					"resiliencia="+$("#resiliencia_max").val()+"-"+$("#resiliencia_min").val()+"+"+
					"dureza="+$("#dureza_min").val()+"-"+$("#dureza_min").val();

	$.getJSON(server_url,
	{
		target: "Material",
		method: "UpdateMaterial",
		name: $("#name").val(),
		chlimits: quimicos,
		mlimits: mecanicos,
		email: user,			// "pmata@amro.com",
		password: pass,			//"123",
		id: $("#material_seleccionado_id").html(),
	},
	function(data) {
		//alert( $("#material_seleccionado_id").html());
	});
}

function getMaterialList()
{
	getMaterials();
}

function getMaterial(id, name)
{
	$.getJSON(server_url,
	{
		target: "Material",
		method: "GetMaterial",
		name: name,
		id: id,
		email: user,			// "pmata@amro.com",
		password: pass,			// "123"
	},
	function(data) {
		if(data.materials.length > 1)
			alert("Error en la cantidad de materiales, no se puede especificar el material seleccionado");
		else	
		{
			// Name and Id
			$("#name").val(data.materials[0].name);
			$("#material_seleccionado_name").html(data.materials[0].name);
			$("#material_seleccionado_id").html(data.materials[0].id);
			
			// Quimicos
			$("#carbono_max").val(data.materials[0].chlimits.c[0]);
			$("#carbono_min").val(data.materials[0].chlimits.c[1]);
			$("#manganeso_max").val(data.materials[0].chlimits.mn[0]);
			$("#manganeso_min").val(data.materials[0].chlimits.mn[1]);
			$("#silicio_max").val(data.materials[0].chlimits.si[0]);
			$("#silicio_min").val(data.materials[0].chlimits.si[1]);
			$("#fosforo_max").val(data.materials[0].chlimits.p[0]);
			$("#fosforo_min").val(data.materials[0].chlimits.p[1]);
			$("#azufre_max").val(data.materials[0].chlimits.s[0]);
			$("#azufre_min").val(data.materials[0].chlimits.s[1]);
			$("#cromo_max").val(data.materials[0].chlimits.cr[0]);
			$("#cromo_min").val(data.materials[0].chlimits.cr[1]);
			$("#niquel_max").val(data.materials[0].chlimits.ni[0]);
			$("#niquel_min").val(data.materials[0].chlimits.ni[1]);
			$("#molibdeno_max").val(data.materials[0].chlimits.mo[0]);
			$("#molibdeno_min").val(data.materials[0].chlimits.mo[1]);			
			$("#cobre_max").val(data.materials[0].chlimits.cu[0]);
			$("#cobre_min").val(data.materials[0].chlimits.cu[1]);			
			$("#vanadio_max").val(data.materials[0].chlimits.v[0]);
			$("#vanadio_min").val(data.materials[0].chlimits.v[1]);			
			$("#ce_max").val(data.materials[0].chlimits.ce[0]);
			$("#ce_min").val(data.materials[0].chlimits.ce[1]);
			
			// Mecanicos
			$("#tension_rotura_max").val(data.materials[0].mlimits.tension_rotura[0]);
			$("#tension_rotura_min").val(data.materials[0].mlimits.tension_rotura[1]);
			$("#limite_fluencia_max").val(data.materials[0].mlimits.limite_fluencia[0]);
			$("#limite_fluencia_min").val(data.materials[0].mlimits.limite_fluencia[1]);
			$("#alargamiento_max").val(data.materials[0].mlimits.alargamiento[0]);
			$("#alargamiento_min").val(data.materials[0].mlimits.alargamiento[1]);
			$("#estriccion_max").val(data.materials[0].mlimits.estriccion[0]);
			$("#estriccion_min").val(data.materials[0].mlimits.estriccion[1]);
			$("#resiliencia_max").val(data.materials[0].mlimits.resiliencia[0]);
			$("#resiliencia_min").val(data.materials[0].mlimits.resiliencia[1]);
			$("#dureza_max").val(data.materials[0].mlimits.dureza[0]);
			$("#dureza_min").val(data.materials[0].mlimits.dureza[1]);
		}	
	});
}

function deleteMaterialConfirmation(name, id)
{
	if(confirm("Esta a punto de eliminar el material "+name))
	{
		deleteMaterial(id, name);
	}
}

function getMaterials()
{
	$.getJSON(server_url,
	{
		target: "Material",
		method: "GetMaterial",
		email: user,			// "pmata@amro.com",
		password: pass,			// "123"
	},
	function(data) {
		var inner_html = "<table><tr><th>Material</th><th>Eliminar</th></tr><tr>"
		
		for(i = 0; i < data.materials.length; i++)
		{	
			inner_html += "<td><a href='#' id='material_"+data.materials[i].id+"' onclick='loadMaterial(\""+data.materials[i].name+"\", \""+data.materials[i].id+"\");'>"+data.materials[i].name+"</a></td>";
			inner_html += "<td align='center'><img src='img/delete.png' width='20' heigth='20' alt='Eliminar' title='Eliminar' onclick='deleteMaterialConfirmation(\""+data.materials[i].name+"\", \""+data.materials[i].id+"\");' /></td></tr>";
		}
		$("#material_list").html(inner_html);
		$("#materiales_totales").html("Cantidad de Materiales: "+data.materials.length);
		$("#material_seleccionado").html("<h4>Ninguno...</h4>");
	});
}

function deleteMaterial(id, name)
{
	$.getJSON(server_url,
	{
		target: "Material",
		method: "DeleteMaterial",
		email: user,				// "pmata@amro.com",
		password: pass,				// "123",
		id: id,
	},
	function(data) {
		console.log("Se elimino material "+name+" con id "+id);
		getMaterialList();
	});
}

function reloadMaterial()
{
	getMaterial( $("#material_seleccionado_id").html(), $("#material_seleccionado_name").html() );
}

