// @ts-check

/** @type {import("prettier").Config} */
const config = {
    bracketSpacing: true,
    printWidth: 120,
    semi: true,
    singleQuote: true,
    tabWidth: 4,
    trailingComma: 'es5',
    useTabs: false,
    vueIndentScriptAndStyle: true,

    overrides: [
        {
            files: "*.md",
            options: {
                printWidth: 80,
                tabWidth: 2
            }
        }
    ],
};

export default config;
