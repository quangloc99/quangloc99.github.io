---
layout: custompost
title: "Writting a better generator - A Guide to Problem Preparation [Part 2]"
date: 2022-03-26 00:00:00 +0300
tags: [en, polygon, codeforces, testlib, cp, test-generation]
prepdir: _embed-contents/2022-02-19-test-generation-guide
old_image_dir: /assets/2022-02-19-test-generation-guide
wrapCode: true
useMathjax: true
image_dir: /assets/2022-03-09-polygon-codeforces-tutorial
toc: 
  use: true
  upper_header_level: 3
customhighlight:
  dir: _embed-contents/2022-02-19-test-generation-guide
vim: spell wrap
---

{% comment %}
Plan:
[ ] Mentions the previous post:
  [ ] The statements, the solutions, generators, validators, ... everything is
  there.
[ ] Reemphasize the reusability and of a generator.
[ ] Explain about strong and interesting tests.
[ ]  
{% endcomment %}

## Enhancements 
{% comment %}
Plan:
[ ] Why some enhancements?
[ ] List of enhancements:
  [x] Shuffle test cases
  [x] Result control
  [ ] Minimum array length
  [ ] Elements values
[ ] Introducing `get-opt`
  [ ] Function for getting default option.
{% endcomment %}

Before going further, I wanted to point out some _minors_ of the problems of the
previous generator. 

### Shuffling the test cases
Previously, our generator only generate the tests so that the first cases are
the `YES` cases, while the last cases are `NO`. This is good for the author to
inspect the test, but a test is not good to be generated this way. A participant
can just stop the process and print `NO` right after the first occurrence of `NO`
test.

There are several ways to fix this. One way is to determine the result of all
the tests first, and then use that to generate the result. 

{% include customhighlight.html caption="Determine test case type before
generating" file="shuffle-cases-first-way.fragment.cpp" ext="cpp" %}

Here I used the function `shuffle` from **`testlib.h`** if `testlib.h` is
included, and not from C++ standard library. The [`std::fill`][cpp-stl-fill]
function on the other hand is from the standard library, which fill a given
range with a given value.

Another way to shuffle the cases is, to _shuffle the cases_ at the end. To do
so, we need to store the test cases into an array/vector, and then shuffle it
after the whole process. The code for this way might look like this:

{% include customhighlight.html caption="Shuffle the cases at the end"
file="shuffle-cases-second-way.fragment.cpp" ext="cpp"
%}

In this code fragment, the line `using TestCase = vector<int>` is for
determining a new type for storing a test case. This problem is simple,
therefore a vector is enough. But with a more complex input, a custom type with
struct/class should be used. And as before, `shuffle` is used to shuffle the
cases. 

I prefer the second way because it is more _extensible_. Even though the second
is a bit longer and will consume more memory, we can reuse the test somewhere
else if necessary. Imagine the case where we need to generate a structure based
on a previously generated structure, then we need to somehow keep that previously
generated structure somewhere.

### Control the number of `YES` tests
Our previous generator accepts an option called `yes-count`, and generate
exactly `yes-count` tests with the result `YES`. But to be honest, for most of
the time, we wanted this options to be about `50%` percent of the number of
tests. The case where we need the other value of `yes-count` is when we are
generating only one test case in a test, which the number of `yes-count` must be
either $0$ or $1$. So, let's make this option an **ratio** instead! We can pass
the values like $0$, $0.5$ or $1$, which meets our requirement, and can
still accept other value if needed. But dealing with real numbers are often not
very nice, so we should use integer instead, with a fixed denominator. I like to
use _percentage_, meaning when the generate accept an integer $x$, our ratio
will be $x / 100$. Per mile (which is $1 / 1000$) also work.

{% include customhighlight.html caption="Using `yes-percent` option"
file="yes-percent.fragment.cpp" ext="cpp" %}

In this code, beside [`opt`][testlib-opt-guide] mentioned in the previous post,
there is also an _undocumented_ function of `testlib.h` called
[`has_opt(key)`][testlib-has-opt], used to check if an option with a name `key`
was passed to the generator. Here, if the key `yes-percent` is not presented,
then we use the default value `50`, since we wanted the two test types to spread
evenly. And after that we calculate the `yes-count` based on `yes-percent`.

{: .notes }
Beware of overflow when doing multiplication.

Consider using ratio when you don't want the value to be exact, but proportional
to some other value.

#### Default value `opt`
We can also see that making _default value_ might become handy in the future, so
let's implement a function for that, using `has_opt` and `opt`.

{% include customhighlight.html caption="get_opt: opt with default value"
file="get-opt.fragment.cpp" ext="cpp" %}

Unlike `opt`, we don't need to pass the type parameter to `get_opt`, because of 
[C++ template argument deduction][cpp-template-argument-deduction].

{: .notes }
There is currently no function to do the thing as the above `get_opt` in
`testlib.h`, and there is also **no function** for checking is an opt is used or
not. So if `get_opt` is used, remember to check your typing carefully to make
sure there is no **typo errors** in the option name. I have thought of a
solution, but that require to modify `testlib.h`. So maybe I will contribute to
`testlib.h` in the future.

### The array length.

[cpp-stl-fill]: https://en.cppreference.com/w/cpp/algorithm/fill
[testlib-opt-guide]: https://codeforces.com/blog/entry/72702
[testlib-has-opt]: https://github.com/MikeMirzayanov/testlib/blob/f28d52804011c5dca2e62fbe7cff45888579b0e8/testlib.h#L70
[cpp-template-argument-deduction]: https://en.cppreference.com/w/cpp/language/template_argument_deduction
