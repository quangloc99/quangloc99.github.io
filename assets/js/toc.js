function createToc(wrapper, navWrapper) {
  class Header {
    constructor(level, elm, navElm) {
      this.level = level;
      this.elm = elm;
      this.navElm = navElm;
    }
    
    getTop() {
      return this.elm.offsetTop;
    }
    
    // might be override/overwrite
    getBottom() {
      return this.elm.offsetBottom;
    }
  }
  const headerTagRegex = /h\d/i;
  const headers = Array(6).fill(0).map(() => []);
  const stk = [];
  for (const elm of wrapper.children) {
    const tag = elm.tagName;
    if (!headerTagRegex.test(tag)) continue;
    const lv = +tag[1] - 1;
    while (stk.length > 0 && stk[stk.length - 1].level <= lv) {
      const back = stk.pop();
      back.getBottom = () => elm.offsetTop;
    }
    const navElm = document.createElement("a");
    navElm.innerHTML = elm.innerHTML;
    navElm.href = `#${elm.id}`;
    navElm.classList.add("nav-elm");
    navElm.classList.add(tag.toLowerCase());
    navWrapper.appendChild(navElm);
    const newHeader = new Header(lv, elm, navElm);
    headers[lv].push(newHeader);
    stk.push(newHeader);
  }
  while (stk.length > 0) {
    const back = stk.pop();
    back.getBottom = () => wrapper.offsetBottom;
  }
}
