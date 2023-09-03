import { defineConfig } from 'vitepress';
import mathjax3 from 'markdown-it-mathjax3';

const customElements = ['mjx-container'];

export default defineConfig({
    // site-level options
    title: 'Darkkcyan blog',
    description: `
Just a personal blog. Might be about my job. Might be about my hobby.
Might be about math. Might be about art. Who knows?`,

    markdown: {
        lineNumbers: true,
        config(md) {
            md.use(mathjax3);
        },
    },

    themeConfig: {
        aside: 'left',
        outline: {
            level: [2, 3],
        },
    },
    vue: {
        template: {
            compilerOptions: {
                isCustomElement: (tag) => customElements.includes(tag),
            },
        },
    },
});
