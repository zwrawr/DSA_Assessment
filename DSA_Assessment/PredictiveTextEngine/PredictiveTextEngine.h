#ifndef PREDICTIVETEXTENGINE_H_INCLUDED
#define PREDICTIVETEXTENGINE_H_INCLUDED


/// ====
/// Defines
/// ====


/// ====
/// Type Definitions
/// ====
typedef struct PredictiveTextEngine PredictiveTextEngine;


/// ====
/// Constructors and Destructor
/// ====
PredictiveTextEngine *predictiveTextEngine_Constructor(void);
void predictiveTextEngine_Deconstructor(PredictiveTextEngine *predictiveTextEngine);


/// ====
/// Functions
/// ====

// Predicts a word from a partialWord
// Returns 1 if the partial word is a word
// Returns 0 if possible word is found
// Returns -1 if no word is found
int predictiveTextEngine_predictWord(PredictiveTextEngine *pte, char *partialWord, char* buf);



#endif // PREDICTIVETEXTENGINE_H_INCLUDED
