/*
 * piechart.js
 * 
 * A tool for auto-generating pie charts
 * within <div> sections of your webpage
 * that reads relative slice information
 * from the query field of URL.
 *
 * A: George Wong
 * C: 28.7.2013
 * E: 28.7.2013
 */

 
function writeHello() {

    document.write("<h1>HELLO</h1>");
    
}
 
function myFunction() {

    // Constants for formatting etc.
    var max = 1;
    var side = 200;
    var angles = [];
    var radius = side/2*0.9;
    var lastAngle = -Math.PI/2;
    var query = window.location.search.substring(1).split('&');
    var pieData = { "a":1, "b":1, "c":1, "d":1, "e":1, "f":1 };
    var colors = [ "#ff0000", "#ff6600", "#fefe00", "#008000", "#3366ff", "#993265" ];

    // Given arc angle, radius, and starting angle, return arc path
    function arcPath (a, r, s) {
        var half = side/2;
        return "M" + half + "," + half +
            " L" + (Math.cos(s)*r+half) + "," + (Math.sin(s)*r+half) +
            " A" + r + "," + r + " 0 0,1" + " " +
            (Math.cos(s+a)*r+half) + "," + (Math.sin(s+a)*r+half);
    }

    // Parse query string
    for (var term in query) {
        pieData[(query[term].split('='))[0]] = parseInt((query[term].split('='))[1]);
    }

    // Do the math to figure out angles in radians
    var sum = pieData["a"]+pieData["b"]+pieData["c"]+pieData["d"]+pieData["e"]+pieData["f"];
    for (var i in pieData) {
        angles.push(pieData[i]*2*Math.PI/sum);
    }

    // Acquire graphics lock
    var svg = d3.select("#ennui_pie")
                .append("svg")
                .attr("width", side)
                .attr("height", side);
                
    // Draw the slices
    for (var i in angles) {
        svg.append("path")
           .attr("d", arcPath (angles[i], radius, (lastAngle%(2*Math.PI))))
           .attr("stroke", "black")
           .attr("stroke-width", 1)
           .attr("fill", function () { return colors[i]; });
        lastAngle += angles[i];
    }

    if (sum < 11) {
        d3.select("#gen").append("i").text("No ennui for you this week!");  
    } else if (sum > 24) {
        d3.select("#gen").append("b").text("Even though your pie might look balenced, you might have a lot of ennui...");
    }

}
