import DefaultTheme from 'vitepress/theme';
import Posts from './components/Posts.vue';
import BlogPost from './layouts/blog-post.vue';
import BlogHome from './layouts/blog-home.vue';
import IncludeImage from './components/IncludeImage.vue';
import CFHandle from './components/CFHandle.vue';

export const theme = {
    extends: DefaultTheme,
    enhanceApp({ app }) {
        app.component('Posts', Posts);
        app.component('blog-post', BlogPost);
        app.component('blog-home', BlogHome);
        app.component('include-image', IncludeImage);
        app.component('cf-handle', CFHandle);
    },
};

export default theme;
