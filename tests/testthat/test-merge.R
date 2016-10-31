library(testthat)
context("merge")

if (!require(hashmap)) {
    stop("hashmap not installed")
}

test_list_x <- list(
        ss_hash = hashmap(LETTERS[1:6], LETTERS[1:6]),
        sd_hash = hashmap(LETTERS[1:6], 1:6 + 0.5),
        si_hash = hashmap(LETTERS[1:6], 1:6),
        sb_hash = hashmap(LETTERS[1:6], (1:6) %% 2 > 0),
        sx_hash = hashmap(LETTERS[1:6], 1:6 + 2i),

        dd_hash = hashmap(1:6 + 0.5, 1:6 + 0.5),
        ds_hash = hashmap(1:6 + 0.5, LETTERS[1:6]),
        di_hash = hashmap(1:6 + 0.5, 1:6),
        db_hash = hashmap(1:6 + 0.5, (1:6) %% 2 > 0),
        dx_hash = hashmap(1:6 + 0.5, 1:6 + 2i),

        ii_hash = hashmap(1:6, 1:6),
        is_hash = hashmap(1:6, LETTERS[1:6]),
        id_hash = hashmap(1:6, 1:6 + 0.5),
        ib_hash = hashmap(1:6, (1:6) %% 2 > 0),
        ix_hash = hashmap(1:6, 1:6 + 2i)
)

test_list_y <- list(
        ss_hash = hashmap(LETTERS[5:10], LETTERS[5:10]),
        sd_hash = hashmap(LETTERS[5:10], 5:10 + 0.5),
        si_hash = hashmap(LETTERS[5:10], 5:10),
        sb_hash = hashmap(LETTERS[5:10], (5:10) %% 2 > 0),
        sx_hash = hashmap(LETTERS[5:10], 5:10 + 2i),

        dd_hash = hashmap(5:10 + 0.5, 5:10 + 0.5),
        ds_hash = hashmap(5:10 + 0.5, LETTERS[5:10]),
        di_hash = hashmap(5:10 + 0.5, 5:10),
        db_hash = hashmap(5:10 + 0.5, (5:10) %% 2 > 0),
        dx_hash = hashmap(5:10 + 0.5, 5:10 + 2i),

        ii_hash = hashmap(5:10, 5:10),
        is_hash = hashmap(5:10, LETTERS[5:10]),
        id_hash = hashmap(5:10, 5:10 + 0.5),
        ib_hash = hashmap(5:10, (5:10) %% 2 > 0),
        ix_hash = hashmap(5:10, 5:10 + 2i)
)

order_first <- function(df) df[order(df[,1]),]

t1 <- lapply(1:length(test_list_x), function(x) {
    txt.x <- names(test_list_x)[x]
    txt.y <- names(test_list_y)[x]

    hx <- test_list_x[[x]]
    hy <- test_list_y[[x]]

    xdf <- order_first(merge(hx, hy))
    tdf <- order_first(
        merge(
            hx$data.frame(),
            hy$data.frame(),
            by = "Keys"
        )
    )

    test_that(sprintf("(%s, %s): inner join works correctly", txt.x, txt.y), {
        expect_equivalent(tdf, xdf)
    })
})

t2 <- lapply(1:length(test_list_x), function(x) {
    txt.x <- names(test_list_x)[x]
    txt.y <- names(test_list_y)[x]

    hx <- test_list_x[[x]]
    hy <- test_list_y[[x]]

    xdf <- order_first(merge(hx, hy, type = "left"))
    tdf <- order_first(
        merge(
            hx$data.frame(),
            hy$data.frame(),
            by = "Keys",
            all.x = TRUE
        )
    )

    test_that(sprintf("(%s, %s): left join works correctly", txt.x, txt.y), {
        expect_equivalent(tdf, xdf)
    })
})

t3 <- lapply(1:length(test_list_x), function(x) {
    txt.x <- names(test_list_x)[x]
    txt.y <- names(test_list_y)[x]

    hx <- test_list_x[[x]]
    hy <- test_list_y[[x]]

    xdf <- order_first(merge(hx, hy, type = "right"))
    tdf <- order_first(
        merge(
            hx$data.frame(),
            hy$data.frame(),
            by = "Keys",
            all.y = TRUE
        )
    )

    test_that(sprintf("(%s, %s): right join works correctly", txt.x, txt.y), {
        expect_equivalent(tdf, xdf)
    })
})

t4 <- lapply(1:length(test_list_x), function(x) {
    txt.x <- names(test_list_x)[x]
    txt.y <- names(test_list_y)[x]

    hx <- test_list_x[[x]]
    hy <- test_list_y[[x]]

    xdf <- order_first(merge(hx, hy, type = "full"))
    tdf <- order_first(
        merge(
            hx$data.frame(),
            hy$data.frame(),
            by = "Keys",
            all = TRUE
        )
    )

    test_that(sprintf("(%s, %s): full outer join works correctly", txt.x, txt.y), {
        expect_equivalent(tdf, xdf)
    })
})
