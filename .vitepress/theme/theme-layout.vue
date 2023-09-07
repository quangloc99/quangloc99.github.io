<script lang="ts" setup>
    import DefaultTheme from 'vitepress/theme';
    import { useData } from 'vitepress';
    import { useSiteRedirect } from './composables/useSiteRedirect';
    import { Config } from './index';

    const { Layout } = DefaultTheme;
    const { theme } = useData<Config>();
    const shouldRedirect = useSiteRedirect(theme.value.redirects);
</script>

<template>
    <Layout v-if="!shouldRedirect" />
</template>
