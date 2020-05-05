library(testthat)
# message(getwd())
# Rcpp::sourceCpp('src/network_exposure.cpp')
correct <- readRDS("../../test_result.rds")
correct <- na.omit(correct)
show_network_exposure("dyad_ties.csv","y.csv")
current <- read.csv("../../output.csv")
current <- na.omit(current)

test_that("Running tests", {
    for(id in current$id){
        message(current[current$id==id,"E_value"])
        message(correct[correct$id==id,"E_value"])
        expect_true(current[current$id==id,"E_value"]== correct[correct$id==id,"E_value"],label = 
                        paste0("Failed on ",id))
    }
})


