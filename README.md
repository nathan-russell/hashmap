<!-- README.md is generated from README.Rmd. Please edit that file -->
hashmap
=======

[![Travis-CI Build Status](https://travis-ci.org/nathan-russell/hashmap.svg?branch=master)](https://travis-ci.org/nathan-russell/hashmap) [![MIT licensed](https://img.shields.io/badge/license-MIT-blue.svg)](./LICENSE) [![CRAN\_Status\_Badge](http://www.r-pkg.org/badges/version/hashmap)](http://cran.r-project.org/package=hashmap)

### Motivation

Unlike many programming languages, R does not implement a native hash table class. The typical workaround is to use `environment`s, taking advantage of the fact that these objects are, by default, internally hashed:

``` r
EE <- new.env(hash = TRUE)  ## equivalent to new.env()

set.seed(123)
vapply(LETTERS, function(x) {
      assign(x, rnorm(1), envir = EE)
      integer(0)
}, FUN.VALUE = integer(0), USE.NAMES = FALSE)

EE[["A"]]
#[1] -0.5604756

EE[["D"]]
#[1] 0.07050839

EE[["Z"]]
#[1] -1.686693
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

set.seed(123)
(HH <- hashmap(LETTERS, rnorm(26)))
## (character) => (numeric)  
##         [Z] => [-1.686693]
##         [Y] => [-0.625039]
##         [R] => [-1.966617]
##         [X] => [-0.728891]
##         [Q] => [+0.497850]
##         [P] => [+1.786913]
##       [...] => [...] 

HH[[c("A", "B")]]
#[1] -0.5604756 -0.2301775
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

What `hashmap` may lack in terms of flexibility it makes up for in two important areas: performance and ease-of-use. Let's begin with the latter by looking at some basic examples.

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

-   Value lookup can be performed by passing a vector of lookup keys to either of `[[` or `$find`:

    ``` r
    H[["a"]]
    #[1] -0.5604756

    H$find("b")
    #[1] -0.2301775

    H[[c("a", "c")]]
    #[1] -0.5604756  1.5587083

    H$find(c("b", "d"))
    #[1] -0.23017749  0.07050839
    ```

-   For non-existant lookup keys, `NA` is returned:

    ``` r
    H[[c("a", "A", "b")]]
    #[1] -0.5604756         NA -0.2301775
    ```

-   Use `$has_key` to check for the existance of individual keys, or `$has_keys` for a vector of keys:

    ``` r
    H$has_key("a")
    #[1] TRUE

    H$has_key("A")
    #[1] FALSE

    H$has_keys(c("a", "A", "b", "B"))
    #[1]  TRUE FALSE  TRUE FALSE
    ```

-   Modification of key-value pairs is done using either of `[[<-` or `$insert`. For non-existing keys, a new key-value pair will be inserted. For existing keys, the previous value will be overwritten:

    ``` r
    H[[c("a", "x")]]
    #[1] -0.5604756         NA

    H[[c("a", "x")]] <- c(1.5, 26.5)
    H[[c("a", "x")]]
    #[1]  1.5 26.5

    H$insert(c("a", "y", "z"), c(100, 200, 300))
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

-   `$keys` and `$values` return every key and value, respectively, and `$data` returns a named vector of values, using the keys as names:

    ``` r
    H[[c("A", "B", "C")]] <- 1:3

    H$keys()
    #[1] "C" "B" "A"

    H$values()
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

#### Implementation Overview

The key to `hashmap`'s ability to perform fast lookups and inserts is the fact that virtually everything is handled on the C++ level. This is achieved through use of the `RCPP_MODULE` macro which generates an S4 wrapper class (`Hashmap`) storing an external pointer to the underlying [C++ class](https://github.com/nathan-russell/hashmap/blob/master/inst/include/hashmap/HashMap.hpp). Consequently, once the initial price of constructing a `Hashmap` has been paid, subsequent lookups and inserts can be performed *very* quickly since the C++ object is persisted between function calls.

Generally speaking, exposing C++ classes to R means dealing with one or both of the following obstacles:

1.  R, unlike C++, does not have a concept of template classes, which means that one cannot simply expose, e.g. any of the STL containers, and expect R to "know what to do". The naive solution to this problem is for the developer to expose several different instances of said template class. This is far from ideal as it involves significant code duplication on the backend (especially for associative containers, which usually have at least two template parameters), and one class per template instance on the frontend (in R).

2.  Although nearly all major C++ compiler vendors have been providing feature-complete implementations of the C++11 standard for several years, R itself is implemented under the assumption of a C++98-compliant toolchain, and as a result packages which depend on more modern C++ features are not exactly encouraged. Furthermore, compiling source code on Windows machines requires the [Rtools extension](https://cran.r-project.org/bin/windows/Rtools/), which is not included with standard distributions of R. As the most current version of Rtools uses gcc 4.6.x (via MinGW), compiling C++11-based source code is not an option for many Windows users. The next [iteration of Rtools](https://github.com/rwinlib/r-base#readme) should be available sometime in the near future, so hopefully this will be less of an issue looking ahead.

To overcome both of the issues outlined above, `hashmap` relies on features provided by the [Boost C++ Libraries](http://www.boost.org/), which are conveniently made available through the [R package BH](https://github.com/eddelbuettel/bh). To address the second obstacle, `hashmap` employs a templated wrapper class [HashTemplate](https://github.com/nathan-russell/hashmap/blob/master/inst/include/hashmap/HashTemplate.hpp), leveraging the functionality of the C++98-compliant `boost::unordered_map` and `boost::hash` (in lieu of C++11's `std::unordered_map` and `std::hash`). Subsequently, the first problem can then be solved by encapsulating instances of `HashTemplate` within a `boost::variant` and making extensive use of `boost::static_visitor` and `boost::apply_visitor`.
