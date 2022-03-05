---
layout: post
title: "A Guide to Test Generation with Polygon and Testlib"
date: 2022-02-19 00:00:00 +0300
tags: [en, polygon, codeforces, testlib, cp]
prepdir: _embed-contents/2022-02-19-test-generation-guide
assetsdir: /assets/2022-02-19-test-generation-guide
wrapCode: true
---

Problem setting is a hard task when preparing a programming competition. As an
[author for a Codeforces round](https://codeforces.com/blog/entry/98385), as
well as a [Codeforces coordinator for the first time
ever](https://codeforces.com/blog/entry/100368), I have to work with [Polygon] and
[`testlib.h`][testlib.h] to prepare problems for contests. But even with very convenient
platform as Polygon and library as `testlib.h`, test generation is still very
tricky. So in this post, I hope to demonstrate some of the patterns that I have
used and thought of for test generation from my little experiences.

## Table of contents
* TOC
{:toc}

{% include mathjax.html %}

## Prerequisite
Even though this post go through some Polygon features, this is not a Polygon
tutorial. This is also true for `testlib.h`. So having basic knowledges on using
Polygon and `testlib.h` is required.

This post also used some C++11 features, so having knowledges on C++11 is also required.

For testing the code offline, use run the code on the command line. This is not
really a requirement, but knowing how to use the command line is better for
fully understanding the commands. 

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

Because it is very short, here are the solutions in Python and C++.

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

## And now the main part
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
  dir=page.prepdir file="out/gen-totally-random-example.sh.out" ext="sh"
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
  caption="Finding a countertest with stress"
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

> Side note: in the editorial, the name of the _increasing array_ is actually
> $b$ and the _decreasing_ one is $a$. While making this blog, I have their
> names wrong. In my defense, making $a$ the increasing array is more natural
> than the other way around. So I'll keep it this way.

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
  dir=page.prepdir file="out/gen-v1-example.sh.out" ext="sh"
%}

Here the first two tests are `YES` and the rest are `NO`. I purposely choose a
larger range so the test that should not be `YES` will be more likely to produce
the `NO` answer.

### Small enhancements
`gen-v1.cpp` is already an ok generator, and it and it is good on its own.
But there are several enhancements we can add to it:
- It can sometimes produce arrays with very small lengths and sometimes an array
  with dominant length. Array with small length like $2$ always has the answer
  `YES`. This can be fixed by adding an option for minimum length for the
  arrays, so the length can be distributed more evenly.
- Now all of the `YES` tests are all at the beginning, and the `NO` tests are at
  the end. That is fine for a human to debug, but not fine for testing
  solutions. To overcome this, we can add an option to tell the generator do we
  want shuffled cases or not.
- Above I said we can _partially_ solve the value range problem. It is partial
  because it is harder to hit the maximum value using the above algorithm. A way
  to fix this is to _pad_ all of the elements with a constant, that is,
  increase all of them by a random constant. To make it hit the maximum
  value, we can use `rnd.wnext` to make that constant more likely to have
  extreme value. Also note that we should only increase, but not decrease,
  because some `YES` tests after decrement will become `NO`.
- Sometimes we don't want a fixed number of `YES` tests, but more often we want
  the number of `YES` tests to be proportional to the total test cases. We can
  change the `yes-count` option to be a ratio. I use _percentages_ for this
  since working with integers is easier.
- Actually, why do we need to specify the `yes-count` parameter? I mean, the
  good old 50% is enough for most cases, right? Let's make `50` the default
  percentages for the number of `YES` tests.
  
That is a number of small enhancements that I can think of. We will add more
thing to it later. For now let's add these enhancements to our generator.

{% include customhighlight.html caption="gen-v2.cpp"
  dir=page.prepdir file="gen-v2.cpp" ext="cpp" collapsed=true
%}



Here are some examples:

{%include customhighlight.html
  caption="gen-v2 example. Using the `min-n` option"
  dir=page.prepdir file="out/gen-v2-example1.sh.out" ext="sh" collapsed=true
%}

With `min-n` option, we can see that the array lengths are distributed
evenly. Point 1 is good!

{%include customhighlight.html
  caption="gen-v2 example. Using the `padding-bias` option for hitting maximum value"
  dir=page.prepdir file="out/gen-v2-example2.sh.out" ext="sh" collapsed=true
%}

In this example, most of the array has hit the max value (which is $200$). This
is because of the nature of randomization. This is good though because we wanted
the test to be random, not being in only one fixed shape.

{%include customhighlight.html
  caption="gen-v2 example. Using `yes-percent`, `no-shuffle-cases` and `padding-bias = -30` "
  dir=page.prepdir file="out/gen-v2-example3.sh.out" ext="sh" collapsed=true
%}

Using `padding-bias -30` means we wanted that the as close to $0$ as possible,
so the final array can be almost the same as without padding. The first three
test cases are having expected results. The $5$-th test case though is
a bit different. That is also because of our algorithm: we only guarantee
that all `YES` tests will have `YES` results, while that is not the case for the
`NO` tests.

### Making **more interesting** `YES` tests

So far we have a generator that can _more or less_ generate test cases. It will
work _fine_ under small constraints. But with bigger constraints, the tests
might be _uninterested_.

_What do you mean by **uninterested**?_ Let's look at how we generate the array
$a$, since the array $b$ generated using the same algorithm. The value of $a$ is
**uniformly** chosen in its value range. Because of that, with a bigger sample
the array $a$ will have a **linear shape**.

If the array $a$ and $b$ have the same range, $a$ is linearly increasing, and
$b$ is linearly decreasing, the generated array will be an almost horizontal line.

{% include image.html
  alt="increasing-linear-plus-decreasing-linear"
  dir=page.assetsdir file="linear-plus-linear.drawio.png"
  width="8cm"
  %}

Let's see the big tests.

{% include customhighlight.html caption="big gen-v2 test for plotting"
  dir=page.prepdir file="out/big-gen-v2-test-for-plotting.sh.out" ext="sh"
%}

And here is the Python script for plotting, which will be reused later.

{% include customhighlight.html caption="plot-test.py"
  dir=page.prepdir file="plot-test.py" ext="py" collapsed=true %}
  
Let's look at the plot.
{% include image.html caption="Plot for big tests, generated by gen-v2"
  alt="plot-for-big-tests-generated-by-gen-v2"
  dir=page.assetsdir file="big-gen-v2-test-for-plotting.png"
%}

There are still ups and downs parts in these tests, which means they still have
their values, but far away, they just look the same.

{% include image.html alt="they-are-the-same-picture"
  dir=page.assetsdir file="they-are-the-same-picture.png"
  width="5cm"
  %}
  
Of course, this can still be overcome with `gen-v2.cpp` by changing the range of
$a$ and $b$, but still, $linear + linear = linear$. We must have a way to
generate a non-linear array. One _obvious_ solution is using `rnd.wnext`, but that
is still boring! We can do better!

How do we know if an increasing array, or function, is _interesting_? For this
problem only, that might be defined by the _curves_ as well as the _plains_ in
the plotting of the array/function. Here _curve_ means that the value will be
changed smoothly, but not _too_ linearly. And _plain_ means repeated values
lying near each other.
  
{% include image.html caption="Some interesting functions"
  alt="some-interesting-functions"
  dir=page.assetsdir file="some-interesting-functions.drawio.png"
  width="8cm"
  %}
  
Welp, the above shows a lot of shapes that need to be covered.

#### Let's start with the stepping functions
Because making lots of elements with the same value is not done in `gen-v2.cpp`.
But this can be done quite simply: just limited the number of "used" values.
That is, instead of randomly choosing the value for each element in the value
range, we will pick some values beforehand, and the elements must only be one of
the picked values.

The `random_array` function can be changed as follows:

{% include customhighlight.html caption="random_array function"
  ext="cpp" dir=page.prepdir file="random-array-v1.fragment.cpp" %}

When `limited-value-a` option is presented, its value will be used as the
number of possible values in the array $a$.

But now we have a branch in our function, which is hard to extend further!
Here is a fix for that.

{% include customhighlight.html
caption="random_array function: using std::function"
  ext="cpp" dir=page.prepdir file="random-array-v2.fragment.cpp" %}

Here I create a local function called `gen_val` with its body changing based on
the parameter `value_count`. Doing so I have separated the value generation
logic from the whole array generation.

Do you know what is cooler? We can use `rnd.wnext` as well!

{% include customhighlight.html
caption="random_array function: using rnd.wnext for value generation"
  ext="cpp" dir=page.prepdir file="random-array-v3.fragment.cpp" %}

Using `rnd.wnext`, we can generate the stepping functions with convex and
concave shapes. We can say that this is one way to _influence vertical_
stepping. Can we do the same for _horizontal_ stepping? Yes, we can, still
with `rnd.wnext`!

{% include image.html caption="Steppings"
  alt="steppings" dir=page.assetsdir file="steppings.drawio.png" %}

{% include customhighlight.html
  caption="random_array function: using rnd.wnext to influence value
picking process"
  ext="cpp" dir=page.prepdir file="random-array-v4.fragment.cpp" %}
  
Using `rnd.wnext`, in this case, does not mean picking a higher/lower value with
a higher chance, because the `values` vector is not sorted! So we can think of
it as with a higher `picking_bias`, one or two values will more likely dominate
other values. You can think of it as plains flatter than the other plain in the
function's plotting.

There are probably more functionalities that can be added to this function, but
`random_array` now is very good at generating _interesting_ stepping functions.
Again, _interesting_ here is defined by the _plains_ and _curves_ of the
plotting, which `random_array` already can generate, even without smoothing!

#### Refactoring the function
We are going to add the smoothing. But before that, our function is now a mess!
It has a lot of parameters, and often, it is not a good idea to keep that many
in a function. And we are going to add some more functionality! Let's quickly
fix this. A way to fix this is to wrap these parameters, as well as the
generating function, inside a _class/struct_. Behold, the power of OOP!

{% include customhighlight.html
  caption="struct RandomArrayGenerator" ext="cpp"
  dir=page.prepdir file="random-array-v5.fragment.cpp" %}

Besides there is no need to pass the parameters to the `struct` all at once, we
can also write a function to build it with `opt`, thus making it reusable for
generating the array b. Not to mention it can be created once, and then used
any number of times!

#### Adding the smoothing (or noise)
One solution for this is suprisingly simple: just add a number of random numbers
to the array. Because we will sort the function afterward, these random numbers
can act like _bridges_, _smoothly_ connecting 2 plains.

{% include image.html caption="Stepping function without and with noises"
  alt="stepping-function-without-and-with-noises"
  dir=page.assetsdir file="with-noises.drawio.png"
  width="80%"
  %}

To do this, we can have an option called `noise_count`. We can generate `size -
noise_count` numbers using the above code, and then add `noise_count` random
numbers to it. Also, we should pass this option as _percentages_.


{% include customhighlight.html
  caption="struct RandomArrayGenerator: adding noises" ext="cpp"
  dir=page.prepdir file="random-array-v6.fragment.cpp" %}

#### Checking the result
{: #checking-the-result }
Here is the generator with the new way to generate the array.

{% include customhighlight.html caption="gen-v3.cpp"
  dir=page.prepdir file="gen-v3.cpp" ext="cpp" collapsed=true %}
  
The first thing to test is if an increasing array is generated as expected by making
$b$ an array with all $0$.

{% include customhighlight.html caption="gen-v3 test increasing array
generation"
  dir=page.prepdir file="out/gen-v3-test-increasing.sh.out" ext="sh" %}
  
{% include image.html caption="gen-v3 increasing arrays plots"
  alt="gen-v3-increasing-arrays-plots"
  dir=page.assetsdir file="gen-v3-test-increasing.png" %}
  
Here we can see the patterns are indeed intended: there are plains, there are
some smooth curves (but not linear). And they branch differently! I'll say this
is an OK result.

Now let's do see for an $a$ with the above parameters and $b$ with only `min-b`
and `max-b`

{% include customhighlight.html caption="gen-v3 test with linear $b$"
  dir=page.prepdir file="out/gen-v3-test-linear-b.sh.out" ext="sh" %}
  
{% include image.html caption="gen-v3 test linear $b$ plots"
  alt="gen-v3-linear-b-plots"
  dir=page.assetsdir file="gen-v3-test-linear-b.png" %}
  
This is still kinda _expectable_ since $b$ is linear, so adding it still
makes things transform _linearly_ but I not expecting that kind of shape.

Now for this test: $a$ and $b$ have the same flag. Here I don't use
`value-bias` to make both arrays have _linear_ shapes.  

{% include customhighlight.html caption="gen-v3 test both arrays"
  dir=page.prepdir file="out/gen-v3-test-both.sh.out" ext="sh" %}
  
{% include image.html caption="gen-v3 test both arrays plots"
  alt="gen-v3-test-both-arrays-plots"
  dir=page.assetsdir file="gen-v3-test-both.png" %}
  
And look at that! That is still far more _interesting_ than what `gen-v2` has
done!

Here are some more plottings!

{% include customhighlight.html caption="gen-v3 examples"
  dir=page.prepdir file="out/gen-v3-examples.sh.out" ext="sh" collapsed=true %}
  
{% include image.html caption="gen-v3 example 1 plot"
  alt="gen-v3-example-1-plot"
  dir=page.assetsdir file="gen-v3-example1.png" %}
{% include image.html caption="gen-v3 example 2 plot"
  alt="gen-v3-example-2-plot"
  dir=page.assetsdir file="gen-v3-example2.png" %}
{% include image.html caption="gen-v3 example 3 plot"
  alt="gen-v3-example-3-plot"
  dir=page.assetsdir file="gen-v3-example3.png" %}
  
And I admit it, I don't know plotting random things is this addicting!

### Making **more interesting** `NO` tests
Till this point, we only paid attention to the `YES` tests. The outputs for the
`NO` tests are still complete chaos. We want the `NO` tests should be as
_interesting_ as the `YES` tests. That is, the plotting should still contain the
curves and plains.

To understand how to make the tests, let's look at how the algorithm handles the
`NO` case. It tries to maximize elements of the decreasing array, and if there
is a negative element, the result is `NO`. With this idea, we can do the
following:
- Generate a `YES` test.
- Try to find the optimal decreasing array.
- Decrease all of the elements of the test so that the optimal decreasing array
  will contain a negative element.

We can implement this algorithm by adjusting the padding part. So the padding
value now has two ranges: a range that will generate a `NO` test, and a range
for a `YES` test. This way, we can even make an unsorted array to have the
result `YES` just by padding. Now we do the following changes:
- Add an option to sort the array. Well actually, let's add 2, one for $a$, one
  for $b$. This can even be done within `RandomArrayGenerator`.
- Determine the correct range for the `YES` tests and `NO` tests, then pick the
  correct range.
  
With these changes, we can also archive _chaotic_ `YES` tests as bi-product!

{% include customhighlight.html caption="New property `do_sort` and `-sorted`
option for RandomArrayGenerator" ext="cpp"
  dir=page.prepdir file="adjust-random-array-generator-for-no-tests.fragment.cpp"
  %}
  
And here is the adjustments for generating the array inside `main`. We must also
include our `solver` here, but we don't need to care about the number being
negative.

{% include customhighlight.html caption="Adjustment inside `main`"
  dir=page.prepdir file="adjust-main-for-no-tests.fragment.cpp" ext="cpp" %}
  
And here is the full code for our new generator. A small note that we 
don't strictly force `NO` tests as `gen-v3`.

{% include customhighlight.html caption="gen-v4.cpp"
  dir=page.prepdir file="gen-v4.cpp" ext="cpp" collapsed=true %}
  
#### Plotting _interesting_ `NO` tests

The following test is from the last example of the section [Making **more
interesting** `YES` tests. Checking the result](#checking-the-result) with small
changes. I set `padding-bias` to $0$ to see how the algorithm choose the
padding. I also add `-no-shuffle-cases` so all the `YES` tests are in the front.
And finally, remember to add `-a-sorted` and `-b-sorted`!

{% include customhighlight.html caption="gen-v4 plotting for `NO` tests"
  dir=page.prepdir file="out/gen-v4-test-for-no-tests.sh.out" ext="sh" %}

{% include image.html caption="gen-v4 plotting for `NO` tests"
  alt="gen-v4-plotting-for-no-tests"
  dir=page.assetsdir file="gen-v4-test-for-no-tests.png" %}

The `NO` tests (the last 3 tests) are indeed having the shapes that we wanted.
The only noticeable difference is in the _height_ of the elements. The `NO`
tests seem to be lower than the `YES` tests because the padding range for `NO`
is lower than the range of `YES`.

Let's now plot the test with high and low `padding-bias`.

{% include customhighlight.html caption="gen-v4 plotting for `NO` tests with
extreme `padding-bias`"
  dir=page.prepdir
  file="out/gen-v4-test-for-no-tests-extreme-padding-bias.sh.out" ext="sh"
  collapsed=true %}

{% include image.html caption="gen-v4 plotting for `NO` tests with a high
`padding-bias`"
  alt="gen-v4-for-no-tests-with-a-high-padding-bias"
  dir=page.assetsdir file="gen-v4-test-for-no-tests-high-padding-bias.png" %}
  
{% include image.html caption="gen-v4 plotting for `NO` tests with a low   
`padding-bias`"
  alt="gen-v4-for-no-tests-with-a-low-padding-bias"
  dir=page.assetsdir file="gen-v4-test-for-no-tests-low-padding-bias.png" %}
  
Yes, they are still separated by height in a same test, but a `NO` test with a
_high_ `padding-bias` is now not **distinguishable** by eyes from a `YES` test
with a _low_ `padding-bias`, which we may call **strong tests** :)).

#### Plotting _chaotic_ `YES` tests
As a bi-product of our generator, _chaotic_ `YES` tests might also be a good
candidate for **strong tests**. Let's remove the `sorted` flags and all other
flags that influence the value distribution. So we are only looking at the
linear case for now. Also because it is chaotic, let's plot for a small length
first, with a lower range of value, from $1$ to $100$ only. Also, I _purposely_
make the maximum value high (which is $30000$). Let's see what happens.

{% include customhighlight.html
  caption="gen-v4 with _chaotic_ YES tests"
  dir=page.prepdir file="out/gen-v4-test-for-chaotic-yes-tests.sh.out" ext="sh"
  %}

{% include image.html 
  dir=page.assetsdir file="gen-v4-test-for-chaotic-yes-tests.png" %}

It worked! But something is kinda off. All of the `YES` tests are _way_ above
the `NO` tests. There is no `padding-bias`, but all of the elements in the `YES`
tests are very close to the maximum value. This might be because the raw minimum
value of the decreasing array is too low. And indeed, in the following test, by
lowering the maximum value, we will have an error for the `YES` tests, but no
error at all for the `NO` tests.

{% include customhighlight.html
  caption="gen-v4 _chaotic_ YES tests failed :("
  dir=page.prepdir file="out/gen-v4-test-for-chaotic-yes-tests-error.sh.out"
  ext="sh" %}
  
We have the error message even with this range. With a wider range of variation,
the padding will be higher than this! A reasonable padding value will not come
from this chaos, but from an algorithm like our original algorithm, that is,
generate the arrays $a$ and $b$ first. Besides, the above test is not
interesting at all, since the values vary in a very small range. And this can be
done with our `gen-v2` generator! Therefore we should **remove** this _feature_.
So now in all `YES` tests, we must sort $a$ and $b$. For sorting in `NO` tests,
we should change the option`a-sorted` and `b-sorted` into `a-sorted-in-no` and
`b-sorted-in-no`.

Here is the final version of the generator after changing the flags from
`-sorted` to `-sorted-in-no`.

{% include customhighlight.html caption="gen-v4.1.cpp"
  dir=page.prepdir file="gen-v4.1.cpp" ext="cpp" collapsed=true %}

### Generate the tests
OMG! Finally, we can now generate tests. So much time was spent on making that
generator! But that is worth it because we wanted our test to be _strong,
diverse, and interesting_. But how do we generate tests with so many options in
the generator? Do we copy and paste and change them by hand? That will be very
painful though. Luckily, Polygon supports a way to generate the generating
command as well!


#### Working with FreeMarker
A test generation script is a file that contains commands (the generator name
with its flags) for generating the tests. Polygon supports [FreeMarker] as a
template engine to write the test generation more easily. A [template engine][template-engine], as
it sounds, is a tool that takes a template and data, and combines them to
produce text output. Sometimes there is no need for the data if the template
does not depend on that.

[FreeMarker] is very powerful. It can act as a programming language on its own.
This post will not go into details about FreeMarker. There is a brief manual
about [FreeMarker] right on the Tests page on Polygon, showing the usage of:
- the [assignment tag](https://freemarker.apache.org/docs/ref_directive_assign.html)
- the [list tag](https://freemarker.apache.org/docs/ref_directive_list.html)
- the [ability to do
  arithmetic](https://freemarker.apache.org/docs/dgui_template_exp.html#dgui_template_exp_arit)

Besides that, there are also:
- [sequences](https://freemarker.apache.org/docs/dgui_template_exp.html#dgui_template_exp_direct_seuqence),
  which are the same as dynamic arrays
- [hashes](https://freemarker.apache.org/docs/dgui_template_exp.html#dgui_template_exp_direct_hash),
  which are the same as dictionaries
- [branching](https://freemarker.apache.org/docs/ref_directive_if.html) (if, elseif, else)
- [functions](https://freemarker.apache.org/docs/ref_directive_function.html)
- and more...

This post won't go into details about FreeMarker, and you don't really need to
know much about FreeMarker to generate test. But knowing them is an advantage
and I highly recommend taking a look at them first.

#### Writing the script
##### Parts of a command
Before generating the tests, we should divide the flags into some groups, since
we are having **A LOT** of flags. Here is one way to group them.

1. `-test-count`, `-sum-n`, `-min-n`, and `-yes-percent`. The first three
   control the length of the array. More often we are going to left
   `-yes-percent` to be blank (its default value is 50), but for the big test,
   we must address it explicitly.
2. `-min-val`, `-max-val` and `-padding-bias`. They control the padding in
   general.
3. `-min-*`, `-max-*`, `-*-value-bias`, `-*-limited-value`, `-*-picking-bias`,
   `-*-noise-percent`, `-*-sorted-in-no`, where `*` is `a` and `b`. These
   control the $a$ and $b$ array generation.
   
After that we can decide which values for which group. For example, the first
group can be a list with the following values.

{%- capture script_length_group_sequence -%}{% raw %}
<#assign length_group = [
  "-test-count 2000 -sum-n 30000 -min-n 10 -yes-percent 0",
  "-test-count 2000 -sum-n 30000 -min-n 10 -yes-percent 25",
  "-test-count 2000 -sum-n 30000 -min-n 10",
  "-test-count 2000 -sum-n 30000 -min-n 10 -yes-percent 75",
  "-test-count 2000 -sum-n 30000 -min-n 10 -yes-percent 100",
  "-test-count 200 -sum-n 30000 -min-n 100",
  "-test-count 1 -sum-n 30000 -min-n 30000 -yes-percent 0",
  "-test-count 1 -sum-n 30000 -min-n 30000 -yes-percent 100"
] >
{% endraw %}{%- endcapture -%}

{% include customhighlight.html ext="freemarker" content=script_length_group_sequence
  caption="Declare length_group as a sequence"
%}

That is what I have done for the past problems. But more logically, it should be
declare as a _hash_, because having a name is more meaningful, and we can do
more thing with that information later :).
{%- capture script_length_group_hash -%}{% raw %}
<#assign length_group = {
  "small-length-0-yes": "-test-count 2000 -sum-n 30000 -min-n 10 -yes-percent 0",
  "small-length-25-yes": "-test-count 2000 -sum-n 30000 -min-n 10 -yes-percent 25",
  "small-length-50-yes": "-test-count 2000 -sum-n 30000 -min-n 10",
  "small-length-75-yes": "-test-count 2000 -sum-n 30000 -min-n 10 -yes-percent 75",
  "small-length-100-yes": "-test-count 2000 -sum-n 30000 -min-n 10 -yes-percent 100",
  "medium-length": "-test-count 200 -sum-n 30000 -min-n 100",
  "big-length-no": "-test-count 1 -sum-n 30000 -min-n 30000 -yes-percent 0",
  "big-length-yes": "-test-count 1 -sum-n 30000 -min-n 30000 -yes-percent 100"
} >

{% endraw %}{%- endcapture -%}
{% include customhighlight.html content=script_length_group_hash
  caption="Declare length_group as a hash"
%}

We can do the same with the second group.
{%capture script_padding_group_hash %}{% raw %}
<#assign padding_group = {
  "no-influence": "",
  "max-padding-only": "-max-val 1000000",
  "max-padding-with-high-bias": "-max-val 1000000 -padding-bias 15",
  "max-padding-with-low-bias": "-max-val 1000000 -padding-bias -15"
} >
{% endraw %}{%- endcapture -%}
{% include customhighlight.html content=script_padding_group_hash
  caption="Declare padding_group as a hash"
%}

For the third group, we have a little problem. The group should be defined for
$a$ and $b$ separately. Luckily, we can use _function_.

{%- capture script_gen_array_group_hash -%}{% raw %}
<#function gen_array_group name>
  <#assign 
    min="-min-${name}" max="-max-${name}" valueBias="-${name}-value-bias"
    limitedValue="-${name}-limited-value" pickingBias="-${name}-picking-bias"
    noisePercent="-${name}-noise-percent" sortedInNo="-${name}-sorted-in-no=1"
  >
  <#return {
    "range-10": "${min} 1 ${max} 10 ${sortedInNo}",
    "range-100": "${min} 1 ${max} 100 ${sortedInNo}",
    "range-300000": "${min} 1 ${max} 30000 ${sortedInNo}",
    "range-300000-no-sort": "${min} 1 ${max} 300000",
    "range-300000-curve-up": "${min} 1 ${max} 300000 ${valueBias} 10 ${sortedInNo}",
    "range-300000-curve-down": "${min} 1 ${max} 300000 ${valueBias} -10 ${sortedInNo}",
    "range-300000-lim-val-10": "${min} 1 ${max} 300000 ${limitedValue} 10 ${sortedInNo}",
    "range-300000-lim-val-10-curve-up": "${min} 1 ${max} 300000 ${limitedValue} 100 ${valueBias} 10 ${sortedInNo}",
    "range-300000-lim-val-10-curve-down": "${min} 1 ${max} 300000 ${limitedValue} 100 ${valueBias} -10 ${sortedInNo}",
    "range-300000-lim-val-100": "${min} 1 ${max} 300000 ${limitedValue} 100 ${noisePercent} 20 ${sortedInNo}",
    "range-300000-lim-val-100-uneven": "${min} 1 ${max} 300000 ${limitedValue} 100 ${noisePercent} 20 ${pickingBias} 10 ${sortedInNo}"
  } >
</#function>
<#assign gen_a_group = gen_array_group("a") >
<#assign gen_b_group = gen_array_group("b") >
{% endraw %}{%- endcapture -%}
{% include customhighlight.html content=script_gen_array_group_hash
  caption="Declare gen_a_group and gen_b_group as a hash"
%}

#### Putting all the parts together
This part is simple: we just loop through each group and then put every part
into one command. Or is it?
{%capture script_generation_loop %} {% raw %}
<#list length_group as length_part, length>
  <#list padding_group as padding_part, padding>
    <#list gen_a_group as gen_a_part, gen_a>
    <#list gen_b_group as gen_b_part, gen_b>
      gen-v4.1 ${length} ${padding} ${gen_a} ${gen_b} > $
    </#list>
    </#list>
  </#list>
</#list>
{% endraw %} {% endcapture %}

{% include customhighlight.html content=script_generation_loop
  caption="Tests generation loop"
%}


Let's see the number of parts in each group:
- `length-group`: 8 parts.
- `padding-group`: 4 parts.
- `gen_a_group` and `gen_b_group`: 11 parts each.

So If we connect all of them into one, we will have $8 \times 4 \times 11^2 =
3872$ tests! We don't have that much time to test with that number of tests, let
alone generate them! So before actually putting them together, we must _prune_
some tests first!

#### Test pruning by sacrificing parts
Objectively, all of the parts that I have introduced above are all
_interesting_. But sometimes they are a lot, and not all tests cases need to be
visited for a strong test set.

For the `length_group`, we don't really need that many cases for adjusting the
`YES` tests count. It is nice to have different ratios in different tests, but
that is not the point of the test. We only need to test if the solution can
distinguish the `YES` and `NO` cases. So we can just put 50 percent there. This
also means the `-yes-percent` flag has little meaning, but it is always fine to
write a general generator.

There is also a waste to separate `YES` and `NO` tests with big lengths. Let's
merge them into one, that is, let's make it 2 test cases and $50\%$ `YES` tests.
To compensate for the loss of the maximum length tests, we can add a few big
tests outside the loop.

{%- capture script_length_group_hash_pruned -%}{% raw %}
<#assign length_group = {
  "small-length": "-test-count 2000 -sum-n 30000 -min-n 10",
  "medium-length": "-test-count 200 -sum-n 30000 -min-n 100",
  "big-length": "-test-count 2 -sum-n 30000 -min-n 13000"
} >
{% endraw %}{%- endcapture -%}
{% include customhighlight.html content=script_length_group_hash_pruned
  caption="Pruned length_group" collapsed=true
%}

For `padding_group`, having max value but no bias at all has the same impact as
no influence. So we can remove `max-padding-only` part.

{%capture script_padding_group_hash_pruned %}{% raw %}
<#assign padding_group = {
  "no-influence": "",
  "max-padding-with-high-bias": "-max-val 1000000 -padding-bias 15",
  "max-padding-with-low-bias": "-max-val 1000000 -padding-bias -15"
} >
{% endraw %}{%- endcapture -%}
{% include customhighlight.html content=script_padding_group_hash_pruned
  caption="Pruned padding_group" collapsed=true
%}

For `gen_a_group` and `gen_b_group`:
- We can remove `range-100`. If we already have `range-10` and `range-1000`, then
  `range-100` has very little impact.
- We can also remove `range-300000-lim-val-100`. With the same reason: we already
  have `range-300000-lim-val-10` and `range-300000-lim-val-100-uneven`, so
  `range-300000-lim-val-100` might have less impact. 
- Let's remove `range-300000-curve-down` and `range-300000-lim-val-10-curve-up`. There
  are 2 pairs of (`-curve-up`, `-curve-down`), so I think it is fine to remove one
  side of each pair.
  
{%- capture script_gen_array_group_hash_pruned -%}{% raw %}
<#function gen_array_group name>
  <#assign 
    min="-min-${name}" max="-max-${name}" valueBias="-${name}-value-bias"
    limitedValue="-${name}-limited-value" pickingBias="-${name}-picking-bias"
    noisePercent="-${name}-noise-percent" sortedInNo="-${name}-sorted-in-no=1"
  >
  <#return {
    "range-10": "${min} 1 ${max} 10 ${sortedInNo}",
    "range-300000": "${min} 1 ${max} 300000 ${sortedInNo}",
    "range-300000-no-sort": "${min} 1 ${max} 300000",
    "range-300000-curve-up": "${min} 1 ${max} 300000 ${valueBias} 10 ${sortedInNo}",
    "range-300000-lim-val-10": "${min} 1 ${max} 300000 ${limitedValue} 10 ${sortedInNo}",
    "range-300000-lim-val-10-curve-down": "${min} 1 ${max} 300000 ${limitedValue} 100 ${valueBias} -10 ${sortedInNo}",
    "range-300000-lim-val-100-uneven": "${min} 1 ${max} 300000 ${limitedValue} 100 ${noisePercent} 20 ${pickingBias} 10 ${sortedInNo}"
  } >
