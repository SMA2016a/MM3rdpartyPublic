#pragma once

// CCameraControlMode �Ի���
#define UPSPIN					-1				         // �ع�ʱ��༭���ϼ�ͷ
#define DOWNSPIN				1				         // �ع��¼��༭���¼�ͷ
	
#define STEP_VSCROLL			10		
#define STEP_MOVE				50

#include <vfw.h>
#include "../sdk/inc/TUCamApi.h"                         // ����SDKͷ�ļ�
#include "afxwin.h"
#include "afxcmn.h"
#include <dbt.h>
#include "TUButton.h"

#define  PAGE_CNT 6                                     // �ܹ�6��TabС����
#define  MAKETAG(a,b,c,d) (a | (b << 8) | (c << 16) | (d << 24))

///#include <stdio.h>

#define TUDBG_PRINTF(format,...)	{char dbgMsg[1024] = {0}; sprintf_s(dbgMsg, "" format"", ##__VA_ARGS__); OutputDebugStringA(dbgMsg);}


class CCameraControlMode : public CDialog
{
	DECLARE_DYNAMIC(CCameraControlMode)

public:
	CCameraControlMode(CWnd* pParent = NULL);           // ��׼���캯��
	virtual ~CCameraControlMode();
	CDialog *m_tabPage[PAGE_CNT];                       // �ӶԻ���ָ��

	
    void InitDrawingResource();                         // ��ʼ��������Դ
    void UnInitDrawingResource();                       // ����ʼ��������Դ

    void InitInformation();                             // ��ʼ����Ϣ
    void InitControlRange();                            // ��ʼ���ؼ���Χ
    void EnableControl(BOOL bLiving = FALSE);           // �ؼ�ʹ��    
//  void EnableTriggerControl(BOOL bEnable = FALSE);    // ��������ʹ��
    void RefreshValue();                                // ˢ�¿ؼ�ֵ
    void UpdateExposureTime(DWORD dwExp);               // �����ع�ʱ�� 
    void UpdatePicview();                               // ˢ��Ԥ������

    void StartWaitForFrame();  
    void StopWaitForFrame();  
    
	int FindUSBKomPID(CString str);
	int FindUSBKomVID(CString str);
// �Ի�������
	enum { IDD = IDD_DLG_CTL}; 

protected:
	//LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam); // ���ô����ƶ�
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	HACCEL hAccKey;
public:

    static void __cdecl WaitForFrameThread(LPVOID lParam); // �ȴ������߳�ʵ��
	
	CFont				m_fntEdit;						// �������ģ�����������
	CString				m_strFilePath;					// �ļ���ַ
	BOOL				m_bShowScroll;					// �Ƿ���ʾ������

	int					m_nCamCtlView_Width;			// ������������
	int					m_nCamCtlView_Heigth;			// ����������߶�
	int					m_nFactScreen_Width;			// ʵ�ʴ��ڿ��
	int					m_nFactScreen_Heigth;			// ʵ�ʴ��ڸ߶�
	int					m_nScrollWindow_Y;				// ��Ļ�������ָ������������ԭ״��

	SCROLLINFO			m_Scrollinfo;					// ��������Ϣ

    /* �����ʼ������ */
    TUCAM_INIT          m_itApi;                        // ��ʼ��SDK����
    TUCAM_OPEN          m_opCam;                        // ���������

    BOOL                m_bWaitting;                    // �����������
    BOOL                m_bLiving;                      // Ԥ�����
    BOOL                m_bSaving;                      // ͼ�񱣴�
    int                 m_nCntSave;                     // �������
    int                 m_nFmtSave;                     // �����ʽ
    int                 m_nFmtCnt;                      // ��ʽ����
    char                m_cPath[MAX_PATH];              // ����·��

    /* λͼ���Ʋ��� */
    HANDLE              m_hThdDraw;                     // ��ʾ�߳̾��
    BITMAPINFOHEADER    m_bmpInfo;                      // λͼͷ����Ϣ
    HDC				    m_hDC;                          // ����λͼDC
    HDRAWDIB		    m_hDib;                         // ����λͼDIB
    TUCAM_FRAME         m_frame;                        // ֡����

    TUCAM_DRAW_INIT     m_itDraw;                       // ���Ƴ�ʼ������
    TUCAM_DRAW          m_drawing;                      // ���Ʋ���

    /* ֡�ʼ��� */
    DWORD               m_dwSTm;                        // ��ʼ����
    DWORD               m_dwITm;                        // ���ʱ��
    DWORD               m_dwFrmCnt;                     // ֡��ͳ��
    float               m_fFps;                         // ֡��

