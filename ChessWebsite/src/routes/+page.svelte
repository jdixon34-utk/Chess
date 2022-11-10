<script>
    import Footer from "../components/Footer.svelte";
    import Icon from '@iconify/svelte';

    /* Variables */
     let noMenu = true;

    /* Handlers and other functions */
    const CloseMenu = () => noMenu = true;
    const OpenMenu = () => noMenu = false;
</script>

<!-- This is the top of the Navigation Bar -->
<div class="w-full h-[9vh] bg-[#171717] text-white flex flex-row justify-between items-center text-[25px] fixed z-40">
    <a href="/" class="ml-6 font-bold text-[#f6be86] hover:text-[#c5986b] transition ease-in-out duration-150 cursor-pointer"><h1>ChadChess&trade</h1></a>

    <!-- This is only viewed on mobile, right side of Navbar -->
    {#if noMenu === true}
        <div class="text-4xl md:hidden mr-6 cursor-pointer" on:click={() => OpenMenu()}>
            <Icon icon="line-md:close-to-menu-alt-transition" />
        </div>
    {:else if noMenu === false}
        <div class="text-4xl md:hidden mr-6 cursor-pointer" on:click={() => CloseMenu()}>
            <Icon icon="line-md:menu-to-close-alt-transition" />
        </div>
    {/if}

   <!-- This is only viewed on desktop, right side of Navbar -->
    <div class="hidden md:flex flex-row">
        <a href="/" class="mr-6 hover:text-[#f6be86] transition ease-in-out duration-200 cursor-pointer"><h1>Play</h1></a>
        <a href="/learn" class="mr-6 hover:text-[#f6be86] transition ease-in-out duration-150 cursor-pointer"><h1>How To Play</h1></a>
        <a href="/about" class="mr-6 hover:text-[#f6be86] transition ease-in-out duration-150 cursor-pointer"><h1>About Project</h1></a>
        <a href="https://github.com/utk-cs340-fall22/Chess" target="_blank" class="mr-6 hover:text-[#f6be86] transition ease-in-out duration-150 cursor-pointer"><h1>Github</h1></a>
    </div>
</div>

<!-- If the mobile menu is clicked, we need to display the menu -->
{#if noMenu === false}
    <div class="flex flex-col h-screen w-screen justify-center items-center bg-black text-white text-4xl md:hidden">
        <a on:click={() => CloseMenu()} href="/" class="mt-6"><h1>Play</h1></a>
        <a on:click={() => CloseMenu()} href="/learn" class="mt-6"><h1>How To Play</h1></a>
        <a on:click={() => CloseMenu()} href="/about" class="mt-6"><h1>About Project</h1></a>
        <a on:click={() => CloseMenu()} href="https://github.com/utk-cs340-fall22/Chess" target="_blank" class="mt-6"><h1>Github</h1></a>
    </div>
{/if}

<!-- If the mobile menu is closed, we show the chess board -->
{#if noMenu === true}
    <div class="flex justify-center items-center bg-[#b0a23a]/30">
        <embed class="md:w-screen md:h-[89vh] md:pt-[12vh] w-screen h-[85vh] pt-[12vh] pb-[4vh]" type="text/html" src="board.html" id="chessEmbed">
    </div>
    <Footer />
{/if}