</#function>
<#assign gen_a_group = gen_array_group("a") >
<#assign gen_b_group = gen_array_group("b") >
{% endraw %}{%- endcapture -%}
{% include customhighlight.html content=script_gen_array_group_hash_pruned
  caption="Pruned gen_a_group and gen_b_group" collapsed=true
%}

The number of tests has been reduced to around $3 \times 3 \times 7^2 = 441$,
which is still a lot.

#### Test pruning by condition
There are also combinations that have a small impact:
- For small and medium-size tests, let's just test them with random values (no
  bias or limited value), since the distribution still looks random with such
  sizes.
- Let's make the pairs or parts made from `gen_a_group` and `gen_b_group` unordered.
  For example, the pairs (`range-10`, `range-300000-no-sort`) and
  (`range-300000-no-sort`, `range-10`) can be considered the same! That is because,
  for a part pair, we can reverse the array to get the reverse part.
  
Here is the full generation script.
{% capture script_full %}{% raw %}
<#assign length_group = {
  "small-length": "-test-count 2000 -sum-n 30000 -min-n 10",
  "medium-length": "-test-count 200 -sum-n 30000 -min-n 100",
  "big-length": "-test-count 2 -sum-n 30000 -min-n 13000"
} >
<#assign padding_group = {
  "no-influence": "",
  "max-padding-with-high-bias": "-max-val 1000000 -padding-bias 15",
  "max-padding-with-low-bias": "-max-val 1000000 -padding-bias -15"
} >
<#function gen_array_group name>
  <#assign 
    min="-min-${name}" max="-max-${name}" valueBias="-${name}-value-bias"
    limitedValue="-${name}-limited-value" pickingBias="-${name}-picking-bias"
    noisePercent="-${name}-noise-percent" sortedInNo="-${name}-sorted-in-no=1"
  >
  <#return {
    "range-10": "${min} 1 ${max} 10 ${sortedInNo}",
    "range-300000": "${min} 1 ${max} 300000 ${sortedInNo}",
    "range-300000-no-sort": "${min} 1 ${max} 300000",
    "range-300000-curve-up": "${min} 1 ${max} 300000 ${valueBias} 10 ${sortedInNo}",
    "range-300000-lim-val-10": "${min} 1 ${max} 300000 ${limitedValue} 10 ${sortedInNo}",
    "range-300000-lim-val-10-curve-down": "${min} 1 ${max} 300000 ${limitedValue} 100 ${valueBias} -10 ${sortedInNo}",
    "range-300000-lim-val-100-uneven": "${min} 1 ${max} 300000 ${limitedValue} 100 ${noisePercent} 20 ${pickingBias} 10 ${sortedInNo}"
  } >
