<script lang="ts" setup>
    import DefaultTheme from 'vitepress/theme';
    import { useData } from 'vitepress';
    import { useSiteRedirect } from './composables/useSiteRedirect';
    import { Config } from './index';
    import { provide, ref, nextTick } from 'vue';
    import { sleep } from '../utils';

    const { Layout } = DefaultTheme;
    const { theme, isDark } = useData<Config>();
    const shouldRedirect = useSiteRedirect(theme.value.redirects);

    const CURTAIN_COLORS = ['white', 'black'];
    // for debugging
    // const CURTAIN_COLORS = ['red', 'yellow'];
    const CURTAIN_MOVE_DURATION_ms = 200;
    const CURTAIN_BACKGROUND_CHANGE_DURATION_ms = 350;

    const curtainIsDark = ref(isDark.value);
    const curtainLeft = ref(0);
    const curtainRight = ref(0);

    function setCurtainPositionForTheme() {
        if (curtainIsDark.value) {
            curtainLeft.value = 100;
        } else {
            curtainRight.value = 100;
        }
    }
    function closeCurtain() {
        curtainLeft.value = curtainRight.value = 0;
    }
    setCurtainPositionForTheme();

    provide('toggle-appearance', async () => {
        closeCurtain();
        await sleep(CURTAIN_MOVE_DURATION_ms);
        isDark.value = !isDark.value;
        await nextTick();
        curtainIsDark.value = !curtainIsDark.value;
        await sleep(CURTAIN_BACKGROUND_CHANGE_DURATION_ms);
        setCurtainPositionForTheme();
        await sleep(CURTAIN_MOVE_DURATION_ms);
    });
</script>

<template>
    <Layout v-if="!shouldRedirect" />
    <div
        class="theme-switcher-curtain"
        :style="{
            '--moveDuration': `${CURTAIN_MOVE_DURATION_ms}ms`,
            '--backgroundChangeDuration': `${CURTAIN_BACKGROUND_CHANGE_DURATION_ms}ms`,
            left: `${curtainLeft}vw`,
            right: `${curtainRight}vw`,
            background: `${CURTAIN_COLORS[+curtainIsDark]}`,
        }"
    />
</template>

<style scoped>
    .theme-switcher-curtain {
        height: 100vh;
        position: fixed;
        z-index: 1000000;
        top: 0;

        transition:
            left ease-in var(--moveDuration),
            right ease-in var(--moveDuration),
            background ease var(--backgroundChangeDuration);
    }
</style>
