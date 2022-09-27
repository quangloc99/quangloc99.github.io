---
layout: custompost
title: "Sinh test (?)"
date: 2022-09-27 10:00:00 +0700
prepdir: _embed-contents/2022-09-27-cp-gen-test
image_dir: /assets/2022-09-27-cp-gen-test
useMathjax: true
toc:
  use: true
---

{% comment %}
Draft layout
* Intro
* Before start
- `mt19937`
+ rand
- `system`
- macros
* Simple stupid problem
* 2/3 programs templates
* Single program 
- Use global variable
- Using file
- Using stream
- Using objects
- Calling itself
* Bonus: Interactive problem
* Bonus: stupid validator?
{% endcomment %}

Môn lập trình thi đấu (competitive programming - CP) quả là một môn thi đấu khá
đặc biệt so với các bộ môn olympic khác. Người thi CP bình thường được cấp một
công cụ rất rất mạnh trong quá trình làm bài, đó là chiếc máy tính...

## Một số kiến thức biết trước khi sinh test
_Phần này chỉ nhắc lại một số kiến thức cơ bản. Bạn có thể bỏ qua._

Điều đầu tiên phải biết rõ ràng phải là ngôn ngữ lập trình. Trong bài viết này
mình sẽ sử dụng C++11, vì đây vẫn là ngôn ngữ lập trình phổ thông nhất đối với
tất cả mọi người. Ngoài ra mình muốn nhấn mạnh là **phiên bản 11** của
C++, vì đây là phiên bản modern đầu tiên của C++, và hầu hết mọi trang web, cũng
như các cuộc thi đều hỗ trợ phiên bản này trở lên.

### Trình sinh số ngẫu nhiên

Nói đến C++11, không thể không nói đến công cụ mới nhất được thêm vào, đó là
**trình sinh số ngẫu nhiên** `mt19937` và `mt19937_64`. Các dùng cũng rất đơn
giản:

{% include customhighlight.html caption="Ví dụ cho mt19937 và mt19937_64"
  dir=page.prepdir
  file="mt19937-examples.fragment.cpp"
  ext="cpp"
%}

Chi tiết về hai class này có thể xem tại [cppreference.com][cppreference-mt19937].

Với phiên bản C++ cũ hơn (C++98), hay với C, ta có thể dùng hàm
[`rand()`][cppreference-rand]. Tuy nhiên hàm này có rất nhiều nhược điểm so với
`mt19937` (xem chi tiết tại [post codeforces này][codeforces-dont-use-rand]). Do
đó `mt19937` nên được sử dụng, nhất là khi ta sử dụng phiên bản C++11 trở lên.

### Macro và tiền xử lý

Trong đa số trường hợp khi giải bài, macro không thực sự cần thiết. Tuy nhiên
đây là cách _đơn giản nhất_ để tùy chỉnh chương trình C++ mà không cần phải động
nhiều vào bài làm. Hãy tưởng tượng đến cuối giờ làm bài mà luống cuống, bạn lại
quên bỏ đi phần code mà bạn dùng để sinh test, như vậy điểm của bài làm đã mất
đi như không có đièu gì xảy ra vậy!

Macro có thể được định nghĩa và kiểm tra như sau trong một chương trình C++.

{% include customhighlight.html caption="Ví dụ định nghĩa và kiểm tra macro"
  dir=page.prepdir
  file="macro-example.fragment.cpp"
  ext="cpp"
%}

Macro còn có thể được định nghĩa ở **ngoài chương trình**. Ta có thể khai báo
macro `MY_MACRO` với câu lệnh dịch sau:

{% include customhighlight.html caption="Định nghĩa macro trong câu lệnh dịch
với cờ -D"
  exp="sh"
  content="
  g++ -DMY_MACRO solution.cpp
  "
%}

Nếu bạn sử dụng trình IDE Code::Blocks, bạn có thể thêm macro vào target bằng
cách chọn `Project > Build option`. Trên cửa sổ hiện lên, hãy chọn tab `#defines`
và thêm danh sách macro bạn muốn thêm vào.

{% include image.html caption="Thêm macro cho Code::Blocks"
  file="codeblocks-defines.png"
%}

### Hàm `system`

Hàm [`system`][cppreference-system] là một hàm cho phép người sử dụng thực thi
một câu lệnh (một chương trình ở ngoài) cho bởi một xâu. Thông thường đây là hàm
rất nguy hiểm và nên hạn chế sử dụng trong quá trình pháp triển sản phẩm. Tuy
nhiên đây là hàm rất đơn giản và mạnh mẽ nếu như ta muốn sử dụng nhiều chương
trình cùng lúc.

{% include customhighlight.html caption="Ví dụ sử dụng hàm `system`"
  dir=page.prepdir
  file="system-example.fragment.cpp"
  ext="cpp"
%}

## Bài toán ví dụ
Để mô phỏng quá trình sinh test, ta sẽ cùng nhau giải một bài toán cơ bản sau:

Cho dãy gồm $n$ số nguyên $a_1, a_2, \ldots, a_n$. Với mỗi phần tử $a_i$, hãy
tìm phần tử $a_j$ sao cho $|a_i - a_j|$ là lớn nhất. Nếu có nhiều đáp án, hãy in
ra đáp án bấ kì.

**Input format**

Dòng đầu tiên gồm số nguyên $n$ ($1 \le n \le 10^5$).

Dòng thứ hai gồm $n$ số nguyên $a_1, a_2, \ldots, a_n$ ($\lvert a_i \rvert \le 10^9$).

**Output format**

Hãy in ra $n$ số. Số thứ $i$ là phần tử $a_j$ sao cho $\lvert a_i - a_j \rvert$ có giá trị
lớn nhất.

Bài toán này được chọn vì:
- Bài này có hai lời giải, một lời giải dễ nhưng chậm, và lời giải nhanh hơn
  nhưng cũng không quá khó.
- Input của bài là một dãy số.
- Output của bài cũng là một dãy số.
- Bài toán có nhiều output.



[cppreference-mt19937]: https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine
[cppreference-rand]: https://en.cppreference.com/w/c/numeric/random/rand
[codeforces-dont-use-rand]: https://codeforces.com/blog/entry/61587
[cppreference-system]: https://en.cppreference.com/w/cpp/utility/program/system
