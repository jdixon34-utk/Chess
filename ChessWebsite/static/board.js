//document.addEventListener("DOMContentLoaded", function () {
   
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
    curr_en_pas = "null";
    win_con = null;
    var past_fen = new Array(0);
    var pro;

    //Lets these variables be used in the .html file and any files .js files in the .html
    localStorage.turn = turn;
    localStorage.pas = pas;
    localStorage.cas = cas;
    localStorage.half = half;
    localStorage.full = full;
    localStorage.flip = flip;
    localStorage.curr_en_pas = curr_en_pas;
    localStorage.test = "bye";
   
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
                //Uncomment to test checkmate and stalemate
                //if((i === 1 && j === 5) || (i === 1 && j === 4)){
                //|| (i === 1 && j === 4) || (i === 1 && j === 8) || (i === 1 && j === 1))
                //{
                    document.getElementById(((i-1) * 8) + (j-1)).appendChild(piece);
                    piece.classList.add("black-piece");
                //}

                //Define all the pieces for the black side
                if(i === 1){
                    if(j === 1){
                        piece.classList.add("r");
                        piece.classList.add("B_r");
                        piece.classList.add("First");
                        piece.classList.add(3);
                    }else if(j === 8){
                        piece.classList.add("r");
                        piece.classList.add("B_r");
                        piece.classList.add("First");
                        piece.classList.add(2);   
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
                //Uncomment to test stalemate and checkmate
                //if((i === 8 && j === 5) || (i === 8 && j === 6)){
                    document.getElementById(((i-1) * 8) + (j-1)).appendChild(piece);
                    piece.classList.add("white-piece");
                //}
                //Defines all the pieces for the white side
                if(i === 8){
                    if(j === 1){
                        piece.classList.add("R");
                        piece.classList.add("W_r");
                        piece.classList.add("First");
                        piece.classList.add(1);
                    }else if(j === 8){
                        piece.classList.add("R");
                        piece.classList.add("W_r");
                        piece.classList.add("First");
                        piece.classList.add(0); 
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
                        piece.classList.add("W_K");
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
        curr_en_pas = localStorage.curr_en_pas;
        var check = false;
        pro = false;
        test = localStorage.test;

        //A win or tie has been reached, this will not allow the user to make another move
        if(win_con !== null){
            alert(win_con);
            return;
        }

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

            let side, color, diff;
            if(turn === "white-piece"){
                color = "w";
            }else{
                color = "b";
            }

            diff = ([].indexOf.call(col.parentNode.children, col)) - ([].indexOf.call(cur.parentNode.parentNode.children, cur.parentNode));
            if(diff > 0){
                side = 1;
            }else{
                side = 0;
            }
                

            //Testes if this is a castling move
            if((cur.classList.contains("k") || cur.classList.contains("K")) && Math.abs(diff) === 2 && valid_castling(side, color)){
                console.log("Just castled");
                
                full++;

                turn = (turn === "white-piece") ? "black-piece" : "white-piece";
        
                localStorage.turn = turn;
                localStorage.half = half;
                localStorage.full = full;

                check = true;
            }
            //Tests if this is actually a valid move
            else if(validMove(col, cur.parentNode, cur, 0, 0) && !king_check(col, cur.parentNode, cur, 0, 0)){
                
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

                move(col, cur.parentNode, cur)

                full++;

                localStorage.half = half;
                localStorage.full = full;

                check = true;
            }
        }
            //Unselect the current piece
        else if(col.children[0] === cur){
                cur.classList.remove("current");
        }
        //Take a piece
        else if(col.children[0] !== undefined && ((cur.classList.contains("white-piece") && col.children[0].classList.contains("black-piece")) || (cur.classList.contains("black-piece") && col.children[0].classList.contains("white-piece")))){
                
            //Tests if this is a valid move
            if(validMove(col, cur.parentNode, cur, 1, 0) && !king_check(col, cur.parentNode, cur, 1, 0)){
                    
                half = 0;

                if(((cur.classList.contains("k") || cur.classList.contains("K")) || ((cur.classList.contains("r") || cur.classList.contains("R")))) 
                    && cur.classList.contains("First")){
                        castling(cur);
                }

                if(((col.children[0].classList.contains("k") || col.children[0].classList.contains("K")) 
                    || ((col.children[0].classList.contains("r") || col.children[0].classList.contains("R")))) 
                    && col.children[0].classList.contains("First")){
                        castling(col.children[0]);
                }

                col.removeChild(col.children[0]);
                move(col, cur.parentNode, cur);
                    
                full++;

                localStorage.half = half;
                localStorage.full = full;

                check = true;

            }
        }
        //Good attempt but there is already a piece there ;D
        else if(col.children[0] !== undefined){
            //alert("Column already has a piece of the same color");
            cur.classList.remove("current");
            col.children[0].classList.add("current");  
        }
        //Else nothing is currently selected and the selected square has no piece so do nothing

        //The current en passant possibility was not used so reset it.
        if(en_pas_ignore === false){
            console.log("en_{pas_ignore");
            pas = "-";
            curr_en_pas =  "null";
            localStorage.curr_en_pas = curr_en_pas;
            localStorage.pas = pas;
        }else{
            en_pas_ignore = false;
        }
        
        if(check && !pro){
            
            //Game ends in tie if the turn timer is 100 or the half turn timer is 50
            if(full === "100"){
                alert("100 turn timer reached. The game has ended in a tie.");
                win_con = "Game has ended in a tie by turn timer. Please refresh the page to play again";
                return;
            }else if(half === "50"){
                alert("50 half-turn timer reached. The game has ended in a tie.");
                win_con = "Game has ended in a tie by half-turn timer. Please refresh the page to play again";
                return;
            }

            //Three repition rule
            if(three_rep()){
                alert("Threefold repetition has occured. The game has ended in a tie.");
                win_con = "Game has ended in a tie by threefold repetition. Please refresh the page to play again";
                return;
            }

            //Tests if the game has ended in a stalemate or a checkmate
            if(stalemate()){

                let index;
                turn = localStorage.turn;
                if(turn === "white-piece"){
                    color = "w";
                    king_loc = document.querySelector(".W_K"); 
                    index = [].indexOf.call(king_loc.parentNode.parentNode.children, king_loc.parentNode);
                }else{
                    color = "b";
                    king_loc = document.querySelector(".b_k"); 
                    index = [].indexOf.call(king_loc.parentNode.parentNode.children, king_loc.parentNode);
                }


                //Getting here means that there are no possible valid moves for the current color.
                //If the king is in check it is a checkmate, if not then it is a stalemate.
                if(in_check(index, color)){
                    victory = (turn === "white-piece") ? "black-piece" : "white-piece";
                    alert("Checkmate! " + victory + " has won!");
                    win_con = "The game has ended with " + victory + " winning by checkmate. Please refresh the page to play again";
                    return;
                }else{
                    alert("Tie! You have reached a stalemate");
                    win_con = "The game has ended in a tie by stalemate. Please refresh the page to play again";
                    return;
                }
            }

            //Tests if there is enough pieces to force a checkmate
            if(insufficient_materials()){
                alert("Tie! By insufficient materials.");
                win_con = "The game has ended in a tie by insufficient materials. Please refresh the page to play again";
                return;
            }

            //Calls the engine after 1 millisecond
            //if(pro){
            //    setTimeout(engine_move,8000);
            //}else{
                setTimeout(engine_move,1);
            //}
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

        var piece_index = [].indexOf.call(piece.parentNode.parentNode.children, piece.parentNode);

        //let pro = false;
        //Pawn promotion
        if((piece.classList.contains("P") || piece.classList.contains("p")) && (piece_index < 8 || piece_index > 55)){
            pawn_promotion(piece);
            pro = true;
        }

        turn = (turn === "white-piece") ? "black-piece" : "white-piece";
        localStorage.turn = turn;

        //if(pro){
            return "p"
        //}
    }


    //Checks if the move is valid. For example, a rook only move left or right
    //Take === 1 when you are taking a piece, used for pawns.
    //Stale === 1 if this is a stalemate check. This is to not use the alerts
    function validMove(new_col, cur_col, piece, take, stale){

        var new_index = [].indexOf.call(new_col.parentNode.children, new_col);
        var old_index = [].indexOf.call(cur_col.parentNode.children, cur_col);
        var diff;

        if(localStorage.flip === '1'){
            diff = 8;
        }else{
            diff = -8;
        }
        /* Checks if the piece is a Pawn or not and determines the valid moves */
        if((piece.classList.item(1) === "P") || (piece.classList.item(1) === "p")){
            
            //Move up one
            if(!take && (Math.floor(new_index / 8) !== Math.floor(old_index / 8)) && (((new_index + diff) === old_index && piece.classList.item(0) === "black-piece") 
                || ((new_index - diff) === old_index && piece.classList.item(0) === "white-piece"))){

                    if(!stale){
                        console.log("Hit Yeah " + new_index + " " + old_index);
                    }
                return true;
            }

            //For taking pieces diagonally
            if(take && (Math.floor(new_index / 8) !== Math.floor(old_index / 8)) && (((Math.abs((new_index + diff) - old_index) === 1) && piece.classList.item(0) === "black-piece") 
                || ((Math.abs((new_index - diff) - old_index) === 1) && piece.classList.item(0) === "white-piece"))){

                    if(!stale){
                        console.log("Hit Yeah dia " + new_index + " " + old_index);
                    }

                return true;
            }

            //Move up two. Only valid on first move
            if(piece.classList.contains("First")){
                if(Math.abs(Math.floor(new_index / 8) - Math.floor(old_index / 8)) === 2 && (((new_index + (diff * 2)) === old_index && piece.classList.item(0) === "black-piece") 
                    || ((new_index - (diff * 2)) === old_index) && piece.classList.item(0) === "white-piece")){
                    
                    //Must have no piece one above the pawn moving
                    if(check_path(new_index, old_index)){
                        return true;
                    }
                }
            }

            //En passant is checked here
            board = document.getElementById("chessboard");
            if(((new_index + 8).toString() === curr_en_pas || (new_index - 8).toString() === curr_en_pas) && 
                (((Math.abs((new_index + diff) - old_index) === 1) && piece.classList.item(0) === "black-piece") 
                || ((Math.abs((new_index - diff) - old_index) === 1) && piece.classList.item(0) === "white-piece"))){
                
                if(!stale){
                    console.log("Hit Yeah enpas " + new_index + " " + old_index + " " + curr_en_pas);
                }

                //Delete the piece if this is not stalemate checking
                if(!stale){
                    board.children[curr_en_pas].removeChild(board.children[curr_en_pas].children[0]);
                }
                return true;
            }

            if(!stale){
                alert("Invalid pawn move");
            }
        }
        /* Checks if the piece is a Queen or not and determines the valid moves */
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

            //Checks diagonally
            if(Math.abs((new_index % 8) - (old_index % 8)) === Math.abs(Math.floor(new_index / 8) - Math.floor(old_index / 8))){
                if(check_path_dia(new_index, old_index)){
                    return true;
                }
            }

            if(!stale){
                alert("Invalid queen move");
            }
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
            }

            if(!stale){
                alert("Invalid rook move");
            }
        }

        /* Checks if the piece is a Bishop or not and determines the valid moves */
        else if((piece.classList.item(1) === "B") || (piece.classList.item(1) === "b")){


            /* If there is attempted diagonal move, we return true and allow move */
            if(Math.abs((new_index % 8) - (old_index % 8)) === Math.abs(Math.floor(new_index / 8) - Math.floor(old_index / 8)) && (Math.abs(new_index - old_index) !== 1)){
                if(check_path_dia(new_index, old_index)){
                    return true;
                }
            }
            
            if(!stale){
                alert("Invalid bishop move");
            }
        }

        /* Checks if the piece is a King or not and determines the valid moves */
        else if((piece.classList.contains("K") === true) || (piece.classList.contains("k") === true)){

            
            /* If there is attempted diagonal move, we return true and allow move */
            if((( 6 < Math.abs(new_index - old_index) && Math.abs(new_index - old_index) < 10) 
                && (Math.abs(Math.floor(new_index / 8) - Math.floor(old_index / 8)) === 1)) 
                || ((Math.abs(new_index - old_index) === 1) && (Math.floor(new_index / 8) - Math.floor(old_index / 8) === 0))){
                
                return true;
            }
            
            if(!stale){
                alert("Invalid king move");
            }
        }

        /* Piece is a Knight and we determine the valid moves */
        else{

            if(((Math.abs(new_index - old_index) === 15 || Math.abs(new_index - old_index) === 17) 
            && Math.abs(Math.floor((new_index - (new_index % 8)) / 8) - Math.floor((old_index - (old_index % 8)) / 8)) === 2)
            || ((Math.abs(new_index - old_index) === 10 || Math.abs(new_index - old_index) === 6) && Math.abs((new_index % 8) - (old_index % 8)) === 2)){
                
                return true;
            }

            if(!stale){
                alert("Invalid knight move");
            }
        }

        return false;
    }

    //Return true if the match ends in a stalemate or checkmate
    function stalemate(){

        board = document.getElementById("chessboard");
        turn = localStorage.turn;

        //Loop over ever piece and test every possible move to see if it is not in check or not after all of them
        for(var i = 0; i < 64; i++){
            
            if(board.children[i].children[0] !== undefined && board.children[i].children[0].classList.contains(turn)){
                for(var j = 0; j < 64; j++){
                    if(i !== j){
                        //Sees if taking a piece will be in check
                        if(board.children[j].children[0] !== undefined && 
                            !board.children[j].children[0].classList.contains(turn)){

                            if(validMove(board.children[j], board.children[i], board.children[i].children[0], 1, 1)
                                && !king_check(board.children[j], board.children[i], board.children[i].children[0], 1, 1)){
                                
                                    console.log("False " + i + " " + j + " take");

                                return false;
                            }
                        }
                        //Sees if moving without taking a piece will be in check
                        else if(board.children[j].children[0] === undefined){
                            if(validMove(board.children[j], board.children[i], board.children[i].children[0], 0, 1)
                                && !king_check(board.children[j], board.children[i], board.children[i].children[0], 0, 1)){
                                
                                    console.log("False " + i + " " + j + " no take");

                                return false;
                            }
                        }
                    }
                }
            }
        }

        return true;
    }

    //Checks if the king will be in check after a move, then undoes the move. Returns true if in check or false if not
    //take === 1 when you are taking a piece
    //stale === 1 when checking stalemate and to not print alerts
    function king_check(new_col, cur_col, piece, take, stale){
        
        turn = localStorage.turn;
        let color, fail, index;

        if(take === 1){
            take_piece = new_col.children[0];
            new_col.removeChild(new_col.children[0]);    
        }

        //Does the move
        cur_col.removeChild(piece);
        new_col.appendChild(piece); 


        if(turn === "white-piece"){
            color = "w";
        }else{
            color = "b";
        }

        //Finds the king's index
        if(color === "w"){
            king_loc = document.querySelector(".W_K"); 
            index = [].indexOf.call(king_loc.parentNode.parentNode.children, king_loc.parentNode);
        }else{
            king_loc = document.querySelector(".B_k");
            index = [].indexOf.call(king_loc.parentNode.parentNode.children, king_loc.parentNode);
        }

        //Cant make a move that would put you into check so it fails
        if(in_check(index, color)){
            if(!stale){
                alert("You can't make a move that would put you into check");

            }
            fail = 1;
        }

        //Undoes the move
        new_col.removeChild(piece);
        cur_col.appendChild(piece);
        
        if(take === 1){
            new_col.appendChild(take_piece);
        }

        if(fail === 1){
            return true;
        }

        return false;
    }

    //Returns true if there are not enough pieces to have a checkmate.
    function insufficient_materials(){
        
        let white_bis = 0;  
        let black_bis = 0;
        let white_kni = 0;
        let black_kni = 0;
        //Tells what square color the bishop is on
        let black_bis_black = false;
        let black_bis_white = false;
        let white_bis_black = false;
        let white_bis_white = false;

        board = document.getElementById("chessboard");
        for(let i = 0; i < 63; i++){
            if(board.children[i].children[0] !== undefined){
                if(board.children[i].children[0].classList.contains("K")){
                    //Do nothing
                }else if(board.children[i].children[0].classList.contains("k")){
                    //Do nothing
                }else if(board.children[i].children[0].classList.contains("B")){
                    white_bis++;
                    if(board.children[i].classList.contains("white")){
                        white_bis_white = true;
                    }else{
                        white_bis_black = true;
                    }
                }else if(board.children[i].children[0].classList.contains("b")){
                    black_bis++;
                    if(board.children[i].classList.contains("white")){
                        black_bis_white = true;
                    }else{
                        black_bis_black = true;
                    }
                }else if(board.children[i].children[0].classList.contains("N")){
                    white_kni++
                }else if(board.children[i].children[0].classList.contains("n")){
                    black_kni++;
                }else{
                    return false;
                }
            }
        }

        //Only kings left
        if(black_bis === 0 && black_kni === 0 && white_bis === 0 && white_kni === 0){
            return true;
        }
        //King and bishop vs king
        else if(((black_bis === 1 && white_bis === 0) || (black_bis === 0 && white_bis === 1)) 
            && black_kni === 0 && white_kni === 0){
            
            return true;
        }
        //King and knight vs king
        else if(((black_kni === 1 && white_kni === 0) || (black_kni === 0 && white_kni === 1))
            && black_bis === 0 && white_bis === 0){

            return true;
        }
        //King and two knights vs king
        else if(((black_kni === 2 && white_kni === 0) || (black_kni === 0 && white_kni === 2))
            && black_bis === 0 && white_bis === 0){

            return true;
        }
        //King and bishop vs king and bishop when both bishops are on the same color.
        else if(((black_bis === 1 && white_bis === 1) && (black_kni === 0 && white_kni === 0))
            && ((black_bis_white && white_bis_white) || (black_bis_black && white_bis_black))){

            return true;
        }else if(((black_kni === 1 && white_kni === 0) && (black_bis === 0 && white_bis === 1)) 
            || ((black_kni === 0 && white_kni === 1) && (black_bis === 1 && white_bis === 0))){

            return true;
        }

        return false;
    }

    //Checks if any piece is in the path of a potential movement
    //Returns false if there is a piece in the path
    function check_path(new_index, old_index){

        board = document.getElementById("chessboard");
        var start;
        var end;

        //Up and Down
        if(new_index - old_index >= 8 || old_index - new_index >= 8){
            
            //Start is the smaller index and the for loop ending is the larger index
            if(new_index > old_index){
                start = old_index;
                end = new_index;
            }else{
                start = new_index;
                end = old_index;
            }
            
            for(var i = start + 8; i < end; i += 8){
                //There is a piece in the way return false
                if(board.children[i].children[0] !== undefined){
                    return false;
                }
            }
        }
        //Left or right
        else{

            //Start is the smaller index and the for loop ending is the larger index
            if(new_index < old_index){
                start = new_index;
                end = old_index
            }else{
                start = old_index;
                end = new_index;
            }

            for(var i = start + 1; i < end; i++){
                //There is a piece in the way return false
                if(board.children[i].children[0] !== undefined){
                    return false;
                }
            }
        }

        return true;
    }

    //Checks if there is a piece in the diagonal path of a potential movement
    //Returns false if a piece is in the path
    function check_path_dia(new_index, old_index){
        
        board = document.getElementById("chessboard");
        var start;
        var end;
        var side;

        //For loop start is the larger index and ending the smaller
        if(new_index > old_index){
            end = old_index;
            start = new_index;
        }else{
            start = old_index;
            end = new_index;
        }

        //Going right
        if((end % 8) > (start % 8)){
            side = -1;
        }
        //Going left
        else{
            side = 1;
        }

        for(var i = (start - (side + 8)); i > end; i -= (side + 8)){
            //Piece in the path return false
            if(board.children[i].children[0] !== undefined){
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
            
            //If the board has been flipped the math of adding to the pas string is different
            if(check === 0){
                pas = rows[new_index % 8];
                pas += 8 - Math.floor(new_index / 8);
            }else{
                pas = rows[7 - (new_index % 8)]
                pas += 1 + Math.floor(new_index / 8);
            }

            //Set curr_en_pas to be the index of the piece that can be en passanted
            curr_en_pas = new_index.toString();
            localStorage.curr_en_pas = curr_en_pas;
            localStorage.pas = pas;
            en_pas_ignore = true;
        }

    }

    //Changes the castling string and classes of the king or rook which just moved
    function castling(piece){

        const options = ['K', 'Q', 'k', 'q'];

        var a, b;

        console.log("In castling");

        //Rook just moved remove its side from the cas string
        if(piece.classList.contains("r") || piece.classList.contains("R")){
            b = cas.replace(options[piece.classList.item(4)], '');
            console.log(piece.classList.item(4));
        }
        //White king just moved remove all its future castling potential
        else if(piece.classList.contains("K")){
            a = cas.replace("K", '');
            if(document.getElementsByClassName("K")[0] !== undefined){
                document.getElementsByClassName("K")[0].classList.remove("First");
            }
            b = a.replace("Q", '');
            if(document.getElementsByClassName("Q")[0] !== undefined){
                document.getElementsByClassName("Q")[0].classList.remove("First");
            }
        }
        //Black king just moved remove all its future castling potential
        else{
            a = cas.replace("k", '');
            if(document.getElementsByClassName("k")[0] !== undefined){
                document.getElementsByClassName("k")[0].classList.remove("First");
            }
            b = a.replace("q", '');
            if(document.getElementsByClassName("q")[0] !== undefined){
                document.getElementsByClassName("q")[0].classList.remove("First");
            }
        }

        piece.classList.remove("First");

        cas = b;
        localStorage.cas = cas;
    }

    //Checks current attempted castling is ok
    //Return true if is is and false if it isn't
    //for side 0 = left and 1 = right
    //color is either "w" or "b"
    function valid_castling(side, color){
 
        pas = localStorage.pas;
        flip = localStorage.flip;
        let check, king_loc, rook_loc;

        if(cas === "-"){
            return false;
        }
 
        //Check equal 'Q' = queenside castle attempted, 'k' = kingside attempt
        //Captial letters if white and lowercase black
        //Stores the location of the king and rook about to move
        if(side === 0 && color === "w"){
            if(flip === "0"){
                check = "Q";
                king_loc = 60;
                rook_loc = 56;
            }else{
                check = "K";
                king_loc = 3;
                rook_loc = 0;
            }
        }else if(side === 1 && color === "w"){
            if(flip === "0"){
                check = "K";
                king_loc = 60;
                rook_loc = 63;
            }else{
                check = "Q";
                king_loc = 3;
                rook_loc = 7;
            }
           
        }else if(side === 0 && color === "b"){
            if(flip === "0"){
                check = "q";
                king_loc = 4;
                rook_loc = 0;
            }else{
                check = "k";
                king_loc = 59;
                rook_loc = 56;
            }
        }else{
            if(flip === "0"){
                check = "k";
                king_loc = 4;
                rook_loc = 7;
            }else{
                check = "q";
                king_loc = 59;
                rook_loc = 63;
            }
        }
 
        //Checks if the attempted castle is in the cas string
        if(!cas.includes(check)){
            return false;
        }

        //Is there pieces between the rook and king
        board = document.getElementById("chessboard");
        if(!check_path(rook_loc, king_loc)){
            return false;
        }

        //Sees if the king will be in check during the castling
        if(side === 0){
            for(var i = king_loc; i > (king_loc - 3); i--){
                if(in_check(i, color)){
                    return false;
                }
            }
        }else{
            for(var i = king_loc; i < (king_loc + 3); i++){
                if(in_check(i, color)){
                    return false;
                }
            }
        }

        //Move the pieces as the castle is valid
        king = board.children[king_loc].children[0];
        rook = board.children[rook_loc].children[0];
        board.children[king_loc].removeChild(king);
        board.children[rook_loc].removeChild(rook);

        if(side === 0){
            board.children[king_loc - 2].appendChild(king);
            board.children[king_loc - 1].appendChild(rook);
        }else{
            board.children[king_loc + 2].appendChild(king);
            board.children[king_loc + 1].appendChild(rook);
        }

        //Removes future castling potential
        if(color === "w"){
            cas = cas.replace("K", '');
            //if(){
            document.getElementsByClassName("K")[0].classList.remove("First");
            //}
            cas = cas.replace("Q", '');
            //if(document.getElementsByClassName("Q")[0] !== undefined){
            //    document.getElementsByClassName("Q")[0].classList.remove("First");
            //}
        }else{
            cas = cas.replace("k", '');
            document.getElementsByClassName("k")[0].classList.remove("First");
            cas = cas.replace("q", '');
            //document.getElementsByClassName("q")[0].classList.remove("First");
        }

        localStorage.cas = cas;

        return true;
 
    }

    //Returns true if the piece at the index is in check
    function in_check(index, color){

        flip = localStorage.flip;
        let color_check;
        board = document.getElementById("chessboard");

        if(color === "w"){
            color_check = "white-piece";
        }else{
            color_check = "black-piece";
        }

        //Left check
        let counter = index - 1;
        while(true){
            if(Math.floor(counter / 8) !== Math.floor(index / 8)){
                break;
            }

            if(board.children[counter].children[0] !== undefined){
                if(board.children[counter].children[0].classList.contains(color_check)){
                    break;
                }

                if(board.children[counter].children[0].classList.contains("q") || board.children[counter].children[0].classList.contains("r")  
                    || board.children[counter].children[0].classList.contains("Q") || board.children[counter].children[0].classList.contains("R")
                    ){
                    
                    console.log(index + " Move is " + counter + " queen or rook left");
                    return true;
                }

                if((board.children[counter].children[0].classList.contains("k") || board.children[counter].children[0].classList.contains("K"))
                    && ((counter - 1) === index)){
                    
                    console.log(index + " Move is " + counter + " king left");
                    return true;
                }

                break;
            }

            counter--;
        }

        //Right check
        counter = index + 1;
        while(true){
            if(Math.floor(counter / 8) !== Math.floor(index / 8)){
                break;
            }

            if(board.children[counter].children[0] !== undefined){
                if(board.children[counter].children[0].classList.contains(color_check)){
                    break;
                }

                if(board.children[counter].children[0].classList.contains("q") || board.children[counter].children[0].classList.contains("r")  
                    || board.children[counter].children[0].classList.contains("Q") || board.children[counter].children[0].classList.contains("R") 
                    && ((Math.floor(index / 8) - Math.floor(counter / 8)) === 0)){
                    console.log(index + " Move is " + counter + " queen or rook right");
                    return true;
                }

                if((board.children[counter].children[0].classList.contains("k") || board.children[counter].children[0].classList.contains("K"))
                    && (counter - index) === 1 && ((Math.floor(index / 8) - Math.floor(counter / 8)) === 0)){
                    console.log(index + " Move is " + counter + " king right");
                    return true;
                }

                break;
            }

            counter++;
        }

        //Up check
        counter = index - 8;
        while(true){
            if(counter < 0){
                break;
            }

            if(board.children[counter].children[0] !== undefined){
                if(board.children[counter].children[0].classList.contains(color_check)){
                    break;
                }

                if(board.children[counter].children[0].classList.contains("q") || board.children[counter].children[0].classList.contains("r")  
                    || board.children[counter].children[0].classList.contains("Q") || board.children[counter].children[0].classList.contains("R")){
                    
                    console.log(index + " Move is " + counter + " queen or rook up");
                    return true;
                }

                if((board.children[counter].children[0].classList.contains("k") || board.children[counter].children[0].classList.contains("K"))
                    && (index - 8) === counter){
                    
                    console.log(index + " Move is " + counter + " king up")
                    return true;
                }

                break;
            }

            counter -= 8;
        }

        //Down check
        counter = index + 8;
        while(true){
            if(counter > 63){
                break;
            }

            if(board.children[counter].children[0] !== undefined){
                if(board.children[counter].children[0].classList.contains(color_check)){
                    break;
                }

                if(board.children[counter].children[0].classList.contains("q") || board.children[counter].children[0].classList.contains("r")  
                    || board.children[counter].children[0].classList.contains("Q") || board.children[counter].children[0].classList.contains("R")){
                    
                    console.log(index + " Move is " + counter + " queen or rook down")
                    return true;
                }

                if((board.children[counter].children[0].classList.contains("k") || board.children[counter].children[0].classList.contains("K"))
                    && (index + 8) === counter){
                    
                    console.log(index + " Move is " + counter + " king down")
                    return true;
                }

                break;
            }

            counter += 8;
        }

        //Up left check
        counter = index - 9;
        while((index % 8) !== 0){
            if(counter < 0){
                break;
            }

            if(board.children[counter].children[0] !== undefined){
                if(board.children[counter].children[0].classList.contains(color_check)){
                    break;
                }

                if(board.children[counter].children[0].classList.contains("q") || board.children[counter].children[0].classList.contains("Q")  
                    || board.children[counter].children[0].classList.contains("B") || board.children[counter].children[0].classList.contains("b")){
                    
                    console.log(index + " Move is " + counter + " queen or bishop up left");
                    return true;
                }

                if((board.children[counter].children[0].classList.contains("k") || board.children[counter].children[0].classList.contains("K"))
                    && (index - 9) === counter){

                    console.log(index + " Move is " + counter + " king up left")
                    return true;
                }

                //For pawns
                if(((board.children[counter].children[0].classList.contains("p") && flip === "0")
                    || (board.children[counter].children[0].classList.contains("P") && flip === "1")) && (index - 9) === counter){
                    

                    console.log(index + " Move is " + counter + " pawn up left");
                    return true;
                }

                break;
            }

            if((counter % 8) === 0){
                break;
            }

            counter -= 9;
        }

        //Up right check
        counter = index - 7;
        while((index % 8) !== 7){
            if(counter < 0){
                break;
            }
        
            if(board.children[counter].children[0] !== undefined){
                if(board.children[counter].children[0].classList.contains(color_check)){
                     
                    break;
                }
        
                if(board.children[counter].children[0].classList.contains("q") || board.children[counter].children[0].classList.contains("Q")  
                    || board.children[counter].children[0].classList.contains("B") || board.children[counter].children[0].classList.contains("b")){

                    console.log(index + " Move is " + counter + " queen or bishop up right");
                    return true;
                }
        
                if((board.children[counter].children[0].classList.contains("k") || board.children[counter].children[0].classList.contains("K"))
                    && (index - 7) === counter){
                    
                    console.log(index + " Move is " + counter + " king up right");
                    return true;
                }
        
                //For pawns
                if(((board.children[counter].children[0].classList.contains("p") && flip === "0")
                    || (board.children[counter].children[0].classList.contains("P") && flip === "1")) && (index - 7) === counter){
                    
                    console.log(index + " Move is " + counter + " pawn up right");
                    return true;
                }
        
                break;
            }
        
            if((counter % 8) === 7){
                break;
            }
        
            counter -= 7;
        }

         //Down right check
         counter = index + 9;
         while((index % 8) !== 7){
             if(counter > 63){
                 break;
             }
 
             if(board.children[counter].children[0] !== undefined){
                 if(board.children[counter].children[0].classList.contains(color_check)){
                     break;
                 }
 
                 if(board.children[counter].children[0].classList.contains("q") || board.children[counter].children[0].classList.contains("Q")  
                    || board.children[counter].children[0].classList.contains("B") || board.children[counter].children[0].classList.contains("b")){
                     
                    console.log(index + " Move is " + counter + " queen or bishop down right");
                    return true;
                 }
 
                 if((board.children[counter].children[0].classList.contains("k") || board.children[counter].children[0].classList.contains("K"))
                    && (index + 9) === counter){
                    
                    console.log(index + " Move is " + counter + " king down right");
                    return true;
                 }
 
                 //For pawns
                 if(((board.children[counter].children[0].classList.contains("p") && flip === "1")
                    || (board.children[counter].children[0].classList.contains("P") && flip === "0")) && (index + 9) === counter){
                    
                    console.log(index + " Move is "+ counter + " pawn down right");
                    return true;
                 }
 
                 break;
             }
 
             if((counter % 8) === 7){
                 break;
             }
 
             counter += 9;
        }

        //Down left check
        counter = index + 7;
        while((index % 8) !== 0){
            if(counter > 63){
                break;
            }

            if(board.children[counter].children[0] !== undefined){
                if(board.children[counter].children[0].classList.contains(color_check)){
                    break;
                }

                if(board.children[counter].children[0].classList.contains("q") || board.children[counter].children[0].classList.contains("Q")  
                    || board.children[counter].children[0].classList.contains("B") || board.children[counter].children[0].classList.contains("b")){
                
                        console.log(index + " Move is " + counter + " queen or bishop down left");
                    return true;
                }

                if((board.children[counter].children[0].classList.contains("k") || board.children[counter].children[0].classList.contains("K"))
                    && (index + 7) === counter){
                
                        console.log(index + " Move is " + counter + " king down left");
                    return true;
                }

                //For pawns
                if(((board.children[counter].children[0].classList.contains("p") && flip === "1")
                    || (board.children[counter].children[0].classList.contains("P") && flip === "0")) && (index + 7) === counter){
                    
                        console.log(index + " Move is " + counter + " pawn down left");
                    return true;
                }

                break;
            }

            if((counter % 8) === 0){
                break;
            }

            counter += 7;
        }
        
        //Knight checks
        if(index + 17 <= 63){
            if((board.children[index + 17].children[0] !== undefined) && (((index + 17) % 8) - (index % 8) === 1)){
                if(!(board.children[index + 17].children[0].classList.contains(color_check))
                    && (board.children[index + 17].children[0].classList.contains("N") || board.children[index + 17].children[0].classList.contains("n"))){
                    
                        console.log(index + " Move is " + counter + " knight 1");
                    return true;
                }
            }
        }
        if(index + 15 <= 63){
            if(board.children[index + 15].children[0] !== undefined && (((index + 15) % 8) - (index % 8) === -1)){
                if(!(board.children[index + 15].children[0].classList.contains(color_check)) 
                    && (board.children[index + 15].children[0].classList.contains("N") || board.children[index + 15].children[0].classList.contains("n"))){
                    
                        console.log(index + " Move is " + counter + " knight 2");
                    return true;
                }
            }
        }
        if(index + 10 <= 63){
            if(board.children[index + 10].children[0] !== undefined && (((index + 10) % 8) - (index % 8) === 2)){
                if(!(board.children[index + 10].children[0].classList.contains(color_check)) 
                    && (board.children[index + 10].children[0].classList.contains("N") || board.children[index + 10].children[0].classList.contains("n"))){
                    
                        console.log(index + " Move is " + counter + " knight 3");
                    return true;
                }
            }
        }
        if(index + 6 <= 63){
            if(board.children[index + 6].children[0] !== undefined && (((index + 6) % 8) - (index % 8) === -2)){
                if(!(board.children[index + 6].children[0].classList.contains(color_check)) 
                    && (board.children[index + 6].children[0].classList.contains("N") || board.children[index + 6].children[0].classList.contains("n"))){
                    
                        console.log(index + " Move is " + counter + " knight 4");
                    return true;
                }
            }
        }
        if(index - 6 >= 0){
            if(board.children[index - 6].children[0] !== undefined && (((index - 6) % 8) - (index % 8) === 2)){
                if(!(board.children[index - 6].children[0].classList.contains(color_check)) 
                    && (board.children[index - 6].children[0].classList.contains("N") || board.children[index - 6].children[0].classList.contains("n"))){
                    
                        console.log(index + " Move is " + counter + " knight 5");
                    return true;
                }
            }
        }
        if(index - 10 >= 0){
            if(board.children[index - 10].children[0] !== undefined && (((index - 10) % 8) - (index % 8) === -2)){
                if(!(board.children[index - 10].children[0].classList.contains(color_check)) 
                    && (board.children[index - 10].children[0].classList.contains("N") || board.children[index - 10].children[0].classList.contains("n"))){
                    
                        console.log(index + " Move is " + counter + " knight 6");
                    return true;
                } 
            }
        }
        if(index - 15 >= 0){
            if(board.children[index - 15].children[0] !== undefined && (((index - 15) % 8) - (index % 8) === 1)){
                if(!(board.children[index - 15].children[0].classList.contains(color_check))
                    && (board.children[index - 15].children[0].classList.contains("N") || board.children[index - 15].children[0].classList.contains("n"))){
                    
                        console.log(index + " Move is " + counter + " knight 7");
                    return true;
                }
            }
        }
        if(index - 17 >= 0){
            if(board.children[index - 17].children[0] !== undefined && (((index - 17) % 8) - (index % 8) === -1)){
                if(!(board.children[index - 17].children[0].classList.contains(color_check))
                    && (board.children[index - 17].children[0].classList.contains("N") || board.children[index - 17].children[0].classList.contains("n"))){
                    
                        console.log(index + " Move is " + counter + " knight 8");
                    return true;
                }
            }
        }

        return false;
    }

    //Makes a queen piece at the given index
    //Used when pawns reach the end of the board
    function make_queen(index){
        
        board = document.getElementById("chessboard");

        piece = document.createElement("DIV");
        piece.id = index + 9 + 9;

        if(board.children[index].children[0].classList.contains("white-piece")){
            piece.classList.add("white-piece");
            piece.classList.add("Q");
        }else{
            piece.classList.add("black-piece");
            piece.classList.add("B_q");
        }

        board.children[index].removeChild(board.children[index].children[0]);
        board.children[index].appendChild(piece);

    }

    //Makes a rook piece at the given index
    //Used when pawns reach the end of the board
    function make_rook(index){
        
        board = document.getElementById("chessboard");

        piece = document.createElement("DIV");
        piece.id = index + 9 + 9;

        if( board.children[index].children[0].classList.contains("white-piece") === true){
            piece.classList.add("white-piece");
            piece.classList.add("R");
            piece.classList.add("W_r");
        }else{
            piece.classList.add("black-piece");
            piece.classList.add("r");
            piece.classList.add("B_r");
        }

        board.children[index].removeChild(board.children[index].children[0]);
        board.children[index].appendChild(piece);

    }

    //Makes a knight piece at the given index
    //Used when pawns reach the end of the board
    function make_knight(index){
        board = document.getElementById("chessboard");

        piece = document.createElement("DIV");
        piece.id = index + 9 + 9;

        if( board.children[index].children[0].classList.contains("white-piece") === true){
            piece.classList.add("white-piece");
            piece.classList.add("N");
        }else{
            piece.classList.add("black-piece");
            piece.classList.add("n");
            piece.classList.add("B_n");
        }

        board.children[index].removeChild(board.children[index].children[0]);
        board.children[index].appendChild(piece);

    }

    //Makes a bishop piece at the given index
    //Used when pawns reach the end of the board
    function make_bishop(index){
        board = document.getElementById("chessboard");

        piece = document.createElement("DIV");
        piece.id = index + 9 + 9;

        if(board.children[index].children[0].classList.contains("white-piece") === true){
            piece.classList.add("white-piece");
            piece.classList.add("B");
        }else{
            piece.classList.add("black-piece");
            piece.classList.add("b");
            piece.classList.add("B_b");
        }

        board.children[index].removeChild(board.children[index].children[0]);
        board.children[index].appendChild(piece);

    }

    function engine_move(){

        //call backend to do move, want to delay it by half a second as it is too fast now
        instring();
        //setTimeout(instring(), 5000);

        turn = localStorage.turn;
        pas = localStorage.pas;
        cas = localStorage.cas;
        half = localStorage.half;
        full = localStorage.full;
        curr_en_pas = localStorage.curr_en_pas;

        if(full === "100"){
            console.log("IN");
            alert("100 turn timer reached. The game has ended in a tie.");
            win_con = "Game has ended in a tie by turn timer. Please refresh the page to play again";
            return;
        }else if(half === "50"){
            alert("50 half-turn timer reached. The game has ended in a tie.");
            win_con = "Game has ended in a tie by half-turn timer. Please refresh the page to play again";
            return;
        }

        //Three repetition rule
        if(three_rep()){
            alert("Threefold repetition has occured. The game has ended in a tie.");
            win_con = "Game has ended in a tie by threefold repetition. Please refresh the page to play again";
            return;
        }

        if(stalemate()){

            let index;
            if(turn === "white-piece"){
                color = "w";
                king_loc = document.querySelector(".W_K"); 
                index = [].indexOf.call(king_loc.parentNode.parentNode.children, king_loc.parentNode);
            }else{
                color = "b";
                king_loc = document.querySelector(".b_k"); 
                index = [].indexOf.call(king_loc.parentNode.parentNode.children, king_loc.parentNode);
            }


            //Getting here means that there are no possible valid moves for the current color.
            //If the king is in check it is a checkmate, if not then it is a stalemate.
            if(in_check(index, color)){
                victory = (turn === "white-piece") ? "black-piece" : "white-piece";
                console.log("Engine won " + turn);
                alert("Checkmate! " + victory + " has won!");
                win_con = "The game has ended with " + victory + " winning by checkmate. Please refresh the page to play again";
                return;
            }else{
                alert("Tie! You have reached a stalemate");
                win_con = "The game has ended in a tie by stalemate. Please refresh the page to play again";
                return;
            }
        }

        //Tests if there is enough pieces to force a checkmate
        if(insufficient_materials()){
            alert("Tie! By insufficient materials.");
            win_con = "The game has ended in a tie by insufficient materials. Please refresh the page to play again";
            return;
        }

    }

    function three_rep(){
        
        let new_fen = get_fen();

        //new_fen[new_fen.length - 1] = "";
        result = new_fen.slice(0, (new_fen.length - 2));
        //console.log(result);
        
        while((result[result.length - 1]) !== " "){
            result = result.slice(0, (result.length - 1));
            //console.log(result);
        }

        result = result.slice(0, (result.length - 1));
        //console.log("Post " + result);

        while((result[result.length - 1]) !== " "){
            result = result.slice(0, (result.length - 1));
            //console.log(result);
        }

        result = result.slice(0, (result.length - 1));
        //console.log("Post " + result);

        for(var i = 0; i < past_fen.length; i += 2){
            
            //console.log("TESt " + result + " " + past_fen[i])
            
            if(past_fen[i] === result){
                
                //console.log("Fen match " + (past_fen[i+1] + 1));
                
                past_fen[i+1]++;

                if(past_fen[i+1] === 3){
                    return true;
                }

                return false;
            }
        }

        past_fen.push(result, 1);
        //past_fen[past_fen.length - 1][0] = new_fen;
        //past_fen[past_fen.length - 1][1] = 1;

        return false;
    }

  //});

  function Please(){
        turn = localStorage.turn;
        pas = localStorage.pas;
        cas = localStorage.cas;
        half = localStorage.half;
        full = localStorage.full;
        curr_en_pas = localStorage.curr_en_pas;
        var check = false;
        pro = false;
        test = localStorage.test;

        if(full === "100"){
            alert("100 turn timer reached. The game has ended in a tie.");
            win_con = "Game has ended in a tie by turn timer. Please refresh the page to play again";
            return;
        }else if(half === "50"){
            alert("50 half-turn timer reached. The game has ended in a tie.");
            win_con = "Game has ended in a tie by half-turn timer. Please refresh the page to play again";
            return;
        }

        //Three repition rule
        if(three_rep()){
            alert("Threefold repetition has occured. The game has ended in a tie.");
            win_con = "Game has ended in a tie by threefold repetition. Please refresh the page to play again";
            return;
        }

        //Tests if the game has ended in a stalemate or a checkmate
        if(stalemate()){

            let index;
            turn = localStorage.turn;
            if(turn === "white-piece"){
                color = "w";
                king_loc = document.querySelector(".W_K"); 
                index = [].indexOf.call(king_loc.parentNode.parentNode.children, king_loc.parentNode);
            }else{
                color = "b";
                king_loc = document.querySelector(".b_k"); 
                index = [].indexOf.call(king_loc.parentNode.parentNode.children, king_loc.parentNode);
            }


            //Getting here means that there are no possible valid moves for the current color.
            //If the king is in check it is a checkmate, if not then it is a stalemate.
            if(in_check(index, color)){
                victory = (turn === "white-piece") ? "black-piece" : "white-piece";
                alert("Checkmate! " + victory + " has won!");
                win_con = "The game has ended with " + victory + " winning by checkmate. Please refresh the page to play again";
                return;
            }else{
                alert("Tie! You have reached a stalemate");
                win_con = "The game has ended in a tie by stalemate. Please refresh the page to play again";
                return;
            }
        }

        //Tests if there is enough pieces to force a checkmate
        if(insufficient_materials()){
            alert("Tie! By insufficient materials.");
            win_con = "The game has ended in a tie by insufficient materials. Please refresh the page to play again";
            return;
        }

        setTimeout(engine_move,1);
  }