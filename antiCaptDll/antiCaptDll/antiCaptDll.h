#include "cv.h"
#include "highgui.h"

// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� ANTICAPTDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// ANTICAPTDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef ANTICAPTDLL_EXPORTS
#define ANTICAPTDLL_API __declspec(dllexport)
#else
#define ANTICAPTDLL_API __declspec(dllimport)
#endif

// �����Ǵ� antiCaptDll.dll ������
class ANTICAPTDLL_API CantiCaptDll {
public:
	CantiCaptDll(void);
	// TODO: �ڴ�������ķ�����
};

extern ANTICAPTDLL_API int nantiCaptDll;

ANTICAPTDLL_API int fnantiCaptDll(void);


//==========================================
ANTICAPTDLL_API void tyPreprocess(char* in, char* out);
ANTICAPTDLL_API char* tyKnow(char* in);
ANTICAPTDLL_API void tyTinyPreprocess(char* in, char* out);
ANTICAPTDLL_API void tyLinePreprocess(char* in, char* out);