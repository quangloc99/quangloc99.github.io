export const postDateFormatter = Intl.DateTimeFormat('en-GB', {
    month: 'short',
    day: '2-digit',
    year: 'numeric',
});

export function formatPostDate(date: Date | string) {
    if (typeof date == 'string') date = new Date(date);
    return postDateFormatter.format(date);
}

export function sleep(ms: number) {
    return new Promise((resolve) => setTimeout(resolve, ms));
}
