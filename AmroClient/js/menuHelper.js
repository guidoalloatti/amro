function hideAll()
{
	$("#crear_certificado_img").hide();
}


$(document).ready(function() {

	hideAll();

    /* Mouseover Actions */
    $("#btn_green").mouseover(function() {
        //$("#btn_green").effect("size", { to: {width: 300,height: 120} }, 1000);
    });

    $("#btn_red").mouseover(function() {
       // alert("Gui 1");
    });

    $("#btn_gray").mouseover(function() {
        //alert("Gui 3");
    });

    $("#btn_blue").mouseover(function() {
        //alert("Gui 3");
    });

    /* Click Actions */
    $("#btn_green").click(function() { // Certificados
        var url = "main.php?invoice_url=ce";
        $(location).attr('href',url);
    });

    $("#btn_red").click(function() { // Ordenes de Compra
        var url = "main.php?invoice_url=oc";
        $(location).attr('href',url);
    });

    $("#btn_blue").click(function() { // ABMS
		var url = "main.php?invoice_url=ab";
        $(location).attr('href',url);
	});

    $("#btn_gray").click(function() {
		var url = "main.php?invoice_url=UNDEF";
        $(location).attr('href',url);
	});

    $("#btn_yellow").click(function() {
		var url = "main.php?invoice_url=pe";
        $(location).attr('href',url);
	});	
	
	$("#btn_orange").click(function() { // Principal
	    var url = "main.php?invoice_url=pr";
        $(location).attr('href',url);
    });
	
	$("#btn_orange_1").click(function() { // Gestion Certificados
	    var url = "main.php?invoice_url=cm";
        $(location).attr('href',url);
    });
	
	// Click en botones de ABM
	$("#btn_cliente_green").click(function() { // Abm Clientes
		var url = "main.php?invoice_url=abm&module=cliente";
        $(location).attr('href',url);
    });
	
	$("#btn_usuarios_red").click(function() { // Abm Usuarios
		var url = "main.php?invoice_url=abm&module=usuario";
        $(location).attr('href',url);
    });
	
	$("#btn_materiales_gray").click(function() { // Abm Clientes
		var url = "main.php?invoice_url=abm&module=material";
        $(location).attr('href',url);
    });
	
	$("#btn_ttermico_blue").click(function() { // Abm Tratamiento Termico
		var url = "main.php?invoice_url=abm&module=ttermico";
        $(location).attr('href',url);
    });
	


	// Botones del menu principal
	$("#menu_button_generar_certificado").mouseover(function(){
		$("#image_div").hide();
		$("#image_div").html('<img id="crear_certificado_img" width="450" src="img/creacion_certificados.png"></img>');
		$("#image_div").show("slow");
	});
	
	$("#menu_button_generar_certificado").mouseout(function (){
		$("#image_div").show("slow");
		$("#image_div").html('<img id="crear_certificado_img" width="450" src="img/creacion_certificados.png"></img>');
		//$("#image_div").hide("slow");
	});

	$("#menu_button_administrar_abm").mouseover(function(){
		$("#image_div").hide();
		$("#image_div").html('<img id="crear_certificado_img" width="450" src="img/altas_bajas_modificaciones.png"></img>');
		$("#image_div").show("slow");
	});
	
	$("#menu_button_administrar_abm").mouseout(function (){
		$("#image_div").show("slow");
		$("#image_div").html('<img id="crear_certificado_img" width="450" src="img/altas_bajas_modificaciones.png"></img>');
		//$("#image_div").hide("slow");
	});

	$("#menu_button_administrar_certificados").mouseover(function(){
		$("#image_div").hide();
		$("#image_div").html('<img id="crear_certificado_img" width="450" src="img/administracion_certificados.png"></img>');
		$("#image_div").show("slow");
	});
	
	$("#menu_button_administrar_certificados").mouseout(function (){
		$("#image_div").show("slow");
		$("#image_div").html('<img id="crear_certificado_img" width="450" src="img/administracion_certificados.png"></img>');
		//$("#image_div").hide("slow");
	});

	$("#menu_button_orden_compra").mouseover(function(){
		$("#image_div").hide();
		$("#image_div").html('<img id="crear_certificado_img" width="450" src="img/administracion_ordenes_compra.png"></img>');
		$("#image_div").show("slow");
	});
	
	$("#menu_button_orden_compra").mouseout(function (){
		$("#image_div").show("slow");
		$("#image_div").html('<img id="crear_certificado_img" width="450" src="img/administracion_ordenes_compra.png"></img>');
		//$("#image_div").hide("slow");
	});
	
	$("#menu_button_permisos").mouseover(function(){
		$("#image_div").hide();
		$("#image_div").html('<img id="crear_certificado_img" width="450" src="img/gestionar_permisos_usuarios.png"></img>');
		$("#image_div").show("slow");
	});
	
	$("#menu_button_permisos").mouseout(function (){
		$("#image_div").show("slow");
		$("#image_div").html('<img id="crear_certificado_img" width="450" src="img/gestionar_permisos_usuarios.png"></img>');
		//$("#image_div").hide("slow");
	});	
	
	$("#menu_button_abm_cliente").mouseover(function(){
		$("#image_div").hide();
		$("#image_div").html('<img id="crear_certificado_img" width="450" src="img/abm_clientes.png"></img>');
		$("#image_div").show("slow");
	});
	
	$("#menu_button_abm_cliente").mouseout(function (){
		$("#image_div").show("slow");
		$("#image_div").html('<img id="crear_certificado_img" width="450" src="img/abm_clientes.png"></img>');
		//$("#image_div").hide("slow");
	});	
	
	$("#menu_button_abm_usuario").mouseover(function(){
		$("#image_div").hide();
		$("#image_div").html('<img id="crear_certificado_img" width="450" src="img/abm_usuarios.png"></img>');
		$("#image_div").show("slow");
	});
	
	$("#menu_button_abm_usuario").mouseout(function (){
		$("#image_div").show("slow");
		$("#image_div").html('<img id="crear_certificado_img" width="450" src="img/abm_usuarios.png"></img>');
		//$("#image_div").hide("slow");
	});
	
	$("#menu_button_abm_ttermico").mouseover(function(){
		$("#image_div").hide();
		$("#image_div").html('<img id="crear_certificado_img" width="450" src="img/abm_ttermico.png"></img>');
		$("#image_div").show("slow");
	});
	
	$("#menu_button_abm_ttermico").mouseout(function (){
		$("#image_div").show("slow");
		$("#image_div").html('<img id="crear_certificado_img" width="450" src="img/abm_ttermico.png"></img>');
		//$("#image_div").hide("slow");
	});
	
	$("#menu_button_abm_materiales").mouseover(function(){
		$("#image_div").hide();
		$("#image_div").html('<img id="crear_certificado_img" width="450" src="img/abm_material.png"></img>');
		$("#image_div").show("slow");
	});
	
	$("#menu_button_abm_materiales").mouseout(function (){
		$("#image_div").show("slow");
		$("#image_div").html('<img id="crear_certificado_img" width="450" src="img/abm_material.png"></img>');
		//$("#image_div").hide("slow");
	});
	
	
	
	
	
	
});




/*
$(document).ready(function(){ 
	$("ul.thumb li").hover(function() {
		$(this).css({'z-index' : '10'});
		$(this).find('img').addClass("hover").stop()
			.animate({
				marginTop: '-110px', 
				marginLeft: '-110px', 
				top: '50%', 
				left: '50%', 
				width: '174px', 
				height: '174px',
				padding: '20px' 
			}, 200);
		
		} , function() {
		$(this).css({'z-index' : '0'});
		$(this).find('img').removeClass("hover").stop()
			.animate({
				marginTop: '0', 
				marginLeft: '0',
				top: '0', 
				left: '0', 
				width: '100px', 
				height: '100px', 
				padding: '5px'
			}, 400);
	});
	 
	//Swap Image on Click
		$("ul.thumb li a").click(function() {
			
			var mainImage = $(this).attr("href"); //Find Image Name
			$("#main_view img").attr({ src: mainImage });
			return false;		
		});
 
});

*/



