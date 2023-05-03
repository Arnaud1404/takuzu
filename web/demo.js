Module.onRuntimeInitialized = () => { start(); }

var canvas = document.getElementById("monCanvas");



canvas.addEventListener('click', canvasLeftClick);        // left click event
canvas.addEventListener('contextmenu', canvasRightClick); // right click event


function canvasLeftClick(event) {
    var g = Module._new_default();
    event.preventDefault(); // prevent default context menu to appear...
    // get relative cursor position in canvas
    console.log("right click at position:", Math.floor(event.offsetX / 83), Math.floor(event.offsetY / 83))
    Module._play_move(g, Math.floor(event.offsetY / 83), Math.floor(event.offsetX / 83), 2)
    printGame(g)
}

function canvasRightClick(event) {
    var g = Module._new_default();
    event.preventDefault(); // prevent default context menu to appear...
    // get relative cursor position in canvas
    console.log("right click at position:", Math.floor(event.offsetX / 83), Math.floor(event.offsetY / 83));
    // update position of mario image used by drawCanvas()
    Module._play_move(g, Math.floor(event.offsetY / 83), Math.floor(event.offsetX / 83), 1)
    printGame(g)
}


function printGame(g) {
    var ctx = canvas.getContext("2d");

    var nb_rows = Module._nb_rows(g);
    var nb_cols = Module._nb_cols(g);
    var cell_width = canvas.width / nb_cols;
    var cell_height = canvas.height / nb_rows;
    ctx.font = "30px Arial";

    for (var row = 0; row < nb_rows; row++) {
        for (var col = 0; col < nb_cols; col++) {
            var number = Module._get_number(g, row, col);
            var immutable = Module._is_immutable(g, row, col);
            var empty = Module._is_empty(g, row, col);
            // var error = Module._has_error(g, row, col);

            var x = col * cell_width;
            var y = row * cell_height;

            if (empty)
                ctx.fillText(" ", x + cell_width / 2, y + cell_height / 2);
            else if (immutable && number == 0)
                ctx.fillText("W", x + cell_width / 2, y + cell_height / 2);
            else if (immutable && number == 1)
                ctx.fillText("B", x + cell_width / 2, y + cell_height / 2);
            else if (!immutable && number == 0)
                ctx.fillText("w", x + cell_width / 2, y + cell_height / 2);
            else if (number == 1)
                ctx.fillText("b", x + cell_width / 2, y + cell_height / 2);
            else ctx.fillText("?", x + cell_width / 2, y + cell_height / 2);
        }
    }
}

function start() {
    console.log("call start routine");
    var g = Module._new_default();
    const LIGHTBULB = 0;
    printGame(g);
    Module._delete(g);
}

