#include "WMIwrapper.h"

namespace hwinfo {
	namespace wmi {

		struct COMData {
			IWbemLocator* pLoc = nullptr;
			IWbemServices* pSvc = nullptr;
			bool initialized = false;
		};

		COMData comData;

		template <typename T>
		bool _queryWMI(const std::string& WMIClass, std::string field, std::vector<T>& value,
			const std::string& serverName = "ROOT\\CIMV2") {

			if (!comData.initialized)
				return false;

			std::string query("SELECT " + field + " FROM " + WMIClass);


			HRESULT hres;
			IEnumWbemClassObject* pEnumerator = nullptr;
			hres = comData.pSvc->ExecQuery(bstr_t(L"WQL"), bstr_t(std::wstring(query.begin(), query.end()).c_str()),
				WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, nullptr, &pEnumerator);
			if (FAILED(hres))
				return false;

			IWbemClassObject* pclsObj = nullptr;
			ULONG uReturn = 0;
			while (pEnumerator) {
				pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);

				if (!uReturn) {
					break;
				}

				VARIANT vtProp;
				pclsObj->Get(std::wstring(field.begin(), field.end()).c_str(), 0, &vtProp, nullptr, nullptr);

				if (std::is_same<T, long>::value || std::is_same<T, int>::value) {
					value.push_back((T)vtProp.intVal);
				}
				else if (std::is_same<T, bool>::value) {
					value.push_back((T)vtProp.boolVal);
				}
				else if (std::is_same<T, unsigned>::value) {
					value.push_back((T)vtProp.uintVal);
				}
				else if (std::is_same<T, unsigned short>::value) {
					value.push_back((T)vtProp.uiVal);
				}
				else if (std::is_same<T, long long>::value) {
					value.push_back((T)vtProp.llVal);
				}
				else if (std::is_same<T, unsigned long long>::value) {
					value.push_back((T)vtProp.ullVal);
				}
				else {
					// TODO: this might cause issues with MinGW. fix this in another way than using the macros
#if defined(__MINGW32__) || defined(__MINGW64__)
					;
#else
					value.push_back((T)((bstr_t)vtProp.bstrVal).copy());
					// BSTR val = SysAllocString(vtProp.bstrVal);
					// value.push_back((bstr_t)val);
#endif
				}

				VariantClear(&vtProp);
				pclsObj->Release();
			}

			if (value.empty()) {
				value.resize(1);
			}

			if (pEnumerator)
				pEnumerator->Release();
			return true;
		}

		bool initializeCOMLibrary() {

			if (comData.initialized)
				return true;

			HRESULT hres;
			hres = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
			if (FAILED(hres)) {
				return false;
			}
			hres = CoInitializeSecurity(nullptr, -1, nullptr, nullptr, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE,
				nullptr, EOAC_NONE, nullptr);

			if (FAILED(hres)) {
				CoUninitialize();
				return false;
			}

			comData.pLoc = nullptr;
			hres = CoCreateInstance(CLSID_WbemLocator, nullptr, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&comData.pLoc);
			if (FAILED(hres)) {
				CoUninitialize();
				return false;
			}

			comData.pSvc = nullptr;
			hres = comData.pLoc->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), nullptr, nullptr, nullptr, 0, nullptr, nullptr, &comData.pSvc);
			if (FAILED(hres)) {
				comData.pLoc->Release();
				CoUninitialize();
				return false;
			}

			hres = CoSetProxyBlanket(comData.pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, nullptr, RPC_C_AUTHN_LEVEL_CALL,
				RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE);
			if (FAILED(hres)) {
				comData.pSvc->Release();
				comData.pLoc->Release();
				CoUninitialize();
				return false;
			}

			comData.initialized = true;
			return true;
		}

		bool closeCOMLibrary() {
			if (!comData.initialized)
				return false;

			if (comData.pSvc) {
				comData.pSvc->Release();
				comData.pSvc = nullptr;
			}

			if (comData.pLoc) {
				comData.pLoc->Release();
				comData.pLoc = nullptr;
			}

			CoUninitialize();
			comData.initialized = false;
			return true;
		}

		bool queryWMI(const std::string& WMIClass, std::string field, std::vector<wchar_t*>& value, const std::string& serverName) {
			return _queryWMI(WMIClass, field, value, serverName);
		}

		bool queryWMI(const std::string& WMIClass, std::string field, std::vector<const wchar_t*>& value, const std::string& serverName) {
			return _queryWMI(WMIClass, field, value, serverName);
		}

		bool queryWMI(const std::string& WMIClass, std::string field, std::vector<unsigned long long>& value, const std::string& serverName) {
			return _queryWMI(WMIClass, field, value, serverName);
		}

		bool queryWMI(const std::string& WMIClass, std::string field, std::vector<long long>& value, const std::string& serverName) {
			return _queryWMI(WMIClass, field, value, serverName);
		}

		bool queryWMI(const std::string& WMIClass, std::string field, std::vector<int>& value, const std::string& serverName) {
			return _queryWMI(WMIClass, field, value, serverName);
		}
	}

}
