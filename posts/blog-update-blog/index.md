---
layout: blog-post
title: Sau một năm đi làm và không động vào blog, tôi quyết định bắt đầu lại với bước đầu tiên là thay đổi blog engine
date: '2023-09-23T08:55:38+07:00'
---

Một tiêu đề có độ dài như thế này các bạn có thể hình dung đến tiêu đề của một
[Light Novel][light-novel] -- tiêu đề thường hay dài để tóm tắt khái quát qua nội
dung của tác phẩm, nhằm thu hút người đọc bởi cái nhìn đầu tiên, trong vô vàn
tác phẩm khác. Nhưng rõ ràng là nó sẽ không có tác dụng lắm nếu như home page
của blog của bạn có phần trích đoạn ngay dưới tiêu đề :rofl:.

[light-novel]: https://anime.stackexchange.com/questions/48832/why-do-light-novels-and-manga-have-long-titles

<!-- more -->

Nhưng riêng với blog này, tiêu đề đã mô tả quá rõ ràng rồi, do đó mình sẽ không
dẫn dắt thêm nữa. Nói là một blog post, nhưng post này sẽ có hai nội dung:
mình tiếp tục viết blog, và thay đổi blog engine. Nhìn vào tiêu đề mà nói,
việc thay đổi blog engine sẽ là tâm điểm chính cho post này.

::: info Đính chính
Nói là đổi _blog engine_, tuy nhiên thứ mình đổi ở đây là đổi [_static site
generator_][static site generator].
:::

## Tại sao mình không sử dụng Jekyll nữa

