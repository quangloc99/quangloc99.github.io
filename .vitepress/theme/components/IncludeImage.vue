<script lang="ts" setup>
    import { useData } from 'vitepress';
    import { computed } from 'vue';
    const props = defineProps<{
        caption?: string;
        alt?: string;
        src?: string;
        file?: string;
        width?: string;
    }>();
    const { frontmatter } = useData();

    const caption = computed(() => props.caption);
    const specialCharacters = /[~!@#$%^&*()-_=+\[\]{}\|;:\'",.<>/?]/g;
    const alt = computed(
        () =>
            props.alt ??
            caption.value
                ?.trim()
                ?.replace(/[ \n\t]/g, '-')
                ?.replace(specialCharacters, '')
    );
    const src = computed((): string => {
        if (props.src) return props.src;
        if (!props.file) return props.file;
        if (frontmatter.value.image_dir) return props.file;
        return `${frontmatter.value.image_dir}/${props.file}`;
    });
</script>

<template>
    <figure>
        <a :href="src" target="_blank">
            <img :src="src" :alt="alt" :style="props.width ? `width: ${props.width}` : ''" />
        </a>
        <figcaption v-if="caption">{{ caption }}</figcaption>
    </figure>
</template>

<style scoped>
    figure {
        text-align: center;
        display: block;
    }
    img {
        border: 1px solid gray;
        margin: 0 auto;
    }
</style>
