// =====================================================
// <summary>
//  This file provides a public interface for the file
//  "PredictiveTextEngine.c".
// </summary>
// <project> Predictive Text </project>
// <author> Y3839090 </author>
// =====================================================

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

// Predicts a set of words from a partialWord
// Returns 1 if the partial word is a word
// Returns 0 if possible words are found
// Returns -1 if no word is found
int predictiveTextEngine_predictWords(PredictiveTextEngine *pte, char *partialWord, char **predictions, int numPredictions);

// Returns the maximum word length supported by the trie
int predictiveTextEngine_MaxWordLength();


#endif // PREDICTIVETEXTENGINE_H_INCLUDED
