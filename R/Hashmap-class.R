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
#'  \item \code{all_keys()}: returns the \code{keys} of \code{H}
#'
#'  \item \code{all_values()}: returns the \code{values} of \code{H}
#'
#'  \item \code{clear()}: deletes all keys and values from \code{H}
#'
#'  \item \code{data()}: returns a named vector of \code{values} using
#'      the \code{keys} of \code{H} as names
#'
#'  \item \code{empty()}: returns \code{TRUE} if \code{H} is empty
#'      (e.g. immediately following a call to \code{clear}), else
#'      returns \code{FALSE}
#'
#'  \item \code{find_values(lookup_keys)}: returns the \code{values}
#'      associated with \code{lookup_keys} for existing key elements,
#'      and \code{NA} otherwise
#'
#'  \item \code{rehash(new_keys, new_values)}: deletes current
#'      \code{keys} and \code{values}, and reinitialize \code{H}
#'      with \code{new_keys} and \code{new_values}, where
#'      \code{new_keys} and \code{new_values} are allowed to be
#'      different SEXP types than the original \code{keys} and
#'      \code{values}
#'
#'  \item \code{set_values(more_keys, more_values)}: adds more
#'      key-value pairs to \code{H}, where existing key elements
#'      (\code{intersect(H$all_keys(), more_keys)}) will be
#'      updated with the corresponding elements in \code{more_values},
#'      and non-existing key elements
#'      \code{setdiff(H$all_keys(), more_keys)} will be inserted
#'      with the corresponding elements in \code{more_values}
#'
#'  \item \code{size()}: returns the size (number of key-value pairs)
#'      of (held by) \code{H}
#'
#' }
#' Additionally, the following two convenience methods which do
#' not require the use of \code{$}:
#'
#' \itemize{
#'
#'  \item \code{`[[`}: equivalent to \code{find_values(lookup_keys)}
#'
#'  \item \code{`[[<-`}: equivalent to
#'      \code{set_values(more_keys, more_values)}
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
#' any(duplicated(H$all_keys()))        #[1] FALSE
#'
#' all.equal(H[[z]], H$find_values(z))  #[1] TRUE
#'
#' ## hash map ordering is random
#' all.equal(
#'     sort(H[[x]]),
#'     sort(H$all_values()))  #[1] TRUE
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
#' H2 <- hashmap(H$all_keys(), H$all_values())
#'
#' all.equal(
#'     sort(H[[H2$all_keys()]]),
#'     sort(H2[[H$all_keys()]]))   #[1] TRUE
#'
#' H$set_values("A", round(pi, 5))
#'
#' H2[["A"]] <- round(pi, 5)
#'
#' ## still true
#' all.equal(
#'     sort(H[[H2$all_keys()]]),
#'     sort(H2[[H$all_keys()]]))
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
#' H3$rehash("D", "text")
#' H3$size()     #[1] 1
#'
#'
NULL
