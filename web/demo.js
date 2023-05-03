Module.onRuntimeInitialized = () => { start(); }

function printGame(g) {
    var text = "";
    var nb_rows = Module._nb_rows(g);
    var nb_cols = Module._nb_cols(g);
    for (var row = 0; row < nb_rows; row++) {
        for (var col = 0; col < nb_cols; col++) {
            var number = Module._get_number(g, row, col);
            var immutable = Module._is_immutable(g, row, col);
            var empty = Module._is_empty(g, row, col);
            // var error = Module._has_error(g, row, col);
            if (empty)
                text += " ";
            else if (immutable && number == 0)
                text += "W";
            else if (immutable && number == 1)
                text += "B";
            else if (number == 0)
                text += "w";
            else if (nummber == 1)
                text += "b";
            else text += "?";
        }
        text += "\n";
    }

    // put this text in <div> element with ID 'result'
    var elm = document.getElementById('result');
    elm.innerHTML = text;
}

function start() {
    console.log("call start routine");
    var g = Module._new_default();
    const LIGHTBULB = 1;
    Module._play_move(g, 0, 0, LIGHTBULB);
    printGame(g);
    Module._delete(g);
}

