// Please see documentation at https://docs.microsoft.com/aspnet/core/client-side/bundling-and-minification
// for details on configuring this project to bundle and minify static web assets.

// Write your JavaScript code.

const uri = "http://api.mj-software.dk/data/latest/"

data = function (num) {
    fetch(uri + num)
        .then(response => response.json())
        .then(data => console.log(data))
}
