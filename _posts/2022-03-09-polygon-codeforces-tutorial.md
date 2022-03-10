---
layout: custompost
title: "Polygon.Codeforces Tutorial - A Guide to Problem Preparation [Part 1]"
date: 2022-03-09 00:00:00 +0300
tags: [en, polygon, codeforces, testlib, cp]
prepdir: _embed-contents/2022-02-19-test-generation-guide
assetsdir: /assets/2022-02-19-test-generation-guide
wrapCode: true
useMathjax: true
useToc: true
image_dir: /assets/2022-03-09-polygon-codeforces-tutorial
---

This is the first part of my series on problem preparation for a programming
contest. In this part, we are going to familiarize ourselves with [Polygon] -- a
modern platform for this purpose in a _professional_ way! There are already a
few posts on this topic, but for the completeness of the series, it would be
nice to include this part.

## Why Polygon?
To prepare a problem, we must _at least_ prepare the followings:
- The problem statement.
- The tests. For this, we must also prepare:
  + A solution.
  + A test generator.
- A checker, if the answer is not unique.

Obviously, a platform is not a requirement to prepare a problem. A problem
statement can just be in plain text format. A solution, a generator and a
checker are also just programs, which can be written with any tools. But there
are a lot of problems during the preparation. Here are some examples:
- How do we know of a test is **valid**? That is, how to know if a test
  satisfies the constraints given in the problem statement? This is hard since a
  test will be _way too big_ for a human to inspect by eye.
- How can we guarantee that the solution is **correct**? How do we test the
  solution if there is no tests beforehand?
- How do we **manage** the tests? How do we add or remove a test? What if the
  generating algorithm changed?

Polygon is a solution to these problems. It aids the problem's author during the
problem preparation process with automation. Of course, using Polygon requires
some additional efforts. So in this post, I hope to overcome the learning
process.

