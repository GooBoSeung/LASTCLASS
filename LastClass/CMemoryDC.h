//CMemoryDC.h
#ifndef _CMEMORYDC_H
#define _CMEMORYDC_H

#include <afxwin.h>

class CMemoryDC :public CDC {
private:
	CBitmap    m_bitmap;             // Offscreen bitmap (���� ȭ�鿡 ��Ÿ�� ��Ʈ��)
	CBitmap*  m_oldBitmap;         // bitmap originally found in CMemDC
	CDC*        m_pDC;                // Saves CDC passed in constructor
	CRect       m_rect;                 // Rectangle of drawing area.
	BOOL       m_bMemDC;         // TRUE if CDC really is a Memory DC.
public:
	CMemoryDC(CDC* pDC, const CRect* pRect = NULL) : CDC()
	{
		ASSERT(pDC != NULL);

		// Some initialization
		m_pDC = pDC;
		m_oldBitmap = NULL;
		m_bMemDC = !pDC->IsPrinting();    // �������� ���, FALSE �� ó��

										  // Get the rectangle to draw
		if (pRect == NULL)
		{
			pDC->GetClipBox(&m_rect);     // �޸� DC �� ó���� �ٽñ׸� ������ ����ϴ�.
		}
		else
		{
			m_rect = *pRect;                     // ���� ���� �Ű����� ������ ���� ���۸��մϴ�.
		}

		if (m_bMemDC)
		{
			// Create a Memory DC, �޸� DC �� �����, ������ �� ��ǥ���� Device ��ǥ�� �����մϴ�.
			CreateCompatibleDC(pDC);
			pDC->LPtoDP(&m_rect);

			// �޸� ��Ʈ���� ȭ�� ǥ���� �������� �����, �̸� �����մϴ�.
			m_bitmap.CreateCompatibleBitmap(pDC, m_rect.Width(), m_rect.Height());
			m_oldBitmap = SelectObject(&m_bitmap);

			// �Ʒ� �κе��� �� ó���� ����Դϴ�. ��, �����ڷ� ���� ���� CDC �� ���θ���,
			// ȭ�� ����, �׸���, ������ ���� ���� �Ű����� �״�� �����ϴ� ������.
			SetMapMode(pDC->GetMapMode());

			// ���� ������ ������ ũ��
			SetWindowExt(pDC->GetWindowExt());
			// ������ �����쿡 ���� ���� ���̴� ������ ũ�� ����
			SetViewportExt(pDC->GetViewportExt());

			// Device ��ǥ�� �� ��ǥ�� �����ϰ�, ������ ����ǥ�� ȭ���� ��Ÿ�� ������ ���� ������� �����Ѵ�.
			pDC->DPtoLP(&m_rect);
			SetWindowOrg(m_rect.left, m_rect.top);
		}
		else
		{
			// Make a copy of the relevent parts of the current 
			// DC for printing
			// ������ ����� ���
			m_bPrinting = pDC->m_bPrinting;
			m_hDC = pDC->m_hDC;
			m_hAttribDC = pDC->m_hAttribDC;
		}

		// Fill background, ����� ���� ���� �Ű����� DC �� �������� ä���.
		FillSolidRect(m_rect, pDC->GetBkColor());
	}

	~CMemoryDC()
	{
		if (m_bMemDC)
		{
			// Copy the offscreen bitmap ont����������o the screen. ȭ���� ���� ��Ʈ������ ��Ÿ����.
			m_pDC->BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(), this, m_rect.left, m_rect.top, SRCCOPY);

			// Swap back the original bitmap. ���� ��Ʈ������ ���� ��Ų��.
			SelectObject(m_oldBitmap);
		}
		else
		{
			// All we need to do is replace the DC with an illegal
			// value, this keeps us from accidentally deleting the 
			// handles associated with the CDC that was passed to 
			// the constructor.              
			m_hDC = m_hAttribDC = NULL;
		}
	}

	// Allow usage as a pointer    
	CMemoryDC* operator->()
	{
		return this;
	}

	// Allow usage as a pointer    
	operator CMemoryDC*()
	{
		return this;
	}
};

#endif // !_CMEMORYDC_H