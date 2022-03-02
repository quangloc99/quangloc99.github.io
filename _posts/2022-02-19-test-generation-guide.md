---
layout: post
title: "A guide to test-generation with Polygon and Testlib"
date: 2022-02-19 00:00:00 +0300
tags: [en, polygon, codeforces, testlib, cp]
prepdir: embed-contents/2022-02-19-test-generation-guide
assetsdir: /assets/2022-02-19-test-generation-guide
wrapCode: true
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
  dir=page.prepdir file="out/gen-totally-random-example.sh.out"
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
  because some `YES` tests after decrement will become `NO.
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
  dir=page.prepdir file="gen-v2.cpp" ext="cpp"
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


[CF1442-editorial]: https://codeforces.com/blog/entry/84298
[generator-with-testlib]: https://codeforces.com/blog/entry/18291
[testlib-opts]: https://codeforces.com/blog/entry/72702
[testlib.h]: https://github.com/MikeMirzayanov/testlib/blob/master/testlib.h
