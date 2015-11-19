$(document).ready(function () {
    var output = function (myMessage) {
        $("#output").html(myMessage);
    }
    
    var data = [];
    //takes two input fields, adds to data array, adds text to key 
    var inputEntry = function () {
        var entry1 = $("input[name=name]").val();
        var entry2 = $("input[name=entry]").val();
        var entryisNaN = isNaN(parseInt(Number(entry2, 10)))
        
        if (entryisNaN) {
            output("Entry should be a number!");
        } else if (entry1 == "") {
            output("Data Name???");
            } else {
                clearFields();
                $("input[name=name]").focus();
                data.push({
                    "name": entry1,
                    "entry": entry2
                });
                $("#key").append("<div><span class=\"delete\">x</span>  <span class=\"keyInfo\">" + entry1 + ": " + entry2 + "</span></div>"); //adds entry to key
            drawFigure(data);
        }
    }
    //Determines percentage, adds text/art to canvas
    var drawFigure = function (data) {
        var total = 0;
        var percentage = 0;
        for (var i = 0; i < data.length; i++) {
            total += Number(data[i].entry);
            //create divs
            $("#canvas").append("<div style=\"display:none\"></div>");
        }
        for (var i = 0; i < data.length; i++) {
            percentage = Math.round((Number(data[i].entry) / total) * 10000) / 100; // to 2 decimal places
            $("#canvas div:nth-child(" + (i + 1) + ")").css("width", (percentage * .8) + "%");
            $("#canvas div:nth-child(" + (i + 1) + ")").css("display", "inline-block");
            //Shortens name if too long
            if (data[i].name.length < 8) {
                $("#canvas div:nth-child(" + (i + 1) + ")").append(data[i].name);
            } else {
                $("#canvas div:nth-child(" + (i + 1) + ")").append(data[i].name.substring(0, 6) + "...");
            }
        }
    }
    var clearFields = function(){
        $("input[name=name]").val("");
        $("input[name=entry]").val("");    
        output("");
        $("#canvas").empty();
    }
    //Graphical effect on submit button
    $("#submitButton").mousedown(function () {
        var shadowProp = '-2px 2px 3px 0px #24663C inset, 2px -2px 3px 0px #7bd572 inset';
        $(this).css("box-shadow", shadowProp);
    });
    //Graphical effect on submit button
    $("#submitButton").mouseup(function () {
        var shadowProp = '2px -2px 3px 0px #24663C inset, -2px 2px 3px 0px #7bd572 inset';
        $(this).css("box-shadow", shadowProp);
    });
    //Enter data on return key
    $("input[name=entry]").keydown(function (key) {
        if (parseInt(key.which, 10) == 13) {
            inputEntry();
        }
    });
    //Enter data on submit button click
    $("#submitButton").click(inputEntry);

    //deletes data entry on click 'x' button
    $(document).on("click", ".delete", function () {
        var n = $(".delete").index(this); //finds "this" in the list of .delete?        
        data.splice(n, 1);
        $("#key div:nth-child(" + (n + 1) + ")").fadeOut("slow", function () {
            $(this).remove()
        });
        drawFigure(data);
        for (var i = 0; i < data.length; i++) {
            output(data[i].name);
        }
    });
});