$(document).ready(function(){
	$("#editList").sortable({revert:true});
	var fileNames;
	$.get('swf_archive/list', function(data){
		fileNames = data.split(",");
		for(var i = 0; i <fileNames.length; i++){
			var fileName = fileNames[i].replace(".swf", "");
			var listObject = "<li><p>" +fileName +"</p><span class=\"deleteEdit\">X</span></li>";
			$("#editList").append($(listObject));
		}
	});
	$(document).on("click", "#submitEdit", function(e){
		var listOrder = [];
		var numFiles = $(e.currentTarget).siblings("div").children("ul").children("li").length;
		for(var i = 0; i < numFiles; i++){
			listOrder.push($($(e.currentTarget).siblings("div").children("ul").children("li")[i].firstChild).html());
		}
		$.ajax({
			url:"swf_archive/edit"
			,type: "PUT"
			,data: {listOrder:listOrder}
		});
	}); 
	$(document).on("click", ".deleteEdit", function(e){
		if(confirm("This will delete the file.\n Are you sure?")){
			console.log($(e.currentTarget).siblings("p").html());
			var file = $(e.currentTarget).siblings("p").html();
			$(e.currentTarget).parent().remove();
			$.ajax({
				url:"swf_archive/edit"
				,type: "DELETE"
				,data: {fileName:file}
			});
		}
	});
	
});