## The problem
To demonstrate the usage of Polygon, we need to prepare a problem ourselves. The
problem that we are going to take a look is [Codeforces 1442A - Extreme
Subtraction](https://codeforces.com/problemset/problem/1442/A).
The problem statement is quite short, but let's repeat it once more time here.

We are given an array $a$ of length $n$. We can use the following operation as
many times as we want: select any integer $k$ ($1 \le k \le n$) and either:
- decrease $a_1, a_2, \ldots, a_k$ (the first $k$ elements) by $1$.,
- decrease $a_n, a_{n - 1}, \ldots, a_{n - k + 1}$ (the last $k$ elements) by
  $1$.

We must answer, for a given array $a$, if it is possible to make all the
elements of the array equal to zero by applying a certain number of operations.

And because this blog is about test generation, we also need to take a look at
the IO format, as well as the constraints.

**Input**

The first line contains one positive integer $t$ ($1 \le t \le 30000$) -- the
number of test cases. Each of the test cases is described as follows.

The first line of the test case contains one integer $n$ ($1 \le n \le 30000$)
-- the number of elements in the array.

The second line of the test case contains $n$ integers $a_1, a_2, \ldots, a_n$
($1 \le a_i \le 10^6$).

The sum of $n$ over all test cases does not exceed $30000$.

**Output**

For each test case, print `YES` if it is possible to make all elements of the
array equal to zero by applying a certain number of operations, and `NO`
otherwise.

**Example**

{%include customhighlight.html caption="Input"  collapsed=true
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

{% include customhighlight.html caption="Output" collapsed=true
content="
YES
YES
NO
YES
" %}

### Why this problem?
The problem is very simple. Its difficulty is average, therefore it is not too
hard to follow. The input is also one of the classic kinds of input: an array.
Array generation is simple, but in some cases, is not easy. In part 2 and 3 we
are going to take a deeper look at it, also **with this problem**.

## Let's create a problem
When entering Polygon, we are greeted with a simple page like this.

{% include image.html caption="Polygon home page" alt="polygon-home-page"
  file="polygon-home-page.png"
%}

On the head bar, there are several options. Polygon allows us to manage
individual problems, as well as group them into one contest. For now, our focus
is on creating a problem, so let's click the `New problem` option.

A new page appeared and ask us to enter the problem name. Let's go with
`extreme-subtraction-clone`. After entering the name, we are directed to the
page with a list of problems. These problems are _shared_ with us, meaning we
own the problem, or the problem's owner grants us the access to it. That's why
there are already some problems like `example-a-plus-b` in that page. In the row
having our problem, under the column `Working Copy` we click `Start` to start
working with it.

{% include image.html caption="Polygon problems page"
  alt="polygon-problems-page"
  file="polygon-problems-page.png" %}

## Problem general info page

{% include image.html caption="Problem general info page"
  alt="problem-general-info-page"
  file="polygon-problem-general-info-page.png" %}

> “A user interface is like a joke. If you have to explain it, it’s not that
> good”. — Martin Leblanc

The above is the General Info page of our problem. I'm not saying that the page
is _bad_. In fact, the page is very _detailed_, so _detailed_ that it was a bit
_shock_ for me when I first created a problem. I think the page is good, but it
is not a beginner-friendly page. There are a lot of information to
digest, so I think it worth _explaining_ a few things first.

### How Polygon manages things
#### Folder structure
If you were trying to prepare problem locally, what would you do? You could
write the statement and store it into a file. You could write solutions and they
will also be files. When there are lots of files, you can divide the files into
sub folders: a folder for statement(s), a folder for the solutions, a folder for
the test generators,... 

Polygon also works with folder structure. Everything on Polygon has its own
_predefined structure_. That is, the statement, the solutions, the
generators,... that you put on Polygon will go to its respective folder. One
advantage of Polygon is that The author only need to work with the user
interface, and Polygon will take care the rest. For most of the time, this
structure is not _visible_ for us, and we don't need to. But there are a way to
do see it, and we go through it later.

#### Version control
Working with code, we often wanted to keep track the changes. Imagine when you
add a _feature_, but it turns out to be _buggy_, then what you want is to revert
back to the previous _version_ of your code. Broadly speaking, this process is
called _version control_. One way to do version control is to copy your entire
folder into a new one and making changes there, but that is not very efficient.
This problem can be solve more efficiently with a _version control system_ like
[git], which is the most popular one for programming. 

For Polygon, you don't need to know git. Polygon is also a version control
system, but with simpler functionality. It can keep track the changes, _mark
the version_, and revert back to one previous _marked_ version.

### Your first commit
Now we can go back to the General Info page to see one detail there. Here is we
wanted to see.

{% include image.html caption="The commit pane" alt="the-commit-pane"
  file="polygon-commit-pane.png" width="8cm" %}

This is the last pane of the right column. Every lines in this pane starts with
`ADDED`, and that means all the files and folders shown in this pane are newly
added, which make sense since we just create a problem. 

If you clicked `DIFF`, a page will appear, showing which file has the changes,
and in which lines, compared to the previous version. Again, this is a new
problem, so all the files here are newly added.

The option `Update Working Copy` is for team-working. Suppose that if you are in
a version behind the newest version, made by your colleague, you can click that.
After that, your version will be updated to be the latest version. All of your
uncommited changes will be merge by Polygon. If there is _conflict_ (when your
changes might not be the same as your colleague), Polygon will ask you to merge
them by yourself, for each conflicted file. For now we should not care about
this option much because we are not working in team.

Now, let's click `Commit Changes`. By doing _a commit_, we mark the our first
version of the problem. After that we are presented with a page, asking us to
enter a message for a commit. This is also _a feature_ of a typical version
control system. A version is a record of the development history, and can also
be treated as a _diary_. A commit message should explain what has been changed
during a version, so the message should be _meaningful_. Even though on Polygon,
you can leave it blank, but it is a good practice to always write a message.

There were not much going on during this first commit. So one _popular_ commit
is `Initial commit`.

{% include image.html caption="Commit page" alt="commit-page"
  file="polygon-commit-page.png" width="90%"%}
  
There is also a check box for _not_ sending an email notification. If leaved
unchecked, an email with full `DIFF` will be sent to you email. This might be
useful when for team-working (yes, another advantage of Polygon), but for one
person, I usually mark it. Be aware that this mail can also be in the _spam_
section.

After making the commit, the _changes_ are gone, because there is no changes in
_the current_ compared to the previous yet.

### Why making a commit now?
As you can see, we have not done anything with this problem. It is fine to add
something first, like the statement, and then do a commit. But I have saw people
using Polygon making a commit after **a lot** of changes. That is not _a good
practice_. It is better to make small commits, with meaningful messages. That
way, the versions are easier to maintain.

### The other user interface parts
There are two more significant UI parts that we should care about: the head bar
and the first pane of the right column.

{% include image.html caption="The head bar" alt="the-head-bar"
  file="polygon-problem-head-bar.png" %}
  
{% include image.html caption="The first pane" alt="the-first-pane"
  file="polygon-problem-main-pane.png" width="8cm" %}

These two UI parts share some options. For example, the option `Statement` in
the head bar also lead to the same page as clicking the word `None` near the
option `Statements` of the pane. The difference is that, the top bar will contains
the link to all of the pages of a problem, while the pane shows only some link.
But the pane shows more information about the problem, like the number of
tests and the number of solutions. There is nothing now so everywhere are `None`
or `0`.

To see them in details, let's move on the following part.


[Polygon]: https://polygon.codeforces.com/
[git]: https://git-scm.com/

{% comment %}
vim: spell
{% endcomment %}
