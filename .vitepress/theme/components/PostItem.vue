<script lang="ts" setup>
import { computed } from 'vue';

const { date, title, excerpt } = defineProps<{
    date: Date;
    title: string;
    url: string;
    excerpt?: string;
}>();

const dateFormatter = Intl.DateTimeFormat('en-GB', {
    month: 'short',
    day: '2-digit',
    year: 'numeric',
});
const formattedDate = computed(() => {
    console.log(date);
    return dateFormatter.format(new Date(date));
});

</script>

<template>
    <div>
        <div><a :href="url"><h3>{{ title }}</h3></a></div>
        <div :class="$style.date">{{ formattedDate }}</div>
        <div v-if="excerpt" v-html="excerpt"></div>
        <hr />
    </div>
</template>

<style module>
.date {
    font-weight: 200;
}
</style>
