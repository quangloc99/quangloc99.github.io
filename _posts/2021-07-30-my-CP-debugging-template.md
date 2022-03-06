---
layout: custompost
title: My CP debugging template
date: 2021-07-30 9:30:00 +0300
tags: [en, cp, debugging]
---
Debugging in competitive programming (CP) is hard. But there are several
attempts have been done to ease this process.  Some people, including some top
CP-ers, have spent their time writing some code, so-called **debugging
templates**. These pieces of code are often used to print out some variables'
value in the code.  For example, [tourist][tourist-codeforces-profile] has his
debugging template, which can be seen in some of his submissions
[here][tourist-debugging-template-1] and [here][tourist-debugging-template-2].
Or [Erricto][Erricto-codeforces-profile] with his ~~ugly~~ debugging template
can be seen [here][Erricto-debugging-template] (and here is the
[explanation][Erricto-debugging-template-explanation]). Some even go further
and make the debugging more _joyful_ by [adding color for the
output][how-to-debug-with-color]. But some people prefer a simpler approach,
and nearly requires nothing, like [Um_nik][Um_nik-codeforces-profile] with [his
printf to stderr][Um_nik-debugging-template].

I also have my debugging template. But why would I created a new template, when
I can just use a very comprehensive like tourist, a also comprehensive but
~~ugly~~ short like Erricto, or just writing things out like Um_nik? Well, I
also prefer simplicity, but for writing a lot of debugging information, the
Um_nik's way is too painful. And my short-term goal now is still ICPC,
therefore investing time just to write nearly 100 lines of code, or writing
code that even I cannot understand in a live competition is not fast and safe.
More over, time should be invested more in thinking and carefully writing code. I
I actually tried really hard to come up with something powerful enough but
should be as simple as possible to type out.

Here is my debugging template (just a part of my CP template).

```c++
#define print_op(...) ostream& operator<<(ostream& out, const __VA_ARGS__& u)
// DEBUGING TEMPLETE ////////////////////////////////////////////////////////////////////////
#define db(val) "["#val" = "<<(val)<<"] "
#define CONCAT_(x, y) x##y
#define CONCAT(x, y) CONCAT_(x, y)
#ifdef LOCAL_DEBUG   
#   define clog cerr << setw(__db_level * 2) << setfill(' ') << "" << setw(0)
#   define DB() debug_block CONCAT(dbbl, __LINE__)
    int __db_level = 0;
    struct debug_block {
        debug_block() { clog << "{" << endl; ++__db_level; }
        ~debug_block() { --__db_level; clog << "}" << endl; }
    };
#else
#   define clog if (0) cerr
#   define DB(...)
#endif

template<class U, class V> print_op(pair<U, V>) {
    return out << "(" << u.first << ", " << u.second << ")";
}
template<class Con, class = decltype(begin(declval<Con>()))>
typename enable_if<!is_same<Con, string>::value, ostream&>::type
operator<<(ostream& out, const Con& con) { 
    out << "{";
    for (auto beg = con.begin(), it = beg; it != con.end(); ++it)
        out << (it == beg ? "" : ", ") << *it;
    return out << "}";
}
template<size_t i, class T> ostream& print_tuple_utils(ostream& out, const T& tup) {
    if constexpr(i == tuple_size<T>::value) return out << ")"; 
    else return print_tuple_utils<i + 1, T>(out << (i ? ", " : "(") << get<i>(tup), tup); 
}
template<class ...U> print_op(tuple<U...>) {
    return print_tuple_utils<0, tuple<U...>>(out, u);
}
// ACTUAL SOLUTION START HERE ////////////////////////////////////////////////////////////////
```

Funny enough, for this purpose of this post, I actually did a little clean up
for my template, so it is a bit different than some of my recent submissions.

It is not like _super short_, but compares to Erricto's template, I say
this is short enough, but still powerful. It also has one **feature** that's
I didn't see anywhere. Let's me explain.

### Always print to `stderr`
To print information to `stderr`, we can use `clog` or `cerr`. These `streams`
are almost equivalent, but `cerr` does not buffer the output. I see they are
the same though because adding `endl` to the end of each printing statement
automatically flushes out the buffer.  In my template, I use `clog` (or rather, a
macro called `clog`, more on that later). 

