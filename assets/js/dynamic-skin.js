// the trick is described here:
// https://derekkedziora.com/blog/dark-mode

{
    const curtainMovingTime_ms = 0.2 * 1000;
    const backgroundChangingTime_ms = 0.4 * 1000;

    const theme = localStorage.getItem('theme');
    if (theme === "dark") {
        document.documentElement.setAttribute('data-theme', 'dark');
    }
    if (!theme) {
        const userPrefers = getComputedStyle(document.documentElement)
                                .getPropertyValue('content');

        if (userPrefers === "dark") {
            document.documentElement.setAttribute('data-theme', 'dark');
            window.localStorage.setItem('theme', 'dark');
        } else {
            document.documentElement.setAttribute('data-theme', 'light');
            window.localStorage.setItem('theme', 'light');
        }
    }

    const curtain = document.createElement("div");
    curtain.classList.add("curtain");
    window.addEventListener("load", () => document.body.appendChild(curtain));

    let isCovering = false;

    window.modeSwitcher = function modeSwitcher() {
        if (isCovering)
            return;
        isCovering = true;
        curtain.classList.add("covering");
        setTimeout(() => {
            let currentMode =
                document.documentElement.getAttribute('data-theme');
            if (currentMode === "dark") {
                document.documentElement.setAttribute('data-theme', 'light');
                window.localStorage.setItem('theme', 'light');
            } else {
                document.documentElement.setAttribute('data-theme', 'dark');
                window.localStorage.setItem('theme', 'dark');
            }
            setTimeout(() => {
                curtain.classList.remove("covering");
                setTimeout(() => isCovering = false, curtainMovingTime_ms);
            }, backgroundChangingTime_ms);
        }, curtainMovingTime_ms);
    }
}
