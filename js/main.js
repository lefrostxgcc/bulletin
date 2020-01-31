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
			$("[data-id='" + r + "'].info").show();
		    });

$(".infosave").on("click", function()
		  {
		      var r = $(this).data('id');
		      var info_ = $("[data-id='"+r+"'].infofield").val();
		      $.ajax({
			  type: "POST",
			  url: "/photo/setinfo",
			  data: {id:r, info:info_},
			  success: function(res)
			  {
			      alert(res);
			  },
			  error: function()
			  {
			      alert("error!");
			  }
		      });
		      var bull_id = $("#photos-row").data('bull_id');
		      $('body').load('/photo/index?id=' + bull_id);
		  });
