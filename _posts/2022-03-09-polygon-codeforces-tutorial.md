---
layout: custompost
title: "Polygon.Codeforces Tutorial - A Guide to Problem Preparation [Part 1]"
date: 2022-03-09 00:00:00 +0300
tags: [en, polygon, codeforces, testlib, cp]
prepdir: _embed-contents/2022-02-19-test-generation-guide
old_image_dir: /assets/2022-02-19-test-generation-guide
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
Working with code, we often want to keep track the changes. Imagine when you add
a _feature_, but it turns out to be _buggy_, then what you want is to revert
back to the previous _version_ of your code. Broadly speaking, this process is
called [_version control_][Version control]. One way to do version control is to
copy your entire folder into a new one and making changes there, but that is not
very efficient. This problem can be solve more efficiently with a _version
control system_ like [git], which is the most popular one for programming. 

For Polygon, you don't need to know git. Polygon is also a version control
system, but with simpler functionality. It can keep track the changes, _mark
the version_, and revert back to one previous _marked_ version.

### Our first commit
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

## Adding the problem statement
Before adding the problem statement, notice that in the General Info page, there
are also input boxes for the input/output files, the time and memory limits. In
the original problem, the time limit is $2s$, and the rest are the same, so we
should now change the time to $2000ms$. **Remember to press `Save`**.

{% include image.html caption="Input boxes for IO files, time and memory limit"
alt="input-boxes-for-io-files-time-and-memory-limit"
file="polygon-problem-general-info-limits.png" width="16cm" %}


### The statement page

By clicking the `Statement` option in the head bar, a page asking us to choose
the language for statement will appear. We can choose English and put the
original problem statement. Polygon asks us to choose the language because it
can manage the problem statements in various languages, making it suitable for
prepare problems for competition at international scale.

After choosing the language, the following page appears.

{% include image.html caption="Problem statement page" 
alt="problem-statement-page" file="polygon-problem-statement-page.png" %}

First of all, if you look at the last pane of the right column again, there are
new files added by Polygon. The content of these newly added files can be edited
in this page.

In the center, there are several boxes for creating parts of the statement. The
parts are clear, so I think no explanation is needed for each of them. But they
are divided by parts instead of only one big text for easier management. For
example, Polygon supports both web format and PDF format for problem statement.
By dividing the statement into parts, Polygon can put the parts into the
corresponding position in the position for each format.

If you wanted to add images to your problem, you can add the image at the bottom
of this page, and then include it in your statement.

There are also some options at the top. `Edit with preview` will split your
screen by two, showing your texts on one side, and the beautiful, formatted
statement on the other side. With split view, it is easier to see what you are
typing and what it will look like. The `Review` option is for reviewing the some
_parts_ of _the problem_ in one screen, namely the statement, the validator and
the checker. More on that later. The `Delete Current` is for deleting this
statement, and `Create New` is for creating new statement in another language.

### $\TeX$
To write the statement, Polygon supports [$\TeX$][tex] but with minimal set of
commands. $\TeX$ has some options for formatting, as well as its _math mode_ for
writing formula, therefore $\TeX$ is suitable for writing statement. Another
reason for supporting $\TeX$ is for generating PDF version of the statement. 

If you don't know $\TeX$, Polygon also includes a small manual right in that
page, so do check it out. The syntax of $\TeX$ is also simple: it is plain text,
but if you need some special formatting, you can use $\TeX$ command with the
syntax `\commandName{Texts}`.

Beside the minimal set of commands, Polygon supports extensive math mode using
[MathJax]. For writing a formula inside a paragraph, use the `$formula$` (inline
style) syntax, and for writing a formula in an individual paragraph, use the
`$$formula$$` (display style) syntax. For example writing `$\sum \frac{1}{n}$`
will result the formula $\sum \frac{1}{n}$ inside this paragraph, while `$$\sum
\frac{1}{n}$$` will result

{% comment %}
Using div here because kramdown putting everything inside a <p> tag
{% endcomment %}
<div>
$$\sum\frac{1}{n}$$
</div>

There are a lot of commands, but again, you don't need to know $\TeX$ to learn
them. You can see a list of commands in [this wiki page][latex-mathematics].

### Writing the statement

First, the name of the problem can be `Extreme Subtraction Clone`, because we
are cloning that problem.

The followings are part of the legend, the input format and the output format:

