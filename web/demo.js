Module.onRuntimeInitialized = () => { start(); }

var canvas = document.getElementById("grille");
var g = null
var size = 83

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
	var mouse_x = event.offsetX,mouse_y= event.offsetY;
    event.preventDefault(); // prevent default context menu to appear...
    // get relative cursor position in canvas
    // update position of mario image used by drawCanvas()
	var i = Math.floor(mouse_y/ size);
    var j = Math.floor(mouse_x/ size);
	console.log("right left at position:", i,j);
    if (Module._is_empty(g, i,j)) {
        Module._play_move(g,i,j, 2);
    } else {
        Module._play_move(g,i,j, 0);
    }
    printGame(g)
	if(Module._is_over(g))
        setTimeout(function() { alert("Jeu gagné, restart ou nouveau jeu ?"); }, 0);
}

function canvasRightClick(event) {
	var mouse_x = event.offsetX,mouse_y= event.offsetY;
    event.preventDefault(); // prevent default context menu to appear...
    // get relative cursor position in canvas
    // update position of mario image used by drawCanvas()
	var i = Math.floor(mouse_y/ size);
    var j = Math.floor(mouse_x/ size);
	console.log("right left at position:", i,j);
    if (Module._is_empty(g, i,j)) {
        Module._play_move(g,i,j, 1);
    } else {
        Module._play_move(g,i,j, 0);
    }
    printGame(g)
	if(Module._is_over(g))
        setTimeout(function() { alert("Jeu gagné, restart ou nouveau jeu ?"); }, 0);
}


function printGame(g) {

    var ctx = canvas.getContext("2d");
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    var nb_rows = Module._nb_rows(g);
    var nb_cols = Module._nb_cols(g);
    ctx.font = "30px Arial";
    // Dessine la grille
    ctx.strokeStyle = "#F98270";
    for (var row = 0; row <= nb_rows; row++) {
        var y = row * size;
        ctx.beginPath();
        ctx.moveTo(0, y);
        ctx.lineTo(size*nb_cols, y);
        ctx.stroke();
    }
    for (var col = 0; col <= nb_cols; col++) {
        var x = col * size;
        ctx.beginPath();
        ctx.moveTo(x, 0);
        ctx.lineTo(x,size*nb_rows);
        ctx.stroke();
    }

    for (var row = 0; row < nb_rows; row++) {
        for (var col = 0; col < nb_cols; col++) {
            var number = Module._get_number(g, row, col);
            var immutable = Module._is_immutable(g, row, col);
            var empty = Module._is_empty(g, row, col);
            var error = Module._has_error(g, row, col);
			console.log(row,col,"couleur",number);
            var x = col * size;
            var y = row * size;
            if (!empty) {
                if (error)
                    ctx.drawImage(erreur, x, y, size, size);
                if (immutable && number == 0)
                    ctx.drawImage(ImB, x, y, size, size);
                else if (immutable && number == 1)
                    ctx.drawImage(ImN, x, y, size, size);
                else if (number == 0){
                    ctx.drawImage(blanc, x, y, size, size);
					console.log("blanc en case",x,y);}
                else if (number == 1){
                    ctx.drawImage(noir, x, y, size, size);
					console.log("noir en case",x,y);}
					
            }
        }
    }
}
//buttons
const restart = document.getElementById("restart");
restart.addEventListener("click", function() {
    Module._restart(g)
    printGame(g)
  });
const solve = document.getElementById("solve");
solve.addEventListener("click", function() {
	Module._restart(g)
    Module._solve(g)
	console.log(Module._solve(g))
    printGame(g)
	if(Module._is_over(g))
        setTimeout(function() { alert("Jeu gagné, restart ou nouveau jeu ?"); }, 0);
});
const undo = document.getElementById("undo");
undo.addEventListener("click", function() {
    Module._undo(g)
    printGame(g)
});
const redo = document.getElementById("redo");
redo.addEventListener("click", function() {
    Module._redo(g)
    printGame(g)
	if(Module._is_over(g))
        setTimeout(function() { alert("Jeu gagné, restart ou nouveau jeu ?"); }, 0);
});

const random = document.getElementById("random");
random.addEventListener("click", function() {
	Module._delete(g)
	var row =document.getElementById("rows_selector");
	var col = document.getElementById("cols_selector");
	var wrapping = document.getElementById("wrapping");
	var unique = document.getElementById("unique");
    g = Module._new_random(row.value,col.value,wrapping.checked,unique.checked)
	size = Math.min(Math.floor(500/Module._nb_rows(g)),Math.floor(500/Module._nb_cols(g)))
    printGame(g)
});



function start() {
    console.log("call start routine");
    g = Module._new_default();
    printGame(g);
}

Règles.addEventListener("click", function () {
    Popup.classList.add("show");
});      
closePopup.addEventListener("click", function () {
    Popup.classList.remove("show");
});
window.addEventListener("click", function (event) {
    if (event.target == Popup) {
        Popup.classList.remove("show");
    }
});

Commandes.addEventListener("click", function () {
    Popup1.classList.add("show");
});
closePopup1.addEventListener("click", function () {
    Popup1.classList.remove("show");
});
window.addEventListener("click", function (event) {
    if (event.target == Popup1) {
        Popup1.classList.remove("show");
    }
});