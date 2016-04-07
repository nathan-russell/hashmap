library(hashmap)
library(data.table)
library(ggvis)

env_hash <- function(keys, values) {
    EE <- new.env(size = length(keys))
    values <- as.list(values)
    names(values) <- keys
    list2env(values, envir = EE)
    invisible(EE)
}

env_find <- function(keys, env) {
    value_t <- class(env[[keys[1]]])
    vapply(keys, function(k) env[[k]],
           FUN.VALUE = vector(value_t, 1L),
           USE.NAMES = FALSE)
}

Keys <- replicate(10e5, {
    paste0(sample(letters, 10, TRUE),
           collapse = "")
})
Values <- rnorm(length(Keys))
Lookup <- sample(Keys, 10e2)

microbenchmark::microbenchmark(
    "Hash" = hashmap(Keys, Values),
    "Env" = env_hash(Keys, Values),
    times = 25L
)

E <- env_hash(Keys, Values)
H <- hashmap(Keys, Values)

all.equal(env_find(Lookup, E), H[[Lookup]])

microbenchmark::microbenchmark(
    "Hash" = H[[Lookup]],
    "Env" = env_find(Lookup, E),
    times = 500L
)

Res <- rbindlist(lapply(seq(5, length(Lookup), 10), function(x) {
    .dt <- data.table(
        microbenchmark::microbenchmark(
            "Hash" = H[[Lookup[1:x]]],
            "Env" = env_find(Lookup[1:x], E),
            times = 200L))[,Eval := x]
    .dt
}))

Summary <- Res[,.(Median = round(median(time) / 10e2, 2),
   Mean = round(mean(time) / 10e2, 2)),
   by = "expr,Eval"]

Summary %>%
    ggvis(~Eval, ~Median) %>%
    layer_points(fill = ~expr) %>%
    add_axis("x", title = "Key Lookups per Expression",
             title_offset = 40) %>%
    add_axis("y", title = "Expression Time (mu)",
             title_offset = 70)

Summary %>%
    ggvis(~Eval, ~log(Median)) %>%
    layer_points(fill = ~expr) %>%
    add_axis("x", title = "Key Lookups per Expression",
             title_offset = 40) %>%
    add_axis("y", title = "log(Expression Time) (mu)",
             title_offset = 40)
