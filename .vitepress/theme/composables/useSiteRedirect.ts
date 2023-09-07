import { computed, MaybeRefOrGetter, toValue } from 'vue';
import type { Config } from '../index';

export function useSiteRedirect(redirectMap: MaybeRefOrGetter<Config['redirects']>) {
    const shouldRedirect = computed(() => {
        if (typeof window === 'undefined') return false;
        const redirectMapValue = toValue(redirectMap);
        for (const { srcPart, dest } of redirectMapValue) {
            if (window.location.href.indexOf(srcPart) === -1) continue;
            window.location.href = `${dest}${window.location.hash}${window.location.search}`;
            return true;
        }
        return false;
    });
    return shouldRedirect;
}

export default useSiteRedirect;