Here are some advantages of printing the debug information to `stderr`:
- First, we can separate the debug information from the program's output.
  Because if `stdout` is used instead (which a lot of people do), occasionally
  the submissions will get `WA` (wrong answer) verdict because of forgetting to
  remove the code for debugging.

- Second, the debug information can be redirected into a file rather than the
  terminal. So if the program is run like this:
    ```sh
    ./main < input.txt > output.txt 2> debug.log
    ```    
  or just add this line to the beginning of the `main()` function:
    ```c++
    freopen("debug.log", "w", stderr);
    ```
    
  we can see the whole debug output on our favorite editor instead of
  the limited terminal.

- And third, if we use a different stream than the `cout`, we can use macro
  to magically remove those debug lines. Check out my template again:
    ```c++
    #ifdef LOCAL_DEBUG   
    #   define clog cerr << flush << setw(__db_level * 2) << setfill(' ') << "" << setw(0)
    //...
    #else
    #   define clog if (0) cerr
    //...
    #endif
    ```
    
    If there is **not** a macro named `LOCAL_DEBUG` defined beforehand, there
    will be no debug printing. For example, if we have the following code:
    
    ```c++
    int a, b;
    cin >> a >> b;
    clog << "a = " << a << endl;
    clog << "b = " << b << endl;
    cout << (a + b) << endl;
    ```

    In case of **no** `LOCAL_DEBUG`, the code is transformed to:

    ```c++
    int a, b;
    cin >> a >> b;
    if (0) cerr << "a = " << a << endl;
    if (0) cerr << "b = " << b << endl;
    cout << (a + b) << endl;
    ```

    which effectively tells the compiler to just remove these codes out because
    they will never be executed.

    On the other hand, if `LOCAL_DEBUG` is defined, then it will be printed.
    But my `clog` macro in this case is a bit _terrifying_, so more on that later.
    To define `LOCAL_DEBUG`, one can define it when compiling the code.
    
    ```sh
    g++ -DLOCAL_DEBUG ./main.cpp -o main
    ```
    
### The `db()` macro
```c++
#define db(val) "["#val" = "<<(val)<<"] "
```
This is a very basic macro, very fast to write, and yet it is very useful.  Its
job is to save us a lot of keystrokes: it will concatenate the expression (that
is, what we passed to the macro) and the result of the expression, and wrap
them around a pair of square brackets.

We can rewrite the above example:
```c++
int a, b;
cin >> a >> b;
clog << db(a) << db(b) << endl;
cout << (a + b) << endl;
```
If we enter `2 3` into the `stdin`, we will get the following from the `stderr`:
```
[a = 2] [b = 3] 
```

which is great, because we don't have to write the name of the variable before
actually passing it value to `clog`.

But this is not just variable, but any kind of expression. For example:
```c++
clog << db(1) << db(2) << endl;
clog << db(gcd(6, 8)) << endl;
clog << db(string(10, '=')) << endl;
for (int i = 0; i < 5 ; ++i) {
    clog << db(i) << db(i * 2) << db(i * i)  << endl;
}
vector<int> odds = {1, 3, 5, 7, 9};
for (int i = 0; i < (int)odds.size(); ++i) {
    clog << db(i) << db(odds[i]) << db(odds[i] * 3 + 1) << endl;
}
```
The debugging output will be.
```
[1 = 1] [2 = 2] 
[gcd(6, 8) = 2] 
[string(10, '=') = ==========] 
[i = 0] [i * 2 = 0] [i * i = 0] 
[i = 1] [i * 2 = 2] [i * i = 1] 
[i = 2] [i * 2 = 4] [i * i = 4] 
[i = 3] [i * 2 = 6] [i * i = 9] 
[i = 4] [i * 2 = 8] [i * i = 16] 
[i = 0] [odds[i] = 1] [odds[i] * 3 + 1 = 4] 
[i = 1] [odds[i] = 3] [odds[i] * 3 + 1 = 10] 
[i = 2] [odds[i] = 5] [odds[i] * 3 + 1 = 16] 
[i = 3] [odds[i] = 7] [odds[i] * 3 + 1 = 22] 
[i = 4] [odds[i] = 9] [odds[i] * 3 + 1 = 28] 
```

