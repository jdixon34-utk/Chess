document.addEventListener("DOMContentLoaded", function () {
   
    table = document.createElement("BOARD");
    chessArea = document.getElementById("chessarea");
    table.id = "chessboard";
    chessArea.appendChild(table);
    
    //Fen string variables
    turn = "white-piece";
    const pas = [];
    cas = "KQkq";
    half = 0;
    full = 0;
    var en_pas_ignore = false;
    var flip = "no";

    //Lets these variables be used in the .html file and any files .js files in the .html
    localStorage.turn = turn;
    localStorage.pas = pas;
    localStorage.cas = cas;
    localStorage.half = half;
    localStorage.full = full;
    localStorage.flip = flip;
   
    const rows = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'];
    //Create the squares and pieces
    for (var i = 1; i < 9; i++) {
        var col, child, piece;
 
        for (var j = 1; j < 9; j++) {
 
            //Create each square/column of the board
            col = document.createElement("COL");
            col.id = ((i-1) * 8) + (j-1);
            color = (i%2 === j%2) ? "white" : "black";
            col.classList.add(color);
 
            //Create the piece
            piece = document.createElement("DIV");
            piece.id = "fd" + i + j;
 
            //Lets the user click on columns to do moves
            col.onclick = function(e) {  
                moveStart(e, this);
            };
 
            document.getElementById("chessboard").appendChild(col);
 
 
            //Define the colors and piece type of the pieces
            if (i < 3) {
                document.getElementById(((i-1) * 8) + (j-1)).appendChild(piece);
                piece.classList.add("black-piece");
                //Define all the pieces for the black side
                if(i === 1){
                    if(j === 1){
                        piece.classList.add("r");
                        piece.classList.add("B_r");
                        piece.classList.add("First");
                        piece.classList.add(2);
                    }else if(j === 8){
                        piece.classList.add("r");
                        piece.classList.add("B_r");
                        piece.classList.add("First");
                        piece.classList.add(3);   
                    }else if(j === 2 || j === 7){
                        piece.classList.add("n");
                        piece.classList.add("B_n");
                    }else if(j === 3 || j === 6){
                        piece.classList.add("b");
                        piece.classList.add("B_b");
                    }else if(j === 4){
                        piece.classList.add("q");
                        piece.classList.add("B_q");
                    }else{
                        piece.classList.add("k");
                        piece.classList.add("B_k");
                        piece.classList.add("First");
                    }
                }else{
                    piece.classList.add("p");
                    piece.classList.add("B_p");
                    piece.classList.add("First");
                }
            }
            else if (i > 6) {
                document.getElementById(((i-1) * 8) + (j-1)).appendChild(piece);
                piece.classList.add("white-piece");
                //Defines all the pieces for the white side
                if(i === 8){
                    if(j === 1){
                        piece.classList.add("R");
                        piece.classList.add("W_r");
                        piece.classList.add("First");
                        piece.classList.add(0);
                    }else if(j === 8){
                        piece.classList.add("R");
                        piece.classList.add("W_r");
                        piece.classList.add("First");
                        piece.classList.add(1); 
                    }    
                    else if(j === 2 || j === 7){
                        piece.classList.add("N");
                    }else if(j === 3 || j === 6){
                        piece.classList.add("B");
                    }else if(j === 4){
                        piece.classList.add("Q");
                    }else{
                        piece.classList.add("K");
                        piece.classList.add("First");
                    }
                }else{
                    piece.classList.add("P");
                    piece.classList.add("W_p");
                    piece.classList.add("First");
                }
            }
        }
 
    } 
 
    //Checks if a move is valid, if so does the move
    //e is click event, not used.
    //Col is the column the user clicked on
    function moveStart(e, col){
 
        //Current piece selected, will be undefined at start
        var cur = document.getElementsByClassName("current")[0];
       
        //Nothing is currently selected and column selected has a piece
        if(cur === undefined && col.children[0] !== undefined){
            if(col.children[0].classList.item(0) === turn){
                col.children[0].classList.add("current");
            }else{
                alert("It is currently " + turn + "'s turn.");
                console.log(col.children[0].classList.item(0) + " " + half);
            }
        }
        //Valid move. So move the piece
        else if(cur !== undefined && col.children[0] === undefined){
            
            //IF a pawn checks if an en passant is now valid
            if((cur.classList.contains("B_p") === true) || (cur.classList.contains("P") === true)){
                half = 0;
                
                if(cur.classList.contains("First")){
                    en_Pas(col, cur.parentNode);
                }

            }else{
                half++;
            }

            if(((cur.classList.contains("k") || cur.classList.contains("K")) || ((cur.classList.contains("r") || cur.classList.contains("R")))) 
                && cur.classList.contains("First")){
                    castling(cur);
            }

            move(col, cur.parentNode, cur);
            en_pas_ignore = false;

            full++;

            localStorage.half = half;
            localStorage.full = full;
        }
        //Unselect the current piece
        else if(col.children[0] === cur){
                cur.classList.remove("current");
        }
        //Take a piece
        else if(col.children[0] !== undefined && ((cur.classList.contains("white-piece") && col.children[0].classList.contains("black-piece")) || (cur.classList.contains("black-piece") && col.children[0].classList.contains("white-piece")))){
            half = 0;
            col.removeChild(col.children[0]);
            move(col, cur.parentNode, cur);
            full++;

            localStorage.half = half;
            localStorage.full = full;
        }
        //Good attempt but there is already a piece there ;D
        else if(col.children[0] !== undefined){
            alert("Column already has a piece of the same color");
        }
        //Else nothing is currently selected and the selected square has no piece so do nothing

    }
 
    //Move piece from cur_col to new_col
    function move(new_col, cur_col, piece) {

        //En passant stuff
        //No longer first move so first is removed
        if(piece.classList.contains("First")){
            piece.classList.remove("First");
        }else if(piece.classList.contains("en_Pas") && en_pas_ignore !== true){
            
            //Item 4 tells us the index the piece is at in the pas array
            pas[piece.classList.item(4)] = ',';
            localStorage.pas = pas;

            piece.classList.remove(piece.classList.item(3));
            piece.classList.remove(piece.classList.item(4));

        }
 
        //Moves the piece
        cur_col.removeChild(piece);
        new_col.appendChild(piece); 
        piece.classList.remove("current");

        turn = (turn === "white-piece") ? "black-piece" : "white-piece";
        localStorage.turn = turn;
    }
 

    //Checks if an en passant is valid and sets the pieces class
    function en_Pas(new_col, old_col){

        //Rows of the board
        const rows = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'];
        
        //Gets the indexs of columns in the board
        var new_index = [].indexOf.call(new_col.parentNode.children, new_col);
        var old_index = [].indexOf.call(old_col.parentNode.children, old_col);
        var check = localStorage.flip;
        
        //Might not be an En Passant so we check
        if((old_index + 16) === new_index || (old_index - 16) === new_index){
            
            //Temporary debugging print
 
            //Add a class setting the piece as currently possible en Passant and the index of the array it is located in
            old_col.children[0].classList.add("en_Pas");
            var length = pas.length;
            old_col.children[0].classList.add(pas.length);

            //Push the row and column of the piece
            //pas.push(rows[new_index % 8]);
            
            //If the board has been fliped it changes the push
            console.log("hi " + localStorage.flip);
            if(check === "no"){
                pas.push(rows[new_index % 8]);
                pas.push(8 - Math.floor(new_index / 8));
                console.log(rows[new_index % 8] + " " + (8 - Math.floor(new_index / 8)) + " enpas1 " + check + " " + localStorage.flip);
            }else{
                pas.push(rows[7 - (new_index % 8)]);
                pas.push(1 + Math.floor(new_index / 8));
                console.log(rows[7 - (new_index % 8)] + " " + (1 + Math.floor(new_index / 8)) + " enpas2 " + check);
            }

            localStorage.pas = pas;
            en_pas_ignore = true;
        }

    }

    function castling(piece){

        const options = ['K', 'Q', 'k', 'q'];

        var a, b;

        if(piece.classList.contains("r") || piece.classList.contains("R")){
            b = cas.replace(options[piece.classList.item(4)], '');
        }else if(piece.classList.contains("K")){
            a = cas.replace("K", '');
            document.getElementsByClassName(0)[0].classList.remove("First");
            b = a.replace("Q", '');
            document.getElementsByClassName(1)[0].classList.remove("First");
        }else{
            a = cas.replace("k", '');
            document.getElementsByClassName(2)[0].classList.remove("First");
            b = a.replace("q", '');
            document.getElementsByClassName(3)[0].classList.remove("First");
        }

        piece.classList.remove("First");

        cas = b;
        localStorage.cas = cas;
    }

  });