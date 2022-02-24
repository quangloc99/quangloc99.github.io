---
layout: post
title: "A guide to test-generation with Polygon and Testlib"
date: 2021-10-01 11:44:00 +0300
tags: [en, polygon, codeforces, testlib, cp]
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
##### Input
```
4
3
1 2 1
5
11 7 9 6 8
5
1 3 1 3 1
4
5 2 1 10
```
##### Output
```
YES
YES
NO
YES
```
