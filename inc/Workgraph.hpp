#pragma once

#include <common.hpp>

class Buffer;
class Device;

class WorkGraph
{
private:
	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

	Device* pDevice_ = nullptr;
	ComPtr<ID3D12WorkGraphProperties1> workGraphProp_ = nullptr;
	D3D12_PROGRAM_IDENTIFIER workGraphProgramID_ = {};
	D3D12_WORK_GRAPH_MEMORY_REQUIREMENTS memReqs_ = {};
	// D3D12_GPU_VIRTUAL_ADDRESSとsizeInBytesをもつ構造体
	D3D12_GPU_VIRTUAL_ADDRESS_RANGE backingMemoryAddressRange_ = {};
	ComPtr<ID3D12Resource> backingMemory_ = nullptr;
	UINT workGraphIndex_ = 0;
	UINT numEntryPoints_ = 0;
	UINT numNodes_ = 0;

	// CommandList.SetProgramに渡す構造体
	D3D12_SET_PROGRAM_DESC pgDesc_ = {};

	bool InitWorkGraphContext(const StateObject& stateObject, UINT maxInputRecords = 0, UINT maxNodeInputs = 0);

public:
	WorkGraph();
	~WorkGraph() = default;
	bool Init(Device* pDevice, const StateObject& stateObject, UINT maxInputRecords = 0, UINT maxNodeInputs = 0);

	D3D12_SET_PROGRAM_DESC GetProgramDesc() const;
	D3D12_SET_PROGRAM_DESC* GetPProgramDesc();
};