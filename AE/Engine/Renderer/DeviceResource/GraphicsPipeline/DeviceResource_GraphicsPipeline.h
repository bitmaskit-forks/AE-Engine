#pragma once

#include "../../../BUILD_OPTIONS.h"
#include "../../../Platform.h"

#include "../DeviceResource.h"

namespace AE
{

class FileResource_RawData;

class DeviceResource_GraphicsPipeline : public DeviceResource
{
	friend bool ContinueGraphicsPipelineLoadTest_1( DeviceResource * resource );
	friend DeviceResource::LoadingState ContinueGraphicsPipelineLoad_1( DeviceResource * resource );

public:
	DeviceResource_GraphicsPipeline( Engine * engine, DeviceResource::Flags resource_flags );
	~DeviceResource_GraphicsPipeline();

	uint32_t									GetImageCount() const;
	VkPipeline									GetVulkanPipeline() const;

private:
	LoadingState								Load();
	UnloadingState								Unload();

	VkPipeline									vk_pipeline									= VK_NULL_HANDLE;

	VkShaderModule								vk_vertex_shader_module						= VK_NULL_HANDLE;
	VkShaderModule								vk_tessellation_control_shader_module		= VK_NULL_HANDLE;
	VkShaderModule								vk_tessellation_evaluation_shader_module	= VK_NULL_HANDLE;
	VkShaderModule								vk_geometry_shader_module					= VK_NULL_HANDLE;
	VkShaderModule								vk_fragment_shader_module					= VK_NULL_HANDLE;

	FileResourceHandle<FileResource_RawData>	vertex_shader_resource;
	FileResourceHandle<FileResource_RawData>	tessellation_control_shader_resource;
	FileResourceHandle<FileResource_RawData>	tessellation_evaluation_shader_resource;
	FileResourceHandle<FileResource_RawData>	geometry_shader_resource;
	FileResourceHandle<FileResource_RawData>	fragment_shader_resource;

	// this is the amount of images the pipeline uses in the shaders
	uint32_t									image_count									= 0;

	Vector<VkDynamicState>						dynamic_states;
};

}
