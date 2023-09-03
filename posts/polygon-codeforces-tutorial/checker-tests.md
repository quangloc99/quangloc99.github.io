::: code-group
``` [Test 1. All correct case (with all character cases)]
=== Input ===
6
5
1 3 1 3 1
5
1 3 1 3 1
1
1
1
1
1
1
1
1
=== Output ===
no
NO
yes
yeS
yEs
yES
=== Answer ===
nO
No
Yes
YeS
YEs
YES
=== Verdict ===
OK
```

``` [Test 2. Output has fewer tokens]
=== Input ===
2
1
1
1
1
=== Output ===
yes
=== Answer ===
yes
yes
=== Verdict ===
PRESENTATION_ERROR
```

``` [Test 3. Answer has fewer tokens]
=== Input ===
2
1
1
1
1
=== Output ===
yes
yes
=== Answer ===
yes
=== Verdict ===
CRASHED
```

``` [Test 4. Output has wrong token format]
=== Input ===
1
1
1
=== Output ===
nice
=== Answer ===
yes
=== Verdict ===
PRESENTATION_ERROR
```

``` [Test 5. Output has more tokens]
=== Input ===
1
1
1
=== Output ===
yes
yes
=== Answer ===
yes
=== Verdict ===
PRESENTATION_ERROR
```

``` [Test 6. Answer ans more tokens]
=== Input ===
1
1
1
=== Output ===
yes
=== Answer ===
yes
yes
=== Verdict ===
CRASHED
```

``` [Test 7. Expected YES, found NO]
=== Input ===
1
1
1
=== Output ===
no
=== Answer ===
yes
=== Verdict ===
WRONG_ANSWER
```

``` [Test 8. Expected NO, found YES]
=== Input ===
1
5
1 3 1 3 1
=== Output ===
yes
=== Answer ===
no
=== Verdict ===
WRONG_ANSWER
```
:::
