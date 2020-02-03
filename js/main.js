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
			$.ajax({
			    type: "POST",
			    url: "/photo/getinfo",
			    data: {id:r},
			    success: function(res)
			    {
				$("[data-id='"+r+"'].infofield").val(res);
			    },
			    error: function()
			    {
				alert("error!");
			    }
			});
			$("[data-id='" + r + "'].info").show();
		    });

$(".avabutton").on("click", function()
		   {
		       var currPhotoId = $(this).data('id');
		       var currBullId = $("#photos-row").data('bull_id');
		       $.ajax({
			   type: "POST",
			   url: "/photo/setavatar",
			   data: {PhotoId: currPhotoId, BullId: currBullId},
			   success: function(res)
			   {
			       alert(res);
			   },
			   error: function()
			   {
			       alert("error!");
			   }
		       });
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
			  },
			  error: function()
			  {
			      alert("error!");
			  }
		      });
		      var bull_id = $("#photos-row").data('bull_id');
		      $('body').load('/photo/index?id=' + bull_id);
		  });

$(".deletebutton").on("click", function()
		      {
			  var r = $(this).data('id');
			  var del = confirm("Вы действительно хотите " +
					    "удалить это изображение?");
			  if (del == true)
			  {
			      alert("Вы выбрали OK");
			  }
			  else
			  {
			      alert("Вы выбрали Отмена");
			  }
		      }
		     );
