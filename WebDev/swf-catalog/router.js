var path = require("path");
var url = require("url");

module.exports = function(){
	return function(req, res, callback){
		switch(url.parse(req.url).pathname){
		case "/":
			file_path = "views/index.html";
			break;
		case "/swf_archive/list":
			file_path = "/swf_archive";
			break;
		default:
			file_path = pathname;
		}
	}
}