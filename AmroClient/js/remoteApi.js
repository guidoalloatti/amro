$(document).ready(function() {

	$("#validate_login_button").click(function(){
		validateLogin();
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
			console.log(data.result);
			});
		});
	}
	
});