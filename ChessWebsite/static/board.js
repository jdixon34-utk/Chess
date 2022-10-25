document.addEventListener("DOMContentLoaded", function () {
   
    table = document.createElement("BOARD");
    chessArea = document.getElementById("chessarea");
    table.id = "chessboard";
    chessArea.appendChild(table);
    
    turn = "white-piece";
    const pas = [];
    cas = "KQks";
    half = 0;
    full = 0;
    var en_pas_ignore = false;

    localStorage.turn = turn;
    localStorage.pas = pas;
    localStorage.cas = cas;
    localStorage.half = half;
    localStorage.full = full;
   
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
                piece.classList.add("white-piece");
                //Defines all the pieces for the white side
                if(i === 1){
                    if(j === 1 || j === 8){
                        piece.classList.add("R");
                    }else if(j === 2 || j === 7){
                        piece.classList.add("N");
                    }else if(j === 3 || j === 6){
                        piece.classList.add("B");
                    }else if(j === 4){
                        piece.classList.add("Q");
                    }else{
                        piece.classList.add("K");
                    }
                }else{
                    piece.classList.add("P");
                    piece.classList.add("W_p");
                    piece.classList.add("First");
                }
            } else if (i > 6) {
                document.getElementById(((i-1) * 8) + (j-1)).appendChild(piece);
                piece.classList.add("black-piece");
                //Define all the pieces for the black side
                if(i === 8){
                    if(j === 1 || j === 8){
                        piece.classList.add("r");
                        piece.classList.add("B_r");
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
                    }
                }else{
                    piece.classList.add("p");
                    piece.classList.add("B_p");
                    piece.classList.add("First");
                }
            }
        }
 
    }

    //var hold = document.createElement("FEN");
    //hold.id = "hidden";
    //hold.classList.add("white-piece");
    //hold.classList.add("temp");
    //hold.classList.add("KQks");
    //hold.classList.add(0);
    //hold.classList.add(51);
    //turn = "white-piece";
    //pas = "";
    //cas = "KQks";
    //half = 0;
    //full = 0;
    //document.getElementById("chessboard").appendChild(hold);
 
 
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
            if((cur.classList.contains("B_p") === true) || (cur.classList.contains("P") === true)){
                half = 0;
                
                if(cur.classList.contains("First")){
                    en_Pas(col, cur.parentNode);
                }

            }else{
                half++;
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

        //Temp del
        //console.log(fen());
    }
 
    //Move piece from cur_col to new_col
    function move(new_col, cur_col, piece) {
        //console.log(new_col);
        //console.log(cur_col);
        //console.log(piece);

        if(piece.classList.contains("First")){
            piece.classList.remove("First");
        }else if(piece.classList.contains("en_Pas") && en_pas_ignore !== true){
            
            //remove from pas array
            console.log(piece.classList.item(3) + " " + piece.classList.item(4))
            
            pas[piece.classList.item(4)] = ',';
            localStorage.pas = pas;

            piece.classList.remove(piece.classList.item(3));
            piece.classList.remove(piece.classList.item(4));

        }
 
        cur_col.removeChild(piece);
        new_col.appendChild(piece);
 
        piece.classList.remove("current");


        //You would have to remove all classes store them then readd  them with the changed turn to keep order
        turn = (turn === "white-piece") ? "black-piece" : "white-piece";
        localStorage.turn = turn;
    }
 
    
    function en_Pas(new_col, old_col){

        //Rows of the board
        const rows = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'];
        
        //Gets the indexs of columns in the board
        var new_index = [].indexOf.call(new_col.parentNode.children, new_col);
        var old_index = [].indexOf.call(old_col.parentNode.children, old_col);
        
        //console.log(old_index + " " + new_index); 
        
        //might not be an En Passant so we check
        if((old_index + 16) === new_index || (old_index - 16) === new_index){
            
            console.log(rows[new_index % 8] + " " + Math.floor(new_index / 8));
            old_col.children[0].classList.add("en_Pas");
            var length = pas.length;

            old_col.children[0].classList.add(pas.length);

            pas.push(rows[new_index % 8]);
            pas.push(Math.floor(new_index / 8) + 1);

            //pas.push(final);
            localStorage.pas = pas;

            en_pas_ignore = true;
        }

    }

    function fen(){
 
        let fen = "";
 
        let tab = document.getElementById("chessboard");
 
        let count = tab.childElementCount;
 
        console.log("hi " + tab + " " + count + tab.children[0]);
 
        // iterate over all child nodes
        let space = 0;
        for(let i = 7; i >= 0; i--){
        for(let j = 0; j < 8; j++){

            //Add a space if there is no piece
            //console.log((i * 8) + j);
            if(tab.children[(i * 8) + j].children[0] === undefined){
                space++;
            }else{
                //Add the spaces
                if(space !== 0){
                    fen += space;
                    space = 0;
                }
                fen += tab.children[(i * 8) + j].children[0].classList.item(1);
            }
    
            if(j === 7 && i !== 0){
                if(space !== 0){
                    fen += space;
                }
                fen += '/';
                space = 0;
                //console.log((i * 8) + j);
            }
        }
    }
 
        fen += ' ';
 
        //Whose turn is it
        //b = black | white = w
        //Don't have this in front end yet
       
        let t = (turn === "white-piece") ? "w" : "b";
        
        fen += t + ' ';
 
        //Next you say what castling is available
        //q = castle queenside possible
        //k = castle kingside
        //Can be either KQkq or Qk- or -- or etc
        fen += cas + ' ';
 
        //Next you do en passant targets
        //you give it in terms of squares like e3.
        //This is different then how squares are named so will
        //Need to convert that either here or where they are made.
 
        //fen += pas + ' ';
 
        //Next is how many moves both players have made since the last pawn advance or piece capture
        //Global variable I assume, given as 99 or some other number
        //Game ends if draw if this is 100
 
        fen += half + ' ';
        //fen += " "
 
        //Last field is the number of completed turns in the game.
        //This number is incremented by one every time Black moves.
        //Global variable, is just a number
 
        fen += full + ' ';
 
        return fen;
    }

  });
  
 
  });