    /* ����������� */
    float               m_fScale;                       // ���ű���
    int                 m_nCurWidth;                    // ��ǰ���
    int                 m_nCurHeight;                   // ��ǰ�߶�
    int                 m_nCliWidth;                    // ��ǰ�ͻ��˿��
    int                 m_nCliHeight;                   // ��ǰ�ͻ��˸߶�
    int                 m_nDrawOffX;                    // ˮƽƫ��  
    int                 m_nDrawOffY;                    // ��ֱƫ��
    int                 m_nDrawWidth;                   // ���ƿ��
    int                 m_nDrawHeight;                  // ���Ƹ߶�

    /* ���� */
    BOOL                m_bTgrMode;                     // ����ģʽ
    BOOL                m_bTrigger;                     // ����״̬
    HANDLE              m_hThdTrigger;                  // �����߳̾��

    HANDLE              m_hThdWaitForFrame;             // ���ݲ����߳̾��

    int                 m_nCnt;

	UINT                m_uiTriFrame;                   // ����֡

    /*������������ ImageName+Times+Frames*/
    UINT                m_uiCapTimes;                   // ����
    UINT                m_uiCapFrames;                  // ֡��
    
	HDEVNOTIFY			m_hHDevNotify;
	HDEVNOTIFY			m_hLDevNotify;
	HDEVNOTIFY			m_hUDevNotify;
public:
	/*�������*/
	BOOL OnBnClickedBtnLive();

	/*���ROI��ť*/
	BOOL OnBtnRoiFunction();

	/*ˢ��ROI��ť*/
	BOOL OnRefreshRoiState();

	/*����Զ���ROI����*/
	BOOL OnChkRoiFunction();

	/*���¼��*/
	BOOL OnBtnRecord();

	/*���ɫ�׷�Χˢ��*/
	BOOL OnRefreshLevelRange();

	/*�������Raw��ťˢ��*/
	BOOL OnBtnRefreshRaw(BOOL bRaw = FALSE);

	/*�ı䴰�ڴ�С*/
	afx_msg void OnSize(UINT nType, int cx, int cy);

	/*�������¼�*/
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	/*���ù������ߴ��С*/
	void SetScrollSize(int nWidth, int nHeigth);

	/*�ر�����*/
    afx_msg void OnDestroy();

	/*INFO������ť*/
	afx_msg void OnBnClickedBtnInfo();

    afx_msg void OnBnClickedBtnControlcontrol();
    afx_msg void OnBnClickedBtnImagecapture();
    afx_msg void OnBnClickedBtnMorepara();
    afx_msg void OnBnClickedBtnRoi();
    afx_msg void OnBnClickedBtnTrigger();

	/*���ܽ���ѡ��*/
	//afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
    
	/*���ü��̰���*/
    virtual BOOL PreTranslateMessage(MSG* pMsg);



    void UpdateControl();

	INT                 m_nPicNum;    // ����ͼƬ����
    BOOL                m_bUseTm;
    CString             m_szPicName;  // �ļ�������Ϣ
	int                 m_nRecTm;     // ¼���ʱ

    int m_nTriMode;

	/* ¼�� */
    BOOL                m_bRecording;                   // �Ƿ�����¼��  
    
	/* ��ǩҳ */
	//CTabCtrl            m_tab;                          //���һ��CTab����ģ��

	
	/* ROI���� */
	BOOL               m_bChk;
	UINT               m_uHOffset;
    UINT               m_uVOffset;
    UINT               m_uWidth;
    UINT               m_uHeight;

	DWORD              m_dwFccHandler;                // ������������  

	BOOL               OnCaptureSnap();               // View ����
	BOOL               OnCaptureRecord();             // View ¼��
	BOOL               OnCaptureTriger();             // View ����
	BOOL               OnCapturePlay();               // Viww Ԥ��
    
	BOOL               m_bshow0;                      //��ʾ�Ƿ������ı�־λ
	BOOL               m_bshow1;                      //��ʾ�Ƿ������ı�־λ
	BOOL               m_bshow2;                      //��ʾ�Ƿ������ı�־λ
	BOOL               m_bshow3;                      //��ʾ�Ƿ������ı�־λ
	BOOL               m_bshow4;                      //��ʾ�Ƿ������ı�־λ
	BOOL               m_bshow5;                      //��ʾ�Ƿ������ı�־λ
	BOOL               m_bshow6;                      //��ʾ�Ƿ������ı�־λ
	BOOL               m_bshow7;                      //��ʾ�Ƿ������ı�־λ

	CRect              rectSmall;                     //����ʱ��ʾ��С��
	CRect              rectLarge;                     //��չʱ��ʾ���
	int                m_nheight;                     //�������߶�

    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
   
	afx_msg LRESULT OnDeviceChange(WPARAM wParam, LPARAM lParam);  //USB�ж���Ϣ��ȡ

    CTUButton m_btnInfo;
    CTUButton m_btnCtrl;
    CTUButton m_btnImgCap;
    CTUButton m_btnROI;
    CTUButton m_btnTrigger;
    CTUButton m_btnImgAdjustment;
};
