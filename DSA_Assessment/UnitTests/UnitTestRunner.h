// == == == == == == == == == == == == == == == == == == == == == == == == == == =
// <summary>
//  This file provides a public interface for the file
//  "UnitTestRunner.c".
// </summary>
// <project> Predictive Text </project>
// <author> Y3839090 </author>
// =====================================================

#ifndef UNITTESTRUNNER_H_INCLUDED
#define UNITTESTRUNNER_H_INCLUDED


/// ====
/// Defines
/// ====

/// ====
/// Type Definitions
/// ====
typedef struct UTRunner UTRunner;


/// ====
/// Constructors and Destructor
/// ====
UTRunner *utr_Constructor(int num, int(**funcs)(UTRunner *utr), char *name, FILE *log);
void utr_Deconstructor(UTRunner *utr);


/// ====
/// Functions
/// ====
int utr_RunTests(UTRunner *utr);
void utr_PrintMessage(UTRunner *utr, int passed, char *success, char *failure);


#endif // UNITTESTRUNNER_H_INCLUDED