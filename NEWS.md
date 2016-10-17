# hashmap 0.2.0

## New Features

* Added `save_hashmap` and `load_hashmap` function for saving and loading 
  `Hashmap` objects (#3).
  
* Added S3 `plot` method.

* Added `clone` function for creating deep copies. This is also reflected in 
  the C++ API via `HashMap::clone`. 

## Improvements

* Integers are now printed correctly. 

* Key and value vector access is now automatically cached on the first call to 
  `$keys()` and `$values()`, respectively.

* Better handling of `Date` and `POSIXt` names for `$data()` (#4).
