#pragma once

#include "../../BUILD_OPTIONS.h"
#include "../../Platform.h"

#include <tinyxml2.h>

#include "../../Memory/MemoryTypes.h"
#include "../../Math/Math.h"
#include "../../Renderer/DescriptorSet/DescriptorSetHandle.h"

#include "SceneBase.h"

#include "../../Renderer/DeviceResource/DeviceResource.h"

namespace AE
{

class Engine;
class UniformBuffer;
class DeviceResource_GraphicsPipeline;
class DeviceResource_Mesh;
class DeviceResource_Image;

class SceneNode : public SceneBase
{
public:
	struct ImageInfo
	{
		Array<DeviceResourceHandle<DeviceResource_Image>, BUILD_MAX_PER_SHADER_SAMPLED_IMAGE_COUNT>		image_resources;
		int32_t																							image_count			= -1;
	};

	struct RenderInfo
	{
		DeviceResourceHandle<DeviceResource_GraphicsPipeline>				graphics_pipeline_resource;
		ImageInfo							image_info						= {};
	};

	struct MeshInfo
	{
		String								name;
		bool								is_visible						= true;
		
		// Mesh specific transformation depricated since we now allow only one mesh per scene node
		/*
		Vec3								position						= Vec3( 0, 0, 0 );
		Quat								rotation						= Quat( 1, 0, 0, 0 );
		Vec3								scale							= Vec3( 1, 1, 1 );
		*/

		UniquePointer<UniformBuffer>		uniform_buffer					= nullptr;
		DescriptorSetHandle					uniform_buffer_descriptor_set	= nullptr;

		DeviceResourceHandle<DeviceResource_Mesh>							mesh_resource;

		RenderInfo							render_info						= {};
	};

											SceneNode( Engine * engine, SceneManager * scene_manager, SceneBase * parent, const Path & scene_node_path, SceneBase::Type scene_node_type );
	virtual									~SceneNode();

protected:
	// because it's easier to call parent functions than branching child object's functions
	// I have inverted the parsing into sections, ParseConfigFile() is responsible for calling it's immediate
	// parent class parse function and the function will parse that level of the XML file as well as any below
	// returns new parent xml element for the next stage or nullptr if error
	tinyxml2::XMLElement				*	ParseConfigFile_SceneNodeLevel();

	// because it's easier to call parent functions than branching child object's functions
	// I have inverted the resource checking, CheckResourcesLoaded() is responsible for calling it's immediate
	// parent class check function and the function will check that level's resources that were requested by the XML file as well as any below
	// returns READY if everyting on this level was loaded, NOT_READY if something was missing and UNABLE_TO_LOAD if something went wrong
	ResourcesLoadState						CheckResourcesLoaded_SceneNodeLevel();

	// because it's easier to call parent functions than branching child object's functions
	// I have inverted the finalizing into levels, FinalizeResources() is responsible for calling it's immediate
	// parent class'es finalize function and the function will finalize that level of resources defined by the XML file as well as any below
	// returns true if everything is OK, false if there was an error in which case this scene node will not participate in updates or rendering operations
	bool									FinalizeResources_SceneNodeLevel();

//	Vector<SharedPointer<MeshInfo>>			mesh_info_list;
	SharedPointer<MeshInfo>					mesh_info				= nullptr;
};

}