If I don't have my debugging template, this will be the first macro I will
write (besides automatically commenting `clog` of course), and I actually can
just use this macro to debug without the other. This macro can also be used
with `cout` or any `ostream`, it is actually handy in some cases. For example,
when I generating test cases, I can print the expected result and my solution
result with this macro.

There are a handful of alternatives to this macro. Tourist’s template has a
macro called debug which can accept multiple arguments instead of one like
mine, but it does not work like mine. For example: `int a = 1, b = 2; debug(a,
b);` will produce `[a, b]: 1 2`. Here the expressions are printed first, then
their values. In the case of long-expression, I prefer the result next to the
expression. There are attempts to do that with macro accepting multiple
arguments, but they are just very long.

### The `debug_block` struct and `DB()` macro.
This is the one additional feature that I am proud of, and also the core of
this template. Let’s see the code once again.
```c++
#define CONCAT_(x, y) x##y
#define CONCAT(x, y) CONCAT_(x, y)
#ifdef LOCAL_DEBUG   
#   define clog cerr << setw(__db_level * 2) << setfill(' ') << "" << setw(0)
#   define DB() debug_block CONCAT(dbbl, __LINE__)
    int __db_level = 0;
    struct debug_block {
        debug_block() { clog << "{" << endl; ++__db_level; }
        ~debug_block() { --__db_level; clog << "}" << endl; }
    };
#else
#   define clog if (0) cerr
#   define DB(...)
#endif
```

The `debug_block` is very simple. It only changed the `__db_level`: add 1 when
an instance of this struct is created, and decrease it by 1 when the instance
is destroyed. `__db_level` is only used in the `clog` macro.  The `clog`
actually does a little thing before accepting the other values: it will print
out `2 * __db_level` spaces. This means when there is no instance of
`debug_block`, no spaces before printing. If there is one instance, 2 spaces
will be printed. And if there is `k` instance, `2 * k` spaces.

To use this struct, simply declare a variable of unique name inside a code
block.  All `clog` statements afterward will be automatically indented by 2.
Check out this example.
```c++
clog << "no indent" << endl;
debug_block first_db;                   // indent once
clog << "one indent" << endl;
clog << "same indent" << endl;
{
    debug_block second_db;              // indent twice
    clog << "more indent" << endl;
}
// dedent
int t = 1;
for (int i = 1; i <= 3; ++i) {
    debug_block third_db;               // indent again, but the level still is 2
    t *= i;
    clog << db(i) << db(t) << endl;
}
```

```
no indent
{
  one indent
  same indent
  {
    more indent
  }
  {
    [i = 1] [t = 1] 
  }
  {
    [i = 2] [t = 2] 
  }
  {
    [i = 3] [t = 6] 
  }
}
```

This works thanks to one of the features of C++: [Resource Acquisition Is
Initialization][RAII], or RAII for short. Broadly speaking, when the object is
created, its constructor will be called, and the destructor will be called only
when the instance is going out of its scope. This is also the principle of all
of the `stl` collections, `ifstream/ofstream`, `mutex`, ... They will
automatically free their resources when not needed, and for most of the case,
it is when they are going out of their scope.

What's about the `DB()` macro? It is also used for saving keystrokes:
instead of naming every instance of struct `debug_block`, it will generate a
name, based on the line number when the macro is called, and declare an
instance with that name. So the above example can be changed like following:
```c++
clog << "no indent" << endl;
DB();                               // <-- new here
clog << "one indent" << endl;
clog << "same indent" << endl;
{
    DB();                           // also here
    clog << "more indent" << endl;
}
int t = 1;
for (int i = 1; i <= 3; ++i) {
    DB();                           // and here
    t *= i;
    clog << db(i) << db(t) << endl;
}
```
And the result is the same.

Of cause, this macro is automatically removed when there is **no**
`LOCAL_DEBUG` macro.

This macro is **really** useful. For the problems with multiple test cases, this
macro will separate debug information for each test. It can be used in a
recursive function, producing an indent level for each recursive call. It
simply can just be used anywhere just to separate the computation logic.
This is the reason **I am proud of this macro**, and somehow I didn't see people
created something quite like this.

### The printing functions
Not everything can be printed to `std::ostream` (yet). But lucky for us, with
the power of C++, we add overloading functions for printing what every type
we like (except what already has that function).

