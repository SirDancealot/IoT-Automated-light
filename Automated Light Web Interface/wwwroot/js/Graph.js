const uri = "http://api.mj-software.dk/data/latest/"

fetchData = function (num) {
    return fetch(uri + num)
        .then(response => response.json())
}


window.onload = async function () {

    var dataPoints = []

    var data = await fetchData(10)

    for (var i = 0; i < 10; i++) {

        var json = data[i]["time"];
        var date = new Date(json);
        dataPoints.push({x: date, y: data[i]["temp"]})
    }

    var chart = new CanvasJS.Chart("chartContainer", {
        animationEnabled: true,
        title: {
            text: "Temperature at MCU"
        },
        axisX: {
            valueFormatString: "HH:mm:ss, DD/MM/YY"
        },
        axisY: {
            title: "Temperature (in °C)",
            suffix: " °C"
        },
        legend: {
            cursor: "pointer",
            fontSize: 16,
            itemclick: toggleDataSeries
        },
        toolTip: {
            shared: true
        },
        data: [{
            name: "Myrtle Beach",
            type: "spline",
            yValueFormatString: "#0.## °C",
            showInLegend: true,
            dataPoints: dataPoints
        }]
    });
    chart.render();

    function toggleDataSeries(e) {
        if (typeof (e.dataSeries.visible) === "undefined" || e.dataSeries.visible) {
            e.dataSeries.visible = false;
        }
        else {
            e.dataSeries.visible = true;
        }
        chart.render();
    }

}