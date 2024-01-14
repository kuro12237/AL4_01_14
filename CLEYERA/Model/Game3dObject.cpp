#include "Game3dObject.h"

void Game3dObject::Create()
{
	MaterialBuffer_ = CreateResources::CreateBufferResource(sizeof(Material));
}

void Game3dObject::SetModel(uint32_t index)
{
	if (prevModelIndex_ != index)
	{
	    model_ = ModelManager::GetModel(index);
		texHandle_ = ModelManager::GetObjData(index).material.handle;
	}
	prevModelIndex_ = index;
}

void Game3dObject::Draw(WorldTransform worldTransform ,ViewProjection view)
{
	if (model_ == nullptr)
	{
		return;
	}


	model_->UseLight(UseLight_);

	Material * materialData;
	MaterialBuffer_->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	materialData->shininess = shininess;
	materialData->color = color_;
	materialData->uvTransform = MatrixTransform::AffineMatrix(uvScale_, uvRotate, uvTranslate);


	model_->CommandCallPipelineVertex();

	Commands command = DirectXCommon::GetInstance()->GetCommands();

	command.m_pList->SetGraphicsRootConstantBufferView(0, MaterialBuffer_->GetGPUVirtualAddress());
	command.m_pList->SetGraphicsRootConstantBufferView(1, worldTransform.buffer_->GetGPUVirtualAddress());
	command.m_pList->SetGraphicsRootConstantBufferView(2, view.buffer_->GetGPUVirtualAddress());
	DescriptorManager::rootParamerterCommand(3, texHandle_);
	
	model_->Draw(view);
}
