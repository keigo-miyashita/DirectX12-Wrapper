#pragma once

#include <common.hpp>

// DescriptorHeap��1��1�Ή��̐݌v
// DescriptorHeap�𕪊����ĕ�����DescriptorTable��
// �����@�͑Ή����Ă��Ȃ�
// CBV, SRV, UAV�̏��ɋL�q
// SAMPLER�͂��ꂾ��
class DescriptorTable
{
private:
	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

	std::vector<CD3DX12_DESCRIPTOR_RANGE> descRanges_;
	// CBV_SRV_UAV or SAMPLER
	D3D12_DESCRIPTOR_HEAP_TYPE heapType_ = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	UINT baseRegCBV_ = 0;
	UINT numCBV_ = 0;
	UINT baseRegSRV_ = 0;
	UINT numSRV_ = 0;
	UINT baseRegUAV_ = 0;
	UINT numUAV_ = 0;
	UINT baseRegSampler_ = 0;
	UINT numSampler_ = 0;

	void CreateBufferDescriptorRanges(UINT baseRegCBV, UINT numCBV, UINT baseRegSRV, UINT numSRV, UINT baseRegUAV, UINT numUAV);
	void CreateSamplerDescriptorRanges(UINT baseRegSampler, UINT numSampler);

public:
	DescriptorTable();
	~DescriptorTable() = default;
	void InitAsBuffer(UINT baseRegCBV, UINT numCBV, UINT baseRegSRV, UINT numSRV, UINT baseRegUAV, UINT numUAV);
	void InitAsSampler(UINT baseRegSampler, UINT numSampler);
	UINT GetNumDescRanges() const;
	const CD3DX12_DESCRIPTOR_RANGE* GetPDescRanges() const;
};