Unlike Tourist, I only add 3 more basic printing functions, which are for
`std::pair`, `std::tuple` and general container (`std::vector`, `std::list`,
`std::set`, `std::map`, etc. ), except for `std::string` because it already
existed.

I think demonstration is better in this case:
```c++
// simple pair
pair<int, string> a = {123, "abc"};
clog << db(a) << endl;

// simple vector
vector<int> b = {2, 4, 6, 8};
clog << db(b) << endl;

// vector with pair
vector<pair<int, int>> c = { {1, 2}, {2, 4}, {4, 6} };
cout << db(c) << endl;

// map
map<string, double> length_unit = {
    {"m", 1},
    {"cm", 0.01},
    {"mm", 0.001},
    {"km", 1000}
};
clog << db(length_unit) << endl;

// tuple
clog << db(make_tuple(1, 2, 3, 'a', 'b', 'c')) << endl;
clog << db(make_tuple(a, b, c)) << endl;

// set of vector
set<vector<int>> s = {
    {1, 2, 3, 4, 5, 6},
    {1, 1, 2, 3, 5, 8},
    {1, 4, 9, 16, 25, 64},
};
clog << db(s) << endl;
```

And the output to `stderr`:
```
[a = (123, abc)] 
[b = {2, 4, 6, 8}] 
[length_unit = {(cm, 0.01), (km, 1000), (m, 1), (mm, 0.001)}] 
[make_tuple(1, 2, 3, 'a', 'b', 'c') = (1, 2, 3, a, b, c)] 
[make_tuple(a, b, c) = ((123, abc), {2, 4, 6, 8}, {(1, 2), (2, 4), (4, 6)})] 
[s = {{ '{{' }}1, 1, 2, 3, 5, 8}, {1, 2, 3, 4, 5, 6}, {1, 4, 9, 16, 25, 64}}] 
```

Let's see the code for the magic that I used ;).
```c++
#define print_op(...) ostream& operator<<(ostream& out, const __VA_ARGS__& u)
// DEBUGING TEMPLETE ////////////////////////////////////////////////////////////////////////
// ...
// for printing std::pair
template<class U, class V> print_op(pair<U, V>) {
    return out << "(" << u.first << ", " << u.second << ")";
}
// for printing collection
template<class Con, class = decltype(begin(declval<Con>()))>
typename enable_if<!is_same<Con, string>::value, ostream&>::type
operator<<(ostream& out, const Con& con) { 
    out << "{";
    for (auto beg = con.begin(), it = beg; it != con.end(); ++it)
        out << (it == beg ? "" : ", ") << *it;
    return out << "}";
}
// for printing std::tuple
template<size_t i, class T> ostream& print_tuple_utils(ostream& out, const T& tup) {
    if constexpr(i == tuple_size<T>::value) return out << ")"; 
    else return print_tuple_utils<i + 1, T>(out << (i ? ", " : "(") << get<i>(tup), tup); 
}
template<class ...U> print_op(tuple<U...>) {
    return print_tuple_utils<0, tuple<U...>>(out, u);
}
```

Firstly, the macro `print_op` is used to save a few keystrokes.  It
accepts a type and expands to the printing function (or rather `operator<<`)
signature.

The printing for `std::pair` is straightforward though.

Next is the printing function for general containers. First I need to check if
it is a _probable_ container, and here I check if it has the `begin()`
iterator. This is done by pulling out the type of the begin iterator of the
container type.  If it failed to do so, then it is not a container. Failing
here is not an error though, also because of a C++ feature: [Substitution
Failure Is Not An Error][SFINAE], or SFINAE. The next magic trick is checking
if the type is the same as `std::string`, which is done by
[`std::enable_if`][std::enable_if].  After all of the magic, printing is
also straightforward. The only downside of this approach is everything is on
one line (unlike python [pretty print][python-pprint]), but when the log is
opened on an editor, that does not matter as far as we can separate lines by
hand. Or we can use for-loop in the case of multiple-dimension containers.

And finally, the printing for `std::tuple`. I put it last because it is not
always necessary (a `struct` is preferred for more fields). Here I used a
helper function that prints out the tuple in the recursive style. We can
not use a simple for-loop like with containers because we don't know the size as
well as the fields' types of the tuple at the runtime. But we know this 
information in the compile-time, hence the use of the template parameter for
keeping track of the number of the printed fields.

And finally, because we add more printing functions to a custom type, the
`print_op` macro will come in handy. For example:

