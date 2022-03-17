---
layout: custompost
title: "Polygon.Codeforces Tutorial - A Guide to Problem Preparation [Part 1]"
date: 2022-03-09 00:00:00 +0300
tags: [en, polygon, codeforces, testlib, cp]
prepdir: _embed-contents/2022-02-19-test-generation-guide
old_image_dir: /assets/2022-02-19-test-generation-guide
wrapCode: true
useMathjax: true
image_dir: /assets/2022-03-09-polygon-codeforces-tutorial
toc: 
  use: true
  upper_header_level: 4
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
be treated as a _diary_ or a _journal_. A commit message should explain what has
been changed during a version, so the message should be _meaningful_. Even
though on Polygon, you can leave it blank, but it is a good practice to always
write a message.

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

There is also the second pane of the right column, but for this tutorial, it
does not contain much information, except for the last part.

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

The second line of each test case contains $n$ integers $a_1, a_2, \ldots, a_n$ ($1 \le a_i \le 10^6$).

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

**Note.** I put this part before the test generation part, because
a validator is _generally easy to write_, while the test generation is the
hardest part.

### The `Select validator` page
When you click the `Validator` option on the top bar, here is validator page
will look like.

{% include image.html caption="Select validator page" alt="select-validator-page" 
file="polygon-validator-page.png"
%}

We can see that the Polygon's developers are nice enough to put on some example
for us to see, as well as a little guide. I also recommend to read that guide
before writing the validator. [Here][validator-guide] is
the link to the guide. There are also some examples in `testlib.h`'s [github
repository](https://github.com/MikeMirzayanov/testlib/tree/master/validators),
and you should take a look at it.

To add your validator, there is a button to upload your validator. There is also
a drop-down menu for selecting _existing_ validator. But since there is no
standard generator yet, you must add your first before any items appear.

There is a also a section to add the validator tests. Because the test
validation step is important, the validator should also be tested thoroughly.
More on that part later.

### The validator's implementation

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
  spaces can cause these solutions to fail.
- If you don't call `inf.readEof()`, there will also be an error for not
  confirming the input has been fully read.
  
**Notes.** The result about white spaces and EOF mentioned above is called the
_well-formed policy_. More on that in the test generation section.

Now we can add this validator to Polygon. **Remember to click `Set validator`**
for confirming the validator with Polygon.

**Note.** Polygon also produces some warnings for missing some good practice.
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

**Note.** The last line has an extra line break.
  
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

The rule of thumb is the tests must [cover][test-coverange] what should be tested, and in this
case they are the `inf.read*` and `ensuref` function calls.
  
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

Of course, this commit can be broken into two smaller commits: one when the
validator is added, and one when you are finished with the tests. Here I made
one commit to not break the flow of the post.

In some cases, you might failed some validator tests, you still can made a
commit. After fixing the bug, you can create another commit like `Fix
validator bug ...`. Again, we can treat the it as a _diary_ or _journal_.

## The checker
A checker is a program for checking whether or not _an answer_ is correct. What
is the correctness anyway? Usually, this means the answer of the participant is
_the same_ as the jury's (or the author's) answer. But that is not the case for
most of the problem. There are problems with non-unique answer, and the checker
must also check that. An example of non-unique answer problem is to trace a
shortest path between two vertices in a graph. If the answer is the path, then
the checker must check if two given vertices are reachable using the path, and
if the path is truly the shortest.

Before going further, let's look at the `Select checker` page.

### The `Select checker` page
{% include image.html caption="`Select checker` page"
  alt="select-checker-page" file="polygon-checker-selection-page.png" %}
  
The page is almost identical as the `Select validator` page, with the same
functionalities, as well as the examples. And I also recommend to read the
[guide][checker-guide] for writing checker with `testlib.h` before writing your
own.

Different from the `Select validator` page, there are already some standard
checkers ready to use. As mentioned before, usually the answer of the
participant is checked against the answer of jury, and there are some checker to
check some typical type of outputs.

### The standard checkers
{% include image.html caption="List of standard checkers"
  alt="list-of-standard-checkers" file="polygon-standard-checkers.png" %}
  
For most cases, you can actually always choose the checker `wcmp.cpp`, since
comparing integers for most cases is the same as comparing words (or tokens).
But with different kind of input, it make more sense to use the exact checker,
for example, the checker `ncmp.cpp` should be used for comparing sequence of
integers. For a specific type of output, the corresponding checker can also
check for the output formatting, as well as producing more readable messages.
The case that we should not use the checker for tokens is when comparing _real
numbers_ output, since the checker should checking the answers relatively or
absolutely with a small value.

In our case, we can use the checker `nyesno.cpp` (not `yesno.cpp`, since we are
comparing sequence of `YES` and `NO` tokens, and not just one!). Selecting it
then we are done with the checker part.

**Note.** After selecting the checker, it is possible to see the checker's
source code.

