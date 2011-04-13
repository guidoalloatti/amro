$(document).ready(function() {

	var html_code = "Codigo de retorno de la llamada: ";

	$("#validate_login_button").click(function(){
		validateLogin();
		renderHtml();
	});

	function validateLogin()
	{
		$.getJSON("http://192.168.1.101:8080/?jsoncallback=?",
		{
			target: "User",
			method: "Login",
			email: "pmata@amro.com",
			password: "123",
			format: "json"
		},
		function(data) {
			$.each(data.items, function(i,item){
				html_code += i+". "+data.result;
			});
		});
	}
	
	function renderHtml()
	{
		$("#html_change").replaceWith(html_code);
	}
	
});