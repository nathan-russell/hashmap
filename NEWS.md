# hashmap 0.2.2

## Bug Fixes

* Fixed a bug that was causing a build error on macOS.

# hashmap 0.2.1

## Improvements 

* By default, on non-Solaris platforms the internal hash table used is 
  `spp::sparse_hash_map` (from the C++ library 
  [`sparsepp`](https://github.com/greg7mdp/sparsepp)), rather than 
  `boost::unordered_map`. In all cases this should result in improved 
  performance and reduced memory usage; for a more detailed analysis 
  refer to the 
  [sparsepp benchmark](https://github.com/greg7mdp/sparsepp/blob/master/bench.md). 
  To revert to `boost::unordered_map` on these platforms, add 
  `-DHASHMAP_NO_SPP` to `PKG_CPPFLAGS` in the **Makevars** file and rebuild 
  the package. 

# hashmap 0.2.0

## New Features

* Added `save_hashmap` and `load_hashmap` function for saving and loading 
  `Hashmap` objects (#3).
  
* Added S3 `plot` method.

* Added `clone` function for creating deep copies. This is also reflected in 
  the C++ API via `HashMap::clone`. 
  
* Added S3 `merge` method.

## Improvements

* Integers are now printed correctly. 

* Key and value vector access is now automatically cached on the first call to 
  `$keys()` and `$values()`, respectively.

* Better handling of `Date` and `POSIXt` names for `$data()` (#4).
