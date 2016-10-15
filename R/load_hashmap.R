#' @title Load Hashmaps
#'
#' @name load_hashmap
#' @rdname load_hashmap
#'
#' @description \code{load_hashmap} reads a file created by a call to
#'  \code{\link{save_hashmap}} and returns a \code{Hashmap} object.
#'
#' @usage load_hashmap(file)
#'
#' @param file the name of a file previously created by a call to
#'  \code{save_hashmap}.
#'
#' @return A \code{Hashmap} object on success; an error on failure.
#'
#' @details The object returned will contain all of the same key-value
#'  pairs that were present in the original \code{Hashmap} at the time
#'  \code{save_hashmap} was called, but they are not guaranteed to be
#'  in the same order, due to rehashing.
#'
#' @seealso \code{\link{save_hashmap}}
#'
#' @examples
#' H <- hashmap(sample(letters[1:10]), sample(1:10))
#' tf <- tempfile()
#'
#' save_hashmap(H, tf)
#'
#' H2 <- load_hashmap(tf)
#' all.equal(
#'     sort(H$find(H2$keys())),
#'     sort(H2$values())
#' )
#'
#' all.equal(
#'     H$data.frame(),
#'     readRDS(tf)
#' )

#' @export load_hashmap
load_hashmap <- function(file) {
    hash_data <- readRDS(file)
    hashmap(hash_data[[1]], hash_data[[2]])
}
