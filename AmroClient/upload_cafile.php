<?php

$upload_path = "upload/analisis_quimicos/";

/*
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
*/
  
if ($_FILES["file"]["size"] < 2000000000)
//((($_FILES["file"]["type"] == "image/gif")
//|| ($_FILES["file"]["type"] == "image/jpeg")
//|| ($_FILES["file"]["type"] == "image/pjpeg"))
//&&
{
	if ($_FILES["file"]["error"] > 0)
    {
		echo "Return Code: " . $_FILES["file"]["error"] . "<br />";
		echo '<script>window.opener.alert("Error! Debe seleccionar un archivo."); window.close();</script>';
    }
	else
    {
		echo "Upload: " . $_FILES["file"]["name"] . "<br />";
		echo "Type: " . $_FILES["file"]["type"] . "<br />";
		echo "Size: " . ($_FILES["file"]["size"] / 1024) . " Kb<br />";
		echo "Temp file: " . $_FILES["file"]["tmp_name"] . "<br />";

		if (file_exists($upload_path . $_FILES["file"]["name"]))
		{
			echo $_FILES["file"]["name"] . " already exists. ";
			//echo "<script>window.opener.alert('El archivo ya existe en el servidor. Cambie el nombre.'); window.close();</script>";
		}
		else
		{
			if(move_uploaded_file($_FILES["file"]["tmp_name"],$upload_path . $_FILES["file"]["name"]))
			{
				echo "Se subio correctamente el archivo en: " . $upload_path . $_FILES["file"]["name"];
				//echo "<script>window.opener.uploadCAFile('" . $_FILES["file"]["name"] . "'); window.close();</script>";
			}
			else
			{
				echo "No se subio el archivo";
				//echo '<script>window.opener.alert("No se pudo subir el archivo, error en el servidor."); window.close();</script>';
			}
		}
      }
    }
else
{
  echo "Invalid file";
  //echo '<script>window.opener.alert("Error! El archivo supera los 200MB."); window.close();</script>';
}
?>