```c++
// a line with slope form: y = ax + b
struct Line {
    double a, b;
    Line(double a_, double b_): a(a_), b(b_) {}
    double operator()(double x) const {
        return a * x + b;
    }
    friend print_op(Line) {
        return out << "y = " << u.a << " * x " << showpos << u.b;
    }
};

struct Circle {
    double x, y, r;
    Circle(double x_, double y_, double r_) : x(x_), y(y_), r(r_) {
        assert(r >= 0);
    }
    friend print_op(Circle) {
        return out << "(x " << showpos << -u.x << ") ^ 2 + (y " << showpos << -u.y << ")^2 = " << u.r << "^2";
    }
};

// inside main
clog << Line(1, 2) << endl;
clog << Line(-1, 2) << endl;
clog << Circle(1, 2, 3) << endl;
```

And the output:
```
y = 1 * x +2
y = -1 * x +2
(x -1) ^ 2 + (y -2)^2 = +3^2
```

The output is meaningful enough that we can plug it onto [desmos].  Here is the
live example of the above output.

<iframe src="https://www.desmos.com/calculator/gesehakdnh?embed" width="500"
height="500" style="border: 1px solid #ccc" frameborder=0></iframe>

## Some tips for using this template
- For print array, instead of just printing out `db(a[i])`, index can also be
printed:
    ```c++
    clog << db(i) << db(a[i]) << endl;
    ```
Well, I do have a printing function for `std::vector`, but the above also
applied for the case where we want to print values that depend on the 
current index.
- A multiple-dimension array can also be print as above, but if there are a lot
of them, using `DB()` might help:
    ```c++
    for (int i = 0; i < n; ++i) {
        DB();
        clog << db(i) << endl;
        for (int j = 0; j < m; ++j) {
            clog << db(j) << db(a[i][j]) << endl;
        }
    }
    ```
- `DB()` macro can be used inside every kind of code block. To wrap a part of 
the log inside a `debug_block`, we can just use a simple code block around that  
part of the code.
- `DB()` macro can also be used in recursion, like `dfs`. Just don't run it on 
large input, otherwise, the output is too _wide_ to handle.
- `db()` macro can also be used inside `print_op`. It is OK-ish, but not too
clean.


## Conclusion
Well, this is my first actual post. I said that I might not write about
competitive programming, but it seems like I have some _OK-ish_ topics to share.

It is not what I intend to write in the first place: I actually planned
to write about debugging in CP in general. But firstly, that idea is based on
my debugging template, and secondly, I actually have to explain what in the
world is my template about. So I ended up with the first long blog post
just talking about how my code works. I do not regret tho, because explaining
this is necessary for the initial idea, and I also like to share my template
anyway, talking about _how cool my template is_.

With that all being said, I hope you enjoy this kind of technical post about
just a small piece of code, which I do proud of, and still used a lot.  See you
in the next post!

---

### Side note
I started this post on 07/30, but end up abundant it for about 2 weeks. I only
tried to finish this post because I reduce the goal from a post about debugging
to just about my template. So yeah, the first post, yay!


[tourist-codeforces-profile]: https://codeforces.com/profile/tourist
[tourist-debugging-template-1]: https://codeforces.com/contest/1540/submission/120602670
[tourist-debugging-template-2]: https://codeforces.com/contest/1553/submission/123310012

[Erricto-codeforces-profile]: https://codeforces.com/profile/Errichto
[Erricto-debugging-template]: https://codeforces.com/contest/1523/submission/117877943
[Erricto-debugging-template-explanation]: https://codeforces.com/blog/entry/67830

[Um_nik-codeforces-profile]: https://codeforces.com/profile/Um_nik
[Um_nik-debugging-template]: https://codeforces.com/contest/1552/submission/123756921

[how-to-debug-with-color]: https://codeforces.com/blog/entry/92669

[desmos]: https://www.desmos.com

[RAII]: https://en.cppreference.com/w/cpp/language/raii
[SFINAE]: https://en.cppreference.com/w/cpp/language/sfinae
[std::enable_if]: https://en.cppreference.com/w/cpp/types/enable_if

[python-pprint]: https://docs.python.org/3/library/pprint.html


{% comment %}
vim: spell spl=en nocindent autoindent
{% endcomment %}
