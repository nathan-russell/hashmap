library(testthat)
context("Basic functionality")

hashmap_list <- function(n = 20) {
    if (!require(hashmap)) {
        stop("hashmap not installed")
    }

    ix <- as.integer(10e4 * runif(n))
    dx <- rnorm(n)
    sx <- replicate(n, {
        paste0(sample(letters, 10, TRUE), collapse = "")
    })
    bx <- rbinom(n, 1, 0.5) > 0

    list(
        ss_hash = hashmap(sx, sx),
        sd_hash = hashmap(sx, dx),
        si_hash = hashmap(sx, ix),
        sb_hash = hashmap(sx, bx),
        dd_hash = hashmap(dx, dx),
        ds_hash = hashmap(dx, sx),
        di_hash = hashmap(dx, ix),
        db_hash = hashmap(dx, bx),
        ii_hash = hashmap(ix, ix),
        is_hash = hashmap(ix, sx),
        id_hash = hashmap(ix, dx),
        ib_hash = hashmap(ix, bx)
    )
}

test_list <- hashmap_list()

xx <- lapply(1:length(test_list), function(x) {
    txt <- names(test_list)[x]
    test_that(sprintf("%s: data is values with keys as names", txt), {
        .data <- test_list[[x]]$data()
        .values <- test_list[[x]]$values()
        names(.values) <- test_list[[x]]$keys()
        expect_equal(.values, .data)
    })
})