</#function>
<#assign gen_a_group = gen_array_group("a") >
<#assign gen_b_group = gen_array_group("b") >
<#list length_group as length_part, length>
  <#list padding_group as padding_part, padding>
    <#assign used_a_part = {} >
    <#list gen_a_group as gen_a_part, gen_a>
      <#assign used_a_part = used_a_part + {gen_a_part: true} >
      <#list gen_b_group as gen_b_part, gen_b>
        <#if !(used_a_part[gen_b_part]??) >
          <#continue>
        </#if>
        <#if length_part == "small-length" || length_part == "medium-length">
          <#if padding_part != "no-influence">
            <#continue>
          </#if>
          <#if gen_a_part != "range-10" && gen_a_part != "range-300000">
            <#continue>
          </#if>
          <#if gen_b_part != "range-10" && gen_b_part != "range-300000">
            <#continue>
          </#if>
        </#if>
        gen-v4.1 ${length} ${padding} ${gen_a} ${gen_b} > $
      </#list>
    </#list>
  </#list>
</#list>
<#-- 2 tests with n = 30000 -->
gen-v4.1 -test-count 1 -sum-n 30000 -min-n 30000 -yes-percent 100 ${padding_group["max-padding-with-low-bias"]} ${gen_a_group["range-300000-lim-val-10"]} ${gen_b_group["range-300000-lim-val-100-uneven"]} > $
gen-v4.1 -test-count 1 -sum-n 30000 -min-n 30000 -yes-percent 0 ${padding_group["max-padding-with-high-bias"]} ${gen_a_group["range-300000-no-sort"]} ${gen_b_group["range-300000-curve-up"]} > $
{% endraw %}{% endcapture %}

