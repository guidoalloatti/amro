//$(document).ready(function(){});

/*
	numero de fieldsets
	*/
	var fieldsetCount;// = $('#formElem').children().length;

	/*
	posicion actual de fieldset / navigation link
	*/
	var current 	= 1;

	/*
	suma y guarda el ancho de cada uno de los fieldsets
	fija la suma final como el total ancho de todos los pasos de elementos
	*/
	var stepsWidth	= 0;
    var widths 		= new Array();

function loadCert() {
//$(function() {
	fieldsetCount = $('#formElem').children().length;
	
	$('#steps .step').each(function(i){
        var $step 		= $(this);
		widths[i]  		= stepsWidth;
        stepsWidth	 	+= $step.width();
    });
	$('#steps').width(stepsWidth);

	/*
	para evitar problemas con IE, hacemos un focus del primer elemento de entrada en el formulario
	*/
	$('#formElem').children(':first').find(':input:first').focus();	

	/*
	mostramos el navigation barra
	*/
	$('#navigation').show();

	/*
	cuando hacemos click sobre el link de navegación
	el formulario se desliza hasta el correspondiente fieldset
	*/
    $('#navigation a').bind('click',function(e){
		var $this	= $(this);
		var prev	= current;
		$this.closest('ul').find('li').removeClass('selected');
        $this.parent().addClass('selected');
		/*
		almacenamos la posicional del link
		en la variable current 
		*/
		current = $this.parent().index() + 1;
		/*
		animate / slide al siguiente o al correspondiente
		fieldset. El orden de los links en la navegación
		es el orden de los fieldset.
		Por otro lado, despues de deslizar, lanzamos un evento de focus sobre el primer
		elemento input de el nuevo fieldset
		Si hacemos click sobre el ultimo (confirmation), entonces validamos todos los fieldset
		si no validaremos solo los previos al que tenemos
		antes de que el formulario se deslice
		*/
        $('#steps').stop().animate({
            marginLeft: '-' + widths[current-1] + 'px'
        },500,function(){
			if(current == fieldsetCount - 1)
				validateSteps();
			else
				validateStep(prev);
			$('#formElem').children(':nth-child('+ parseInt(current) +')').find(':input:first').focus();
		});
        e.preventDefault();
    });

	/*
	haciendo click en el tab (sobre la ultima entrada de cada fieldset), hacemos que el form
	deslice al siguiente paso
	*/
	$('#formElem > fieldset').each(function(){
		var $fieldset = $(this);
		$fieldset.children(':last').find(':input').keydown(function(e){
			if (e.which == 9){
				$('#navigation li:nth-child(' + (parseInt(current)+1) + ') a').click();
				/* force the blur for validation */
				$(this).blur();
				e.preventDefault();
			}
		});
	});	

	/*
	si hay errores no permitimos al usuario enviar
	*/
	$('#registerButton').bind('click',function(){
		if($('#formElem').data('errors')){
			alert('Por favor corregir los errores en las solapas marcadas');
			return false;
		}
		
		generateCertificate();
		event.preventDefault();
	});
	
	/* 
	 * Para que compruebe la validación del último paso sin tener que
	 * pasar a otro step.
	 */
	$('#formElem').children(':nth-child(' + parseInt(fieldsetCount-1) + ')').find(':input:not(button)').each(function(){
		var $this = $(this);
		$this.change(function(event){
			validateSteps();
			event.preventDefault();
		});
	});	
		
	loadAllClients();
	loadAllMaterials();
	loadAllUsers();
	getTT();
}

/*
validamos errores sobre todos los campos de los fieldsets
y recuperamos si tiene errores en $('#formElem').data()
*/
function validateSteps(){
	var FormErrors = false;
	for(var i = 1; i < fieldsetCount; ++i){
		var error = validateStep(i);
		if(error == -1)
			FormErrors = true;
	}
	$('#formElem').data('errors',FormErrors);
}

/*
validamos un fieldset
y retornamos -1 si encontramos errores o 1 si es correcto
*/
function validateStep(step){
	if(step == fieldsetCount) 
		return;
	
	var error = 1;
	var hasError = false;
	$('#formElem').children(':nth-child('+ parseInt(step) +')').find(':input:not(button)').each(function(){
		var $this 		= $(this);
		var valueLength = jQuery.trim($this.val()).length;
		
		if($this.attr('id') != '_file' && valueLength == ''){
			hasError = true;
			$this.css('background-color','#FFEDEF');			
		}
		else {
			$this.css('background-color','#FFFFFF');					
		}
		
		if ($this)
		
		if (step == 5 && ($this.attr('id') == 'select_reviewer' || $this.attr('id') == 'select_approver'))
			if ($this.val() == 0) {
				hasError = true;
				$this.css('background-color','#FFEDEF');
			} else
				$this.css('background-color','#FFFFFF');
	});
	var $link = $('#navigation li:nth-child(' + parseInt(step) + ') a');
	$link.parent().find('.error,.checked').remove();

	var valclass = 'checked';
	if(hasError){
		error = -1;
		valclass = 'error';
	}
	$('<span class="'+valclass+'"></span>').insertAfter($link);

	return error;
}