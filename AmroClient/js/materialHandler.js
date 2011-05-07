// Global Variables Definitions

$(document).ready(function() {

	getMaterialList();

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

// Funciones de Manejo de Clientes
function newMaterial()
{
	$("#name").val("");
	$("#carbono").val("");
	$("#cromo").val("");
	$("#manganeso").val("");
	$("#silicio").val("");
	$("#fosforo").val("");
	$("#azufre").val("");
	$("#niquel").val("");
	$("#molibdeno").val("");
	$("#cobre").val("");
	$("#vanadio").val("");
	$("#ce").val("");
	$("#tension_rotura").val("");
	$("#limite_fluencia").val("");
	$("#alargamiento").val("");
	$("#estriccion").val("");
	$("#resiliencia").val("");
	$("#dureza").val("");
}
	
function loadMaterial(name, id)
{
	getMaterial(id, name);
}

function insertMaterial()
{
	
	var quimicos = 	"c:"+$("#carbono").val()+"+"+
					"mn:"+$("#manganeso").val()+"+"+
					"si:"+$("#silicio").val()+"+"+
					"p:"+$("#fosforo").val()+"+"+
					"s:"+$("#azufre").val()+"+"+
					"cr:"+$("#cromo").val()+"+"+
					"ni:"+$("#niquel").val()+"+"+
					"mo:"+$("#molibdeno").val()+"+"+
					"cu:"+$("#cobre").val()+"+"+
					"v:"+$("#vanadio").val()+"+"+
					"ce:"+$("#ce").val();	

	var mecanicos = "tension_rotura:"+$("#tension_rotura").val()+"+"+
					"limite_fluencia:"+$("#limite_fluencia").val()+"+"+
					"alargamiento:"+$("#alargamiento").val()+"+"+
					"estriccion:"+$("#estriccion").val()+"+"+
					"resiliencia:"+$("#resiliencia").val()+"+"+
					"dureza:"+$("#dureza").val();
	
	$.getJSON("http://localhost:8080/?callback=?",
	{	
		target: "Material",
		method: "NewMaterial",
		name: $("#name").val(),
		chlimits: quimicos,
		mlimits: mecanicos,
		email: "pmata@amro.com",
		password: "123",
	},
	function(data) {
		getMateriaList();
	});
}

function updateMaterial()
{

		var quimicos = 	"c:"+$("#carbono").val()+"+"+
					"mn:"+$("#manganeso").val()+"+"+
					"si:"+$("#silicio").val()+"+"+
					"p:"+$("#fosforo").val()+"+"+
					"s:"+$("#azufre").val()+"+"+
					"cr:"+$("#cromo").val()+"+"+
					"ni:"+$("#niquel").val()+"+"+
					"mo:"+$("#molibdeno").val()+"+"+
					"cu:"+$("#cobre").val()+"+"+
					"v:"+$("#vanadio").val()+"+"+
					"ce:"+$("#ce").val();	

	var mecanicos = "tension_rotura:"+$("#tension_rotura").val()+"+"+
					"limite_fluencia:"+$("#limite_fluencia").val()+"+"+
					"alargamiento:"+$("#alargamiento").val()+"+"+
					"estriccion:"+$("#estriccion").val()+"+"+
					"resiliencia:"+$("#resiliencia").val()+"+"+
					"dureza:"+$("#dureza").val();

	$.getJSON("http://localhost:8080/?callback=?",
	{
		target: "Material",
		method: "UpdateMaterial",
		name: $("#name").val(),
		chlimits: quimicos,
		mlimits: mecanicos,
		email: "pmata@amro.com",
		password: "123",
	},
	function(data) {
	});
}

function getMaterialList()
{
	getMaterials();
}

function getMaterial(id, name)
{
	$.getJSON("http://localhost:8080/?callback=?",
	{
		target: "Material",
		method: "GetMaterial",
		name: name,
		id: id,
		email: "pmata@amro.com",
		password: "123"
	},
	function(data) {
		if(data.materials.length > 1)
			alert("Error en la cantidad de materiales, no se puede especificar el material seleccionado");
		else	
		{
			$("#name").val(data.materials[0].name);
			
			
			
			
			$("#material_seleccionado_name").html(data.material[0].name);
			$("#material_seleccionado_id").html(data.material[0].id);
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
	$.getJSON("http://localhost:8080/?callback=?",
	{
		target: "Material",
		method: "GetMaterial",
		email: "pmata@amro.com",
		password: "123"
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
	$.getJSON("http://localhost:8080/?callback=?",
	{
		target: "Material",
		method: "DeleteMaterial",
		email: "pmata@amro.com",
		password: "123",
		id: id,
	},
	function(data) {
		console.log("Se elimino material "+name+" con id "+id);
		getMateriasList();
	});
}

function reloadMaterial()
{
	getMaterial( $("#material_seleccionado_id").html(), $("#material_seleccionado_name").html() );
}

