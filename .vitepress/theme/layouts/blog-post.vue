<script lang="ts" setup>
    import { computed } from 'vue';
    import VPDoc from 'vitepress/dist/client/theme-default/components/VPDoc.vue';
    import { useData } from 'vitepress';
    import { formatPostDate } from '../../utils';

    const { frontmatter } = useData();
    const shouldShowTitle = computed(() => !!frontmatter.value.title || !!frontmatter.value.date);
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
    </VPDoc>
</template>
