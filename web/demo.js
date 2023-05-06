Module.onRuntimeInitialized = () => { start(); }

var canvas = document.getElementById("monCanvas");
var g = null


var noir = new Image()
noir.src = "../resources/images/noir.png"

var ImN = new Image()
ImN.src = "../resources/images/immu_noir.png"

var blanc = new Image()
blanc.src = "../resources/images/blanc.png"

var ImB = new Image()
ImB.src = "../resources/images/immu_blanc.png"

var erreur = new Image()
erreur.src = "../resources/images/erreur.png"

canvas.addEventListener('click', canvasLeftClick);        // left click event
canvas.addEventListener('contextmenu', canvasRightClick); // right click event


function canvasLeftClick(event) {
    var nb_rows = Module._nb_rows(g);
    var nb_cols = Module._nb_cols(g);
    event.preventDefault(); // prevent default context menu to appear...
    // get relative cursor position in canvas
    console.log("right left at position:", Math.floor(event.offsetX / (500 / nb_cols)), Math.floor(event.offsetY / (500 / nb_rows)));
    // update position of mario image used by drawCanvas()
    Module._play_move(g, Math.floor(event.offsetY / (500 / nb_rows)), Math.floor(event.offsetX / (500 / nb_cols)), 2)
    printGame(g)
}

function canvasRightClick(event) {
    var nb_rows = Module._nb_rows(g);
    var nb_cols = Module._nb_cols(g);
    event.preventDefault(); // prevent default context menu to appear...
    // get relative cursor position in canvas
    console.log("right click at position:", Math.floor(event.offsetX / (500 / nb_rows)), Math.floor(event.offsetY / (500 / nb_cols)));
    // update position of mario image used by drawCanvas()
    Module._play_move(g, Math.floor(event.offsetY / (500 / nb_rows)), Math.floor(event.offsetX / (500 / nb_cols)), 1)

    printGame(g)
}


function printGame(g) {

    var ctx = canvas.getContext("2d");
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    var nb_rows = Module._nb_rows(g);
    var nb_cols = Module._nb_cols(g);
    var cell_width = canvas.width / nb_cols;
    var cell_height = canvas.height / nb_rows;
    ctx.font = "30px Arial";

    // Dessine la grille
    ctx.strokeStyle = "#F98270";
    for (var row = 0; row <= nb_rows; row++) {
        var y = row * cell_height;
        ctx.beginPath();
        ctx.moveTo(0, y);
        ctx.lineTo(canvas.width, y);
        ctx.stroke();
    }
    for (var col = 0; col <= nb_cols; col++) {
        var x = col * cell_width;
        ctx.beginPath();
        ctx.moveTo(x, 0);
        ctx.lineTo(x, canvas.height);
        ctx.stroke();
    }

    for (var row = 0; row < nb_rows; row++) {
        for (var col = 0; col < nb_cols; col++) {
            var number = Module._get_number(g, row, col);
            var immutable = Module._is_immutable(g, row, col);
            var empty = Module._is_empty(g, row, col);
            var error = Module._has_error(g, row, col);

            var x = col * cell_width;
            var y = row * cell_height;
            if (!empty) {
                if (error)
                    ctx.drawImage(erreur, x, y, cell_width, cell_height);
                if (immutable && number == 0)
                    ctx.drawImage(ImB, x, y, cell_width, cell_height);
                else if (immutable && number == 1)
                    ctx.drawImage(ImN, x, y, cell_width, cell_height);
                else if (number == 0)
                    ctx.drawImage(blanc, x, y, cell_width, cell_height);
                else if (number == 1)
                    ctx.drawImage(noir, x, y, cell_width, cell_height);
            }
        }
    }
}

function start() {
    console.log("call start routine");
    g = Module._new_default();
    printGame(g);
}
