<script lang="ts" setup>
    import { computed, CSSProperties } from 'vue';
    import { useCFUserInfo, CFRank } from '../composables/useCFUserInfo';
    const props = defineProps<{
        nickname: string;
        rank?: CFRank;
        displayMaxRank?: boolean;
    }>();

    function useRank() {
        if (props.rank) return props.rank;

        const { userInfo, error } = useCFUserInfo(props.nickname);
        return computed(() =>
            error ? undefined : props.displayMaxRank ? userInfo.value.maxRank : userInfo.value.rank
        );
    }

    const rank = useRank();
</script>

<template>
    <span class="cf-handle" :class="rank?.replace(' ', '-') ?? ''">{{ props.nickname }}</span>
</template>

<style>
    .cf-handle.newbie {
        color: gray;
    }
    .cf-handle.pupil {
        color: #77ff77;
    }
    .cf-handle.specialist {
        color: #77ddbb;
    }
    .cf-handle.expert {
        color: #aaaaff;
    }
    .cf-handle.candidate-master {
        color: #ff88ff;
    }
    .cf-handle.master {
        color: #ffcc88;
    }
    .cf-handle.international-master {
        color: #ffbb55;
    }
    .cf-handle.grandmaster {
        color: #ff7777;
    }
    .cf-handle.international-grandmaster {
        color: #ff3333;
    }
    .cf-handle.legendary-grandmaster {
        color: #ff3333;
    }
    .cf-handle.legendary-grandmaster::first-letter {
        color: black;
    }
    .cf-handle.headquater {
        color: black;
        font-weight: 800;
    }
    
    .dark .cf-handle.cf-handle.legendary-grandmaster::first-letter {
        color: white;
    }
    
    .dark .cf-handle.headquater {
        color: white;
    }
</style>
