
#include "../inc/typedef.h"
#include "../exception/exception.h"

#include "list_double_link.h"


/// @Brief
///  Create double linked list memery vessle.
/// @Param
///  _pSLstMem: The pointer of the list memery.
///  _lstSz: The size of the specified memery.
/// @Return
///  Exception code, contain Error code and warn code.
///  @Ref eExcpt_t
eExcpt_t DList_Create( SDLinkNode_t *_pDLstMem, const long _lstSz )
{

    return ERR_SUCCESS;
} // End DList_Create()

/// @Brief
///  Insert one element into the empty node of the specified list.
/// @Param
///  _pSLst: The pointer of the list will be inserted.
///  _e: The element want to insert into list.
/// @Return
///  Exception code, contain Error code and warn code.
///  @Ref eExcpt_t
eExcpt_t DList_Insert( SDLinkNode_t *_pSLst, const SDLinkNode_t _e )
{

    return ERR_SUCCESS;
} // End DList_Insert()

/// @Brief
///  Delete one element from the specified list.
/// @Param
///  _pSLst: The pointer of the list will be deleted.
///  _e: The element want to delete in the specified list.
/// @Return
///  Exception code, contain Error code and warn code.
///  @Ref eExcpt_t
eExcpt_t DList_Delete( SDLinkNode_t *_pSLst, const SDLinkNode_t _e )
{

    return ERR_SUCCESS;
} // End DList_Delete()
