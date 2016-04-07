#' @title Internal hash map class
#'
#' @name Hashmap-class
#' @aliases Hashmap
#' @rdname Hashmap-class
#' @include classes.R
#'
#' @description A C++ class providing hash map functionality
#'      for atomic vectors
#'
#' @details A \code{Hashmap} object (\code{H}) resulting from a
#'      call to \code{hashmap(keys, values)} provides the following
#'      methods accessable via \code{$method_name}:
#'
#' \itemize{
#'
#'  \item \code{keys()}: returns the \code{keys} of \code{H}.
#'
#'  \item \code{values()}: returns the \code{values} of \code{H}.
#'
#'  \item \code{cache_keys()}: caches an internal vector with the
#'      hash table's current keys resulting in very low overhead
#'      calls to \code{keys()}. For larger hash tables this has a
#'      significant effect. However, any calls to modifying
#'      functions (\code{clear}, \code{insert}, etc.) will invalidate
#'      the cached state.
#'
#'  \item \code{cache_values()}: caches an internal vector with the
#'      hash table's current values resulting in very low overhead
#'      calls to \code{values()}. For larger hash tables this has a
#'      significant effect. However, any calls to modifying
#'      functions (\code{clear}, \code{insert}, etc.) will invalidate
#'      the cached state.
#'
#'  \item \code{keys_cached()}: returns \code{TRUE} if the hash table's
#'      keys are currently cached, and \code{FALSE} otherwise.
#'
#'  \item \code{values_cached()}: returns \code{TRUE} if the hash table's
#'      values are currently cached, and \code{FALSE} otherwise.
#'
#'  \item \code{erase(remove_keys)}: deletes entries for elements
#'      that exist in the hash table, and ignores elements that do not.
#'
#'  \item \code{clear()}: deletes all keys and values from \code{H}.
#'
#'  \item \code{data()}: returns a named vector of \code{values} using
#'      the \code{keys} of \code{H} as names.
#'
#'  \item \code{empty()}: returns \code{TRUE} if \code{H} is empty
#'      (e.g. immediately following a call to \code{clear}), else
#'      returns \code{FALSE}.
#'
#'  \item \code{find(lookup_keys)}: returns the \code{values}
#'      associated with \code{lookup_keys} for existing key elements,
#'      and \code{NA} otherwise.
#'
#'  \item \code{has_key(lookup_key)}: returns \code{TRUE} if
#'      \code{lookup_key} exists as a key in \code{H} and
#'      \code{FALSE} if it does not.
#'
#'  \item \code{has_keys(lookup_keys)}: vectorized equivalent of
#'      \code{has_key}.
#'
#'  \item \code{rehash(n_buckets)}: for the internal hash table, sets the
#'      number of buckets to at least \code{n} and the load factor to
#'      less than the max load factor.
#'
#'  \item \code{bucket_count()}: returns the current number of buckets
#'      in the internal hash table.
#'
#'  \item \code{hash_value(keys)}: compute hash values for the vector
#'      \code{keys} using the hash table's internal hash function. Note
#'      that \code{keys} need not exist in the hash table, but it must
#'      have the same type as the hash table's keys. This can be useful
#'      for investigating the efficacy of the object's hash function.
#'
#'  \item \code{renew(new_keys, new_values)}: deletes current
#'      \code{keys} and \code{values}, and reinitialize \code{H}
#'      with \code{new_keys} and \code{new_values}, where
#'      \code{new_keys} and \code{new_values} are allowed to be
#'      different SEXP types than the original \code{keys} and
#'      \code{values}.
#'
#'  \item \code{insert(more_keys, more_values)}: adds more
#'      key-value pairs to \code{H}, where existing key elements
#'      (\code{intersect(H$keys(), more_keys)}) will be
#'      updated with the corresponding elements in \code{more_values},
#'      and non-existing key elements
#'      \code{setdiff(H$keys(), more_keys)} will be inserted
#'      with the corresponding elements in \code{more_values}.
#'
#'  \item \code{size()}: returns the size (number of key-value pairs)
#'      of (held by) \code{H}.
#'
#' }
#' Additionally, the following two convenience methods which do
#' not require the use of \code{$}:
#'
#' \itemize{
#'
#'  \item \code{`[[`}: equivalent to \code{find(lookup_keys)}.
#'
#'  \item \code{`[[<-`}: equivalent to
#'      \code{insert(more_keys, more_values)}.
#'
#' }
#'
#' @examples
#'
#' x <- replicate(10e3,
#'     paste0(sample(letters, 12, TRUE),
#'            collapse = "")
#' )
#' y <- rnorm(length(x))
#' z <- sample(x, 100)
#'
#' H <- hashmap(x, y)
#'
#' H$empty()       #[1] FALSE
#' H$size()        #[1] 10000
#'
#' ## necessarily
#' any(duplicated(H$keys()))        #[1] FALSE
#'
#' all.equal(H[[z]], H$find(z))  #[1] TRUE
#'
#' ## hash map ordering is random
#' all.equal(
#'     sort(H[[x]]),
#'     sort(H$values()))  #[1] TRUE
#'
#' ## a named vector
#' head(H$data())
#'
#' ## redundant, but TRUE
#' all.equal(
#'     H[[names(head(H$data()))]],
#'     unname(head(H$data())))
#'
#' ## setting values
#' H2 <- hashmap(H$keys(), H$values())
#'
#' all.equal(
#'     sort(H[[H2$keys()]]),
#'     sort(H2[[H$keys()]]))   #[1] TRUE
#'
#' H$insert("A", round(pi, 5))
#'
#' H2[["A"]] <- round(pi, 5)
#'
#' ## still true
#' all.equal(
#'     sort(H[[H2$keys()]]),
#'     sort(H2[[H$keys()]]))
#'
#' ## changing SEXPTYPE of key or value must be explicit
#' H3 <- hashmap(c("A", "B", "C"), c(1, 2, 3))
#'
#' H3$size()     #[1] 3
#'
#' H3$clear()
#' H3$size()     #[1] 0
#'
#' ## not allowed
#' class(try(H3[["D"]] <- "text", silent = TRUE)) #[1] "try-error"
#'
#' ## okay
#' H3$renew("D", "text")
#' H3$size()     #[1] 1
#'
#'
NULL
