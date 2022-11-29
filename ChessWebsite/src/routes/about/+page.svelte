<script>
    import Navbar from "../../components/Navbar.svelte";
    import Footer from "../../components/Footer.svelte";
</script>

<Navbar />

<div class="w-full min-h-[89vh] h-full md:px-[5vh] lg:px-[10vh]">
    <h1 class="pt-[9vh] flex justify-center items-center font-bold text-3xl">About the Project</h1>

    <div class="pt-[3vh] w-full h-full flex flex-col justify-center items-center px-[10vw] pb-[2vh]">

        <!-- Describing our project -->
        <div class="flex flex-col">
            <h1 class="text-2xl font-semibold pb-[1vh]">Project Information</h1>
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

    
        <!-- Languages and technologies used -->
        <div class="flex flex-col">
            <h1 class="text-2xl font-semibold pb-[1vh]">Languages and Technologies</h1>
            <p class="pb-[2vh]">
                We were able to use an array of different tools in our project. While the engine itself was done
                solely in C++, we had to use a variety of different technologies on the front-end such as: Svelte, TailwindCSS, and Web Assembly.
                Here is everything we used and what it was used for.

            <ul class="pb-[4vh]">
                <li class="pb-[1vh]">
                    <a class="text-[#de7864] hover:text-[#c8543d] font-bold underline" href="https://devdocs.io/cpp/" target="_blank">C++</a>
                    - Chess Engine
                </li>
                <li class="pb-[1vh]">
                    <a class="text-[#de7864] hover:text-[#c8543d] font-bold underline" href="https://developer.mozilla.org/en-US/docs/WebAssembly" target="_blank">Web Assembly</a>
                    - Bridging Back End and Front End
                </li>
                <li class="pb-[1vh]">
                    <a class="text-[#de7864] hover:text-[#c8543d] font-bold underline" href="https://svelte.dev/docs" target="_blank">Svelte</a>
                    - Web Application
                </li>
                <li class="pb-[1vh]">
                    <a class="text-[#de7864] hover:text-[#c8543d] font-bold underline" href="https://v2.tailwindcss.com/docs" target="_blank">TailwindCSS</a>
                    - Major Styling
                </li>
                <li class="pb-[1vh]">
                    <a class="text-[#de7864] hover:text-[#c8543d] font-bold underline" href="https://developer.mozilla.org/en-US/" target="_blank">JavaScript, HTML, CSS</a>
                    - Chess Board
            </ul>
        </div>

        <!-- Resources -->
        <div class="flex flex-col">
            <h1 class="text-2xl font-semibold pb-[1vh]">Project Timeline</h1>
            <p class="pb-[2vh]">
                While we have provided a considerable amount of information regarding the basics
                and "need to know's" of chess. It is HIGHLY recommended that you use these
                sources here. They will provide more in depth explanations and exceptions to the rules
                that we did not cover. As well as some basic tips, strategies, and tactics to learn 
                as you go.
            </p>

            <ul class="pb-[4vh]">
                <li class="pb-[1vh]">
                    <a class="text-[#de7864] hover:text-[#c8543d] font-bold underline" href="https://www.chesshouse.com/pages/chess-rules" target="_blank">The Rules of Chess</a>
                    - A great website that goes into more detail on the basics above.
                </li>
                <li class="pb-[1vh]">
                    <a class="text-[#de7864] hover:text-[#c8543d] font-bold underline" href="https://www.chess.com/learn-how-to-play-chess" target="_blank">7 Steps To Get You Started</a>
                    - Essential information with videos to help with concepts.
                </li>
                <li class="pb-[1vh]">
                    <a class="text-[#de7864] hover:text-[#c8543d] font-bold underline" href="https://nextlevelchess.blog/beginner-chess-strategy/" target="_blank">Beginner Chess Strategy</a>
                    - After learning the basics, we recommend learning strategy.
                </li>
            </ul>
        </div>

        <!-- Contributors -->
        <div class="flex flex-col">
            <h1 class="text-2xl font-semibold pb-[1vh]">Contributors and Repo</h1>
            <p class="pb-[2vh]">
               This project was created by the quintet listed below, with advice along the way from
               our TA 
               <a class="underline hover:text-" href="https://github.com/adam-mcdaniel" target="_blank">Adam McDaniel</a>.
                Please checkout our individual github profiles as well as the project repo below.
            </p>

            <ul class="pb-[4vh]">
                <li class="pb-[1vh]">
                    <a class="text-[#de7864] hover:text-[#c8543d] font-bold underline" href="https://github.com/jdixon34-cs340" target="_blank">Jared Dixon</a>
                    - Back End (Chess Engine)
                </li>
                <li class="pb-[1vh]">
                    <a class="text-[#de7864] hover:text-[#c8543d] font-bold underline" href="https://github.com/Brandon-Marth" target="_blank">Brandon Marth</a>
                    - Front End (Web Assembly and Web Application)
                </li>
                <li class="pb-[1vh]">
                    <a class="text-[#de7864] hover:text-[#c8543d] font-bold underline" href="https://github.com/JMcknight75" target="_blank">Justin McKnight</a>
                    - Back End (Chess Engine)
                </li>
                <li class="pb-[1vh]">
                    <a class="text-[#de7864] hover:text-[#c8543d] font-bold underline" href="https://github.com/Dev5ter" target="_blank">Devin Munsey</a>
                    - Back End (Chess Engine)
                </li>
                <li class="pb-[1vh]">
                    <a class="text-[#de7864] hover:text-[#c8543d] font-bold underline" href="https://github.com/Jxk0be" target="_blank">Jake Shoffner</a>
                    - Front End (Web Application)
                <li class="pb-[1vh]">
                     <a class="text-[#de7864] hover:text-[#c8543d] font-bold underline" href="https://github.com/utk-cs340-fall22/Chess" target="_blank">Project Repository</a>
                    - Source Code (Front and Back End)
            </ul>
        </div>

    </div>
</div>

<Footer />