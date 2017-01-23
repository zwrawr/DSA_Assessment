// =====================================================
// <summary>
//  This file provides a public interface for the file
//  "List.c". This is a generic list implimentation,
// </summary>
// <project> Predictive Text </project>
// <author> Y3839090 </author>
// =====================================================

#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED



/// ====
/// TypeDefs
/// ====
typedef struct List List;

/// ====
/// Constructors and Destructor
/// ====
List *list_Constructor(size_t itemSize);
void list_Deconstructor(List *list);


/// ====
/// Functions
/// ====
int list_Add(List *list, void *data);
int list_Read(List *list, int index, void *data);
int list_Remove(List *list, int index);
int list_Size(List *list);
int list_isEmpty(List *list);


#endif // LIST_H_INCLUDED
