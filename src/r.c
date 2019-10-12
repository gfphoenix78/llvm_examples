//
// Created by Hao Wu on 7/30/19.
//
#include <R.h>
#include <Rinternals.h>
#include <Rembedded.h>
#include <R_ext/Parse.h>
#include <stdio.h>
#include <stdlib.h>

SEXP try_eval(SEXP call, SEXP env) {
    int error = 0;
    SEXP ret;
    PROTECT(ret = R_tryEval(call, env, &error));
    if (error) {
        fprintf(stderr, "error=%d\n", error);
        exit(1);
//Rcpp::stop("R_tryEval() raised error");
    }
    return ret;
}
static void r_init()
{
    char *rargv[] = {"rclient", "--slave",
//                     "--silent",
                     "--no-save", "--no-restore"};
    int rargc = sizeof(rargv) / sizeof(rargv[0]);

    if (!Rf_initEmbeddedR(rargc, rargv)) {
//TODO: return an error
        fprintf(stderr, "can not start Embedded R");
        exit(1);
    }
    printf("init ok\n");
}
// PROTECT(rbody = mkString(code));
//	/*
//	  limit the number of expressions to be parsed to 2:
//		- the definition of the function, i.e. f <- function() {...}
//		- the call to the function f()
//
//	  kind of useful to prevent injection, but pointless since we are
//	  running in a container. I think -1 is equivalent to no limit.
//	*/
//	PROTECT(tmp = R_PARSEVECTOR(rbody, -1, &status));
//
//	if (tmp != R_NilValue) {
//		PROTECT(fun = VECTOR_ELT(tmp, 0));
//	} else {
//		PROTECT(fun = R_NilValue);
//	}
//
//	if (status != PARSE_OK) {
//		if (last_R_error_msg != NULL) {
//			errmsg = strdup(last_R_error_msg);
//		} else {
//			errmsg = strdup("Parse Error\n");
//			errmsg = realloc(errmsg, strlen(errmsg) + strlen(code) + 1);
//			errmsg = strcat(errmsg, code);
//		}
//		goto error;
//	}
//
//	UNPROTECT(3);
//	*errorOccurred = 0;
//	return fun;
int main()
{
//    const char *code = "f1<-function(){\nreturn (1)\n}\nf1()\n";
    const char *code = "as.vector(1:8)";
    SEXP r_code, res, tmp;
    ParseStatus status;

    setenv("R_HOME", "/usr/local/Cellar/r/3.6.1/lib/R", 1);
    r_init();

    PROTECT(r_code = mkString(code));
    PROTECT(tmp = R_ParseVector(r_code, -1, &status, R_NilValue));
    Rf_PrintValue(tmp);
    if (tmp != R_NilValue) {
        PROTECT(tmp = VECTOR_ELT(tmp, 0));
    } else {
        PROTECT(tmp = R_NilValue);
    }
    PROTECT(res = try_eval(tmp, R_GlobalEnv));

    printf("res = %p\n", res);
    Rf_PrintValue(res);
    UNPROTECT(2);
    return 0;
}