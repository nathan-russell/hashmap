library(testthat)
context("Date and POSIXct")

kd <- Sys.Date() + 1:20
vd <- Sys.Date() + 21:40

kdt <- as.POSIXct(sprintf("%s", Sys.time() + 1:20),
                  tz = Sys.timezone())
vdt <- as.POSIXct(sprintf("%s", Sys.time() + 21:40),
                  tz = Sys.timezone())

dh <- hashmap(kd, vd)
dth <- hashmap(kdt, vdt)

test_that("Date: class is preserved for keys", {
    expect_equal(class(dh$keys()), class(kd))
})

test_that("Date: class is preserved for values", {
    expect_equal(class(dh$values()), class(vd))
})

test_that("POSIXct: class is preserved for keys", {
    expect_equal(class(dth$keys()), class(kdt))
})

test_that("POSIXct: class is preserved for values", {
    expect_equal(class(dth$values()), class(vdt))
})

test_that("POSIXct: tzone is preserved for keys", {
    expect_equal(attr(dth$keys(), "tzone"), attr(kdt, "tzone"))
})

test_that("POSIXct: tzone is preserved for values", {
    expect_equal(attr(dth$values(), "tzone"), attr(vdt, "tzone"))
})
