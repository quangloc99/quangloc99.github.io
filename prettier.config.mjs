// @ts-check

/** @type {import("prettier").Config} */
const config = {
    overrides: [
        {
            files: '*.{ts,js,json,mjs}',
            options: {
                bracketSpacing: true,
                printWidth: 120,
                semi: true,
                singleQuote: true,
                tabWidth: 4,
                trailingComma: 'es5',
                useTabs: false,
            },
        },
    ],
};

export default config;
