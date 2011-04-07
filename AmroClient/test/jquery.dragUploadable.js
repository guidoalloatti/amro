    (function($){
	
		if (typeof(window.File) == 'object' && typeof(window.FileReader) == 'function' && typeof(window.FileList) == 'object') {
			// 
			console.log("DnD is supported!");
			alert("DnD is supported!");
		}
	
         $.fn.dragUploadable = function(postURL, fieldName, options) {

          var defaults = {
            dragenterClass: "",
            dragleaveClass: ""
          };
          var options = $.extend(defaults, options);

          return this.each(function() {
                obj = $(this);
                obj.bind("dragenter", function(event){
                    obj.removeClass(options.dragleaveClass);
                    obj.addClass(options.dragenterClass);
                    event.stopPropagation();
                    event.preventDefault();
                }, false);
    obj.bind("dragover", function(event){
        event.stopPropagation();
        event.preventDefault();
        }, false);
    obj.bind("dragleave", function(event){
                    obj.removeClass(options.dragenterClass);
                    obj.addClass(options.dragleaveClass);
                    event.stopPropagation();
                    event.preventDefault();
                }, false);
    obj.bind("drop", function(event){
        var data = event.originalEvent.dataTransfer;
        upload(postURL, fieldName, data);
        event.stopPropagation();
                    event.preventDefault();
      }, false);
          });
         };
        })(jQuery);

    function dropSetup() {
        var dropContainer = document.getElementById("output");

dropContainer.addEventListener("dragenter", function(event){dropContainer.innerHTML = 'DROP';event.stopPropagation();event.preventDefault();}, false);
dropContainer.addEventListener("dragover", function(event){event.stopPropagation();event.preventDefault();}, false);
dropContainer.addEventListener("drop", upload, false);
    };

    function upload(postURL, fieldName, data) {

        var boundary = '------multipartformboundary' + (new Date).getTime();
        var dashdash = '--';
        var crlf     = '\r\n';

        /* Build RFC2388 string. */
        var builder = '';

        builder += dashdash;
        builder += boundary;
        builder += crlf;

        var xhr = new XMLHttpRequest();

        /* For each dropped file. */
        for (var i = 0; i < data.files.length; i++) {
            var file = data.files[i];

            /* Generate headers. */
            builder += 'Content-Disposition: form-data; name="' + fieldName + '"';
            if (file.fileName) {
              builder += '; filename="' + file.fileName + '"';
            }
            builder += crlf;

            builder += 'Content-Type: application/octet-stream';
            builder += crlf;
            builder += crlf; 

            /* Append binary data. */
            builder += file.getAsBinary();
            builder += crlf;

            /* Write boundary. */
            builder += dashdash;
            builder += boundary;
            builder += crlf;
        }

        /* Mark end of the request. */
        builder += dashdash;
        builder += boundary;
        builder += dashdash;
        builder += crlf;

        xhr.open("POST", postURL, true);
        xhr.setRequestHeader('content-type', 'multipart/form-data; boundary='
            + boundary);
        xhr.sendAsBinary(builder);        

        xhr.onload = function(event) {
            /* Response from server */
            if (xhr.responseText) {
                alert(xhr.responseText);
            }

        };

    }
