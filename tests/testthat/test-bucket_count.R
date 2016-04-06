library(testthat)
context("Basic bucket_count")

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
    xx <- complex(real = round(runif(20) * 10e4, 4),
                  imaginary = round(runif(20) * 10e4, 4))

    list(
        ss_hash = hashmap(sx, sx),
        sd_hash = hashmap(sx, dx),
        si_hash = hashmap(sx, ix),
        sb_hash = hashmap(sx, bx),
        sx_hash = hashmap(sx, xx),

        dd_hash = hashmap(dx, dx),
        ds_hash = hashmap(dx, sx),
        di_hash = hashmap(dx, ix),
        db_hash = hashmap(dx, bx),
        dx_hash = hashmap(dx, xx),

        ii_hash = hashmap(ix, ix),
        is_hash = hashmap(ix, sx),
        id_hash = hashmap(ix, dx),
        ib_hash = hashmap(ix, bx),
        ix_hash = hashmap(ix, xx)
    )
}

test_list <- hashmap_list()

xx <- lapply(1:length(test_list), function(x) {
    txt <- names(test_list)[x]
    test_that(sprintf("%s: bucket_count is greater than zero", txt), {
        expect_true(test_list[[x]]$bucket_count() > 0)
    })
})
