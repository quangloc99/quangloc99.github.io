## Scripts
For local note development.
```sh
bundle exec jekyll serve
```

## Customization documentation
### The layout `custompost.html`

This layout inherit the default `post` layout of jekyll. It is used to
initialized some liquid global variables that used internally in this repo, as
well as adding some components to the post. This layout should be used in order
to use the components below.

### Mathjax
To use mathjax inside the page, use the `custompost` layout, then include the
following into the frontmatter:

```yaml
---
mathjax: true
---
```

### TOC

This repo has a custom TOC, which is a nice sidebar, generated with Javascript.

To have this custom TOC, use the `custompost` layout, then in the frontmatter:

```yaml
---
toc: true  # Should be truthful
---
```

#### Usage
##### Frontmatter config
```yaml
---
toc:
    # [Optional, default is 2]
    # The smallest header number to be included in TOC.
    lower_header_level: 2
    # [Optional, default is 6]
    # The biggest header number to be included in TOC. 
    upper_header_level: 3
---
```

### `Customhighlight`

Along side with the default highlighting, this component provides:
- File include
- Code wrapping
- Collapsible container (with caption)

#### Usage
##### Frontmatter config
```yaml
---
customhighlight:
    # [Optional]
    # The default directory that contains the files to be included
    dir: some dir
    # [Optional]
    # Wether the component has its content _wrapped_
    wrap: true
---
```

##### Include

```liquid
{% include customhighlight.html
    dir="some dir"
    file="filename.ext"
    content="string"
    noStrip=true/false
    ext="extension"
    collapsed=true/false
    wrap=true/false
%}
```

- `dir`: the directory to the file. If not provided, `page.customhighlight.page` will be used.
- `file`: the file name.
- `content`: specify the inline content to use instead of including the file.
- `noStrip`: wether to strip the `content` (remove spaces at the beginning and at the end).
- `ext`: the extension. If not provided, and if the file name has a period, the final part after the period is used.
- `collapsed`: wether the component is hidden when the user visit the page.
- `wrap`: wether the component has its content _wrapped_. If not provided, `page.customhighlight.wrap` is used.


### Image
This component allows to specify the following to an `img` element:
- File includes
- Alt text
- Caption
- Click to see full image

#### Usage
##### Frontmatter config
```yaml
---
# [Optional]
# Specify the directory that contains the included images.
image_dir: some dir
---
```

##### Include
```liquid
{% include image.html
    dir="some dir"
    file="filename.png"
    url=""
    caption="caption"
    alt="alt text"
%}
```

- `dir`: the directory to the file. If not provided, `page.image_url` will be used.
- `file`: the file name.
- `url`: use image url instead of file name.
- `caption`: the image caption.
- `alt`: alt text for the image. If not provided, `caption` is preprocessed (by removing some special characters and joined all the words with hyphens) and used.

### [Utterances](https://utteranc.es/)

Utterances is **turned on by default** when the `custompost` layout is used. Also note that it will not be showm for the development environment (it will refetch a lot of time otherwise).

#### Usage
##### Frontmatter config
```yaml
---
utterances:
    # To disable utterances.
    disable: true
---
```