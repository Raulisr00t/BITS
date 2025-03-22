#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <Bits.h>
#include <atlcomcli.h>

int Error(HRESULT hr) {
	printf("[!] Error: 0x%X", GetLastError());
	return hr;
}

int main(int argc, const char* argv[]) {

	HRESULT hr;
	LPCWSTR url = L"https://link.testfile.org/15MB";
	CHAR userProfile[MAX_PATH];
	CHAR PATH[MAX_PATH];

	GetEnvironmentVariableA("USERPROFILE", userProfile, MAX_PATH);

	sprintf(PATH, "%s\\AppData\\Local\\Temp\\15mb.bin", userProfile);

	wchar_t wFullPath[MAX_PATH];
	MultiByteToWideChar(CP_ACP, 0, PATH, -1, wFullPath, MAX_PATH);

	LPCWSTR file = wFullPath;
	wprintf(L"[+] Path: %ls\n", file);

	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

	CComPtr<IBackgroundCopyManager> mgr;

	hr = mgr.CoCreateInstance(__uuidof(BackgroundCopyManager));
	
	if (FAILED(hr)) {
		return Error(hr);
	}

	CComPtr<IBackgroundCopyJob> job;
	GUID id;

	hr = mgr->CreateJob(L"TestJOB", BG_JOB_TYPE_DOWNLOAD, &id, &job);
	
	if (FAILED(hr)) {
		return Error(hr);
	}

	hr = job->AddFile(url, file);

	if (FAILED(hr)) {
		return Error(hr);
	}

	hr = job->Resume();

	if (FAILED(hr)) {
		return Error(hr);
	}

	BG_JOB_STATE state;
	for (;;) {
		job->GetState(&state);
		if (state == BG_JOB_STATE_ERROR || state == BG_JOB_STATE_TRANSFERRED)
			break;

		printf(".");
		Sleep(500);
	}

	if (state == BG_JOB_STATE_TRANSFERRED) {
		job->Complete();
		printf("[+] SUCCESS\n");
	}

	else {
		CComPtr<IBackgroundCopyError> err;
		job->GetError(&err);
		PWSTR text;
		err->GetErrorDescription(LANG_USER_DEFAULT, &text);

		if (SUCCEEDED(hr)) {
			printf("[!] ERROR:%ws\n", text);
			CoTaskMemFree(text);
		}
	}

	return 0;
}