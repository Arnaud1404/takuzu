var canvas = document.getElementById('mycanvas');
var ctx = canvas.getContext('2d');
ctx.save();
ctx.fillStyle = 'yellow';
ctx.fillRect(100, 100, 80, 80);
ctx.restore();
