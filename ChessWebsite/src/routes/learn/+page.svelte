<script>
    import Navbar from "../../components/Navbar.svelte";
    import Footer from "../../components/Footer.svelte";
</script>

<Navbar />

<div class="w-full min-h-[89vh] h-full md:px-[5vh] lg:px-[10vh]">
    <h1 class="pt-[9vh] flex justify-center items-center font-bold text-3xl">How to Play</h1>

    <div class="pt-[3vh] w-full h-full flex flex-col justify-center items-center px-[10vw] pb-[2vh]">

        <!-- Overall general concept -->
        <div class="flex flex-col">
            <h1 class="text-2xl font-semibold pb-[1vh] capitalize">The general idea</h1>
            <p class="pb-[4vh]">
                Chess is played between two people. Each player has 16 pieces: 8 pawns,
                2 knights, 2 bishops, 2 rooks, 1 queen, and finally 1 king. The main point 
                of the game is to <span class="font-medium underline">checkmate the opposing player</span>. Checkmate is when the king 
                piece is able to be captured and can't escape. But more on that later, for now
                let's learn some of the basic rules.
            </p>
        </div>

        <!-- Basic rules -->
        <div class="flex flex-col">
            <h1 class="text-2xl font-semibold pb-[1vh] capitalize">Some basic rules</h1>
            <p class="pb-[2vh]">
                A person gets to move one piece per turn. Players continue trading turns until either 
                someone gets checkmated, someone resigns, or there is a <span class="font-medium underline">stalemate 
                (a player is not in check but can't move except into check)</span>. 
            </p>

            <p class="pb-[4vh]">
                Each piece has its own 
                specific valid moves it can make during that turn. Let's dive into the types of pieces and 
                how they can move across the board.
            </p>
        </div>
    
        <!-- How to move pieces -->
        <div class="flex flex-col">
            <h1 class="text-2xl font-semibold pb-[1vh]">Pieces and How They Move</h1>
            <p class="pb-[2vh]">
                Here are all the unique chess pieces that you will have to learn as you play. While our website
                will prevent you from making illegal moves, 
                <span class="font-medium underline">it is important to become familiar with these pieces and how they move</span> 
                to improve your game.
            </p>

            <ul class="pb-[1vh]">
                <li class="pb-[1vh]"><a href="https://www.chess.com/terms/chess-king" target="_blank" class="text-[#769656] hover:text-[#526d38] font-bold underline">King</a> - can <span class="font-medium">move one square in any direction</span> (left, right, up, down, diagonal).</li>
                <li class="pb-[1vh]"><a href="https://www.chess.com/terms/chess-queen" target="_blank" class="text-[#769656] hover:text-[#526d38] font-bold underline">Queen</a> - can <span class="font-medium">move in any direction</span> like the king, but is <span class="font-medium">not limited to one square</span>.</li>
                <li class="pb-[1vh]"><a href="https://www.chess.com/terms/chess-rook" target="_blank" class="text-[#769656] hover:text-[#526d38] font-bold underline">Rook</a> - can <span class="font-medium">move in any valid square</span> that is either <span class="font-medium">horizontal or vertical to it</span>.</li>
                <li class="pb-[1vh]"><a href="https://www.chess.com/terms/chess-bishop" target="_blank" class="text-[#769656] hover:text-[#526d38] font-bold underline">Bishop</a> - can <span class="font-medium">move in any valid square</span> that is <span class="font-medium">diagonal to it</span>.</li>
                <li class="pb-[1vh]"><a href="https://www.chess.com/terms/chess-knight" target="_blank" class="text-[#769656] hover:text-[#526d38] font-bold underline">Knight</a> - can 
                    <span class="font-medium">move up or down one square vertically and over two squares horizontally</span> 
                    OR <span class="font-medium">up or down two squares vertically and over one square horizontally</span>
                    ("L" shape movement).
                </li>
                <li><a href="https://www.chess.com/terms/chess-pawn" target="_blank" class="text-[#769656] hover:text-[#526d38] font-bold underline">Pawn</a> - can move one square in any direction (left, right, up, down, diagonal)</li>
            </ul>
            <p class="pb-[4vh] text-[13px] text-[#769656]">
                * Click on the <span class="underline">piece name</span> to get more information
            </p>
        </div>

        <!-- Resources -->
        <div class="flex flex-col">
            <h1 class="text-2xl font-semibold pb-[1vh] capitalize">Helpful resources</h1>
            <p class="pb-[2vh]">
                While we have provided a considerable amount of information regarding the basics
                and "need to know's" of chess. It is HIGHLY recommended that you use these
                sources here. They will provide more in depth explanations and exceptions to the rules
                that we did not cover. As well as some basic tips, strategies, and tactics to learn 
                as you go.
            </p>

            <ul class="pb-[4vh]">
                <li class="pb-[1vh]">
                    <a class="text-[#769656] hover:text-[#526d38] font-bold underline" href="https://www.chesshouse.com/pages/chess-rules" target="_blank">The Rules of Chess</a>
                    - A great website that goes into more detail on the basics above.
                </li>
                <li class="pb-[1vh]">
                    <a class="text-[#769656] hover:text-[#526d38] font-bold underline" href="https://www.chess.com/learn-how-to-play-chess" target="_blank">7 Steps To Get You Started</a>
                    - Essential information with videos to help with concepts.
                </li>
                <li class="pb-[1vh]">
                    <a class="text-[#769656] hover:text-[#526d38] font-bold underline" href="https://nextlevelchess.blog/beginner-chess-strategy/" target="_blank">Beginner Chess Strategy</a>
                    - After learning the basics, we recommend learning strategy.
                </li>
            </ul>

        </div>
    </div>
</div>

<Footer />