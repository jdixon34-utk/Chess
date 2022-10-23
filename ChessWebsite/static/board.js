document.addEventListener("DOMContentLoaded", function () {
   
    table = document.createElement("BOARD");
    chessArea = document.getElementById("chessarea");
    table.id = "chessboard";
    chessArea.appendChild(table);
    
    turn = "white-piece";
    pas = "";
    cas = "KQks";
    half = 0;
    full = 0;


   
    for (var i = 1; i < 9; i++) {
        var col, child, piece;
 
        for (var j = 1; j < 9; j++) {
 
            //Create each square/column of the board
            col = document.createElement("COL");
            col.id = "col" + i + j;
            color = (i%2 === j%2) ? "white" : "black";
            col.classList.add(color);
 
            //Create the piece
            piece = document.createElement("DIV");
            piece.id = "piece" + i + j;
 
            //Lets the user click on columns to do moves
            col.onclick = function(e) {  
                moveStart(e, this);
            };
 
            document.getElementById("chessboard").appendChild(col);
 
 
            //Define the colors and piece type of the pieces
            if (i < 3) {
                document.getElementById("col" + i + j).appendChild(piece);
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
                }
            } else if (i > 6) {
                document.getElementById("col" + i + j).appendChild(piece);
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
            move(col, cur.parentNode, cur);
            if((cur.classList.contains("p") === true) || (cur.classList.contains("P") === true)){
                half = 0;
            }else{
                half++;
            }
            full++;
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
        }
        //Good attempt but there is already a piece there ;D
        else if(col.children[0] !== undefined){
            alert("Column already has a piece of the same color");
        }
        //Else nothing is currently selected and the selected square has no piece so do nothing

        //Temp del
        console.log(fen());
    }
 
    //Move piece from cur_col to new_col
    function move(new_col, cur_col, piece) {
        //console.log(new_col);
        //console.log(cur_col);
        //console.log(piece);
 
        cur_col.removeChild(piece);
        new_col.appendChild(piece);
 
        piece.classList.remove("current");


        //You would have to remove all classes store them then readd  them with the changed turn to keep order
        turn = (turn === "white-piece") ? "black-piece" : "white-piece";
    }
 
    function fen(){
 
        let fen = "";
 
        let tab = document.getElementById("chessboard");
 
        let count = tab.childElementCount;
 
        console.log("hi " + tab + " " + count + tab.children[0]);
 
        // iterate over all child nodes
        let space = 0;
        for(let i = 0; i < count; i++){
 
            if(tab.children[i].children[0] === undefined){
                space++;
            }else{
                if(space !== 0){
                    fen += space;
                }
                space = 0;
                fen += tab.children[i].children[0].classList.item(1);
            }
 
            if((((i + 1) % 8) === 0) && (i !== 63)){
                if(space !== 0){
                    fen += space;
                }
                fen += '/';
                space = 0;
                console.log(i);
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

  