<script>
    import Icon from '@iconify/svelte';

    /* Variables */
    let noMenu = true;

    /* Handlers and other functions */
    const CloseMenu = () => noMenu = true;
    const OpenMenu = () => noMenu = false;
</script>

<!-- This is the top of the Navigation Bar -->
<div class="w-full h-[9vh] bg-[#171717] text-white flex flex-row justify-between items-center text-[25px] fixed z-40">
    <a href="/" class="ml-6"><h1>ChadChess&trade</h1></a>

    <!-- This is only viewed on mobile, right side of Navbar -->
    {#if noMenu === true}
        <div class="text-4xl md:hidden mr-6" on:click={() => OpenMenu()}>
            <Icon icon="line-md:close-to-menu-alt-transition" />
        </div>
    {:else if noMenu === false}
        <div class="text-4xl md:hidden mr-6" on:click={() => CloseMenu()}>
            <Icon icon="line-md:menu-to-close-alt-transition" />
        </div>
    {/if}
</div>

