// MyCGDoc.h : interface of the CMyCGDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYCGDOC_H__6B2FF3FA_37E9_4A32_9E83_4E1214FE44E0__INCLUDED_)
#define AFX_MYCGDOC_H__6B2FF3FA_37E9_4A32_9E83_4E1214FE44E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyCGDoc : public CDocument
{
protected: // create from serialization only
	CMyCGDoc();
	DECLARE_DYNCREATE(CMyCGDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyCGDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyCGDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyCGDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCGDOC_H__6B2FF3FA_37E9_4A32_9E83_4E1214FE44E0__INCLUDED_)
