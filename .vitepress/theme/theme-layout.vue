<script lang="ts" setup>
    import { computed } from 'vue';
    import DefaultTheme from 'vitepress/theme';
    import { useData } from 'vitepress';
    import type { Config } from './index';

    const { Layout } = DefaultTheme;
    const { theme } = useData<Config>();

    const shouldRedirect = computed(() => {
        if (!theme.value.redirects) return false;
        for (const { srcRegex, dest } of theme.value.redirects) {
            if (!window.location.href.match(new RegExp(srcRegex))) continue;
            window.location.href = `${dest}${window.location.hash}${window.location.search}`;
            return true;
        }
        return false;
    });
</script>

<template>
    <Layout v-if="!shouldRedirect" />
</template>
