<?php

$upload_path = "upload/";

/*
header("content-type:text/plain"); 
$keys = array(
    "PATH_INFO",
    "PATH_TRANSLATED",
    "PHP_SELF",
    "REQUEST_URI",
    "SCRIPT_FILENAME",
    "SCRIPT_NAME",
    "QUERY_STRING"
);

$info_row = "<tr><td>$_SERVER[SERVER_SOFTWARE]</td><td></td><td></td>\n";
print "Path Information for $_SERVER[SERVER_SOFTWARE]\n\n";

foreach($keys as $key) {
    print '$_SERVER["'.$key.'"] = '.$_SERVER[$key]."\n";
    $info_row .= "<td>$_SERVER[$key]</td>\n";
}

print '__FILE__ = '. __FILE__;
$info_row .= "<td>".__FILE__."</td>\n</tr>";

print "\n\n\n" . $info_row;


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
		}
		else
		{
			$move_retun = move_uploaded_file($_FILES["file"]["tmp_name"], $upload_path . $_FILES["file"]["name"]);
			echo "<br/>Stored in: " . $upload_path . $_FILES["file"]["name"];
			echo "<br/>Upload Return: ".$move_retun;
		}
    }
  }
else
{
  echo "Invalid file";
}
?>