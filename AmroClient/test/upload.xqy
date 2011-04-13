let $upload-fieldname := "upload"
let $image := xdmp:get-request-field( $upload-fieldname )
let $filename := xdmp:get-request-field-filename($upload-fieldname)
let $path := fn:concat("/somewhere/", $filename)
let $doc-saved := xdmp:save($path, $image)
return $image
