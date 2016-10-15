#' @title Save Hashmaps
#'
#' @name save_hashmap
#' @rdname save_hashmap
#'
#' @description \code{save_hashmap} writes a \code{Hashmap}'s data to the
#'  specified file, which can be passed to \code{\link{load_hashmap}} at a
#'  later point in time to recreate the object.
#'
#' @usage save_hashmap(x, file, overwrite = TRUE)
#'
#' @param x an object created by a call to \code{hashmap}.
#'
#' @param file a filename where the object's data will be saved.
#'
#' @param overwrite if \code{TRUE} (default) and \code{file} exists,
#'  it will be overwritten. If \code{FALSE} and \code{file} exists, an
#'  error is thrown.
#'
#' @return Nothing on success; an error on failure.
#'
#' @details Saving is done by calling \code{base::saveRDS} on the object's
#'  \code{data.frame} representation, \code{x$data.frame()}. Attempting to
#'  save an empty \code{Hashamp} results in an error.
#'
#' @seealso \code{\link{load_hashmap}}, \code{\link{saveRDS}}
#'
#' @examples
#' H <- hashmap(sample(letters[1:10]), sample(1:10))
#' tf <- tempfile()
#'
#' save_hashmap(H, tf)
#'
#' inherits(
#'     try(save_hashmap(H, tf, FALSE), silent = TRUE),
#'     "try-error"
#' )
#'
#' H$insert("zzzzz", 123L)
#' save_hashmap(H, tf)
#'
#' load_hashmap(tf)

#' @export save_hashmap
save_hashmap <- function(x, file, overwrite = TRUE) {
    if (!inherits(x, "Rcpp_Hashmap")) {
        msg <- sprintf(
            "Object '%s' is not a hashmap.",
            deparse(substitute(x))
        )
        stop(msg)
    }

    if (x$empty()) {
        stop("Attempt to save empty hashmap. Aborting.")
    }

    if (!overwrite && file.exists(file)) {
        msg <- sprintf(
            "File '%s' already exists. Aborting.",
            file
        )
        stop(msg)
    }

    saveRDS(x$data.frame(), file)
}
