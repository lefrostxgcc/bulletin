$(".bullphotos").hover(
    function()
    {
	document.getElementById("bullavatar").src = this.getAttribute('src');
    }
);
