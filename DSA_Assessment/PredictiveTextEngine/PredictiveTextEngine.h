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
char *predictWord(char *partialWord);



#endif // PREDICTIVETEXTENGINE_H_INCLUDED
