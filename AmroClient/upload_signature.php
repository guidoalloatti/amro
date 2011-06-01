<?php

$upload_path = "certificados/img/".$_GET["user"]."/";

if ($_FILES["file"]["error"] > 0)
  {
  echo "Error: " . $_FILES["file"]["error"] . "<br />";
  }
else
  {
  echo "Upload: " . $_FILES["file"]["name"] . "<br />";
  echo "Type: " . $_FILES["file"]["type"] . "<br />";
  echo "Size: " . ($_FILES["file"]["size"] / 1024) . " Kb<br />";
  echo "Stored in: " . $_FILES["file"]["tmp_name"];
  }

  
if ($_FILES["file"]["size"] < 2000000000)
//((($_FILES["file"]["type"] == "image/gif")
//|| ($_FILES["file"]["type"] == "image/jpeg")
//|| ($_FILES["file"]["type"] == "image/pjpeg"))
//&&
{
	if ($_FILES["file"]["error"] > 0)
    {
		echo "Return Code: " . $_FILES["file"]["error"] . "<br />";
		echo '<script>window.opener.alert("Error! Seleccionar un archivo válido."); window.close();</script>';
    }
	else
    {    	
		echo "Upload: " . $_FILES["file"]["name"] . "<br />";
		echo "Type: " . $_FILES["file"]["type"] . "<br />";
		echo "Size: " . ($_FILES["file"]["size"] / 1024) . " Kb<br />";
		echo "Temp file: " . $_FILES["file"]["tmp_name"] . "<br />";

		
		if(move_uploaded_file($_FILES["file"]["tmp_name"],$upload_path . $_FILES["file"]["name"]))
		{
			echo "Se subio correctamente el archivo en: " . $upload_path . $_FILES["file"]["name"];
			echo "<script>window.opener.updateSignature('" . $_FILES["file"]["name"] . "', '" . $_GET["user"] . "'); window.close();</script>";
		}
		else
		{
			echo "No se subio el archivo";
			//rmdir($upload_path);
			echo '<script>window.opener.alert("No se pudo subir el archivo, error en el servidor."); </script>';
		}
		
      }
    }
else
{
  echo "Invalid file";
  echo '<script>window.opener.alert("Error! El archivo supera los 200MB."); window.close();</script>';
}
?>