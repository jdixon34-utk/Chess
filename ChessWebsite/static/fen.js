function fen(){
 
    //Get the variables from board.js
    turn = localStorage.turn;
    pas = localStorage.pas;
    cas = localStorage.cas;
    half = localStorage.half;
    full = localStorage.full;
    flip = localStorage.flip;

    let fen = "";
    let tab = document.getElementById("chessboard");
    let count = tab.childElementCount;
    
    let space = 0;
    //Iterate over all child nodes
    if(flip === "no"){
        for(let i = 0; i <= 7; i++){
            for(let j = 0; j < 8; j++){

            //Add a space if there is no piece
                if(tab.children[(i * 8) + j].children[0] === undefined){
                    space++;
            }   else{
                    //Add the spaces now that there is a piece
                    if(space !== 0){
                        fen += space;
                        space = 0;
                    }

                    fen += tab.children[(i * 8) + j].children[0].classList.item(1);
                }

                //End of the row and not the last row
                if(j === 7 && i !== 7){
                
                    if(space !== 0){
                        fen += space;
                    }

                    fen += '/';
                    space = 0;
                }
            }
        }
    }else{
        for(let i = 7; i >= 0; i--){
            for(let j = 0; j < 8; j++){

            //Add a space if there is no piece
                if(tab.children[(i * 8) + j].children[0] === undefined){
                    space++;
            }   else{
                    //Add the spaces now that there is a piece
                    if(space !== 0){
                        fen += space;
                        space = 0;
                    }

                    fen += tab.children[(i * 8) + j].children[0].classList.item(1);
                }

                //End of the row and not the last row
                if(j === 7 && i !== 0){
                
                    if(space !== 0){
                        fen += space;
                    }

                    fen += '/';
                    space = 0;
                }
            }
        }
    }

    fen += ' ';

    //Whose turn is it, b = black | white = w
   
    let t = (turn === "white-piece") ? "w" : "b";
    
    fen += t + ' ';

    //Next you say what castling is available
    //q = castle queenside possible
    //k = castle kingside
    //Can be either KQkq or Qk- or -- or etc
    if(cas !== ''){
        fen += cas + ' ';
    }else{
        fen += '-' + ' ';
    }
    
    //Next you do en passant targets
    var check = false;
    for(var i = 0; i < pas.length; i += 4){
        //Ignore ,'s as that is what we set indexes that are no longer en passant targets to.
        if(pas[i] !== ','){
            fen += pas[i] + pas[i+2] + ' ';
            check = true;
        }
    }
    if(check === false){
        fen += "- "
    }
    //Next is how many moves both players have made since the last pawn advance or piece capture
    //Game ends in a draw if this is 100

    fen += half + ' ';

    //Last field is the number of completed turns in the game.
    //This number is incremented by one every time Black moves.

    fen += full + ' ';

    return fen;
}
