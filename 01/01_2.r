a <- function(n){ return(n) }
b <- function(n){ return(sqrt(n)) }
cc <- function(n){ return(log(n,2)) }
d <- function(n){ return(log(log(n, 2),2)) }
e <- function(n){ return((log(n,2))*(log(n,2))) }
f <- function(n){ return(n/(log(n,2))) }
g <- function(n){ return(sqrt(n)*((log(n,2))^2)) }
h <- function(n){ return((1/3)^n) }
i <- function(n){ return((3/2)^n) }
j <- function(n){ return(0*n+14) }



plot(a, xlim=c(1, 100), ylim=c(0,100))
par(new=T)
plot(b, col="red", xlim=c(1, 100), ylim=c(0,100))
par(new=T)
plot(cc, col="blue", xlim=c(1, 100), ylim=c(0,100))
par(new=T)
plot(d, col="green", xlim=c(1, 100), ylim=c(0,100))
par(new=T)
plot(e, col="yellow", xlim=c(1, 100), ylim=c(0,100))
par(new=T)
plot(f, col="orange", xlim=c(1, 100), ylim=c(0,100))
par(new=T)
plot(g, col="purple", xlim=c(1, 100), ylim=c(0,100))
par(new=T)
plot(h, col="cyan", xlim=c(1, 100), ylim=c(0, 100))
par(new=T)
plot(i, col="gray", xlim=c(1, 100), ylim=c(0,100))
par(new=T)
plot(j, col="pink", xlim=c(1, 100), ylim=c(0,100))

