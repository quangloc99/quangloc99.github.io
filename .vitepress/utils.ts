export const postDateFormatter = Intl.DateTimeFormat('en-GB', {
    month: 'short',
    day: '2-digit',
    year: 'numeric',
});

export function formatPostDate(date: Date | string) {
    console.log(date);
    if (typeof date == 'string') date = new Date(date);
    console.log(date);
    return postDateFormatter.format(date);
}
