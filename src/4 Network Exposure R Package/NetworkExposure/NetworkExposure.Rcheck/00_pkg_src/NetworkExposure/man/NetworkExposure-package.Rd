\name{NetworkExposure-package}
\alias{NetworkExposure-package}
\alias{NetworkExposure}
\docType{package}
\title{
  Calculates Netowork Exposure
}
\description{
 Calculate Network Exposure Given W and Y matrix
}
\details{
  First load the library
  library(NetworkExposure)
Then run the library with W and Y file names
show_network_exposure("dyad_ties.csv","y.csv")
It'll save output to output.csv file
}
\author{
Your Name, email optional.

Maintainer: Your Name <your@email.com>
}
\references{
  This optional section can contain literature or other references for
  background information.
}
\keyword{ package }
\seealso{
  Optional links to other man pages
}
\examples{
  \dontrun{
    # load the library 
    library(NetworkExposure)
    # calculate network exposure
    show_network_exposure("dyad_ties.csv","y.csv")
  }
}
