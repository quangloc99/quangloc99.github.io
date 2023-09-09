import { defineConfig, defineConfigWithTheme } from 'vitepress';
import { Config } from './theme';
import implicitFigures from 'markdown-it-implicit-figures';
import makdownItKatex from 'markdown-it-katex';

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

    sitemap: {
        hostname: 'https://quangloc99.github.io',
    },
    srcExclude: ['legacy-jekyll-component/**/*'],

    markdown: {
        config(md) {
            md.use(implicitFigures, {
                dataType: false, // <figure data-type="image">, default: false
                figcaption: 'title', // <figcaption>alternative text</figcaption>, default: false
                keepAlt: true, // <img alt="alt text" .../><figcaption>alt text</figcaption>, default: false
                lazyLoading: false, // <img loading="lazy" ...>, default: false
                link: true, // <a href="img.png"><img src="img.png"></a>, default: false
                tabindex: true,
            });
            md.use(makdownItKatex);
        },
    },

    head: [
        // [
        //     'script',
        //     {
        //         src: 'https://polyfill.io/v3/polyfill.min.js?features=es6',
        //     },
        // ],
        // [
        //     'script',
        //     {
        //         id: 'MathJax-script',
        //         async: 'true',
        //         src: 'https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-chtml.js',
        //     },
        // ],
        // ['script', {}, `MathJax = ${JSON.stringify(MathJaxSetting)}`],
        [
            'link',
            {
                rel: 'stylesheet',
                href: 'https://cdnjs.cloudflare.com/ajax/libs/KaTeX/0.16.8/katex.min.css',
            },
        ],
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
            {
                srcPart: '2022/03/08/polygon-codeforces-tutorial',
                dest: '/posts/polygon-codeforces-tutorial/index.html',
            },
            { srcPart: '2021/10/01/im-red-now-what', dest: '/posts/im-red-now-what/index.html' },
            { srcPart: '2021/07/30/my-CP-debugging-template.html', dest: '/posts/my-CP-debugging-template.html' },
        ],
    },
});
