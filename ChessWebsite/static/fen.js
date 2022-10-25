function fen(){
 
    turn = localStorage.turn;
    pas = localStorage.pas;
    cas = localStorage.cas;
    half = localStorage.half;
    full = localStorage.full;

    let fen = "";

    let tab = document.getElementById("chessboard");

    let count = tab.childElementCount;

    //console.log("hi " + tab + " " + count + tab.children[0]);

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

    var check = false;
    for(var i = 0; i < pas.length; i += 4){
        console.log(pas[2]);
        if(pas[i] !== ','){
            fen += pas[i] + pas[i+2] + ' ';
            check = true;
        }
    }
    if(check === false){
        fen += "- "
    }
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
