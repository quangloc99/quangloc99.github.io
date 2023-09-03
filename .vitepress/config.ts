import { defineConfig } from 'vitepress';

export default defineConfig({
    // site-level options
    title: 'Darkkcyan blog',
    description: `
Just a personal blog. Might be about my job. Might be about my hobby.
Might be about math. Might be about art. Who knows?`,
    
    markdown: {
        lineNumbers: true,
    },

    themeConfig: {
        aside: 'left',
        outline: {
            level: [2, 3]
        }
    },
});
