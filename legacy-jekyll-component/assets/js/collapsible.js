window.addEventListener("load", () => {
    const elms = document.querySelectorAll(".collapse-checkbox");
    Array.from(elms).forEach(elm => {
        const forElmId = elm.getAttribute("for-elm");
        if (!forElmId) return;
        const wrapper = elm.parentElement;
        if (!wrapper) return;
        const labelElm = wrapper.nextElementSibling;
        if (!labelElm) return; 
        const collapsibleElm = document.querySelector(`#${forElmId}`);
        if (!collapsibleElm) return; 
        collapsibleElm.classList.add("collapsible");
        collapsibleElm.style.height = collapsibleElm.offsetHeight + "px";
        function update() {
            if (elm.checked) {
                labelElm.classList.add("collapse");
                collapsibleElm.classList.add("collapse");
            } else {
                labelElm.classList.remove("collapse");
                collapsibleElm.classList.remove("collapse");
            }
        }
        update();
        elm.addEventListener("change", update);
    });
});
