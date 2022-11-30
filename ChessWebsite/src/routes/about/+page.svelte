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
                Our project was to create a chess website, where the user could play our chess bot
                and test their skills. When we first came together as a group, we had the general idea
                but had no real idea of how we were going to execute this within the given time.
                After some thought and advice from our TA, we decided on dividing the work into a front-end
                and back-end. The latter being built in pure C++ and the former using Svelte.
            </p>

            <p class="pb-[4vh]">
                While that is a basic description of the project and how it came to be, there were many hurdles
                we had to overcome in order to get where we are today. We learned quickly that we had to
                work together if we were to complete this challenge in time.
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
                    <a class="text-[#769656] hover:text-[#526d38] font-bold underline" href="https://devdocs.io/cpp/" target="_blank">C++</a>
                    - Chess Engine
                </li>
                <li class="pb-[1vh]">
                    <a class="text-[#769656] hover:text-[#526d38] font-bold underline" href="https://developer.mozilla.org/en-US/docs/WebAssembly" target="_blank">Web Assembly</a>
                    - Bridging Back End and Front End
                </li>
                <li class="pb-[1vh]">
                    <a class="text-[#769656] hover:text-[#526d38] font-bold underline" href="https://svelte.dev/docs" target="_blank">Svelte</a>
                    - Web Application
                </li>
                <li class="pb-[1vh]">
                    <a class="text-[#769656] hover:text-[#526d38] font-bold underline" href="https://v2.tailwindcss.com/docs" target="_blank">TailwindCSS</a>
                    - Major Styling
                </li>
                <li class="pb-[1vh]">
                    <a class="text-[#769656] hover:text-[#526d38] font-bold underline" href="https://developer.mozilla.org/en-US/" target="_blank">JavaScript, HTML, CSS</a>
                    - Chess Board
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
                    <a class="text-[#769656] hover:text-[#526d38] font-bold underline" href="https://github.com/jdixon34-cs340" target="_blank">Jared Dixon</a>
                    - Back End (Chess Engine)
                </li>
                <li class="pb-[1vh]">
                    <a class="text-[#769656] hover:text-[#526d38] font-bold underline" href="https://github.com/Brandon-Marth" target="_blank">Brandon Marth</a>
                    - Front End (Web Assembly and Web Application)
                </li>
                <li class="pb-[1vh]">
                    <a class="text-[#769656] hover:text-[#526d38] font-bold underline" href="https://github.com/JMcknight75" target="_blank">Justin McKnight</a>
                    - Back End (Chess Engine)
                </li>
                <li class="pb-[1vh]">
                    <a class="text-[#769656] hover:text-[#526d38] font-bold underline" href="https://github.com/Dev5ter" target="_blank">Devin Munsey</a>
                    - Back End (Chess Engine)
                </li>
                <li class="pb-[1vh]">
                    <a class="text-[#769656] hover:text-[#526d38] font-bold underline" href="https://github.com/Jxk0be" target="_blank">Jake Shoffner</a>
                    - Front End (Web Application)
                <li class="pb-[1vh]">
                     <a class="text-[#769656] hover:text-[#526d38] font-bold underline" href="https://github.com/utk-cs340-fall22/Chess" target="_blank">Project Repository</a>
                    - Source Code (Front and Back End)
            </ul>
        </div>

    </div>
</div>

<Footer />