#include <Windows.h>
#include <math.h>
#include "resource.h"
#define GR 0.4
#define PI 3.14159265

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE gi;
HWND hDlgWnd, hSpeed, hDegree, hY, hOK;
int iSpeed, iDegree, iX, iY;
RECT wndRect;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	gi = hInstance;
	iX = 0;
	iY = 200;
	iSpeed = 10;
	iDegree = 45;

	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (uMsg) {
	case WM_INITDIALOG:
		hDlgWnd = hDlg;
		hSpeed = GetDlgItem(hDlg, IDC_EDIT1);
		hDegree = GetDlgItem(hDlg, IDC_EDIT2);
		hY = GetDlgItem(hDlg, IDC_EDIT3);
		hOK = GetDlgItem(hDlg, IDOK);
		SetDlgItemInt(hDlg, IDC_EDIT1, 10, FALSE);
		SetDlgItemInt(hDlg, IDC_EDIT2, 45, FALSE);
		SetDlgItemInt(hDlg, IDC_EDIT3, 200, FALSE);
		SendMessage(hSpeed, EM_SETLIMITTEXT, 3, 0);
		SendMessage(hDegree, EM_SETLIMITTEXT, 3, 0);
		SendMessage(hY, EM_SETLIMITTEXT, 3, 0);
		GetWindowRect(hDlg, &wndRect);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			iSpeed = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, FALSE);
			iDegree = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, FALSE);
			iY = GetDlgItemInt(hDlg, IDC_EDIT3, NULL, FALSE);
			InvalidateRect(hDlg, NULL, TRUE);
			return TRUE;
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return TRUE;
		}
		return FALSE;
	case WM_PAINT:
		hdc = BeginPaint(hDlg, &ps);
		iX = 0;
		MoveToEx(hdc, iX, iY, NULL);
		float t = 0;
		float x = iX, y = iY;
		float XSpeed = iSpeed * cosf((float)iDegree*PI/180);
		float YSpeed = -(iSpeed * sinf((float)iDegree*PI/180));
		while (t < 10 && iX < wndRect.right && iY < wndRect.bottom)
		{
			x += XSpeed;
			y += YSpeed;
			YSpeed += GR;
			LineTo(hdc, x, y);
			t += 0.1f;
		}
		EndPaint(hDlg, &ps);
		return TRUE;
	}
	return FALSE;
}