<script lang="ts" setup>
    import { computed } from 'vue';
    import { formatPostDate } from '../../utils';

    const { date, title, excerpt } = defineProps<{
        date: Date;
        title: string;
        url: string;
        excerpt?: string;
    }>();
    const formattedDate = computed(() => formatPostDate(date));
</script>

<template>
    <div>
        <div>
            <a :href="url">
                <h3>{{ title }}</h3>
            </a>
        </div>
        <div :class="$style.date">{{ formattedDate }}</div>
        <div :class="$style.excerpt" v-if="excerpt" v-html="excerpt"></div>
        <hr />
    </div>
</template>

<style module>
    .date {
        font-weight: 200;
    }
    .excerpt {
        opacity: 0.7;
    }
</style>
