<!-- README.md is generated from README.Rmd. Please edit that file -->
hashmap
=======

------------------------------------------------------------------------

### Motivation

Unlike many programming languages, R does not implement a native hash table class. The typical workaround is to use `environment`s, taking advantage of the fact that these objects are, by default, internally hashed:

``` r
EE <- new.env(hash = TRUE)  ## equivalent to new.env()

(EE$A <- 1)
#[1] 1

(EE[["B"]] <- 2)
#[1] 2

(EE[["A"]] <- 10)
#[1] 10

ls(EE)
#[1] "A" "B"
```

In many situations, this is a fine solution - lookups are reasonably fast, and `environment`s are highly flexible, allowing one to store virtually any type of R object (functions, lists, other environments, etc.). However, one of the major downsides to using `envinronment`s as hash tables is the inability to work with vector arguments:

``` r
EE[[c("A", "B")]]
#Error in EE[[c("A", "B")]] : 
#  wrong arguments for subsetting an environment

EE[c("A", "B")]
#Error in EE[c("A", "B")] : 
#  object of type 'environment' is not subsettable
```

This is rather unfortunate considering R's overwhelming tendency towards vectorized operations.

------------------------------------------------------------------------

### Solution

``` r
library(hashmap)

(HH <- hashmap(c("A", "B"), c(1, 2)))
## (character) => (numeric)  
##         [B] => [+2.000000]
##         [A] => [+1.000000]

(HH[["A"]] <- 10)
#[1] 10

HH[[c("A", "B")]]
#[1] 10  2
```

It is important to note that unlike the `environment`-based solution, `hashmap` does *NOT* offer the flexibilty to store arbitrary types of objects. Any combination of the following *atomic* vector types is currently permitted:

-   keys
    -   `integer`
    -   `numeric`
    -   `character`
-   values
    -   `logical`
    -   `integer`
    -   `numeric`
    -   `character`

------------------------------------------------------------------------

### Features

What `hashmap` may lack in terms of flexibility it makes up for in two important areas: performance and ease-of-use. Let's begin with the latter by looking at examples of typical uses.

#### Usage

-   A `Hashmap` is created by passing a vector of keys and a vector of values to `hashmap`:

    ``` r
    set.seed(123)
    H <- hashmap(letters[1:10], rnorm(10))
    H
    ## (character) => (numeric)  
    ##         [j] => [-0.445662]
    ##         [i] => [-0.686853]
    ##         [h] => [-1.265061]
    ##         [g] => [+0.460916]
    ##         [e] => [+0.129288]
    ##         [d] => [+0.070508]
    ##       [...] => [...] 
    ```

-   If the lengths of the two vectors are not equal, the longer object is truncated to the length of its counterpart, and a warning is issued:

    ``` r
    hashmap(letters[1:5], 1:3)
    ## (character) => (integer)
    ##         [c] => [3]      
    ##         [b] => [2]      
    ##         [a] => [1]      
    Warning message:
    In new_CppObject_xp(fields$.module, fields$.pointer, ...) :
      length(keys) != length(values)!

    hashmap(letters[1:3], 1:5)
    ## (character) => (integer)
    ##         [c] => [3]      
    ##         [b] => [2]      
    ##         [a] => [1]      
    Warning message:
    In new_CppObject_xp(fields$.module, fields$.pointer, ...) :
      length(keys) != length(values)!
    ```

-   Value lookup can be performed by passing a vector of lookup keys to either of `[[` or `$find_values`:

    ``` r
    H[["a"]]
    #[1] -0.5604756

    H$find_values("b")
    #[1] -0.2301775

    H[[c("a", "c")]]
    #[1] -0.5604756  1.5587083

    H$find_values(c("b", "d"))
    #[1] -0.23017749  0.07050839
    ```

-   For non-existant lookup keys, `NA` is returned:

    ``` r
     H[[c("a", "A", "b")]]
    #[1] -0.5604756         NA -0.2301775
    ```

-   Use `$has_key` to check for the existance of individual keys:

    ``` r
    H$has_key("a")
    #[1] TRUE

    H$has_key("A")
    #[1] FALSE
    ```

-   Modification of key-value pairs is done using either of `[[<-` or `$set_values`. For non-existing keys, a new key-value pair will be inserted. For existing keys, the previous value will be overwritten:

    ``` r
    H[[c("a", "x")]]
    #[1] -0.5604756         NA

    H[[c("a", "x")]] <- c(1.5, 26.5)
    H[[c("a", "x")]]
    #[1]  1.5 26.5

    H$set_values(c("a", "y", "z"), c(100, 200, 300))
    H[[c("a", "y", "z")]]
    #[1] 100 200 300
    ```

-   Use `$size` to check the number of key-value pairs, `$empty` to check if the hash table is empty, and `$clear` to delete all existing entries:

    ``` r
    H$size()
    #[1] 13

    H$empty()
    #[1] FALSE

    H$clear()

    H$empty()
    #[1] TRUE

    H$size()
    #[1] 0

    H
    ## [empty Hashmap]
    ```

-   `$all_keys` and `$all_values` return every key and value, respectively, and `$data` returns a named vector of values, using the keys as names:

    ``` r
    H[[c("A", "B", "C")]] <- 1:3

    H$all_keys()
    #[1] "C" "B" "A"

    H$all_values()
    #[1] 3 2 1

    H$data()
    #C B A 
    #3 2 1 
    ```

-   By default, only the first 6 key-value pairs of a `Hashmap` are printed, where `[...] => [...]` indicates that additional entries exist but are not displayed. This can be adjusted via `options()`:

    ``` r
    getOption("hashmap.max.print")
    #[1] 6

    H
    ## (character) => (numeric)  
    ##         [C] => [+3.000000]
    ##         [B] => [+2.000000]
    ##         [A] => [+1.000000]

    H[[letters[1:10]]] <- rnorm(10)
    H
    ## (character) => (numeric)  
    ##         [j] => [-0.472791]
    ##         [i] => [+0.701356]
    ##         [h] => [-1.966617]
    ##         [g] => [+0.497850]
    ##         [e] => [-0.555841]
    ##         [d] => [+0.110683]
    ##       [...] => [...]

    options(hashmap.max.print = 15)
    H
    ## (character) => (numeric)  
    ##         [j] => [-0.472791]
    ##         [i] => [+0.701356]
    ##         [h] => [-1.966617]
    ##         [g] => [+0.497850]
    ##         [e] => [-0.555841]
    ##         [d] => [+0.110683]
    ##         [c] => [+0.400772]
    ##         [f] => [+1.786913]
    ##         [b] => [+0.359814]
    ##         [a] => [+1.224082]
    ##         [C] => [+3.000000]
    ##         [B] => [+2.000000]
    ##         [A] => [+1.000000]
    ```

------------------------------------------------------------------------

#### Performance

TODO
