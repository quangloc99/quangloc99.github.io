---
layout: post
title: "A guide to test-generation with Polygon and Testlib"
date: 2022-02-19 00:00:00 +0300
tags: [en, polygon, codeforces, testlib, cp]
prepdir: embed-contents/2022-02-19-a-guide-to-test-generation-with-polygon-and-testlib
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

## Validator

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

Wrting validation tests is also important in order to ensure its correctness. How
do I write validation tests? For each of the `read` statements, as well as
`ensuref` statements, I add two tests for them -- one with a value lower than
the lower bound, and one with a value higher than the upper bound.

Below are the my validation tests.
- The first two are for testing the value of
`test-count`.
- The next two are for testing the value of `n`.
- And the following two are for the value of `a`.
- The next test is to test a very small test.
- The next test is for testing the `ensuref` statement, that is, ensuring if the
  sum of `n` does not exceed $30000$.
- And finally I add another small random test.

Remember that on Polygon, there is an option for separting tests using `===` (3
equal signs). And also note about the must be an empty last line.

{% include customhighlight.html dir=page.prepdir file="validation-test.txt"
  caption="9 validation tests"
%}

{% include customhighlight.html dir=page.prepdir
  file="validation-test-verdicts.txt"
  caption="Verdicts for validation tests"
%}

