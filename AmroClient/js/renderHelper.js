var html_code = "";

$(document).ready(function(){
	var pre = document.createElement('pre');
	document.body.appendChild(pre);
});

function renderHtml() {
	$("#html_change").replaceWith(html_code);
}

function dump2(obj, indent) {
	var out = '';
	for (var i in obj) 
	{
		if (typeof obj[i] == 'object')
			out += indent + i + ": " + "\n" + dump2(obj[i], indent + "\t");											
		else
			out += indent + i + ": " + obj[i] + "\n";
	}
	return out;
}	

function dump(obj) 
{
	out = dump2(obj, "");
	pre.innerHTML = out;
}