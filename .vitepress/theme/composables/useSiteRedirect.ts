import { computed, MaybeRefOrGetter, toValue } from 'vue';
import type { Config } from '../index';

export function useSiteRedirect(redirectMap: MaybeRefOrGetter<Config['redirects']>) {
    const shouldRedirect = computed(() => {
        const redirectMapValue = toValue(redirectMap);
        if (!redirectMapValue) return;
        for (const { srcRegex, dest } of redirectMapValue) {
            if (!window.location.href.match(new RegExp(srcRegex))) continue;
            window.location.href = `${dest}${window.location.hash}${window.location.search}`;
            return true;
        }
        return false;
    });
    return shouldRedirect;
}

export default useSiteRedirect;
