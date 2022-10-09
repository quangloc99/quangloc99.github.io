---
layout: custompost
title: "Sinh test (?)"
date: 2022-09-27 10:00:00 +0700
customhighlight:
  dir: _embed-contents/2022-09-27-cp-gen-test
image_dir: /assets/2022-09-27-cp-gen-test
mathjax: true
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
* Template rating criteria
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
  file="system-example.fragment.cpp"
  ext="cpp"
%}

## Tiêu chí đánh giá template
Blog này có xét nhiều template cho việc stress test. Tất nhiên các template sẽ
khác nhau, do đó chúng có các điểm mạnh và yếu khác nhau. Để xem xét được những
điểm mạnh yếu của một template, mình sẽ xét một vài tiêu chí sau:

- **Kiến thức cần biết thêm**. Một số template yêu cầu người sử dụng phải
  biết thêm những kiến thức khác ngoài kiến thức cần biết cho lập trình thi đấu.
  Như vậy template đòi hỏi nhiều kiến thức bên ngoài cũng sẽ gây khó khăn cho
  những bạn mới học.

- **Công chuẩn bị**. Một số template có nhiều công chuẩn bị hơn template khác, cụ
  thể là ở việc người sử dụng template cần thiết phải tạo thêm file, cần phải
  setup trình dịch/IDE để có thể dịch thêm file. Nếu công chuẩn bị chiếm nhiều
  thời gian, nó có thể ảnh hưởng đến quá trình làm bài trong kì thi. Tuy nhiên
  template có thể đem lại nhiều lợi thế hơn template khác.

- **Kiểm tra nhập xuất**. Một số template không kiểm tra phần nhập xuất của
  chương trình. Và nhiều khi bug có thể nằm ở chính phần nhập xuất (đọc
  thiếu/thừa dữ liệu).
  
- **Reset bộ nhớ toàn cục**. Trong CP, bộ nhớ toàn cục hay được sử dụng để chia
  sẻ dữ liệu với nhiều hàm khác nhau, làm đơn giản hóa việc code. Nhưng một số
  template sẽ không reset bộ nhớ toàn cục của chương trình. Nếu như trạng thái
  của bộ nhớ toàn cục không giống như lần đầu chạy (được khởi tạo bởi 0), lần
  chạy test sau sẽ có thể không cho ra đúng kết quả. Do đó người dùng template
  như vậy cần phải tự reset bộ nhớ sau mỗi test.

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
- Bài này có hai lời giải, cả lời giải nhanh và chậm đề dễ hiểu và dễ cài đặt.
- Input của bài là một dãy số.
- Output của bài cũng là một dãy số.
- Bài toán có nhiều output.

### Solution cho bài toán
#### Solution _chậm_
Với mỗi một phần tử trong mảng, ta có thể tìm đáp án sử dụng một vòng lặp. Như
vậy độ phức tạp cho solution sẽ là $O(n^2)$.

{% include customhighlight.html caption="Code cho lời giải chậm"
  file="slow-solution-example.cpp"
  ext="cpp"
  collapsed=true
%}

#### Solution _nhanh_
Nhận thấy rằng, giá trị _xa_ một phần tử nhất chỉ có thể là giá trị nhỏ nhất
hoặc lớn nhất trong mảng, nên ta có thể tìm hai giá trị này trước, và việc tìm
đáp án cho mỗi phần tử lúc này sẽ là $O(1)$.

{% include customhighlight.html caption="Code cho lời giải nhanh"
  file="fast-solution-example.cpp"
  collapsed=true
%}

## Template sinh test 1: chuẩn bị thêm 1-2 chương trình



[cppreference-mt19937]: https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine
[cppreference-rand]: https://en.cppreference.com/w/c/numeric/random/rand
[codeforces-dont-use-rand]: https://codeforces.com/blog/entry/61587
[cppreference-system]: https://en.cppreference.com/w/cpp/utility/program/system
