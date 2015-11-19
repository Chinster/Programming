var http = require("http")
	,url = require("url")
	,fs = require("fs")
	,express = require("express")
	,mongodb = require("mongodb")
	,mongoose = require("mongoose")
	,Session = require("connect-mongodb")
	,Account = require("./account-model.js");
	
function start(){
	var port = process.env.PORT || 5000;	
	//creates database
	var dbUrl = process.env.MONGOHQ_URL || "mongodb://127.0.0.1/";
	mongoose.connect(dbUrl);
	mongoose.connection.on('error', console.error.bind(console, 'connection error:'));
	mongoose.connection.once('open', function callback () {
		console.log("Connected to mongoose!");
	});
	
	
	Account.remove({}, function (err) {
		if (err) return handleError(err);
	});
	var admin = new Account({name:"administrator",username:"christopher", password:"rabbit",type:"admin",email:"ctchin13@gmail.com"});
	admin.save(function(err){
		if(err) return handleError(err);
	});
	var listOrder;
	fs.readdir("./swf_archive", function(err, files) {    
			 if(err) throw err;
			 else listOrder = files;
	});
	
	var app = express();
	app.configure(function(){
		//app.use(express.favicon());		
		app.use(express.bodyParser({ keepExtensions: true, uploadDir: "./swf_archive" }));
		app.use(express.static(__dirname + "/"));
	});
	
	//copy pasta
	/*
	app.configure('production', function(){
	  var oneWeek = 657450000;
	  app.use(express.static(__dirname + '/../public', { maxAge: oneWeek }));
	  var session = express.session({
			store: new Session({
				  url: dbUrl, 
				  maxAge: 300000
			}),
			secret: 'superTopSecret' 
	  });
	  app.use(session);

	  app.use(mongooseAuth.middleware());
	  app.use(require('.\index.html').middleware());
	  app.use(express.methodOverride());
	  app.use(express.errorHandler());  
	});
	*/
	//copy pasta
	app.get("/", function(req, res){
		res.redirect("/index.html");
	});
	app.get("/swf_archive/list", function(req, res){	
		res.writeHeader(200);
		var filesString = listOrder.toString();
		var fileBuffer = new Buffer(filesString);
		res.write(fileBuffer);
		res.end();
	});
	app.get("/adminPage", function(req, res){
		res.redirect("../adminPage.html");
	});
	app.put("/login", function(req, res){
		var usernameInput = req.body.usernameInput;
		var passwordInput = req.body.passwordInput;
		console.log("Logging in with credentials: " +usernameInput+"//"+passwordInput);
		Account.findOne({username:usernameInput}, function(err, account) {
			if(err) throw err;
			account.comparePassword(passwordInput, function(err, isMatch){
				if(isMatch) {
					res.send("success");
				}
				else {res.send("Username or password incorrect");}
			})
		});
	});
	app.put("/swf_archive/edit", function(req, res){
		for(var i = 0; i < listOrder.length; i++){
			listOrder[i]=req.body.listOrder[i];
		}
		res.end();
	});
	app.post("/swf_archive/edit", function(req, res){
		function manageFile(file){
			if(file.type == "application/x-shockwave-flash"){
				console.log(file.name+" saved!");
				var newPath = file.path.split("/");
				newPath.pop();
				newPath = newPath+"/"+file.name;
				fs.rename(file.path, newPath, function(err){if(err) throw err;});
				listOrder.push(file.name);
			}
			else{
				fs.unlink(file.path, function(err){
					if(err) throw err;
					else console.log(file.name+" deleted.");
				});
			}
		};
		//if singular file
		if(typeof req.files.fileInput.length != "number"){
			var file = req.files.fileInput;
			manageFile(req.files.fileInput);
		}
		//if multiple files
		else{
			for(var i = 0;i < req.files.fileInput.length; i++){
				manageFile(req.files.fileInput[i]);
			}
		}
		res.redirect("/../../adminPage.html");
	});
	app.del("/swf_archive/edit", function(res, req){
		var fileName = res.body.fileName+".swf";
		listOrder.splice(listOrder.indexOf(res.body.fileName),1);
		fs.unlink("swf_archive/"+fileName, function(err){
			if(err) throw err;
			else console.log(fileName+" deleted!");
			req.end();
		});
	});
	
	
	app.listen(port);
	console.log("App has started on " +port);
}
start();