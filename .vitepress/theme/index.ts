import DefaultTheme from 'vitepress/theme';
import Posts from './components/Posts.vue';
import BlogPost from './layouts/blog-post.vue';

export const theme = {
    extends: DefaultTheme,
    enhanceApp({ app }) {
        app.component('Posts', Posts);
        app.component('blog-post', BlogPost);
    },
};

export default theme;
