// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// show_network_exposure
void show_network_exposure(std::string dyad_ties_file, std::string y_file);
RcppExport SEXP _NetworkExposure_show_network_exposure(SEXP dyad_ties_fileSEXP, SEXP y_fileSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type dyad_ties_file(dyad_ties_fileSEXP);
    Rcpp::traits::input_parameter< std::string >::type y_file(y_fileSEXP);
    show_network_exposure(dyad_ties_file, y_file);
    return R_NilValue;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_NetworkExposure_show_network_exposure", (DL_FUNC) &_NetworkExposure_show_network_exposure, 2},
    {NULL, NULL, 0}
};

RcppExport void R_init_NetworkExposure(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
