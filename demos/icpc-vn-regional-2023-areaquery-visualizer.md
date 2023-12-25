---
layout: blog-post
title: Visualizer cho bài Area query ICPC Việt Nam Regional 2023
aside: false
---

Đây là demo nhỏ để mô phỏng bài [Area query][problem] với lời giải của mình. Chi tiết về demo ở phía dưới.

This is a small demo to visualize the [Area query][problem] with my solution. Details about the demo are below.

<iframe
    frameBorder="0"
    style="
        width: 100%;
        height: 80vh;
    "
    src="https://quangloc99.github.io/vietnam-icpc-2023-regional-areaquery-visualizer/?input=NwoxIDEKMSA3CjIgOAo0IDcKNyA0CjggMgo3IDEKMTUKQSAxIDMKQSAxIDQKQSAxIDUKQSAxIDYKPyAxIDMKUiAxIDMKQSAyIDQKUiAxIDYKQSA1IDcKPyAyIDUKUiAxIDUKUiAxIDQKQSA0IDcKQSAyIDcKPyA3IDQKICAgIA%3D%3D&storedCheckboxes=111" />

## Tính năng

- Cho phép nhập input của một test case với format đã mô tả ở trong đề bài.
  - Input sẽ được validate, nhưng sẽ không kiểm tra chặt chẽ từng khoảng trắng.
- Vẽ hình:
  - Các phần đa giác được chia, cấu trúc cây tạo bởi các vùng được cắt, và vùng cắt được giữ lại cho truy vấn **cuối cùng**.
  - Màu của vùng cắt, màu của đường cắt và màu của các nút của cây tương ứng với nhau là giống nhau.
- Output:
  - [Euler tour của cây][tree-euler-tour], với màu tương ứng với node trên cây.
  - Thứ tự thăm các đường cắt khi đi trên cạnh của đa giác đã cho theo thứ tự đỉnh $1, 2, \ldots, n$, với màu tương ứng với màu của đường cắt.
  - Cũng là thứ tự thăm đường cắt nhưng in ra cả đường cắt thay vì mỗi đỉnh.
  - Đáp án cho truy vấn **cuối cùng**.
- Control:
  - Checkbox để ẩn/hiện output.
- Preview: link để có thể chèn vào blog khác mà không có phần control.

## Source code

Ban đầu để code nhanh thì mình đã phát triển cái visualizer này trên codepen [tại đây][visualizer-on-codepen], và ban đầu mình cũng định dùng code pen để host luôn.

Song phần copy preview hoạt động không tốt lắm, nên cuối cùng mình lại host trên github page. Các bạn có thể xem source code [tại đây][visualizer-on-github].

---

## Features

- Allows inputting a test case following the format described in the problem statement.
  - The input will be validated but won't be strictly checked for each space.
- Drawing:
  - Divides the polygons, creates a tree structure based on the cut regions, and keeps the cut region for the **final query**.
  - The color of the cut region, the color of the cut path, and the color of the corresponding tree nodes are the same.
- Output:
  - [Euler tour of the tree][tree-euler-tour], with colors corresponding to the nodes on the tree.
  - Order of visiting the cut paths while traversing the edges of the given polygon in the order of vertices $1, 2, \ldots, n$, with colors corresponding to the cut paths.
  - Also the order of visiting cut paths but displaying the entire cut paths instead of individual vertices.
  - Answer for the **final query**.
- Control:
  - Checkbox to hide/show output.
- Preview: Link to embed into other blogs without the control section.

## Source code

The initial idea was to develop this visualizer quickly on CodePen [here][visualizer-on-codepen], and originally, I planned to use CodePen to host it.

However, copying the preview didn't work well, so ultimately, I ended up hosting it on GitHub Pages. You can view the source code [here][visualizer-on-github].

[problem]: https://oj.vnoi.info/problem/icpc23_regional_a
[tree-euler-tour]: https://codeforces.com/blog/entry/18369
[visualizer-on-codepen]: https://codepen.io/quangloc99/full/oNmKgEO
[visualizer-on-github]: https://github.com/quangloc99/vietnam-icpc-2023-regional-areaquery-visualizer