{% include customhighlight.html content=script_full
  caption="The full script" collapsed=true
%}

The script produced $92$ tests, which is _more or less acceptable_ for a problem
D in a Div2 Codeforces contest.

### Multitest compression. Making complex tests.
Again, $92$ is _more or less acceptable_. But looking at the number of tests of
this problem on Codeforces, there is only $10$! How can they generate so few
tests? Maybe the question should be _how did we end up with so many tests?_ Well
it is because of the way we are generating the test. All the cases, even though
really diverse, they still use a same set of options flag. In other words, we
still don't use the multitest **effectively**.

But how should we design a generator to handle such complexity? Imagine we are
generating 10 test cases in one test, each of them should be generated with a
different set of options. The function `opts` in `testlib.h` for now does not
accept very complex options, and if we wanted to specify more complex options,
we need _parse_ the argument, which should the library's job, not our!

This is a problem that I think lots of author has met. The solution is either
writing a more specific generator, or tests concatination. But we are
programmers, should _code reuse_ be one of one of aim. I have given some
thoughts for this, and I have come up with two solutions.

#### Multitest compression the _ugly_ way
We already have a generator, and it is built by extending the previous generator.
Writing a specific generator required us to decompose it, which is the opposite
of extension. This section aims to provide a way to actually reuse the generator
without decomposing it, but with some hacks.

