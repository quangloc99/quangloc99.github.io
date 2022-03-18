function createToc(wrapper, navWrapper, {
    title = "",
    getBottom = () => wrapper.offsetTop + wrapper.offsetHeight,
    lowerHeaderLevel = 2,
    upperHeaderLevel = 6
} = {}) {
    --lowerHeaderLevel;
    --upperHeaderLevel;
    const MAGIC_OFFSET_BETWEEN_SECTION = 70;
    class Header {
        constructor(level, elm, navElm) {
            this.level = level;
            this.elm = elm;
            this.navElm = navElm;
        }

        getTop() { return this.elm.offsetTop; }

        // might be override/overwrite
        getBottom() { return this.getTop() + this.elm.offsetHeight; }

        getHeight() { return this.getBottom() - this.getHeight(); }

        isIntersected(lower, upper) {
            return Math.max(lower, this.getTop()) <=
                   Math.min(upper, this.getBottom());
        }
    }
    const headerTagRegex = /h\d/i;
    const headers = Array(6).fill(0).map(() => []);
    const stk = [];
    if (title !== "") {
        const navElm = document.createElement("a");
        navElm.innerHTML = title;
        navElm.href = "#";
        navElm.classList.add("nav-elm");
        navElm.classList.add("h1");
        navElm.tabindex = "0";
        navWrapper.appendChild(navElm);
        const newHeader = new Header(0, wrapper, navElm);
        headers[0].push(newHeader);
    }
    for (const elm of wrapper.children) {
        const tag = elm.tagName;
        if (!headerTagRegex.test(tag))
            continue;
        const lv = +tag[1] - 1;
        if (lv < lowerHeaderLevel || lv > upperHeaderLevel) {
            continue;
        }
        while (stk.length > 0 && stk[stk.length - 1].level >= lv) {
            const back = stk.pop();
            back.getBottom = () => elm.offsetTop - MAGIC_OFFSET_BETWEEN_SECTION;
        }
        const navElm = document.createElement("a");
        navElm.innerHTML = elm.innerHTML;
        navElm.href = `#${elm.id}`;
        navElm.classList.add("nav-elm");
        navElm.classList.add(tag.toLowerCase());
        navElm.tabindex = "0";
        navWrapper.appendChild(navElm);
        const newHeader = new Header(lv, elm, navElm);
        headers[lv].push(newHeader);
        stk.push(newHeader);
    }
    while (stk.length > 0) {
        const back = stk.pop();
        back.getBottom = getBottom;
    }

    let ticking = false;

    function scrollspyUpdate() {
        const lower = window.scrollY;
        const wheight = window.innerHeight;
        const upper = lower + wheight;
        for (const headerLayer of headers) {
            for (const header of headerLayer) {
                if (!header.isIntersected(lower, upper)) {
                    header.navElm.classList.remove("active");
                } else {
                    header.navElm.classList.add("active");
                }
                let readPercent =
                    (lower - header.getTop() + wheight) /
                    (header.getBottom() - header.getTop() + wheight) * 100;
                readPercent = Math.max(0, Math.min(100, readPercent));
                header.navElm.style.setProperty("--read-percent",
                                                readPercent + "%");
            }
        }
    }

    scrollspyUpdate();

    document.addEventListener('scroll', function(e) {
        if (ticking)
            return;
        window.requestAnimationFrame(function() {
            scrollspyUpdate();
            ticking = false;
        });

        ticking = true;
    });

    if (ResizeObserver) {
        new ResizeObserver(scrollspyUpdate).observe(wrapper);
    }
}
