const uri = "http://api.mj-software.dk/data/latest/"

fetchData = function (num) {
    return fetch(uri + num)
        .then(response => response.json())
}


window.onload = async function () {

    var temp = []
    var lux = []
    var humidity = []

    var data = await fetchData(10)

    for (var i = 0; i < 10; i++) {

        var json = data[i]["time"];
        var date = new Date(json);
        temp.push({ x: date, y: data[i]["temp"] })
        lux.push({ x: date, y: data[i]["lux"] })
        humidity.push({ x: date, y: data[i]["humidity"] })
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
            name: "Temperature",
            type: "spline",
            yValueFormatString: "#0.## °C",
            showInLegend: true,
            dataPoints: temp
        }]
    });
    chart.render();
    var chart1 = new CanvasJS.Chart("chartContainer1", {
        animationEnabled: true,
        title: {
            text: "Light level at MCU"
        },
        axisX: {
            valueFormatString: "HH:mm:ss, DD/MM/YY"
        },
        axisY: {
            title: "Light level (in lux)",
            suffix: " lux"
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
            name: "Light level",
            type: "spline",
            yValueFormatString: "#0.## lux",
            showInLegend: true,
            dataPoints: lux
        }]
    });
    chart1.render();
    var chart2 = new CanvasJS.Chart("chartContainer2", {
        animationEnabled: true,
        title: {
            text: "Humidity at MCU"
        },
        axisX: {
            valueFormatString: "HH:mm:ss, DD/MM/YY"
        },
        axisY: {
            title: "Humidity (in %)",
            suffix: " %"
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
            name: "Humidity",
            type: "spline",
            yValueFormatString: "#0.## %",
            showInLegend: true,
            dataPoints: humidity
        }]
    });
    chart2.render();

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