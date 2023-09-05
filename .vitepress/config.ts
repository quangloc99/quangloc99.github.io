import { defineConfig } from 'vitepress';

const MathJaxSetting = {
    tex: {
        packages: ['base'],
        inlineMath: [['$', '$']],
        displayMath: [
            ['$$', '$$'],
            ['\\[', '\\]'],
        ],
    },
};

export default defineConfig({
    // site-level options
    title: 'Darkkcyan blog',
    description: `
Just a personal blog. Might be about my job. Might be about my hobby.
Might be about math. Might be about art. Who knows?`,

    markdown: {},

    head: [
        [
            'script',
            {
                src: 'https://polyfill.io/v3/polyfill.min.js?features=es6',
            },
        ],
        [
            'script',
            {
                id: 'MathJax-script',
                async: 'true',
                src: 'https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-chtml.js',
            },
        ],
        ['script', {}, `MathJax = ${JSON.stringify(MathJaxSetting)}`],
    ],

    themeConfig: {
        aside: 'left',
        outline: {
            level: [2, 3],
        },
    },
});