Mình lựa chọn [Jekyll] là vì đó là lựa chọn _mặc định_ khi host blog trên
[Github page](https://pages.github.com/). Github page xử lý các tài nguyên
tĩnh, do đó sử dụng một [static site generator] là một lựa chọn hợp lý.
Sử dụng [static site generator] cũng giúp người viết blog nói riêng và
người quản lý nội dung nói chung không cần phải quan tâm đến việc quản lý
dữ liệu động. [Jekyll] còn được Github ủng hộ, do đó đây lúc nào cũng là
một trong những sự lựa chọn hàng đầu khi bắt đầu viết blog mà host trên
Github page. Cá nhân mình nghĩ rằng [Jekyll] vẫn là một sự lựa chọn
tôt khi mới bắt đầu.

[Jekyll] có đi kèm với một theme mặc định là [Mimima][Jekyll-minima]. Mình
cũng rất thích theme này với mô tả trong Github repo của nó:

> Minima is a one-size-fits-all Jekyll theme for writers.

Tức đây là một theme rất đơn giản, nhưng có thiết kế modern và vừa mắt. Câu
mô tả trên không sai một tí nào luôn!

Vậy khi mới mở blog, mình sử dụng Jekyll và tất nhiên cũng dùng minima luôn.
Tất nhiên cũng sửa sửa nhẹ. Do lúc mình cài, phiên bản Minima khi tạo blog
mới là 2.0, nên mình có bump nó lên 3.0 để dùng các tính năng mới hơn.

Tuy nhiên mình không chỉ mỗi tập chung vào phần nội dung. Mình là người rất chú
trọng hình thức. Vì đây là static site generator, mình quản lý toàn bộ nội dung
của blog, bao gồm cả theme, do đó mình hoàn toàn có thể thực hiện modding site
của mình. Do đó là mình đã thêm kha khá component cho trang blog, như là
theme-switcher, table of content, import file code từ ngoài, comment section,
...  Từ bài viết cuối của mình là mình còn có những component đang viết dở, song
mình không tiếp tục mod nữa mà mình đi làm những thứ khác, bỏ quên chúng luôn.
Về những component đã thêm vào, mình còn document chúng lại. Các bạn có thể đọc
file [README.md][old-blog-readme] cũ tại đây để xem những component mình đã thêm
vào.

![Presentation](./img/megamind-presentation.gif "Presentation!")

Đó là khoảng 1 năm về trước. Bây giờ khi nhìn lại, mình nhận ra rằng nếu mod
như vậy lại rất khổ sở. Mình không biết Ruby (ngôn ngữ mà [Jekyll] sử dụng)
để mod ở tầng đó (well thật ra là mình có thể học nhưng mình nhớ mình đọc
đâu đó mà Github page với Jekyll không chạy custom Ruby gì gì đó, nên mới
không tiếp tục). Việc mod do đó diễn ra ở phần Front-end, và mình mod luông
bằng ngôn ngữ template mà Jekyll sử dụng - [Liquid][Liquid-lang]. Liquid
có thể sử dụng như một ngôn ngữ lập trình hoàn chỉnh. Nó có biến, vòng
lặp và rẽ nhánh. Mình có thê include component bất kì vào blog post và layout
riêng của mình. Nhưng có những trở ngại nhất định khi dùng Liquid:

::: details Việc include nội dung bên ngoài.
Khi mình muốn include content ở ngoài, file đó cần nằm cùng thư mục `_posts` của
Jekyll mà không được nằm trong chỗ khác. Ngoài ra mình còn cần phải ignore các
file này khỏi site, những nội dung này lại cần nằm trong một thư mục khác có dầu
`_` ở trước tên. Nên là mình tống hết chúng nó vào một thư mục là
`_embed_contents`. Nó còn các chi tiết lẻ tẻ khác nữa, nhưng nói dến đây cũng có
thể thấy quản lý nội dung không rành mạch lắm.
:::

::: details Việc include file `script` và `style`.
Các component mình tạo ra chủ yếu là component Front-end, và chúng yêu cầu các
file `script` và `style`. Với giới hạn của Liquid, mình phải tự phát minh ra
include-guard y như trong C. Về triển khai bạn có thể tham khảo tạo file này
[file này][old-blog.custom-include-guard]. Chưa kể khi include `script` và
`style` như thế này là include vào giữa `body` chứ không phải là một chỗ cố
dịnh.
:::

<!-- maybe more ? -->

Và có nhiều chi tiết lặt vặt khác. Như vậy thật thời gian mình bỏ ra để mod
blog site của mình còn nhiều hơn cả thời gian viết blog. Đến đây mình mời nhận
ra rằng mình nên sử dụng tool khác thay vì Jekyll. Một Front-end framework thực
sự thay vì một ngôn ngữ template đơn thuần.

## Vậy mình đã chọn static site generator nào?

Nếu như bạn nhìn vào trang blog của mình và chưa biến nó giống cái tool nào,
thì mình xin giới thiệu chiếc static site generator [Vitepress]! Vitepress
đã đạt, thậm chí vượt qua tiêu chí mình mà mình chọn static site generator:

- Sử dụng [Vue][Vuejs] Front-end framework. Như mình đã đề cập ở trên, mình
muốn sử dụng một framework để mod dễ dàng hơn. Thậm chí tool này còn được tạo
ra chính bởi team tạo ra Vue, được sử dụng bởi team Vue để viết documentation.
Nên đây là tool rất tín!

- Ngôn ngữ lập trình cho Front-end chính là `JavaScript` và `TypeScript`. Việc
có `TypeScript` là một điểm cộng rất lớn. Mình đã tiếp xúc rất nhiều với
`TypeScript` trong vòng một năm vừa qua, và quan điểm của mình là có typing lúc
nào cũng tốt hơn.  (btw mình tự tin nói rằng mình thông thạo `TypeScript`. Sẽ có
blog về `TypeScript`.  Soon :tm:)

- Well, ngôn ngữ lập trình cho phần core và configuration cũng là `TypeScript`
luôn. Mình có thể mod thêm phần core và configuration nếu muốn (và tất nhiên là
có mod rồi).

Tất nhiên mình cũng đã tham khảo qua các lựa chọn khác. Sau khi Google thì mình
đã tìm ra trang tổng hợp được các [site generator][site-generator-list]. Các lựa
chọn nổi bật như sau:

- Hugo: tool viết bằng Go và được shill là alternative mạnh cho Jekyll. Mình chưa
đi sâu vào tool này tho, nhưng khi biết Vitepress thì mình nghĩ là sẽ không đi vào
sâu hơn nữa.
- Hexo: actually same as above.
- Gasby: đây là tool có phần Front-end dựa trên React. Không phải mình anti-React,
nhưng có thể nói mình _thạo_ Vue hơn (dù thật ra mình cũng mù hai cái ngang nhau).
- Vuepress: đây là tiền thân của Vitepress. Do Vitepress rõ ràng là tool mới hơn,
nên Vuepress _nằm ngoài phương trình_.
- Các tool còn lại: đều hướng đến việc viết documentation hơn là việc viết blog.

:::details Ngoài lề
Danh sách các tool generator kia cũng có nhiều tool thú vị, được viết trên nhiều
ngôn ngữ lập trình khác nhau. Có những tool viết bằng `C++` và `Rust`, rồi thậm chí
cả `Bash`. Do đã chọn được tool rồi nên mình không đi sâu vào chúng nữa.
:::

Tất nhiên Vitepress cũng có trở ngại khác. Vitepress cũng là tool sử dụng chủ yếu
để viết documentation hơn là được sử dụng để viết blog. Tuy nhiên cũng đã có các
_attempts_ sử dụng Vitepress cho blogging:

- [Theme Vitepress cho blog][vitepressblog].
- [Project template cho Vitepress][vitepress-blog-starter].
- [Một danh sách các blog cá nhân sử dụng Vitepress trên Github](https://github.com/topics/vitepress-blog).

Như vậy có thể tự tin khẳng định Vitepress cũng là tool phù hợp cho việc blogging.
Với mục đích là mod site, nên mình cũng không sử dụng các template/theme có sẵn.
Thay vào đó là mình bắt tay vào mod từ đầu. Tất nhiên các project trên cũng được
sử dụng với mục đích tham khảo :joy:.

[static site generator]: https://en.wikipedia.org/wiki/Static_site_generator
[github-page]: https://pages.github.com/
[Jekyll]: https://jekyllrb.com/
[Jekyll-minima]: https://github.com/jekyll/minima
[old-blog-readme]: https://github.com/quangloc99/quangloc99.github.io/blob/cc332508d79420158ab00518260bd41e870d6dbb/README.md
[Liquid-lang]: https://shopify.github.io/liquid/
[old-blog.custom-include-guard]: https://github.com/quangloc99/quangloc99.github.io/blob/cc332508d79420158ab00518260bd41e870d6dbb/legacy-jekyll-component/_includes/customhighlight.html#L1
[Vitepress]: https://vitepress.dev/
[Vuejs]: https://vuejs.org/
[site-generator-list]: https://jamstack.org/generators/
[vitepressblog]: https://vitepressblog.dev/guide/getting-started
[vitepress-blog-starter]: https://github.com/sfxcode/vitepress-blog-starter