### Writing our own checker
Even though we already have our own checker, for the sake of the completeness, I
think it worth to write our own checker in this tutorial.

The standard checker is very general, since it is _input independent_. For this
problem, let's make the check the output with the dependency on the number of
test cases. That is, our checker should check if the number of read token is the
same as the number of test cases.

#### The `readAns` paradigm
This is one part in the [guide for writing checker][checker-guide]. The main
idea is, when writing a checker, it is a good practice to write a function for
reading and (_paritially_) checking the answer from a stream, and use it to read
the participant's answer as well as the jury's answer. After that, we can check
these answers against each other.

#### The checker's implementation
{% include customhighlight.html caption="checker.cpp" dir=page.prepdir ext="cpp"
file="checker.cpp" %}

**Note.** I use [clang-format], so don't notice the _weird_ parameter
indentation formatting.

{% comment %}  This part is removed since `setTestCase` is used instead.
**Note.** The function `englishEnding(number)` is for getting the _order_ ending
of a number. For example, `englishEnding(1) == "st"`, `englishEnding(3) = "rd"`,
`englishEnding(10) == "th"`. This is undocumented in [the guide][checker-guide],
but it is on the [feature list in the source code of
`testlib.h`](https://github.com/MikeMirzayanov/testlib/blob/f28d52804011c5dca2e62fbe7cff45888579b0e8/testlib.h#L114)
{% endcomment %}

If you have seen the source code of `nyesno.cpp`, I have borrowed some part from
it. But with the dependence on the number of test cases, as well as using the
`readAns` paradigm, the code is significantly shorten.

Here I used a function here called `quitif(condition, verdict, message)`. If the
`condition` is `true`, then the `verdict` will be returned with the `message`.
If used with the input stream (`inf`) or the answer stream (`ansf`), then the
verdict will always be `_fail`, no matter what is passed to the second
parameter. This make sense because the input should be correct (validated by the
validator), and the answer should also be correct before passing to the checker.
And in case of failure, that's mean the there might be a bug in our checker or
the solution.

#### Adding the checker tests
As in the case of the validator, we must also test the checker. And as before,
the tests must [cover][test-coverange] the functionalities that we wanted to
test. And in this case:
- The token format (should be `YES` or `NO` case insensitive).
- The number of tokens (should not be less or more than the number of test
  cases).
- The participant's answer and the jury's answer must be matched.

To add the tests, click the `Add test` link to go to the `Create checker test`
page.

{% include image.html caption="Create checker test" alt="create-checker-test"
  file="polygon-create-checker-test-page.png" %}
  
Here there are input boxes for the `Input`, the `Output` and the `Answer`. It is
not simple as with the `validator` case, so we can not specify multiple tests
within a text area.

There is a also a button for generating the answer from the _model solution_. So
if you have a model solution, pressing that button will save us a little time
for not needing to recreate the true answer. But now let's make them by hand.

Here are the tests. For space-saving, each test's parts are put into one file
with the separator `===section===`. Also the verdict `CRASHED` corresponds to
the `_fail` verdict in `testlib.h`.


Here are the results of the tests.

{% include_relative 
  _embed-contents/2022-03-09-polygon-codeforces-tutorial/checker-tests.liquid 
%}

{% include image.html caption="Checker tests results"
alt="checker-tests-results"
file="polygon-checker-test-result.png" %}

**Remember** to check the verdicts and the Checker comments.

### A commit again
Let's do the commit with the message `Add checker with checker tests`. Again, of
course we can split this commit into two smaller one like in the validator case.
Or there might also be bug in our code, which should also be fixed and saved
with another commit. This part is completely similar to the validator. But it is
up to you to decide when is the right time to make a commit.

## The model solution
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

### Adding the solutions to Polygon
To add the solutions to Polygon, click the option `Solutions files` on the top
bar, or on the right pane, `None` or `(0/0)` link at the `Solutions` section.

{% include image.html caption="Solutions page" alt="solutions-page"
  file="polygon-solutions-page.png" %}
  
The page is simple. There is a link to add the solutions. Now let's add the
above two solutions first. Here is the page after adding the solutions.

{% include image.html caption="Solutions page after adding solutions" alt="solutions-page-after-adding-solutions"
  file="polygon-solutions-page-after-adding-solutions.png" %}

**Note.** The solution name (without the extension part) must be all different.
  
By default, the first uploaded solution will be the `Main correct` (or model)
solution, and other solution will be just be `Correct` solution. Even though
there can be more than one correct solutions, the `Main correct solution` will
be used to generate the output. You can change the solution type by click the
`Change?` option at the `Type` column for each solution.

{% include image.html caption="Solution types"
alt="solution-types" file="polygon-solution-types.png" %}

I think the types are self-explanatory, since most of them are normal verdicts
in a contest. There are _more_ general verdict like `Incorrect` means that the
solution of this type can have the verdict either be `WA`, or `TLE` or `MLE`,
or maybe `Presentation error`. The `Incorrect` verdict can be used when the
solution has a different verdict for a different input.

There is no limit for a given solution type. Instead, if there are more
solutions, with different _predictable_ verdicts, then they should be added as
well. The point of having multiple solutions, either correct or incorrect, is to
_verify_ the test-set. The test-set should be strong enough to _**kill** specific
incorrect solutions_, while must remain correct for all _correct solutions_ to
pass.

### More commits!
We make a commit with the message `Add two correct solutions`.

## Stress testing. Our first test generator.

[Here][stress-testing] is the Wikipedia page about stress testing. In
competitive programming, stress testing is used not for all of the reason stated
in the Wikipedia page, but there is a main point:
- to confirm mathematical model is accurate enough in predicting breaking points
  or safe usage limits
  
Stress testing on Polygon is conducted with multiple solutions (can also be
incorrect solution). The output of these solution will be checked against the
output of the **model solution**. The tests for stress testing is also generated
from a test generator.

With this way of doing stress testing, we not only can ensure the correctness of
the mathematical model, but also eliminate the _implementation errors_. Suppose
we are stress testing two solutions against each other. Both solution have the
equal chance of being incorrect, since we have not tested them before.
But with stress testing, _implementation errors_ is very easy to detect, because
the **likelihood** of two solutions having the same _implementation errors_ is
**not high**. If the result of these solutions are not matched, we should not
only suspect the errors in one solution, but in both solutions. And if after
fixing the implementation errors (in both solutions), the output of the
solutions are still not matched, then we can conclude that the mathematical
model is incorrect, with a concrete counter example. From there, we should find
the error in the proof, or try to find another solution. If two solutions are
not enough to guarantee the correctness, remember that Polygon allows stress
testing with multiple solutions!

In this section, we are going to test the correctness of the model solution with
stress testing. So to do that, we are going to add another solution, as well as
creating a test generator.

### What solution are we going to test against?

First of all, this solution should be a _correct_ solution. In order to reduce
the implementation errors, this solution should solve this problem in a
_different way_. Since we only use this solution for checking the correctness of
the model solution, we don't need this solution to be fast. With these in mind,
_brute-forcing_ is always a candidate. The brute-force solution is often _more_
correct because it uses _less_ assumptions.

In this problem, brute force can be done with **simulation** -- we simply try
all possible ways to decrease the input array, and when we have all $0$, we can
conclude that there is an answer. Such simulation can be implemented with
recursion, but to make it a little faster, we can also use _memorization_ --
that is, storing all visited states.

{% include customhighlight.html caption="brute-force.cpp"
  dir=page.prepdir file="brute-force.cpp" ext="cpp" collapsed=true
%}

We add this solution to Polygon the same was as in the previous section, but we
set the _type_ of this solution to _Time limit exceeded_, because it can
produce correct result, but it will run very slow on a big test case.

### Our first generator
#### The `Files` page
To add a generator to Polygon, we must use the `Files` page (from the `Files`
option on the top bar) instead of the `Tests` page. In the `Files` page, there
are also added source files like our `validator.cpp` and `checker.cpp`, as well
as `testlib.h`. The other files are for PDF file generation with $\LaTeX$.

{% include image.html caption="The Files page" alt="the-files-page"
  file="polygon-files-page.png" %}
  
As before, the developers are very nice, leaving us some examples, as well as
[the guide][generator-guide] for writing a generator with testlib.h. Please
read [the guide][generator-guide] before continueing.


#### Functionalities for a test generator

Before writing the out first generator, I think it worth pointing out some
functionalities of a generator. I wanted to make it clear, not for this
generator, but also the future generators, and also for this part -- stress
testing.

##### Re-usability
A generator is used not only to generate a test, but also multiple tests. And we
with the generator can generate a variety of tests. In this problem, for
example, the test cases should have different lengths, the array elements should
have different value ranges, and the answer for the tests should be
_controllable_ (having a specific amount of `YES` answers).

For this, a generator should have the ability to accept our external
parameters/options to generate a test. Normally, a program can accepts [arguments
from command line][cli-args], and these options can be accessed via the `argc`
and `argv` arguments accepted by the `main` function. Polygon does support this
way of passing arguments to the generator, and you can use `argc` and `argv` as
intended.

Recently, `testlib.h` supports a new way of way (or the old way but _fancier_)
of passing and getting the arguments, called **`opts`**. For more details about
**`opts`**, and see it in action, please refer to [this guide][opts-guide]. For
**`opts`**, I wanted to point out that there is an function that is not
mentioned in the guide.

- `has_opt(key)` returns `true` if there is an option with the name `key`.

With this function, we can specify default options as well, which will save us
some efforts passing the arguments.

{% comment %} maybe move `has_opt` to the exact location where it is used? {%
endcomment %}


##### Random number generation

The tests are often _randomly_ generated by a generator. As you may have known
before, the process for generating the random number (random number generation
-- or RNG for short) of a computer program is [pseudo-random][pseudo-random].
The numbers generated by a computer program is not completely random, but they
must based on some initial value, called [a seed][random-seed]. 

For RNG, the [generator guide][generator-guide] already provides functions for
generating random numbers. But they did not specify how exactly the generator
chooses the random seed, besides this sentence:

> ... a generator must output the same test when compiled by any compiler on any
> platform if it is run in the same way (using the same command line
> parameters).

This is a small detail, but I wanted to point it out before going to stress
testing. The arguments passed to the generator are [hashed][hash-function], and
the hash code is used as the random seed. Therefore, the test will be the same
for the same set of arguments. This is also means that the arguments for the
generator are _important_: it determined both the _shape_ of the test, as well
as the random seed!

#### The first generator's implementation

{% include customhighlight.html caption="gen-totally-random.cpp"
  dir=page.prepdir file="gen-totally-random.cpp" ext="cpp"
%}

This generator accepts 4 arguments/options:
- `test-count` -- the number of of test cases.
- `sum-n` -- the sum of array lengths over all test cases.
- `min-a` and `max-a` -- the minimum value and maximum value for array's
  elements.

The generator will generate `test-count` _totally random_ arrays. To determine 
the length for each array, I use `rnd.partition()` function. 

- `rnd.partition(size, sum, [min_part=1])` returns a vector of the given
  size, the sum of whose elements must equal the second parameter, and elements
  must not be lower than `min_part`.

This function is not in the [generator guide][generator-guide], because this
function is _new_. See
[the feature list](https://github.com/MikeMirzayanov/testlib/blob/f28d52804011c5dca2e62fbe7cff45888579b0e8/testlib.h#L67)
of `testlib.h` for more newly added functions.

There is also `println` function, which will print elements of a C++ collection 
space-separatedly without any trailing spaces. Remember that the trailing spaces
will cause the validation failure.

Even though it generates _totally random_ tests, for test with very small
constraints, the rate of `YES` tests will not be small, making the generator
suitable for stress testing.

Let's run it locally to generate a test with 5 test cases, the sum of length is
20, and the value range is from 1 to 5.

{% include customhighlight.html caption="gen-totally-random example"
  dir=page.prepdir file="out/gen-totally-random-example.sh.out" ext="sh"
%}

It is looking good. Let's add it to Polygon, via the `Files` page.

### Adding the stress test
#### The stresses page
{% include image.html caption="The stresses page" alt="the-stresses-page"
  file="polygon-stresses-page.png" %}

This page can be accessed via the `Stresses` option on the top bar. The layout
of the stresses page is similar to the previous pages: one table, and one
button to add an item.

Let's add a stress to Polygon.

{% include image.html alt="stress-against-brute-force"
  caption="Stress against brute-force solution"
  file="polygon-add-stress.png"
  %}
  
In this page:
- The `Script pattern` input allows us to write a script pattern for test
  generation. Here the script pattern is
```
gen-totally-random -test-count [1..10] -sum-n 20 -min-a 1 -max-a 5
```
Polygon also supports minimal random parameters generation. Here I wanted the
`test-count` to be a random number between $1$ and $10$. A fixed `sum-n` and
a randomized `test-count` are good to randomize the test cases `n` without
worrying about the constraints.
- There are also `Time limit` and `Memory limit` input boxes, because the
  stress-tested solution might not work well under the original problem's
  constraints.
- The `total-time-limit` is the total time to do stresses. If `60 seconds` is
  chosen, the stress will repeatedly run till the $1$ minute mark is reached.
- Finally, Polygon allows us to choose which solutions to run. Note that it is
  **not necessary** to add the model solution to the stress, since Polygon will
  use its output to check the other solutions anyway. But sometime it might
  still be a good idea, in case of changing the model solution.

For the configuration as in the image, click `Save and Run` to run the stress.
After at least $2$ minutes it will produce the `OK ` result. It might be higher
than $2$ minutes because of some other reasons, for example, if you update the
generators or solutions, recompilation will take time.

{% include image.html alt="the-stress-result"
  caption="The stress result"
  file="polygon-first-stress.png"
  %}
  
**Note.** Polygon will not refresh itself _for most of the time_, so you must
press refresh by yourself.

#### Finding countertest

But wait, _something is off_. Isn't the arguments is _the same_ for most of the
time? We only make `test-count` random, with a very small range. So did we only
do stress testing with only 10 tests repeatedly? Well no. To see why, let's
create another stress. It will be the same as the above stress, but now with
lower time limit for the brute-force solution to have `TLE` verdict.

After a few seconds after running, we will receive the following table.

{% include image.html alt="the-new-stress-result"
  caption="The new-stress result"
  file="polygon-second-stress.png"
  %}
  
By clicking the `view` link of the new stress, we got the following page.

{% include image.html alt="view-of-the-second-stress"
  caption="View of the second stress"
  file="polygon-stress-view-counter-test.png"
  %}
  
In the page, it says that the brute-force solution run too long to generate a
result, hence the `TL` verdict. If you see the `Countertest` row, there is a
command, but now it has an additional string after it. This is the mechanism of
Polygon for generating _totally_ random tests. By appending a random string at
the end of the command, the _random seed_ will be different even for a fixed
specified set of options.

### Commit, commit, commit!
We can _safely_ conclude that our solution is correct and contains no bug. Now
we can do a commit, for example, `Add brute-force solution and 2 stresses`. And
of course, it is better to split it into smaller commits, but again, we can do
the commit here to not break the flow of the post.

## Test generation
### A better test generator
We already have a generator. But that generator in general is not good. A random
array is very unlikely to have an answer `YES`, and we need to fix that. How
about we _don't_ generate the array, but the _increasing array_ $a$ and
_decreasing array_ $b$ as in the editorial, then summing them up? Doing so will
guarantee to have the answer `YES` because that is what the problem **is
asking** the participant to do.

**Note.** In the editorial, the name of the _increasing array_ is actually $b$
and the _decreasing_ one is $a$. While making this blog, I have their names
wrong. In my defense, making $a$ the increasing array is more natural than the
other way around. So I'll keep it this way.

For this algorithm, there are some problems when reusing the code from
`gen-totally-random.cpp`
- We can not use `min-a` and `max-a` for this algorithm.
- That are only `YES` tests, how about the `NO` tests?

The first problem can be _partially_ solved by adding the value for
arrays $a$ and $b$ separately. For the second problem, we are going to generate
arrays $a$ and $b$ now, so let's also add an option to generate them randomly
instead of sorted. There should also be an option to specify how many of them
are `YES`, and how many are `NO`.

Here is the generator with the above idea.

{%include customhighlight.html caption="gen-v1.cpp"
  dir=page.prepdir file="gen-v1.cpp" ext="cpp"
%}

In this current version, all the `YES` tests are at the beginning, while all the
`NO` tests are at the end. Even though it is not good for a test, but it does
help us seeing the result of the test easier. And we will fix this for the
future version of the generator, but let's keep this for now.

Let's run it
{%include customhighlight.html caption="gen-v1 example"
  dir=page.prepdir file="out/gen-v1-example.sh.out" ext="sh"
%}

Here the first two tests are `YES` and the rest are `NO`. I purposely choose a
larger range so the test that should not be `YES` will be more likely to produce
the `NO` answer.

This generator works, so let's add this to Polygon.

### Adding the tests
#### The `Create tests` page
{% include image.html caption="The create tests page" alt="the-create-tests-page"
file="polygon-create-tests-page.png"
%}

Similarly to the other pages, there is a table, and a button to add the tests.
But in this page there are more elements than the other pages.

There are some checkboxes in the top of the page. The well-formed policy is
what we have discussed in the `test validation` section. If checked, then
Polygon will also automatically validate the tests according to this policy. If
you click on the question mark near the `Test well-formed` text, there is a
pop-up window appears, explaining the policy.

{% include image.html caption="Polygon's test well-formed policy explaination"
alt="polygon-test-well-formed-policy-explaination"
file="polygon-well-formed-policy.png"
%}

The other two checkboxes is for adding points and groups, and mainly used for
other format like IOI, where there are subtasks and each subtasks has different
scoring. Problem on Codeforces must be fully solved, so we don't need to check
those checkboxes.

The _huge_ part at the end is called _script_. This is a way to add the
tests: by calling the generator. On the right of the input area box, there is a
text, explaining how to write the script. This is what we have done before when
calling the generator offline, and now on Polygon, we can compose them into a
list of commands, which is actually called a _script_.

Clicking `Add Test` link above the table, a page will appear, providing us some
other ways to add the tests. We will see it shortly.

The `Preview Tests` is for, you guess it, previewing the tests. We will see it
later after generating the tests.

#### Adding the example tests
Now let's click the `Add Test` link. Here is the page looks like.

{%include image.html caption="The add test page" alt="the-add-test-page"
  file="polygon-add-test-page.png" %}
  
Above, there are options to add tests from an archive or files. This is suitable
for existing contests with available tests, but it is not recommended when we
already have the test generators. An archive or files will be very big, making
them hard to maintain. 

Notice that there is an option called `type`, which let's us to choose to add
the test either manually or with a script again. Since we are adding the example
test, we choose to add the test manually.

Remember that beside the original example, we also added a test case when
writing the statement. Here will be our test input.

{% include customhighlight.html caption="Example test input" collapsed=true
content="
5
3
1 2 1
5
11 7 9 6 8
5
1 3 1 3 1
4
5 2 1 10
4
3 2 1 2

" %}

Since this is the example test, we should click the check box `Use in
statements` as well. After that the page should look like this.

{%include image.html caption="The add test page after adding the a test"
alt="the-add-test-page-after-adding-a-test"
file="polygon-add-test-page-added-test.png" %}

There is also an option for specifying custom output. This feature is useful
for problem with non-unique outputs.

Click the `Create` button to add the example test. Now if you go to the
`Statement` page again and see the statement, the example test will appear.

### Writing the test generation script
Each command in the script on Polygon is similar to when we are executing the
generator locally. The differences is the generator name, which we only specify 
its name, and the _output_ file, denoted by the syntax `> [id]` where `[id]` is
the test number, or `> $` for automatically id generation.

A few first tests might be these.

{% include customhighlight.html caption="First few tests"
content="
gen-v1 -test-count 300 -sum-n 30000 -yes-count 150 -min-a 1 -max-a 10 -min-b 1 -max-b 10 > $
gen-v1 -test-count 300 -sum-n 30000 -yes-count 150 -min-a 1 -max-a 10 -min-b 100 -max-b 1000 > $
gen-v1 -test-count 300 -sum-n 30000 -yes-count 150 -min-a 100 -max-a 1000 -min-b 1 -max-b 10 > $
gen-v1 -test-count 300 -sum-n 30000 -yes-count 150 -min-a 100 -max-a 1000 -min-b 100 -max-b 1000 > $
" %}

Here are 4 tests, the array length of the test cases in these tests is $100$ on
average, with $50\%$ of the cases with the result `YES`, and the value size for
the array $a$ and $b$ _slightly_ varies.

We can of course, continue adding that. But that is not very elegant, since we
must copy and paste a lot and change the test cases little by little.
Fortunately, Polygon has a solution for that.

#### Introducing FreeMarker.
[FreeMarker] is the template engine used on Polygon, and in this case for
_generating_ the script for test generation. There is a brief manual about
FreeMarker to the right of the script input box, and please do check it out
first. FreeMarker is very powerful, and it can be used as a real programming
language. This tutorial will demonstrate some of its power in writing the test
generation script.

#### Making the lengths varies
This can be done by altering the `test-count` option. For that, we can use the `<#list>`
tag, which is equivalent to a for loop.

{% include customhighlight.html caption="Altering the testCount"
content="
<#assign testCount = 10000 >
<#list 1..5 as i>
  gen-v1 -test-count ${testCount} -sum-n 30000 -yes-count 150 -min-a 1 -max-a 10 -min-b 1 -max-b 10 > $
  gen-v1 -test-count ${testCount} -sum-n 30000 -yes-count 150 -min-a 1 -max-a 10 -min-b 100 -max-b 1000 > $
  gen-v1 -test-count ${testCount} -sum-n 30000 -yes-count 150 -min-a 100 -max-a 1000 -min-b 1 -max-b 10 > $
  gen-v1 -test-count ${testCount} -sum-n 30000 -yes-count 150 -min-a 100 -max-a 1000 -min-b 100 -max-b 1000 > $
<#assign testCount = testCount / 10>
</#list>
" %}

There is some problem with this: the `yes-count` is the same. One way to fix it
is to replace `150` of `yes-count` with the expression `${testCount / 2}`. But
that expression will produce `0.5` for `testCount == 1`.

Another way to solve this problem is to use [sequence][FreeMarker-sequence]
which is equivalent to array/vector in a normal programming language.
We will create a sequence of a pairs `(testCount, yesCount)`. To simplify, we
will create a 2D sequence instead. The script will then look like this.

{% include customhighlight.html caption="Altering the testCount and yesCount
with sequence"
content="
<#assign testAndYesCounts = [
  [10000, 5000],
  [100, 50],
  [1, 0],
  [1, 1]
] >
<#list testAndYesCounts as testAndYesCount >
  <#assign testCount = testAndYesCount[0] >
  <#assign yesCount = testAndYesCount[1] >
  gen-v1 -test-count ${testCount} -sum-n 30000 -yes-count ${yesCount} -min-a 1 -max-a 10 -min-b 1 -max-b 10 > $
  gen-v1 -test-count ${testCount} -sum-n 30000 -yes-count ${yesCount} -min-a 1 -max-a 10 -min-b 100 -max-b 1000 > $
  gen-v1 -test-count ${testCount} -sum-n 30000 -yes-count ${yesCount} -min-a 100 -max-a 1000 -min-b 1 -max-b 10 > $
  gen-v1 -test-count ${testCount} -sum-n 30000 -yes-count ${yesCount} -min-a 100 -max-a 1000 -min-b 100 -max-b 1000 > $
</#list>
" %}

With this approach, we have more control over the test. Here we generated $16$
tests, as opposed to the previous method which generated $20$ tests. 

#### Making the value range varies
We can as well use sequence of pairs to specifies the value ranges, and use
loops to iterate over them.

{% include customhighlight.html caption="Altering the value ranges with sequences
and loops"
content="
<#assign testAndYesCounts = [
  [10000, 5000],
  [100, 50],
  [1, 0],
  [1, 1]
] >
<#assign valueRanges = [
  [1, 10],
  [100, 1000],
  [100000, 500000]
] >
<#list testAndYesCounts as testAndYesCount >
  <#assign testCount = testAndYesCount[0] >
  <#assign yesCount = testAndYesCount[1] >
  <#list valueRanges as aValueRange>
    <#list valueRanges as bValueRange>
      gen-v1 -test-count ${testCount} -sum-n 30000 -yes-count ${yesCount} -min-a ${aValueRange[0]} -max-a ${aValueRange[1]} -min-b ${bValueRange[0]} -max-b ${bValueRange[1]} > $
    </#list>
  </#list>
</#list>
" %}

This script will produce $4 \times 3 \times 3 = 36$ tests. FreeMarker really
helps us writing the script more easily. With just a little code, we can produce
a large amount of tests!

#### Preview the tests
**Remember** to click the `Save Script` button. Let's go to the test preview
page.

{% include image.html caption="Test review" alt="test-review"
  file="polygon-test-review-page.png" %}
  
For each test, Polygon will show a few first character of the input, as well as
the output. Seeing the whole test is a lot, but a few first line is enough for  
online reviewing. It also allows to download the tests to review it more
throughoutly when necessary.

When there is some problem with a test, the message will also display there. For
example, if you happened to add another range for the value range like `[500000,
1000000]` in the script, then there will be an error because `1000000 + 1000000`
will exceed the maximum value of array.

{% include image.html caption="Test review with errors"
alt="test-review-with-errors"
  file="polygon-test-review-with-error.png" %}
  
It is a bit hard to see the error in a small box, so you can download the test
to see it locally, or maybe run that command on your computer and do the
validation locally.

### Commit! Commit more! Commit forever!
The commit message can be `Add a better generator with tests`. But as always, it
should be broken down, like when you add the generator and when you add the
tests.

## Final touches
We basically have done everything to prepare a problem, from writing the
statement to generate the tests. If you look at the right pane again, there are  
sections that we have not touched yet. They are `Package`, `Verification`,
`Review problem` and `Show warnings`.

{% include image.html caption="The right pane after"
  file="polygon-right-pane-after.png"
%}

### Show warnings
Remember about the warning when writing the `validator`? By clicking the link,
we are directed to the page containing all the warnings. We have done a good job
not to leave any warnings in the other section, but the section `Show warning`
is still <div style="color: orange">orange</div>. That because there is a small
thing that Polygon recommends us to do: add the tags to the problem.

{% include image.html caption="Warnings page"
file="polygon-warnings-page.png"
%}

To add the `tags` for the problem, we can go to the `General info` page.
{% include image.html caption="Adding tags in the General info page"
file="polygon-problem-general-info-page-add-tags.png" %}

The tags doesn't seem to be useful, but one of their use on Polygon is for
`Searching`. There is a `Search` option on the top bar in the **home page**
(when you logged in).

{% include image.html caption="The search page" file="polygon-search.png" %}

After adding the tags, you can make a commit as well.

### Review problem
By clicking the link in the section `Review problem` of the right pane, a page
shows up with three columns: problem statement, validator and checker.

{% include image.html caption="Review problem page"
file="polygon-problem-review-page.png" %}

I purposely capture this image **before** adding the tags, to show that in this
page, warnings also appear as well. There are only validator and checker besides
the problem statement, because the validator and the checker must **be aligned**
to the problem statement. The reviewer should check if the constraints for the
input are correctly checked by the validator, as well as if the checker
correctly checks the output.

### Invocation
There is an option call `Invocation` on the top bar of the problem. When
clicked, this page shows up.

{% include image.html caption="Invocation page"
file="polygon-invocation-page.png" %}

This page is for running some/all solutions against the some/all tests. When
clicking `Want to run solutions?`, two tables will appear, one for choosing
solution, and one for choosing the tests. After choosing, click on `Run
judgement` to run them.

{% include image.html caption="Choose to run all solutions against all tests"
file="polygon-invocation-run-all-solutions-against-all-tests.png" %}

After that, there will be a new item on the table. Click the `view` link of the
items to see the running result. The solutions are also ran on the fly, so you
need to refresh the page to update the result.

The result table grows vertically with the number of tests, so it will be huge.
There are some useful information at the end of the table though, like the
number of passed tests, the resource usages for each solution. There are also
scores if you use scoring.

{% include image.html caption="Invocation result"
file="polygon-invocation-result.png" %}

There are also notes about the color coding. Base on that you can adjust the  
time and memory limit accordingly.

**Note.** The invocation page is not shared among the author of the problem.

### Verification
If you click the `(start)` link of the `Verify` section in the right pane, it
seems like nothing happen. But actually, Polygon will create **a new
invocation** for all solutions and all tests, which can be seen in the
`invocation page`. And after that, Polygon will **collect** the invocation
result and compare it to the solutions verdicts. If everything matches, then the
verification is **success**. Otherwise it is **failed**, meaning something is
wrong, and you should fix it.

{% include image.html caption="Verification failed with reason"
file="polygon-verification-failed.png" %}

We got **failed** verdict, because while we mark the solution `brute-force.cpp`
as `TLE`, it has `MLE` verdict for the $10$-th test. To fix it, we should change
the verdict of the `brute-force` solution into `Time limit exeeced or Memory
limit exceeded` (or `TLE or MLE`). After fixing and re-run verification, we will
get the `OK` result.

{% include image.html caption="Verfication ok"
file="polygon-verification-ok.png" %}

### Package 
A package is a zip file, containing all of the files of the problem, in the
same directory as on Polygon. CodeForces in particular will use the package file
to import the problem from Polygon, making it very easy to add problems to
CodeForces.

{% include image.html caption="The package page"
file="polygon-package-page.png" %}

These are the same old tables with an adding buttons. Beside the table for
packages, recently there is also a table for the problem material. [See
here][polygon-updates-02-2022] for more details.

As seen here, there are two type of packages. The `standard` package only
includes all files of the problem, while the `full` package contains additional
files, noticeably the **generated tests**. So the `full` package will be heavier
but things are already done in the `full` package. The `standard` package, however,
is enough, since everything are _reproducible_. The checker, validator, the
solutions and generators are all in the package, and there even a script for
running them. CodeForces only requires standard package to import the problem.

There is also a checkbox `Verify`. With this checked, Polygon will also do the
verification process (again), and when failed, Polygon won't produce the
package.

Also note that Polygon only create a package when there is currently no changes
because it is for a version, not _half_ version. Make sure to commit changes
before creating a package. That being said, you can create any package for any
version, whichever you like, and Polygon will store the package for you.

{% include image.html caption="Create a new standard package"
file="polygon-package-page-create-new-package.png" %}

You can download the package and see it for yourselves.

### Adding the problem to a CodeForces mashup
To create a Mashup on Codeforces, go to `Gym > Mashup > Create new mashup`.

{% include image.html caption="CodeForces create a new mashup"
file="codeforces-create-mashup-page.png" %}

There is a note about how to add the problem to CodeForces. We must grant the
access of the problem to the user `CodeForces` on Polygon.

On the top bar of the problem on Polygon, click `Manage Acess`. (And yes, there
is a table with an adding button). Click `Add users` and type `codeforces`
and then click `Add users` button.

{% include image.html caption="Manage access page with codeforces added"
file="polygon-manage-access-page.png" %}

The link to this problem on Polygon is on the second pane of the right column.

{% include image.html caption="The link to the problem in the second pane"
file="polygon-the-second-pane.png" %}

Click it to copy the link, and paste it to the mashup creation page. Click
`Create Mashup Contest` to finally create the contest. That is, you finally
added this problem to a Mashup contest on Codeforces! You can share this contest
with your friends, or add it to a Codeforces group.

Again, [here][contest-invitation] is the link to the result of this post.


[contest-invitation]: https://codeforces.com/contestInvitation/0b42bfbee9fb4479e24492e688458a1bfa30c835
[Polygon]: https://polygon.codeforces.com/
[Version control]: https://en.wikipedia.org/wiki/Version_control
[git]: https://git-scm.com/
[tex]: https://en.wikipedia.org/wiki/TeX
[MathJax]: https://www.mathjax.org/
[latex-mathematics]: https://en.wikibooks.org/wiki/LaTeX/Mathematics
[testlib.h]: https://codeforces.com/testlib
[validator-guide]: https://codeforces.com/blog/entry/18426
[checker-guide]: https://codeforces.com/blog/entry/18431
[clang-format]: https://clang.llvm.org/docs/ClangFormat.html
[test-coverange]: https://en.wikipedia.org/wiki/Code_coverage
[CF1442-editorial]: https://codeforces.com/blog/entry/84298
[stress-testing]: https://en.wikipedia.org/wiki/Stress_testing
[generator-guide]: https://codeforces.com/blog/entry/18291
[cli-args]: https://en.wikipedia.org/wiki/Command-line_argument_parsing
[opts-guide]: https://codeforces.com/blog/entry/72702
[pseudo-rng]: https://en.wikipedia.org/wiki/Random_number_generation#%22True%22_vs._pseudo-random_numbers
[random-seed]: https://en.wikipedia.org/wiki/Random_seed
[hash-function]: https://en.wikipedia.org/wiki/Hash_function
[FreeMarker]: freemarker.org
[FreeMarker-sequence]: https://freemarker.apache.org/docs/dgui_template_exp.html#dgui_template_exp_direct_seuqence
[polygon-updates-02-2022]: https://codeforces.com/blog/entry/100519

{% comment %}
vim: spell wrap
{% endcomment %}
