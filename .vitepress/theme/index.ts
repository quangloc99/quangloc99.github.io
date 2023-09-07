import { Theme } from 'vitepress';
import DefaultTheme, { type DefaultTheme as DefaultThemeType } from 'vitepress/theme';
import Posts from './components/Posts.vue';
import BlogPost from './layouts/blog-post.vue';
import BlogHome from './layouts/blog-home.vue';
import IncludeImage from './components/IncludeImage.vue';
import CFHandle from './components/CFHandle.vue';
import ThemeLayout from './theme-layout.vue';

export const theme: Theme = {
    extends: DefaultTheme,
    Layout: ThemeLayout,
    enhanceApp: async ({ app }) => {
        app.component('Posts', Posts);
        app.component('blog-post', BlogPost);
        app.component('blog-home', BlogHome);
        app.component('include-image', IncludeImage);
        app.component('cf-handle', CFHandle);
    },
};

export default theme;

export type Config = DefaultThemeType.Config & {
    redirects?: {
        srcPart: string;
        dest: string;
    }[];
};
