---
layout: post
title: "A guide to test-generation with Polygon and Testlib"
date: 2022-02-19 00:00:00 +0300
tags: [en, polygon, codeforces, testlib, cp]
prepdir: embed-contents/2022-02-19-test-generation-guide
assetsdir: /assets/2022-02-19-test-generation-guide
---

{% include mathjax.html %}

<!-- introduction bla bla -->

## The problem
The problem that we are going to take a look and make tests for today is
[Codeforces 1442A - Extreme
Subtraction](https://codeforces.com/problemset/problem/1442/A). The problem
statement is quite short, but let's repeat it once more time here.

We are given an array $a$ of length $n$. We can use the following operation as
many times as we want: select any integer $k$ ($1 \le k \le n$) and either:
- decrease $a_1, a_2, \ldots, a_k$ (the first $k$ elements) by $1$.,
- decrease $a_n, a_{n - 1}, \ldots, a_{n - k + 1}$ (the last $k$ elements) by
  $1$.

We must answer, for a given array $a$, if it is possible to make all the
elements of the array equal to zero by applying a certain number of operations.

And because this blog is about test generation, we also need to take a look at
the IO format, as well as the constraints.

#### Input
The first line contains one positive integer $t$ ($1 \le t \le 30000$) -- the
number of test cases. Each of the test cases is described as follows.

The first line of the test case contains one integer $n$ ($1 \le n \le 30000$)
-- the number of elements in the array.

The second line of the test case contains $n$ integers $a_1, a_2, \ldots, a_n$
($1 \le a_i \le 10^6$).

The sum of $n$ over all test cases does not exceed $30000$.

#### Output
For each test case, print `YES` if it is possible to make all elements of the
array equal to zero by applying a certain number of operations, and `NO`
otherwise.

#### Example
{%include customhighlight.html caption="Input" 
content="
4
3
1 2 1
5
11 7 9 6 8
5
1 3 1 3 1
4
5 2 1 10
"%}

{%include customhighlight.html caption="Output"
content="
YES
YES
NO
YES
" %}

## Before test generation
### Validator

After preparing the statement, the easiest thing to do is to write a validator.
A validator is a program that checks if the input follows the specified format
and constraints as in the statement. This post does not focus on test
validation. But we should as well go through it. Firstly, the validator is very
easy to write. And secondly, by pointing out whether a test follows the
constraints, the validator helps detect some bugs with the generator.

Without further a due, here is the validator. It is simple for this problem, so
I won't go into details here.

{%include customhighlight.html dir=page.prepdir file="validator.cpp"
  caption="validator.cpp" ext="cpp"
%}

Writing validation tests is also important in order to ensure its correctness. How
do I write validation tests? For each of the `read` statements, as well as
`ensuref` statements, I add two tests for it -- one with a value lower than
the lower bound, and one with a value higher than the upper bound.

Below are my validation tests.
- The first two are for testing the value of
`test-count`.
- The next two are for testing the value of `n`.
- And the following two are for the value of `a`.
- The next test is to test a very small test.
- The next test is for testing the `ensuref` statement, that is, ensuring if the
  sum of `n` does not exceed $30000$.
- And finally, I add another small random test.

Remember that on Polygon, there is an option for separating tests using `===` (3
equal signs). And also note about the must be an empty last line.

{% include customhighlight.html dir=page.prepdir file="validation-test.txt"
  caption="9 validation tests" collapsed=true
%}

{% include customhighlight.html dir=page.prepdir
  file="validation-test-verdicts.txt"
  caption="Verdicts for validation tests" collapsed=true
%}

If you notice, there are test that does not follow the format, like in the
second test I only put the number of test cases there. But here I wanted to test
the constraints only, and we can consider the validator correct when it produce
the correct verdict and **error message**. For testing the input formats, we
already have two tests, but more can be added.

{% include image.html alt="validation-test-result"
  caption="Validation test result"
  dir=page.assetsdir file="validation-test-result.png"
%}

### Checker
Each test of this problem has a fixed answer, therefore we can use a standard
checker. For this problem, the checker `std::nyesno.cpp` is enough.

`std::nyesno.cpp` will check for zero or more `yes`/`no` tokens in the output
file, case insensitive.


### Solutions
#### Model solution
A model solution is required in order to generate the output for the tests. 
Arccording to the [editorial][CF1442-editorial], the solution is quite short.
Here is the full solution, quoted from the editorial.

> The problem sounds like this -- check that there are increasing and decreasing
> arrays, the element-wise sum of which is equal to the given array.
> 
> This problem can be solved greedily. Let's maximize each element of the
> decreasing array (let's call this array $a$, and the increasing one $b$).
> Suppose initial array is $v$ and we have solved the problem on a prefix of
> length $i - 1$. Then, for the element $a[i]$, $a[i] \le a[i - 1]$ and $v[i] -
> a[i] \ge b[i - 1]$ must be fulfilled. Rewriting the second inequality and
> combining with the first one, we get $a[i] \le \min (a[i - 1], v[i] - b[i -
> 1])$. It is clear that taking $a[i] = \min (a[i - 1], v[i] - b[i - 1])$ is the
> best by construction.

Because it is very short, here is the solution in Python.

{% include customhighlight.html caption="py_solution.py"
  dir=page.prepdir file="solution.py" ext="py" collapsed=true
%}

{% include customhighlight.html caption="solution.cpp"
  dir=page.prepdir file="solution.cpp" ext="cpp" collapsed=true
%}

#### Very stupid, correct solution
But when preparing a problem, we don't have the tests yet. How can we ensure
that the model solution is correct? One way to do that is to test it against
another solution with a _high chance_ of being correct. Such a solution must
have correctness proven using no math, but our intuition only. I'm talking about
a **brute force** solution.

In this problem, brute force can be done with **simulation** -- we simply try
all possible ways to decrease the input array, and when we have all $0$, we can
conclude that there is an answer. Such simulation can be implemented with
recursion, but to make it a little faster, we can also use _memorization_ --
that is, storing all visited states.

{% include customhighlight.html caption="brute-force.cpp"
  dir=page.prepdir file="brute-force.cpp" ext="cpp" collapsed=true
%}

## And now the main part.
Before writing our very first generator, it is worth pointing out which
functionalities we are going to use. For RNG (random number generation), [this
post][generator-with-testlib] already covered some of them. There is also
[opts][testlib-opts] which allows us to pass parameters to the generator in a
readable way so a generator can be effectively reused.

The above posts are already old, and new functions are being added.
Noticeably:
- `rnd.partition(size, sum, [min_part=1])` is a part of RNG. It will generate a
  vector of the given size, the sum of whose elements must equal the second
  parameter, and elements must not be lower than `min_part`.
- `has_opt(key)` is a part of `opts`, which allows us to check if there is an
  opts with the name `key`.
  
The list of features also lies in [testlib.h] source code. I highly recommend
checking out the list, and also reading some of the functions. There are other
functions, but I will cover them when we get there.

### Our first generator

Let's generate a _totally_ random array. The point of this generator is to make
a _stress_ with the model and brute-force solution. Not every array will produce
the result `YES`, and it seems really unlikely for a random array. But with a
small enough range, surely we can hit `YES`.

> A _stress_ is a feature on Polygon that allows running some solutions with a
> generator. Polygon will generate tests using that generator and run those
> solutions repeatedly for a set time, with a set memory and time limit. The
> point of stress is to **check the correctness** or **find a wrong test**
> that kills a solution.

We still need to specify a few things for this generator. They are the number of
test cases, the array length, and the array element value range. For the first
two, instead of a fixed array length, we can specify the sum of the length. And
with a given test case count, we can split the length of all cases using
`rnd.partition`. With that, we have the following generator.

{% include customhighlight.html caption="gen-totally-random.cpp"
  dir=page.prepdir file="gen-totally-random.cpp" ext="cpp"
%}

Let's run it locally to generate a test with 5 test cases, the sum of length is
20, and the value range is from 1 to 5.

{% include customhighlight.html caption="gen-totally-random example"
  dir=page.prepdir file="gen-totally-random-example.sh.out"
%}

It's looking good so far. We are ready to add a stress on Polygon.

{% include image.html alt="stress-against-brute-force"
  caption="Stress against brute-force solution"
  dir=page.assetsdir file="stress1.png"
  %}

Here the script pattern is

    gen-totally-random -test-count [1..10] -sum-n 20 -min-a 1 -max-a 5

Polygon also supports minimal random parameters generation. Here I wanted the
`test-count` to be a random number between $1$ and $10$. A fixed `sum-n` and
a randomized `test-count` are good to randomize the test cases `n` without
worrying about the constraints.

I put the time limit to the max so the brute-force solution can have more time
to run.

Stress can help us find a counter test. For example, if we lower the time
limit, the brute-force solution will have TLE verdict.

{% include image.html alt="finding-counter-test-with-stress"
  caption="Finding a counting test with stress"
  dir=page.assetsdir file="stress2-finding-counter-test.png"
%}

The counter test is also in the form of a command. It still has the same
form as the script pattern, except for the last parameter. The last
parameter is a random hash that Polygon generates to change the random
seed of RNG for each test. Using testlib.h, the seed of a generator is
registered by calling `registerGen` and the seed is unique for a unique set of
flags/parameters.

### Making `YES` tests
As discussed before, a random array is unlikely to have an answer `YES`, and we
need to fix that. How about we _don't_ generate the array, but the _increasing
array_ $a$ and _decreasing array_ $b$ as in the editorial, then summing them up?
Doing so will guarantee to have the answer `YES` because that is what the
problem **is asking** the participant to do.

For this algorithm, there are some problems when reusing the code from
`gen-totally-random.cpp`
- We can not use `min-a` and `max-a` for this algorithm.
- That are only `YES` tests, how about the `NO` tests?

The first problem can be _partially_ solved by adding the value for
arrays $a$ and $b$ separately. For the second problem, we are going to generate
arrays $a$ and $b$ now, so let's also add an option to generate them randomly
instead of sorted. There should also be an option to sepecify how many of them
are `YES`, and how many are `NO`.

Here is the generator with the above idea.

{%include customhighlight.html caption="gen-v1.cpp"
  dir=page.prepdir file="gen-v1.cpp" ext="cpp"
%}

Let's run it
{%include customhighlight.html caption="gen-v1 example"
  dir=page.prepdir file="gen-v1-example.sh.out" 
%}

Here the first two tests are `YES` and the rest are `NO`. I purposely choose a
larger range so the test that should not be `YES` will be more likely to produce
the `NO` answer.


[CF1442-editorial]: https://codeforces.com/blog/entry/84298
[generator-with-testlib]: https://codeforces.com/blog/entry/18291
[testlib-opts]: https://codeforces.com/blog/entry/72702
[testlib.h]: https://github.com/MikeMirzayanov/testlib/blob/master/testlib.h
