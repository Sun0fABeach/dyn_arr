#define DISP(val) printf("Variable " #val " has value: %g\n"\
						 "Line: %d, File: %s, Function: %s\n",\
						 (double)val, __LINE__, __FILE__, __func__)

#define FV0(f) printf("Value of function call " #f "(): %g\n"\
					 "Line: %d, File: %s, Calling function: %s\n",\
					 (double)f(), __LINE__, __FILE__, __func__)
#define FV1(f, v1) printf("Value of function call " #f "(" #v1 "): %g\n"\
					 "Line: %d, File: %s, Calling function: %s\n",\
					 (double)f(v1), __LINE__, __FILE__, __func__)
#define FV2(f, v1, v2) printf("Value of function call " #f "(" #v1 ", " #v2 "): %g\n"\
					 "Line: %d, File: %s, Calling function: %s\n",\
					 (double)f(v1, v2), __LINE__, __FILE__, __func__)
#define FV3(f, v1, v2, v3) printf("Value of function call "\
					 #f "(" #v1 ", " #v2 ", " #v3 "): %g\n"\
					 "Line: %d, File: %s, Calling function: %s\n",\
					 (double)f(v1, v2, v3), __LINE__, __FILE__, __func__)
