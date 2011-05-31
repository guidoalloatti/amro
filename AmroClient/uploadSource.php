<?php

$html = '
<html>
<body>
<form action="upload_file.php" method="post" enctype="multipart/form-data">
	<label for="file">Subir Archivo:</label>
	<input type="file" name="file" id="file" /> 
	<br/>
	<input type="submit" name="submit" value="Submit" />
</form>
</body>
</html>';

echo $html;

?>