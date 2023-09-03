import { ref, watchEffect, toValue, MaybeRefOrGetter } from 'vue';

export type CFResponse<Result> = { status: 'OK'; result: Result } | { status: 'FAILED'; comment: string };

/**
 * @remarks
 * Partiall schema is manually coded from from CF API.
 * @see https://codeforces.com/apiHelp/objects#User
 */
export type CFUserInfo = {
    handle: string;
    contribution: number;

    // Actually absent if the user didn't participate in any contest yet, or headquater
    rating?: number;
    maxRating?: number;
    rank?: CFRank;
    maxRank?: CFRank;
};

/**
 * @remarks
 * List got from https://codeforces.com/blog/entry/99660
 */
export type CFRank =
    | 'newbie'
    | 'pupil'
    | 'specialist'
    | 'expert'
    | 'candidate master'
    | 'master'
    | 'international master'
    | 'grandmaster'
    | 'international grandmaster'
    | 'legendary grandmaster'
    | 'headquater';

export function useCFUserInfo(userHandle: MaybeRefOrGetter<string>) {
    const userInfo = ref<CFUserInfo>(null);
    const error = ref<Error>(null);

    watchEffect(async () => {
        userInfo.value = null;
        error.value = null;
        try {
            const res: CFResponse<CFUserInfo> = await fetch(
                `https://codeforces.com/api/user.info?handles=${toValue(userHandle)}`
            ).then((res) => res.json());
            if (res.status === 'FAILED') {
                throw new Error(`CFResponse error: ${res.comment}`);
            } else {
                userInfo.value = res.result;
            }
        } catch (e: unknown) {
            error.value = e as Error;
        }
    });

    return { userInfo, error };
}

export default useCFUserInfo;
