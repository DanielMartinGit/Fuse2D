#pragma once
#include <glslang/Public/ShaderLang.h>
#include <glslang/Public/resource_limits_c.h>
#include <glslang/SPIRV/GlslangToSpv.h>
#include <vulkan/vulkan_core.h>

template<class T> T* Temp(T&& v) { return &v; }

VkPipelineShaderStageCreateInfo compile(VkDevice device, VkShaderStageFlagBits vkStage, const char* src)
{
    EShLanguage stage = vkStage == VK_SHADER_STAGE_VERTEX_BIT ? EShLangVertex : EShLangFragment;
    
    glslang::TShader shader{ stage };
    shader.setEnvInput(glslang::EShSourceGlsl, stage, glslang::EShClientVulkan, glslang::EShTargetVulkan_1_3);
    shader.setEnvClient(glslang::EShClientVulkan, glslang::EShTargetVulkan_1_3);
    shader.setEnvTarget(glslang::EshTargetSpv, glslang::EShTargetSpv_1_6);
    shader.setStrings(&src, 1);
    shader.parse((const TBuiltInResource*)glslang_default_resource(), 100, ENoProfile, EShMessages::EShMsgDefault);
    
    glslang::TProgram program{};
    program.addShader(&shader);
    program.link(EShMessages(int(EShMessages::EShMsgSpvRules) | int(EShMessages::EShMsgVulkanRules)));
  
    std::vector<uint32_t> spirv;
    glslang::SpvOptions spvOptions{ .validate = true };
    glslang::GlslangToSpv(*program.getIntermediate(stage), spirv, &spvOptions);
    
    VkShaderModule shaderModule;
    
    vkCreateShaderModule(device, 
        Temp(VkShaderModuleCreateInfo 
        {
            .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
            .codeSize = spirv.size() * sizeof(uint32_t),
            .pCode = spirv.data(),
        }
    ), nullptr, &shaderModule);
    
    return VkPipelineShaderStageCreateInfo{ 
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        .stage = vkStage,
        .module = shaderModule,
        .pName = "main",
    };
}