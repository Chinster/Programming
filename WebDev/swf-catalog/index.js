$(document).ready(function(){
	var bLoginToggle = 0;
	var listHolder = document.createElement("ul");
	$.get('swf_archive/list', function(data){
		console.log("Received");
		console.log(data);
		var fileNames = data.split(",");
		for(var i = 0; i <fileNames.length; i++){
			var fileName = fileNames[i].replace(".swf", "");
			var listObject = "<li><p class=\"displayList\">" +fileName +"</p></li>";
			$(listHolder).append($(listObject));
		}
		console.log(listHolder);
	});
	
	introAnimation();
	
	
	
	$("#loginSlide").click(function(){
		//true = raised;
		//false = loginPanel not showing
		if(bLoginToggle)
			$(this).animate({bottom:"0"},"swing", function(){});
		else
			$(this).animate({bottom:"22%"},"swing", function(){})
		bLoginToggle = !bLoginToggle;
		$("#loginPanel").slideToggle();
	});
	$(document).on("click", "#loginSubmit", function(e){
			var usernameInput = $("input[name=username]").val();
			var passwordInput = $("input[name=password]").val();
			console.log("Sending credentials: " +usernameInput+"//"+passwordInput);
			$.ajax({ 
				url:"login"
				,type: "PUT"
				,data: {usernameInput: usernameInput, passwordInput:passwordInput}
				,success: function(data){
					console.log(data);
					if(data == "success"){
						console.log("Successfully Logged In!");
						window.location.href = "../adminPage.html";
						
					}
					else{
						console.log("Login Failed!");
					}
				}
			});
		}
	);
	
	//creates swf object when list item is clicked
	$(document).on("click",".displayList", function(e){
		var filepath = "swf_archive/"+ e.currentTarget.innerHTML+".swf" ;
		var newSwf = document.createElement("object");
		newSwf.classid = "clsid:d27cdb6e-ae6d-11cf-96b8-444553540000";
		newSwf.codebase = "http://fpdownload.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=8,0,0,0";
		newSwf.width = "100%";
		newSwf.height = "100%";
		var swfParam = document.createElement("param");
		swfParam.name = "SCALE"
		swfParam.value = "noscale"
		$(newSwf).append(swfParam);
		var swfEmbed = document.createElement("embed");
		swfEmbed.src = filepath;
		swfEmbed.width= "100%";
		swfEmbed.height= "100%";
		swfEmbed.SCALE="noscale";
		$(newSwf).append(swfEmbed);
		$("#displayWindow").empty();
		$("#displayWindow").prepend($(newSwf));
	});
	function introAnimation(){
		var $welcome = $("#intro p:first-child");
		var $break = $("#intro hr");
		var $author = $("#intro p:last-child");
		var $main = $("#main");
		$main.css("opacity", "0.1");
		$welcome.animate({
			opacity: 1,
			left: '+=100',
		}, 1200, function() {
		});
		$break.animate({
			opacity: 1,
			width: '100%',
			left:"+=50"
		}, 1200, function() {
			
		});
		$author.animate({
			opacity: 1,
			right: '+=100',
		}, 1200, function(){
			setTimeout(function(){
				$welcome.animate({
					opacity: 0,
					top: '-=100',
				}, 500, function() {
				});
				$break.animate({
					opacity: 0,
					width: '100%',
					left:"-=50"
				}, 500, function() {
					
				});
				$author.animate({
					opacity: 0,
					bottom: '-=100',
				}, 500, function(){
					$("#intro").remove();
				});
			}, 700);
		});
		setTimeout(function(){$main.animate({
			opacity: 1
		}, 1400, function() {
			$("#sideNav").append($(listHolder));
		});}, 1400); 
	}
});