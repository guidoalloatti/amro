$(document).ready(function() {

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
	
});