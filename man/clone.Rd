% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/clone.R
\name{clone}
\alias{clone}
\title{Clone a Hashmap}
\usage{
clone(x)
}
\arguments{
\item{x}{an object created by a call to \code{hashmap}.}
}
\value{
a \code{Hashmap} identical to the input object.
}
\description{
\code{clone} creates a deep copy of a \code{Hashmap} so that
 modifications made to the cloned object do not affect the original object.
}
\details{
Since the actual cloning is done in C++, \code{y <- clone(x)} should
 be much more efficient than \code{y <- hashmap(x$keys(), x$values())}.
}
\examples{

x <- hashmap(letters[1:5], 1:5)

## shallow copy
y <- x
y[["a"]] <- 999

## original is affected
x[["a"]] == 999

z <- clone(x)
z[["c"]] <- 888

## original not affected
x[["c"]] == 888
}
\seealso{
\code{\link{hashmap}}
}
