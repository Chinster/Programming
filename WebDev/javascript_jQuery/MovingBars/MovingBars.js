$(document).ready(function () {
    var barManager = [];
    var mouseDiffX = 0;
    var mouseDiffY = 0;
    for (var i = 1; i <= $("div.bar").length; i++) {
        barManager.push({
            num: i,
            z: $("div.bar:nth-child(" + i + ")").css("z-index"),
            baseLeft: parseInt($("div.bar:nth-child(" + i + ")").css("left"), 10),
            baseTop: parseInt($("div.bar:nth-child(" + i + ")").css("top"), 10),
            baseRotation: (($("div.bar:nth-child(" + i + ")").css("z-index") - 1) * 5) - 35

        });
    }
    $(document).mousemove(function (e) {
        $('#output').html(e.pageX + ', ' + e.pageY);
        /*mouseDiffX = Math.abs(mouseDiffX - e.pageX);
        //mouseDiffY = Math.abs(mouseDiffY - e.pageY);

        if (mouseDiffX > 10){
            mouseDiffX = e.pageX;*/
        var locationRatioX = (e.pageX) / ($(window).width());
        //var locationRatioY = (e.pageY) / ($(window).height());

        for (var i = 1; i <= $("div.bar").length; i++) {
            var baseRotation = barManager[i - 1].baseRotation;
            var baseLeft = barManager[i - 1].baseLeft;
            var baseZ = barManager[i - 1].z;

            $("div.bar:nth-child(" + i + ")").css("left", (baseLeft - (80 * locationRatioX) / (baseZ)) + "px");
            $("div.bar:nth-child(" + i + ")").css("-webkit-transform", "rotate(" + (baseRotation + (8 * locationRatioX) / (baseZ)) + "deg)");
            $("div.bar:nth-child(" + i + ")").css("-mobaseZ-transform", "rotate(" + (baseRotation + (8 * locationRatioX) / (baseZ)) + "deg)");
            $("div.bar:nth-child(" + i + ")").css("-ms-transform", "rotate(" + (baseRotation + (8 * locationRatioX) / (baseZ)) + "deg)");
            $("div.bar:nth-child(" + i + ")").css("-o-transform", "rotate(" + (baseRotation + (8 * locationRatioX) / (baseZ)) + "deg)");
            $("div.bar:nth-child(" + i + ")").css("transform", "rotate(" + (baseRotation + (8 * locationRatioX) / (baseZ)) + "deg)");
        }
        //}
        //Running both y tracking and x tracking has difficulties.
        /*if ( /*mouseDiffY > 10 && e.pageY > $(window).height() / 8 && e.pageY < ($(window).height() * 7) / 8) {
            //mouseDiffY = e.pageY;
            for (var i = 1; i <= $("div.bar").length; i++) {
                console.log(locationRatioY);
                var baseTop = barManager[i - 1].baseTop;
                var baseZ = barManager[i - 1].z;
                $("div.bar:nth-child(" + i + ")").css("top", (baseTop + (75 * locationRatioY * baseZ)) + "px");
            }
        }*/
    });
});