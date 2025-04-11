#include NAMES_INCLUDE
#include EDX11U_INCLUDE_PATH

dx11::string dx11::hr_ts(HRESULT hr) {
	_com_error err(hr);
	LPCWSTR errMsg = err.ErrorMessage();

	// make a wide temp copy
	std::wstring wide_temp(errMsg);

	// convert if necessary
#if NARROW
	std::string narrow_temp;
	{
		lb::codes code;
		narrow_temp = lb::to_narrow_string(wide_temp,&code);
		output_code(code);
	}
	return narrow_temp;
#endif

#if WIDE
	return wide_temp;
#endif
}

dx11::string dx11::debug_info_ts(ID3D11InfoQueue* debug_info_p, lol_blocks::codes* code) {
	/*

	typedef struct D3D11_MESSAGE {
	  D3D11_MESSAGE_CATEGORY Category;
	  D3D11_MESSAGE_SEVERITY Severity;
	  D3D11_MESSAGE_ID       ID;
	  const char             *pDescription;
	  SIZE_T                 DescriptionByteLength;
	} D3D11_MESSAGE;

	*/


	// Get the size of the message
	SIZE_T messageLength = 0;
	HRESULT hr = debug_info_p->GetMessage(0, NULL, &messageLength);

	// Allocate space and get the message
	D3D11_MESSAGE* pMessage = (D3D11_MESSAGE*)malloc(messageLength);
	hr = debug_info_p->GetMessage(0, pMessage, &messageLength);

	if (pMessage == nullptr) {
		*code = lb::codes::pointer_is_nullptr;
		return {};
	}

	std::string temp(pMessage->pDescription, pMessage->DescriptionByteLength);

	// delete the memory
	if (pMessage != nullptr) {
		free(pMessage);
	}

#if NARROW

	*code = lb::codes::success;
	return temp;

#endif

#if WIDE

	std::wstring temp_wide = lb::to_wide_string(temp,code);
	return temp_wide;

#endif

}

dx11::string dx11::error_blob_ts(ID3DBlob* error, lol_blocks::codes* code) {
	if (error == nullptr) {
		*code = lb::codes::pointer_is_nullptr;
		return {};
	}

	// Get the error message from the blob
	const char* errorMessage = static_cast<const char*>(error->GetBufferPointer());
	size_t messageSize = error->GetBufferSize();

	// Convert it to a std::string
	std::string temp_error_str(errorMessage, messageSize);

	// convert if necessary
#if NARROW
	*code = lb::codes::success;
	return temp_error_str;
#endif

#if WIDE
	std::wstring wide_temp = lb::to_wide_string(temp_error_str,code);
	return wide_temp;
#endif
}

lb::codes dx11::hr_tlbc(HRESULT hr) {
	switch (hr) {
		case S_OK:
			return lb::codes::dx_ok;
		case DXGI_ERROR_ACCESS_DENIED:
			return lb::codes::dx_access_denied;
		case DXGI_ERROR_ACCESS_LOST:
			return lb::codes::dx_access_lost;
		case DXGI_ERROR_ALREADY_EXISTS:
			return lb::codes::dx_already_exists;
		case DXGI_ERROR_CANNOT_PROTECT_CONTENT:
			return lb::codes::dx_cannot_protect_content;
		case DXGI_ERROR_DEVICE_HUNG:
			return lb::codes::dx_device_hung;
		case DXGI_ERROR_DEVICE_REMOVED:
			return lb::codes::dx_device_removed;
		case DXGI_ERROR_DEVICE_RESET:
			return lb::codes::dx_device_reset;
		case DXGI_ERROR_DRIVER_INTERNAL_ERROR:
			return lb::codes::dx_driver_internal_error;
		case DXGI_ERROR_FRAME_STATISTICS_DISJOINT:
			return lb::codes::dx_frame_statistics_disjoint;
		case DXGI_ERROR_INVALID_CALL:
			return lb::codes::dx_invalid_call;
		case DXGI_ERROR_MORE_DATA:
			return lb::codes::dx_more_data;
		case DXGI_ERROR_NAME_ALREADY_EXISTS:
			return lb::codes::dx_name_already_exists;
		case DXGI_ERROR_NONEXCLUSIVE:
			return lb::codes::dx_nonexclusive;
		case DXGI_ERROR_NOT_CURRENTLY_AVAILABLE:
			return lb::codes::dx_not_currently_avaliable;
		case DXGI_ERROR_NOT_FOUND:
			return lb::codes::dx_not_found;
		case DXGI_ERROR_REMOTE_CLIENT_DISCONNECTED:
			return lb::codes::dx_remote_client_disconnected;
		case DXGI_ERROR_REMOTE_OUTOFMEMORY:
			return lb::codes::dx_remote_outofmemory;
		case DXGI_ERROR_RESTRICT_TO_OUTPUT_STALE:
			return lb::codes::dx_restrict_to_output_stale;
		case DXGI_ERROR_SDK_COMPONENT_MISSING:
			return lb::codes::dx_sdk_component_missing;
		case DXGI_ERROR_SESSION_DISCONNECTED:
			return lb::codes::dx_session_disconnected;
		case DXGI_ERROR_UNSUPPORTED:
			return lb::codes::dx_unsupported;
		case DXGI_ERROR_WAIT_TIMEOUT:
			return lb::codes::dx_wait_timeout;
		case DXGI_ERROR_WAS_STILL_DRAWING:
			return lb::codes::dx_was_still_drawing;
		default:
			return lb::codes::dx_unknown_code;

	}
}