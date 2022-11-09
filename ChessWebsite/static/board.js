document.addEventListener("DOMContentLoaded", function () {
   
    table = document.createElement("BOARD");
    chessArea = document.getElementById("chessarea");
    table.id = "chessboard";
    chessArea.appendChild(table);
    
    //Fen string variables
    turn = "white-piece";
    pas = "-";
    cas = "KQkq";
    half = 0;
    full = 0;
    var en_pas_ignore = false;
    var flip = 0;
    curr_en_pas = null;

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

        turn = localStorage.turn;
        pas = localStorage.pas;
        cas = localStorage.cas;
        half = localStorage.half;
        full = localStorage.full;
 
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
            if(validMove(col, cur.parentNode, cur, 0)){
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
                //en_pas_ignore = false;

                full++;

                localStorage.half = half;
                localStorage.full = full;
            }
        }
        //Unselect the current piece
        else if(col.children[0] === cur){
                cur.classList.remove("current");
        }
        //Take a piece
        else if(col.children[0] !== undefined && ((cur.classList.contains("white-piece") && col.children[0].classList.contains("black-piece")) || (cur.classList.contains("black-piece") && col.children[0].classList.contains("white-piece")))){
            if(validMove(col, cur.parentNode, cur, 1)){
                half = 0;
                col.removeChild(col.children[0]);
                move(col, cur.parentNode, cur);
                full++;

                localStorage.half = half;
                localStorage.full = full;
            }
        }
        //Good attempt but there is already a piece there ;D
        else if(col.children[0] !== undefined){
            alert("Column already has a piece of the same color");
        }
        //Else nothing is currently selected and the selected square has no piece so do nothing

        if(en_pas_ignore === false){
            pas = "-";
            curr_en_pas =  null;
            localStorage.pas = pas;
        }else{
            en_pas_ignore = false;
        }

    }
 
    //Move piece from cur_col to new_col
    function move(new_col, cur_col, piece) {

        //No longer first move so first is removed
        if(piece.classList.contains("First")){
            piece.classList.remove("First");
        }
 
        //Moves the piece
        cur_col.removeChild(piece);
        new_col.appendChild(piece); 
        piece.classList.remove("current");

        turn = (turn === "white-piece") ? "black-piece" : "white-piece";
        localStorage.turn = turn;
    }
 
    function validMove(new_col, cur_col, piece, take){

        var new_index = [].indexOf.call(new_col.parentNode.children, new_col);
        var old_index = [].indexOf.call(cur_col.parentNode.children, cur_col);
        var diff;

        if(localStorage.flip === '1'){
            diff = 8;
        }else{
            diff = -8;
            console.log(localStorage.flip);
        }

        if((piece.classList.item(1) === "P") || (piece.classList.item(1) === "p")){
            
            console.log("value diff " + diff + " new " + new_index + " old " + old_index + " flipe " + localStorage.flip);
            //Move up one
            if(!take && (((new_index + diff) === old_index && piece.classList.item(0) === "black-piece") 
                || ((new_index - diff) === old_index && piece.classList.item(0) === "white-piece"))){
                //console.log("test hi");
                return true;
            }

            //For taking pieces diagonally
            if(take && (((((new_index + diff) - old_index) === 1 || ((new_index + diff) - old_index) === -1) 
                && piece.classList.item(0) === "black-piece") 
                || ((((new_index - diff) - old_index) === 1 || ((new_index - diff) - old_index) === -1) 
                && piece.classList.item(0) === "white-piece"))){
                //console.log("hit");
                return true;
            }

            //Move up two. Only valid on first move
            if(piece.classList.contains("First")){
                if(((new_index + (diff * 2)) === old_index && piece.classList.item(0) === "black-piece") 
                    || ((new_index - (diff * 2)) === old_index) && piece.classList.item(0) === "white-piece"){
                    
                    //Must have no piece one above
                    if(check_path(new_index, old_index)){
                        return true;
                    }
                }
            }

            //En pas check goes here

            alert("Invalid pawn move");
        }

        else if((piece.classList.item(1) === "Q") || (piece.classList.item(1) === "q")){
            
            //Checks up/down
            if((new_index % 8) === (old_index % 8)){
                if(check_path(new_index, old_index)){
                    return true;
                }
            }

            //Checks left and right
            if(Math.floor(new_index / 8) === Math.floor(old_index / 8)){
                if(check_path(new_index, old_index)){
                    return true;
                }
            }

            //Checks diagonaly
            if(((Math.floor(new_index / 8) * 8) + (new_index % 8)) === new_index){
                if(check_path_dia(new_index, old_index)){
                    return true;
                }
                //console.log("YIPPPE " + old_index + " " + (((new_index % 8) * 8) + (new_index % 8)));
            }

            alert("Invalid queen move");
        }

        /* Checks if the piece is a Rook or not and determines the valid moves */
        else if((piece.classList.item(1) === "R") || (piece.classList.item(1) === "r")){
            
            /* Veritcal movement */
            if((new_index % 8) === (old_index % 8)){
                if(check_path(new_index, old_index)){
                    return true;
                }
            }

            /* Horizontal movement */
            if(Math.floor(new_index / 8) === Math.floor(old_index / 8)){
                if(check_path(new_index, old_index)){
                    return true;
                }
                console.log("YIPPPE " + old_index + " " + (((new_index % 8) * 8) + (new_index % 8)));
            }

            alert("Invalid rook move");
        }

        /* Checks if the piece is a Bishop or not and determines the valid moves */
        else if((piece.classList.item(1) === "B") || (piece.classList.item(1) === "b")){

            /* If there is an attempted vertical move, we alert and return false */
            if((new_index % 8) === (old_index % 8)){
               if(check_path(new_index, old_index)){
                    alert("Invalid bishop move");
                    return false;
                }
            }

            /* IF there is an attempted horizontal move, we alert and return false */
            if(Math.floor(new_index / 8) === Math.floor(old_index / 8)){
                if(check_path(new_index, old_index)){
                    alert("Invalid bishop move");
                    return false;
                }
            }

            /* If there is attempted diagonal move, we return true and allow move */
            if(((Math.floor(new_index / 8) * 8) + (new_index % 8)) === new_index){
                if(check_path_dia(new_index, old_index)){
                    return true;
                }
            }
            
            alert("Invalid bishop move");
        }

        return false;
    }

    function check_path(new_index, old_index){

        board = document.getElementById("chessboard");
        var start;
        var end;

        //Up and Down
        if(new_index - old_index >= 8 || old_index - new_index >= 8){
            if(new_index > old_index){
                start = old_index;
                end = new_index;
            }else{
                start = new_index;
                end = old_index;
            }
            
            for(var i = start + 8; i < end; i += 8){
                if(board.children[i].children[0] !== undefined){
                    console.log("Zap at " + i);
                    return false;
                }
            }
        }
        //Left or right
        else{
            if(new_index < old_index){
                start = new_index;
                end = old_index
            }else{
                start = old_index;
                end = new_index;
            }

            for(var i = start + 1; i < end; i++){
                if(board.children[i].children[0] !== undefined){
                    console.log("Zap at " + i);
                    return false;
                }
            }
        }

        return true;
    }

    function check_path_dia(new_index, old_index){
        board = document.getElementById("chessboard");
        var start;
        var end;
        var side;
        if(new_index > old_index){
            end = old_index;
            start = new_index;
        }else{
            start = old_index;
            end = new_index;
        }

        //GOING UP
            console.log("UP");
            //Going right
            if((end % 8) > (start % 8)){
                console.log("Right");
                side = -1;
            }else{
                side = 1;
            }

            //console.log("Zap at " + i + " start " + start + " end " + end + " " + (start - (side + 8)));
            for(var i = (start - (side + 8)); i > end; i -= (side + 8)){
                //console.log("Zap at " + i + " start " + start + " end " + end + " " + (start - (side + 8)));
                if(board.children[i].children[0] !== undefined){
                    console.log("Zap at " + i + " start " + start + " end " + end + " " + (start - (side + 8)));
                    return false;
                }
            }

        return true;
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
            
            //If the board has been fliped it string add
            if(check === 0){
                pas = rows[new_index % 8];
                pas += 8 - Math.floor(new_index / 8);
                //console.log(rows[new_index % 8] + " " + (8 - Math.floor(new_index / 8)) + " enpas1 " + check + " " + localStorage.flip);
            }else{
                pas = rows[7 - (new_index % 8)]
                pas += 1 + Math.floor(new_index / 8);
                //console.log(rows[7 - (new_index % 8)] + " " + (1 + Math.floor(new_index / 8)) + " enpas2 " + check);
            }

            curr_en_pas = old_col.children[0];
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