<script>
    import Navbar from "../components/Navbar.svelte";
    import { onMount } from 'svelte';
    onMount(() => {
        document.addEventListener("DOMContentLoaded", function () {
   
   table = document.createElement("BOARD");
   table.id = "chessboard";
   document.body.appendChild(table);
 
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
                       piece.classList.add("castle");
                   }else if(j === 2 || j === 7){
                       piece.classList.add("knight");
                   }else if(j === 3 || j === 6){
                       piece.classList.add("bishop");
                   }else if(j === 4){
                       piece.classList.add("queen");
                   }else{
                       piece.classList.add("king");
                   }
               }else{
                   piece.classList.add("pawn");
               }
           } else if (i > 6) {
               document.getElementById("col" + i + j).appendChild(piece);
               piece.classList.add("black-piece");
               //Define all the pieces for the black side
               if(i === 8){
                   if(j === 1 || j === 8){
                       piece.classList.add("castle");
                   }else if(j === 2 || j === 7){
                       piece.classList.add("knight");
                   }else if(j === 3 || j === 6){
                       piece.classList.add("bishop");
                   }else if(j === 4){
                       piece.classList.add("queen");
                   }else{
                       piece.classList.add("king");
                   }
               }else{
                   piece.classList.add("pawn");
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
           col.children[0].classList.add("current");
       }
       //Valid move. So move the piece
       else if(cur !== undefined && col.children[0] === undefined){
           move(col, cur.parentNode, cur);
       }
       //Unselect the current piece
       else if(col.children[0] === cur){
               cur.classList.remove("current");
       }
       //Take a piece
       else if(col.children[0] !== undefined && ((cur.classList.contains("white-piece") && col.children[0].classList.contains("black-piece")) || (cur.classList.contains("black-piece") && col.children[0].classList.contains("white-piece")))){
           col.removeChild(col.children[0]);
           move(col, cur.parentNode, cur);
       }
       //Good attempt but there is already a piece there ;D
       else if(col.children[0] !== undefined){
           alert("Column already has a piece of the same color");
       }
       //Else nothing is currently selected and the selected square has no piece so do nothing
   }
 
   //Move piece from cur_col to new_col
   function move(new_col, cur_col, piece) {
       //console.log(new_col);
       //console.log(cur_col);
       //console.log(piece);
 
       cur_col.removeChild(piece);
       new_col.appendChild(piece);
 
       piece.classList.remove("current");
   }
 
 });
  });

 
</script>

<Navbar />
<h1 class="pt-[9vh]">HOME PAGE</h1>