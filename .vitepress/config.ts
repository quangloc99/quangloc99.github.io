import { defineConfig, defineConfigWithTheme } from 'vitepress';
import { Config } from './theme';

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

export default defineConfigWithTheme<Config>({
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
        nav: [{ text: 'About', link: '/about' }],
        socialLinks: [
            { icon: 'github', link: 'https://github.com/quangloc99' },
            { icon: 'discord', link: 'https://discord.com/users/501085823480102925' },
            { icon: 'facebook', link: 'https://www.facebook.com/TQLoc' },
        ],
        redirects: [
            { srcPart: '2022\/03\/08\/polygon-codeforces-tutorial', dest: '/posts/polygon-codeforces-tutorial/index.html' },
            { srcPart: '2021\/10\/01\/im-red-now-what', dest: '/posts/im-red-now-what/index.html'},
            { srcPart: '2021/07/30/my-CP-debugging-template.html', dest: '/posts/my-CP-debugging-template.html' },
        ],
    },
});
