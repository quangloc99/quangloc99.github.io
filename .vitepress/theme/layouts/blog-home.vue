<script lang="ts" setup>
    import VPDoc from 'vitepress/dist/client/theme-default/components/VPDoc.vue';
    import { useData } from 'vitepress';

    const { frontmatter, description } = useData();
</script>

<template>
    <div class="title-background">
        <div
            v-if="frontmatter.background"
            class="background"
            :style="`--background-image-url: url(${frontmatter.background})`"
            >
        </div>
        <div class="desciption">
            {{description}}
            <hr>
        </div>
    </div>
    <VPDoc class="doc">
    </VPDoc>
</template>

<style scoped>
    .title-background {
        --background-height: 500px;
        height: var(--background-height);
        width: 100%;
    }
    
    .background {
        height: var(--background-height);
        width: 100%;
        position: absolute;
        filter: brightness(0.8);
        z-index: -1;
        background: var(--background-image-url) no-repeat center center/cover;
    }
    
    .desciption {
        width: 90%;
        max-width: 500px;
        margin: 0 auto;
        text-align: center;
        padding-top: calc(var(--background-height) * 0.8);
        color: white;
    }
    
    .desciption hr {
        border: 1px solid white;
    }
</style>
