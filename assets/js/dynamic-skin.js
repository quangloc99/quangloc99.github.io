// the trick is described here:
// https://derekkedziora.com/blog/dark-mode

const theme = localStorage.getItem('theme');
if (theme === "dark") {
    document.documentElement.setAttribute('data-theme', 'dark');
}
if (!theme) {
    const userPrefers =
        getComputedStyle(document.documentElement).getPropertyValue('content');

    if (userPrefers === "dark") {
        document.documentElement.setAttribute('data-theme', 'dark');
        window.localStorage.setItem('theme', 'dark');
    } else {
        document.documentElement.setAttribute('data-theme', 'light');
        window.localStorage.setItem('theme', 'light');
    }

}
    
function modeSwitcher() {
    let currentMode = document.documentElement.getAttribute('data-theme');
    if (currentMode === "dark") {
        document.documentElement.setAttribute('data-theme', 'light');
        window.localStorage.setItem('theme', 'light');
    } else {
        document.documentElement.setAttribute('data-theme', 'dark');
        window.localStorage.setItem('theme', 'dark');
    }
}
