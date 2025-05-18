#pragma once

#include <common.hpp>

class Device;

class RootParameter
{
private:
	D3D12_ROOT_PARAMETER_TYPE rootParamType_;
	// Descriptor table��o�^����Ƃ�����2��
	UINT descTableSize_ = 0;
	const CD3DX12_DESCRIPTOR_RANGE* pDescTable_ = nullptr;
	// Constant��Descriptor�𒼐ړo�^����Ƃ�����1��
	UINT numReg_ = 0;
	// Descriptor�p
	D3D12_SHADER_VISIBILITY shaderVisibility_ = D3D12_SHADER_VISIBILITY_ALL;
	// 32BitsConstant�p
	// 1��32Bits = 4Bytes
	// ��jfloat4 -> 16 Bytes -> numConstant_ = 4
	UINT numConstant_ = 0;

public:
	RootParameter();
	~RootParameter() = default;
	void InitAsDescriptorTable(UINT descTableSize, const CD3DX12_DESCRIPTOR_RANGE* pDescTable, D3D12_SHADER_VISIBILITY shaderVisibility = D3D12_SHADER_VISIBILITY_ALL);
	void InitAsConstantBufferView(UINT numReg, D3D12_SHADER_VISIBILITY shaderVisibility = D3D12_SHADER_VISIBILITY_ALL);
	void InitAsShaderResourceView(UINT numReg, D3D12_SHADER_VISIBILITY shaderVisibility = D3D12_SHADER_VISIBILITY_ALL);
	void InitAsUnorderedAccessView(UINT numReg, D3D12_SHADER_VISIBILITY shaderVisibility = D3D12_SHADER_VISIBILITY_ALL);
	void InitAs32BitConstant(UINT numReg, UINT numConstant = 1);
	D3D12_ROOT_PARAMETER_TYPE GetRootParamType();
	UINT GetDescTableSize();
	const CD3DX12_DESCRIPTOR_RANGE* GetPDescTable() const;
	UINT GetNumReg();
	D3D12_SHADER_VISIBILITY GetShaderVisibility();
	UINT GetNumConstant();
	
};

class RootSignature
{
private:
	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

	Device* pDevice_ = nullptr;
	ComPtr<ID3D12RootSignature> rootSig_ = nullptr;
	std::vector<RootParameter> rootParams_;

public:
	RootSignature();
	~RootSignature() = default;
	bool Init(Device* pDevice);
	bool InitializeRootSignature(D3D12_ROOT_SIGNATURE_FLAGS flags, std::wstring name = L"RootSignature");
	void AddDescriptorTable(const DescriptorTable& descriptorTable, D3D12_SHADER_VISIBILITY shaderVisibility = D3D12_SHADER_VISIBILITY_ALL);
	void AddDescriptor(D3D12_ROOT_PARAMETER_TYPE rootParamType, UINT numReg, D3D12_SHADER_VISIBILITY shaderVisibility = D3D12_SHADER_VISIBILITY_ALL);
	void AddConstant(UINT numReg, UINT numConstant = 1);
	ComPtr<ID3D12RootSignature> GetRootSignature() const;
};