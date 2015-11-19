$(document).ready(function () {
    var globalImageURL = "http://upload.wikimedia.org/wikipedia/commons/thumb/0/08/Pencils_hb.jpg/310px-Pencils_hb.jpg";
    var productList = [];
    var displayList = [];
    var selectedCategory;
    productList.push({
        productName: "Medium Tee",
        productImage: globalImageURL,
        colors: ["red", "green", "biege"],
        category: "Upper Coverings"
    });
    productList.push({
        productName: "Large Tee",
        productImage: "http://2.bp.blogspot.com/--a1GPAf-nZI/TWW4SW9mzOI/AAAAAAAABCQ/4x3ut12YiQg/s1600/100316184706_fish_2.jpg",
        colors: ["red", "green", "biege"],
        category: "Upper Coverings"
    });
    productList.push({
        productName: "Medium Shoe",
        productImage: globalImageURL,
        colors: ["black", "blue", "brown"],
        category: "Pedal Sheaths"
    });
    productList.push({
        productName: "Large Shoe",
        productImage: globalImageURL,
        colors: ["black", "blue", "brown"],
        category: "Pedal Sheaths"
    });
    productList.push({
        productName: "Drafting Pencil",
        productImage: globalImageURL,
        colors: ["silver"],
        category: "Pencils"
    });
    productList.push({
        productName: "Rainbow Pencil",
        productImage: globalImageURL,
        colors: ["red", "orange", "yellow", "green", "blue", "violet"],
        category: "Pencils"
    });
    productList.push({
        productName: "Deep Voice",
        productImage: globalImageURL,
        colors: ["blue"],
        category: "George"
    });
    productList.push({
        productName: "Blue Eyes",
        productImage: globalImageURL,
        colors: ["blue"],
        category: "George"
    });
    $("a").click(function () {
        selectedCategory = String($(this).html());
        displayList = [];
        $("#store").empty();
        for (var i = 0; i < productList.length; i++) {
            if (productList[i].category == selectedCategory) {
                displayList.push(productList[i]);
            }
        }
        for (var i = 0; i < displayList.length; i++) {
            var productImage = "<img src=\"" + displayList[i].productImage + "\" height=\"100px\" width =\"150px\" >";
            var productName = displayList[i].productName;
            var addCartButton = "<p class=\"addCartButton\">Add To Cart</p>"
            $("#store").append("<div class=\"storeItems\">" + productImage + "<p>" + productName + "</p>" + addCartButton + "</div>");
        }
    });
    $(document).on("click", ".addCartButton", function (e) {
        var n = $(".addCartButton").index(this);
        var tempImage = $(e.currentTarget).siblings("img").clone();
        $(e.currentTarget).parent().append(tempImage);
        //$("#store .storeItems:nth-child(" + (n + 1) + ")").append(tempImage);
        tempImage.css("position", "absolute");
        tempImage.css("left", "0");
        tempImage.css("top", "0");
        var tempY = tempImage.offset().top;
        tempImage.animate({
            opacity: 0,
            left: -tempImage.offset().left,
            width: "9px",
            height: "6px"
        }, {duration:500, queue:false}, function () {
            this.remove();
        });
        tempImage.animate({top:+50}, 300, function(){
            tempImage.animate({top:-(tempY+50)}, 200, function(){});
        });
        
        var productName = $(e.currentTarget).siblings("p").text();
        $("#header img").after("<div class=\"cart\">"+productName+"</div>");
    });
});