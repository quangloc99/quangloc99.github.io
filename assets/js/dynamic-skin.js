// the trick is described here:
// https://derekkedziora.com/blog/dark-mode

{
    const delay = 50;
    const curtainMovingTime_ms = 0.2 * 1000 + delay;
    const backgroundChangingTime_ms = 0.3 * 1000 + delay;

    // for the comment engine
    // https://github.com/utterance/utterances/issues/549#issuecomment-907606127
    function changeUtterancesTheme(theme) {
        const iframe = document.querySelector('.utterances-frame')
        if (!iframe) return;
        const message = {type : 'set-theme', theme};
        iframe.contentWindow.postMessage(message, 'https://utteranc.es');
    }

    const utterancesDark = () => changeUtterancesTheme("github-dark-orange");
    const utterancesLight = () => changeUtterancesTheme("boxy-light");

    function toggleSkin() {
        let currentMode = localStorage.getItem("theme");
        if (currentMode === "dark") {
            window.localStorage.setItem('theme', 'light');
        } else {
            window.localStorage.setItem('theme', 'dark');
        }
    }
    function updateSkin() {
        let currentMode = localStorage.getItem("theme");
        if (currentMode === "dark") {
            document.documentElement.setAttribute('data-theme', 'dark');
            utterancesDark();
        } else {
            document.documentElement.setAttribute('data-theme', 'light');
            utterancesLight();
        }
    }

    const theme = localStorage.getItem('theme');
    if (theme === "dark") {
        document.documentElement.setAttribute('data-theme', 'dark');
    }
    if (!theme) {
        const userPrefers = getComputedStyle(document.documentElement)
                                .getPropertyValue('content');

        if (userPrefers === "dark") {
            window.localStorage.setItem('theme', 'dark');
        } else {
            window.localStorage.setItem('theme', 'light');
        }
    }
    updateSkin();

    const curtain = document.createElement("div");
    curtain.classList.add("curtain");
    window.addEventListener("DOMContentLoaded", () => {
        document.body.appendChild(curtain);
        // to update utterances
        setTimeout(() => updateSkin());
    });

    let isCovering = false;

    window.modeSwitcher = function modeSwitcher() {
        if (isCovering)
            return;
        isCovering = true;
        curtain.classList.add("covering");
        setTimeout(() => {
            toggleSkin();
            updateSkin();
            setTimeout(() => {
                curtain.classList.remove("covering");
                setTimeout(() => isCovering = false, curtainMovingTime_ms);
            }, backgroundChangingTime_ms);
        }, curtainMovingTime_ms);
    }
}
