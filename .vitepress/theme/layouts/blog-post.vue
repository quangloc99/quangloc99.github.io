<script lang="ts" setup>
    import { computed } from 'vue';
    import VPDoc from 'vitepress/dist/client/theme-default/components/VPDoc.vue';
    import { useData } from 'vitepress';
    import { formatPostDate } from '../../utils';
    import VueUtterances from 'vue-utterances';

    const { frontmatter, isDark } = useData();
    const shouldShowTitle = computed(() => !!frontmatter.value.title || !!frontmatter.value.date);

    // @ts-ignore
    const isProd: boolean = import.meta.env.PROD;
</script>

<template>
    <VPDoc>
        <template #doc-before>
            <div class="vp-doc">
                <div class="title" v-if="shouldShowTitle">
                    <h1 v-if="frontmatter.title">{{ frontmatter.title }}</h1>
                    <div v-if="frontmatter.date">{{ formatPostDate(frontmatter.date) }}</div>
                    <hr />
                </div>
            </div>
        </template>
        <template #doc-after>
            <VueUtterances v-if="isProd"
                repo="quangloc99/quangloc99.github.io"
                issue-term="title"
                :theme="isDark ? 'github-dark-orange' : 'github-light'"
            />
        </template>
    </VPDoc>
</template>
