import { createContentLoader, ContentData } from 'vitepress';

type Post = ContentData & {
    excerpt: string;
    title: string | undefined;
    date: Date | undefined;
};

const stringOrUndefined = (value: unknown) => (typeof value == 'string' ? value : undefined);
const dateOrUndefined = (value: unknown) => (typeof value == 'string' ? new Date(value) : undefined);

const throwError = (msg: string) => {
    throw new Error(msg);
};

const postPattern = 'posts/**/*.md';
const postLoader = createContentLoader(postPattern, {
    excerpt: '<!-- more -->',
    // excerpt: true,
    transform: (data) =>
        data
            .filter((value) => {
                // exclude post that has name starts with `_`
                const parts = value.url.split('/');
                return !parts[parts.length - 1].startsWith('_');
            })
            .filter((value) => value.frontmatter.layout === 'blog-post')
            .map(
                (value): Post => ({
                    ...value,
                    excerpt: value.excerpt ?? throwError(`Post ${value.url} does not have excerpt`),
                    title:
                        stringOrUndefined(value.frontmatter.title) ??
                        throwError(`Post ${value.url} does not contain 'title' in frontmatter.`),
                    date:
                        dateOrUndefined(value.frontmatter.date) ??
                        throwError(`Post ${value.url} does not contain 'date' in frontmatter`),
                })
            )
            .sort((u, v) => v.date.getTime() - u.date.getTime()),
});

export default postLoader;
declare const data: Awaited<ReturnType<(typeof postLoader)['load']>>;
export { data };
