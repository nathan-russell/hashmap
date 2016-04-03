<!-- README.md is generated from README.Rmd. Please edit that file -->
hashmap
=======

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
##    [B] => [2]   
##    [A] => [1]   
##  [...] => [...]

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

What `hashmap` may lack in terms of flexibility, it makes up for in two important areas: performance and ease-of-use.

#### Vectorized semantics

``` r
# construction 
set.seed(123)
(H <- hashmap(LETTERS[1:10], rnorm(10)))
##                  [I] => [-0.686852851893526]
##                  [H] => [-1.26506123460653] 
##                  [F] => [1.71506498688328]  
##                  [J] => [-0.445661970099958]
##                  [G] => [0.460916205989202] 
##                [...] => [...]  

# lookup
H[[c("A", "C", "D")]]
#[1] -0.56047565  1.55870831  0.07050839

# equivalently
H$find_values(c("A", "C", "D"))
#[1] -0.56047565  1.55870831  0.07050839

# NA for non-matching keys
H[[c("A", "Z")]]
#[1] -0.5604756         NA

# modification
H[[c("a", "b", "c")]] <- c(1, 2, 3)
H[[c("a", "b", "c")]]
#[1] 1 2 3

# equivalently
H$set_values(c("d", "e", "f"), 4:6)
H[[c("d", "e", "f")]]
#[1] 4 5 6

# values are replaced for existing keys
# and inserted for non-existing keys
H[[c("a", "e")]]
#[1] 1 5

H$has_key("zzz")
#[1] FALSE

H[[c("a", "e", "zzz")]] <- c(10, 20, 30)
H[[c("a", "e", "zzz")]]
#[1] 10 20 30
```

------------------------------------------------------------------------

#### Other methods

``` r
H$size()
#[1] 17
 
H$empty()
#[1] FALSE
 
H$clear()
 
H$size()
#[1] 0

H$empty()
#[1] TRUE

H$all_keys()
#character(0)
H$all_values()
#numeric(0)

# use rehash to change class 
# of keys or values 
H$rehash(as.integer(1:3), letters[1:3])

# data() returns a named vector
H$data()
#  3   2   1 
#"c" "b" "a" 

# unlike the venerable data.frame,
# hashmap won't take over your  
# console when accidentally printed 
H$rehash(
    replicate(10e4, {
        paste0(sample(letters, 10, TRUE), collapse = "")
    }),
    rnorm(10e4)
)

H$size()
#[1] 100000

H
##          [vmlxtdzcbe] => [-0.203635009795533] 
##          [qixrbmpmlf] => [0.596118314610788]  
##          [ouxarhfflk] => [-0.57885729882002]  
##          [qxdwrpblzv] => [-1.8888798168618]   
##          [uylwhlcqjx] => [-0.0251941830081833]
##                 [...] => [...]    
```

------------------------------------------------------------------------

#### Performance

TODO
