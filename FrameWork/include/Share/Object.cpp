#include "Object.h"

CObject::CObject()
{

}
CObject::~CObject()
{

}

void CObject::AddRef()
{
	mRefCount++;
}

void CObject::Release()
{
	mRefCount--;
}
