$("#tb").on("click", function()
	    {
		if ($("#testfield").is(":hidden"))
		{
		    $("#testfield").show();
		    $("#tb").html("Скрыть");
		}
		else
		{
		    $("#testfield").hide();
		    $("#tb").html("Показать");
		}
	    });

$(".infobutton").on("click", function()
		    {
			var r = $(this).data('id');
			$("[data-id='" + r + "'].infofield").show();
		    });

$(".infosave").on("click", function()
		  {
		      var r = $(this).data('id');
		      $("[data-id='" + r + "'].infofield").hide();
		  });