{% include customhighlight.html caption="Legend" ext="tex" collapsed=true
  content="
You are given an array $a$ of $n$ positive integers. You can use the following operation as many times as you like: select any integer $1 \le k \le n$ and do one of two things:
\begin{itemize}
\item decrement by one $k$ of the first elements of the array.
\item decrement by one $k$ of the last elements of the array. 
\end{itemize}

For example, if $n=5$ and $a=[3,2,2,1,4]$, then you can apply one of the following operations to it (not all possible options are listed below):

\begin{itemize}
\item decrement from the first two elements of the array. After this operation $a=[2,1,2,1,4]$;
\item decrement from the last three elements of the array. After this operation $a=[3,2,1,0,3]$;
\item decrement from the first five elements of the array. After this operation $a=[2,1,1,0,3]$; 
\end{itemize}

Determine if it is possible to make all the elements of the array equal to zero by applying a certain number of operations.
" %}

{% include customhighlight.html caption="Input" ext="tex" collapsed=true 
content="
The first line contains one positive integer $t$ ($1 \le t \le 30000$) --- the number of test cases. Then $t$ test cases follow.

Each test case begins with a line containing one integer $n$ ($1 \le n \le 30000$) --- the number of elements in the array.

The second line of each test case contains $n$ integers $a_1, a_2, \ldots, a_n$ ($ \le ≤a_i \le 10^6$).

The sum of $n$ over all test cases does not exceed $30000$.
"
%}

{% include customhighlight.html caption="Output" ext="tex" collapsed=true
content="
For each test case, output on a separate line:
\begin{itemize}
\item \t{YES}, if it is possible to make all elements of the array equal to zero by applying a certain number of operations.
\item \t{NO}, otherwise. 
\end{itemize}

The letters in the words \t{YES} and \t{NO} can be outputed in any case.
" %}

There is no example explanation in the original statement, but let's try to
write one:

{% include customhighlight.html caption="Notes" ext="tex" collapsed=true
content="
In the first case, the given array $a$ is $[1, 2, 1]$. We can do the following operations:
\begin{enumerate}
\item decrement from the \bf{first} two elements of the array. After this operation $a = [0, 1, 1]$.
\item decrement from the \bf{last} two elements of the array. After this operation $a = [0, 0, 0]$.
\end{enumerate}
Therefore, the answer is \t{YES}.
" %}

This test case is simple. For more complicated cases, I recommend using _table_
or _images_. So now let's add this case to the example: $[3, 2, 1, 2]$. Here is
what the explanation for this case might look like using table:

{% include customhighlight.html caption="Notes for new cases" ext="tex" collapsed=true
content="
In the last case, the array $a$ is $[3, 2, 1, 2]$. The following table demonstrate the order of operations.

\begin{center}
\begin{tabular}{|c|c|c|}
\hline
Step & Decremented elements & The array $a$ after \\ \hline
Before first step & & $[3, 2, 1, 2]$ \\ \hline
1 & \bf{first} 4 & $[2, 1, 0, 1]$ \\ \hline
2 & \bf{first} 1 & $[1, 1, 0, 1]$ \\ \hline
3 & \bf{last} 1 & $[1, 1, 0, 0]$ \\ \hline
4 & \bf{first} 2 & $[0, 0, 0, 0]$ \\ \hline
\end{tabular}
\end{center}
" %}

{% include image.html caption="Problem statement edit with preview"
alt="problem-statement-edit-with-preview"
file="polygon-problem-statement-edit-with-preview.png"
%}

You can see that there is no Example tests here. That is because the Example
tests must also be added in the `Tests` section, not this section. That way, it
will be ensure its correctness, because when you change the input, Polygon will
validate it again, and generate a new output for it. More on that part later.

After typing the statement, go back to the statement page by clicking the `x`
icon at the top right, and **remember to click `Save`**.

I'm not adding the `Tutorial` here, because it is not the main focus. But you
can do it by yourself as a little exercise. Polygon also supports making
tutorial in web format and PDF format, as well as in various languages.

### Our second commit
I think it is not redundant to remind about the importance of the commit. Here
we have added the problem statement, which is a complete work. Making a commit
now is a reasonable action. The commit message for this version can be something
like `Add problem statement`.


## Test validation
Test validation is always an important step in contest preparation. A test
generator could still be buggy, and might generate invalid tests. So test
validation is a way to prevent this kind of mistake, and potentially (but not
necessary) help us finding the bug in the generator.

But each problem has its own input format and constraints, and therefore there
is no universal way to validate a tests. So to validate a test, the author must
write a program called _validator_ for his problem. This is a program that takes
an input file and checks the validity of the test for a specific problem. On
Polygon, you can write a generator in any tool you like, but it is **strictly**
recommended to use [`testlib.h`][testlib.h] to write validators. `testlib.h` not
only eases the writing validator process, but also it make the validation
message more readable.

**Notes.** I put this part before the test generation part, because
a validator is _generally easy to write_, while the test generation is the
hardest part.

### The validator page
When you click the `Validator` option on the top bar, here is validator page
will look like.

{% include image.html caption="Validator page" alt="validator-page" 
file="polygon-validator-page.png"
%}

We can see that the Polygon's developers are nice enough to put on some example
for us to see, as well as a little guide. I also recommend to read that guide
before writing the validator. [Here](https://codeforces.com/blog/entry/18426) is
the link to the guide. There are also some examples in `testlib.h`'s [github
repository](https://github.com/MikeMirzayanov/testlib/tree/master/validators),
and you should take a look at it.

To add your validator, there is a button to upload your validator. There is also
a drop-down menu for selecting _existing_ validator. But since there is no
standard generator yet, you must add your first before any items appear.

There is a also a section to add the validator tests. Because the test
validation step is important, the validator should also be tested thoroughly.
More on that part later.

### Writing the validator

{%include customhighlight.html dir=page.prepdir file="validator.cpp"
  caption="validator.cpp" ext="cpp"
%}

The validator is simple. But there are some notes for the validator:
- There should be a variable name for each `inf.read*` function call. This will
  produce more readable error messages.
- There should be a message for each `ensuref` function call. The `f` here means
  `format`, the same as `printf` and `scanf`, and it use the same format as
  `printf`. This is for readability too.
- The use of `setTestCase()` function is also for readability.
- The white-spaces (space, EOL character) should be check properly. For normal
  problems solved with `Pascal` or `C++`, spaces are generally not important. But
  for the other languages like `Python`, `Java`, `Kotlin`, the input it often
  read by lines and the tokens are split by spaces. Trailing and duplicated
  spaces can cause these solution to fail.
- If you don't call `inf.readEof()`, there will also be an error for not
  confirming the input has been fully read.

Now we can add this validator to Polygon. **Remember to click `Set validator`**
for confirming the validator with Polygon.

**Notes** Polygon also produces some warnings for missing some good practice.
For example if you don't put the variable name for `test-case`, this message
will appear when you hover your mouse over the validator name.

{% include image.html caption="Polygon's warning for validator"
alt="polygon-warning-for-validator" file="polygon-validator-warning.png" %}


And also note that <span style="color: orange">orange</span> things are often
hoverable, and might be some warnings.

For editing the validator, you can click to the validator's name on the right
panel. To go to the validator page again, you can click `validator` option on
the top bar, or click the `(None)` link to the right of the validator name.

### Adding validator tests
Yes, the thing that we are using to validate the tests should also be tested!
The validator is a program too, and it is written by human. And we human very
often making mistake. But the testing process is not complicated, since the
validator is often not a complicated program. 

To add tests, click `Add test` in the `validator page`. The page for adding the
tests looks like this.

{% include image.html caption="Create validator test page"
alt="create-validator-test-page"
file="polygon-create-validator-test-page.png" %}

The first input box is for the id of the test. The checkbox `Use testset and
group:` is for a problem with multiple test sets and group, like problem with
sub-tasks. Since we don't use sub-task in this problem, we can leave it
unchecked. When the checkbox `Multiple tests` is checked, we can input multiple
validator tests instead of one, separated by 3 equal signs (`===`).

Here are the tests.

{% include customhighlight.html caption="Inputs" dir=page.prepdir
  file="validation-test.txt" collapsed=true %}

**Notes.** The last line has an extra line break.
  
{% include customhighlight.html caption="Verdicts" dir=page.prepdir
  file="validation-test-verdicts.txt" collapsed=true %}
  
For each of the `inf.read*` and `ensuref` function calls, I add two tests for it
-- one with a value lower than the lower bound, and one with a value higher than
the upper bound. The _description_ for the test is as follows.
- The first two are for testing the value of `test-count`.
- The next two are for testing the value of `n`.
- And the following two are for the value of `a`.
- The next test is to test a very small test.
- The next test is for testing the `ensuref` statement, that is, ensuring if the
  sum of `n` does not exceed $30000$.
- And finally, I add another small random test.
  
If you notice, there are test that does not follow the format, like in the
second test I only put the number of test cases there. But here I wanted to test
the constraints only, and we can consider the validator correct when it produce
the correct verdict and **error message**. For testing the input formats, we
already have two tests, but more can be added.

After adding the tests, you can go back to the `Validator page` and run the
tests. Here is the validator test result.

{% include image.html alt="validation-test-result"
  caption="Validation test result"
  dir=page.old_image_dir file="validation-test-result.png"
%}

### Our third commit
You know the drill by now. We have added the validator, with its tests, so it is
a good moment to make another commit. The commit message can be `Add validator
with validator tests`.

[Polygon]: https://polygon.codeforces.com/
[Version control]: https://en.wikipedia.org/wiki/Version_control
[git]: https://git-scm.com/
[tex]: https://en.wikipedia.org/wiki/TeX
[MathJax]: https://www.mathjax.org/
[latex-mathematics]: https://en.wikibooks.org/wiki/LaTeX/Mathematics
[testlib.h]: https://codeforces.com/testlib

{% comment %}
vim: spell wrap
{% endcomment %}
