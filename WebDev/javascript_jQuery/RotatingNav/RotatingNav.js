$(document).ready(function () {
    var rotate = function (start, end, callBack) { //Infinite loops if start>end :D!
        $('#button').css("transform", "rotate(" + start + "deg)")
        $('#button').css("-webkit-transform", "rotate(" + start + "deg)")
        $('#button').css("-moz-transform", "rotate(" + start + "deg)")
        $('#button').css("-ms-transform", "rotate(" + start + "deg)")
        $('#button').css("-o-transform", "rotate(" + start + "deg)")
        if (start != end) {
            setTimeout(function () {
                rotate(++start, end, callBack)
            }, 5);
        } else {
            callBack();
            /*$('#content').animate({
                width: 'toggle'
            },1000);*/

        }

    }
    var contract = function(){
        $("#content span").fadeOut();
            $("#content").animate({
                width: "hide",
            }, 1000);
            $("#top").animate({
                top: "0px",
            }, 1000);
    }
    $("#button").click(function () {
        if (($('#content').is(":visible"))) {
            contract()
            setTimeout(function () {
                rotate(90, 180, function () {})
            }, 1000);
        } else {
            var holder = function () {
                $("#content").animate({
                    width: "show",
                }, 1000);
                $("#top").animate({
                    top: "-499px",
                }, 1000);
                setTimeout(function(){$("#content span").fadeIn();}, 1000);
            };
            rotate(0, 90, holder);

        }
    });
    $("#content").click(function () {
        contract();
        setTimeout(function () {
            rotate(90, 180, function () {})
        }, 1000);
    });
});