  (function() {
  
	
	/*
	alert("Pepito23");
  
    $.event.fix = (function(originalFix) {
      return function(event) {
        event = originalFix.apply(this, arguments);
 
        if (event.type.indexOf('drag') === 0 || event.type.indexOf('drop') === 0) {
          event.dataTransfer = event.originalEvent.dataTransfer;
        }
        return event;
      };
    })($.event.fix);
 
    $.fn.dropImageReader = function(callback) {
      var stopFn;
 
      stopFn = function(event) {
        event.stopPropagation();
        event.preventDefault();
      };
 
      return this.each(function() {
        var $this, element;
 
        element = this;
        $this = $(this);
 
        $this.bind('dragenter dragover dragleave', stopFn);
 
        $this.bind('drop', function(event) {
          stopFn(event);
 
          Array.prototype.forEach.call(event.dataTransfer.files, function(file) {
            var imageType, reader;
 
            imageType = /image.*/;
            if (!file.type.match(imageType)) {
              return;
            }
 
            reader = new FileReader();
 
            reader.onload = function(evt) {
              return callback.call(element, file, evt);
            };
 
            reader.readAsDataURL(file);
          });
        });
      });
    };
  })(jQuery);