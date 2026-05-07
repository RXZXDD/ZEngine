#pragma once
#define CREATE_DEFAULT_CMD_LIST(cmdList) \
	ID3D12CommandList* cmdsLists[] = { cmdList.Get() };

#define EXECUTE_DEFAULT_CMD_LIST(cmdQueue) \
	cmdQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

