.plugin <- Rcpp:::Rcpp.plugin.maker(
    libs = (function() {
        libs_path <- sprintf(
            "%s/hashmap/libs",
            installed.packages()["hashmap","LibPath"][1]
        )

        pattern <- sprintf("*hashmap%s", .Platform$dynlib.ext)
        lib_files <- list.files(
            libs_path,
            pattern = pattern,
            full.names = TRUE,
            recursive = TRUE
        )

        if (length(lib_files) < 1) {
            res <- "failed-to-locate-hashmap-shared-library"
        } else {
            res <- lib_files[1]
        }

        res
    })(),
    package = "hashmap"
)
