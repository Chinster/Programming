var mongoose = require("mongoose")
	,bcrypt = require("bcrypt-nodejs");
	
var SALT_WORK_FACTOR = 10;

var accountSchema = mongoose.Schema({
	name : String
	,username:{type:String, required:true, index: {unique:true}}
	,password:{type:String, required:true}
	,type:{type:String, required:true}
	,email:{type:String, required:true, index:{unique:true}}
	});
accountSchema.pre("save", function(next){
	var user = this;
	if(!user.isModified("password")) return next();
	bcrypt.genSalt(SALT_WORK_FACTOR,function(err,salt){
		if(err) return next(err);
		else bcrypt.hash(user.password, salt, function(){}, function(err, hash){
			if(err) return next(err);
			user.password = hash;
			next();
		});
	});
});
accountSchema.methods.comparePassword = function(candidatePassword, callback){
	var user = this;
	bcrypt.compare(candidatePassword, user.password, function(err, isMatch){
		if(err) callback(err);
		else callback(null, isMatch);
	});
};

module.exports = mongoose.model("Accounts", accountSchema);