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
