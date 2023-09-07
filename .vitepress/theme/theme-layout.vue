<script lang="ts" setup>
    import DefaultTheme from 'vitepress/theme';

    const { Layout } = DefaultTheme;

    const redirectMap = [
        { srcPart: '2022/03/08/polygon-codeforces-tutorial', dest: '/posts/polygon-codeforces-tutorial/' },
    ];

    let shouldRedirect = false;
    for (const { srcPart, dest } of redirectMap) {
        if (window.location.href.indexOf(srcPart) > -1) {
            window.location.href = `${dest}${window.location.hash}${window.location.search}`;
            shouldRedirect = true;
            break;
        }
    }
</script>

<template>
    <Layout v-if="!shouldRedirect" />
</template>