The main idea is to use the power of programming -- we can _simulate_ the command
calling process. Normally this is possible by creating a new process and call
the program with the set of flags. But that way is not possible on Polygon,
therefore we must _simulate_ it.

First we need to somehow call the generator. Well its body is a function named
`main`, we can rename it to something else and then call it in our main. So that
will be something like this:

{%include customhighlight.html
caption="Multitest compression hack: rename the main function with macro"
ext="cpp"
content='
#define main generator
#include "./gen-v4.1.cpp"
#undef main
' %}

This will works, but for example, there might be other function called
`generator` inside `./gen-v4.1.cpp`, or there might also be a function with the
name `generator` outside `./gen-v4.1.cpp` that we might want to use. So instead,
we can wrap it inside a namespace. But before that we must include **all of the
header** used in `./gen-4.1.cpp`.

{% include customhighlight.html
caption="Multitest compression hack: wrap generator inside a namespace"
ext="cpp"
content='
// must include these 2 headers first
#include "testlib.h"
#include <bits/stdc++.h>
namespace GenV41 {
#include "gen-v4.1.cpp"
}
' %}

With this we are successfully encapsulate all of the local variable, function
inside `GenV41` namespace. Now we can call the generator with
`GenV41::main(...)`. The only down side is, again, that we need to include the headers
**before** including `gen-v4.1.cpp`, but in this case is totally fine since
mostly we only use these two headers.

It worths noting that on Polygon, you **can not** include _source files_
(including your validators and generators), but only _resource files_ (which
lies `testlib.h`). So you should add `gen-v4.1.cpp` to _resource files_, and
maybe change its name to `gen-v4.1.inc` (for include). (and maybe inside
`gen-v4.1.cpp` now only `#include "gen-v4.1.inc"` is needed :))

{% include image.html caption="Polygon File section: resource files and source
files"
alt="polygon-file-section-resource-files-and-source-files"
dir=page.assetsdir file="polygon-files.png" %}

That's the calling function done, but how do we pass the argument more easily.
Well we can always write a function for it.

{% include customhighlight.html caption="`call_main` function"
  dir=page.prepdir file="call-main.fragment.cpp" ext="cpp" %}

This function will split a string into parts and getting the arguments that a
`main` function of a program need. Neat, isn't it?

There are two more parts that need to be done. First thing is to correctly pass the
arguments and register them with `testlib.h`. And second thing is to capture the
output. For the first thing, we need to take a look at the `testlib.h` source
code and see how things are handles.
[Here](https://github.com/MikeMirzayanov/testlib/blob/f28d52804011c5dca2e62fbe7cff45888579b0e8/testlib.h#L4038) is the link the the function
`registerGen()`. The full function at the time of writing this blog is the
following:

{%include customhighlight.html caption="`registerGen()` function"
ext="cpp" collapsed=true
content='
void registerGen(int argc, char * argv[], int randomGeneratorVersion) {
    if (randomGeneratorVersion < 0 || randomGeneratorVersion > 1)
        quitf(_fail, "Random generator version is expected to be 0 or 1.");
    random_t::version = randomGeneratorVersion;

    __testlib_ensuresPreconditions();

    testlibMode = _generator;
    __testlib_set_binary(stdin);
    rnd.setSeed(argc, argv);

#if __cplusplus > 199711L || defined(_MSC_VER)
    prepareOpts(argc, argv);
#endif
}
' %}

We can see that this function does a few stuffs, but there is another function
that handles the preparation for `opts` separately. Let's take a look at that
function too (the link to it is
[here](https://github.com/MikeMirzayanov/testlib/blob/f28d52804011c5dca2e62fbe7cff45888579b0e8/testlib.h#L4810))

{%include customhighlight.html caption="`prepareOpts()` function"
ext="cpp" collapsed=true
content='
void prepareOpts(int argc, char * argv[]) {
    if (argc <= 0)
        __testlib_fail("Opts: expected argc>=0 but found " + toString(argc));
    size_t n = static_cast<size_t>(argc); // NOLINT(hicpp-use-auto,modernize-use-auto)
    __testlib_opts = std::map<std::string, std::string>();
    for (size_t index = 1; index < n; index += parseOpt(n, argv, index, __testlib_opts));
    __testlib_argv = std::vector<std::string>(n);
    for (size_t index = 0; index < n; index++)
        __testlib_argv[index] = argv[index];
}
' %}

Here it first reset all of the options first, and then parsing the new options.
So this is the function that we need to use instead of `registerGen()`. And we
can either change the calling `registerGen()` into `prepareOpts`, or use the
power of the macro again.

{% include customhighlight.html
caption="Multitest compression hack: redefine registerGen() for GenV41"
ext="cpp"
content='
// must include these 2 headers first
#include "testlib.h"
#include <bits/stdc++.h>
#define registerGen(argc, argv, rndVer) prepareOpts(argc, argv)
namespace GenV41 {
#include "gen-v4.1.inc"
}
#undef registerGen
' %}

Now to get the output from out generator. One solution is to use `freopen` to
write the output onto another file, and then read it back. But that is not
convenient for us. So instead we should somehow need to write the output
somewhere else. After a bit of googling, I find out [this
solution](https://stackoverflow.com/a/6211644) that write the output of `stdout`
onto another `ostringstream`. Let's change the `call_main` function to return
the output of the generator as a stream.

{% include customhighlight.html caption="`call_main`: returns output from the
generator"
  dir=page.prepdir file="call-main-return-output.fragment.cpp" ext="cpp" %}
  
That's all the part of the hack. Let's try it out by writing a stronger
_pretest_. This pretest will contains all possible cases for very small
constraints, and the rest will be randomly generated. The very small constraints
here will be all arrays with length not exceeding $4$ and the values not
exceeding $5$.

{% include customhighlight.html caption="gen-pretest.cpp"
  dir=page.prepdir file="gen-pretest.cpp" ext="cpp" collapsed=true %}

#### Multitest compression the _programmer_ way
In the previous section, we discussed the case where we don't want to touch the
source code of the existing generators. But the case of `gen-v4.1.cpp`, our
generator is very easy to refactor. We only need it to return the `cases` array
instead of printing out. But we still need to somehow process the options
passed to the generator. For that we can adjust the function `call_main` a bit,
and then call it inside the generator.

{% include customhighlight.html caption="`prepare_opts_from_string`. From the
function `call_main`"
  dir=page.prepdir file="prepare-opts-from-string.fragment.cpp" ext="cpp" collapsed=true %}
  
And here are the adjusted `gen-v4.1.cpp` generator and `gen-pretest` generator.

{% include customhighlight.html caption="gen-v4.1-func.inc"
  dir=page.prepdir file="gen-v4.1-func.inc" ext="cpp" collapsed=true %}
  
{% include customhighlight.html caption="gen-pretest-with-func.cpp"
  dir=page.prepdir file="gen-pretest-with-func.cpp" ext="cpp" collapsed=true %}
  
These code is still not clean though. Here is something that we might do:
- Wrap `gen-v4.1` in a namespace again. Or even inside a `struct/class`.
- We should not rely on `opt`. This can be avoid using the [builder
  pattern][builder-pattern] in OOP.
- We should put `parepare_opts_with_string` into a new header file, and then
  include it in `gen-v4.1-func.inc`.

But these will be way _TOO_ much for generating tests. To be able to do these
things, the problem author must do it _from the start_, and not this late. But
this is only one solution, and Polygon is really flexible, so there might be
other solution to this problem as well.

In theory, if there are $30$ test cases in a test, each with length $1000$, it
is good enough to use the combination of the option for these lengths. If so,
then we can reduce the test count from about $92 / 30 \approx 3$ tests!
With multitest compression, even if we don't prune the test with condition, we
can still generate $441 / 30 \approx 15$, which is very good compared to the
official test set!

But I won't do that in this post. This post is now _WAY TOO LONG_, and the tests
are ready to use. There is no need to change that.

Two above generators are added to our test set. 

## But are the tests actually _strong_?
The array shape generated are cool and all, but that does not prove anything.
Let's test it against some solutions! I will pick the most $5$ earliest `AC` solutions and $5$
earliest `WA` solution. I won't link the solution here because that is wrong,
and you can always look it up on Codeforces. The name of the solution's author
will be in the solution name, so the solution can be found easier.

Here is the result.

{% include image.html caption="Testing result"
  alt="testing-result" dir=page.assetsdir file="testing-result.png" %}
  
This is the bottom of the invocation table, where it shows the verdicts of all
solutions over all tests. Here the highest number of tests that `WA` solution
passes is $49$, about $50\%$ of the tests.

With this result I think we can safely conclude that the tests are _strong_.

## Conclusion
I did not expect that the final post is this _long_. Seriously, it was **WAY TOO
LONG**. And I even planned to add a few more content, but I end up not putting
them in. 

Some may argue that my tests are still not strong enough. But the points of this
post is not really about generating strong tests, but rather explaining the
patterns used when generating tests for a problem. Strong or not, that depends
on your limitation. This is meant to provide you with the tool to do so, and I
hope that I have delivered that to you.


[Polygon]: https://polygon.codeforces.com/
[CF1442-editorial]: https://codeforces.com/blog/entry/84298
[generator-with-testlib]: https://codeforces.com/blog/entry/18291
[testlib-opts]: https://codeforces.com/blog/entry/72702
[testlib.h]: https://github.com/MikeMirzayanov/testlib/blob/master/testlib.h
[FreeMarker]: https://freemarker.apache.org/
[template-engine]: https://en.wikipedia.org/wiki/Template_processor
[builder-pattern]: https://refactoring.guru/design-patterns/builder

{% comment %}
vim: wrap
{% endcomment %}
