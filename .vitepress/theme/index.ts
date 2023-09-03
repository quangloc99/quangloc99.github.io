import DefaultTheme from 'vitepress/theme';
import Posts from './components/Posts.vue';

export const theme = {
    extends: DefaultTheme,
    enhanceApp({ app }) {
        app.component('Posts', Posts);
    },
};

export default theme;
