// MyCGDoc.cpp : implementation of the CMyCGDoc class
//

#include "stdafx.h"
#include "MyCG.h"

#include "MyCGDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyCGDoc

IMPLEMENT_DYNCREATE(CMyCGDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyCGDoc, CDocument)
	//{{AFX_MSG_MAP(CMyCGDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyCGDoc construction/destruction

CMyCGDoc::CMyCGDoc()
{
	// TODO: add one-time construction code here

}

CMyCGDoc::~CMyCGDoc()
{
}

BOOL CMyCGDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyCGDoc serialization

void CMyCGDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMyCGDoc diagnostics

#ifdef _DEBUG
void CMyCGDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyCGDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyCGDoc commands
