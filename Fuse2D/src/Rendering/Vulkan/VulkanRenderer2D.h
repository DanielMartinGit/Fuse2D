#pragma once
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#define GLFW_EXPOSE_NATIVE_WIN32

#include "Fuse2D/src/Core/Resource Manager/ResourceManager.h"
#include "Fuse2D/src/Core/Window/Window.h"
#include "vulkan/vulkan.h"

#include <set>
#include <optional>
#include <algorithm>
#include <array>
#include <chrono>
#include <Fuse2D/Vendor/GLM/ext/matrix_transform.hpp>
#include <Fuse2D/Vendor/GLM/ext/matrix_clip_space.hpp>

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else 
	const bool enableValidationLayers = true;
#endif

const std::vector<const char*> validationLayers =
{
	"VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> deviceExtensions =
{
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

const int MAX_FRAMES_IN_FLIGHT = 2;
const int vsyncEnabled = VK_PRESENT_MODE_IMMEDIATE_KHR;

struct Vertex
{
	glm::vec2 pos;
	glm::vec3 color;
	glm::vec2 texCoord;

	static VkVertexInputBindingDescription getBindingDescription()
	{
		VkVertexInputBindingDescription bindingDescription{};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescription;
	}

	static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions()
	{
		std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);

		attributeDescriptions[2].binding = 0;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

		return attributeDescriptions;
	}
};

const std::vector<Vertex> vertices =
{
	{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
	{{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
	{{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
	{{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}
};

const std::vector<uint16_t> indices = 
{
	0, 1, 2, 2, 3, 0
};

struct uniformBufferObject
{
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 ortho;
};

namespace Fuse2D
{
	// Queue Families
	struct QueueFamilyIndices
	{
		std::optional<uint32_t> m_GhraphicsFamily;
		std::optional <uint32_t> m_PresentFamily;

		bool IsComplete()
		{
			return m_GhraphicsFamily.has_value() && m_PresentFamily.has_value();
		}
	};

	// Swapchain
	struct SwapchainSupportDetails
	{
		VkSurfaceCapabilitiesKHR m_Capabilities;
		std::vector<VkSurfaceFormatKHR> m_SurfaceFormats;
		std::vector<VkPresentModeKHR> m_PresentModes;
	};

	// Main Triangle App
	class HelloTriangleApp
	{
		public:
			HelloTriangleApp() {}
			HelloTriangleApp(Fuse2D::Window* window)
			{
				m_Window = *window;
			}

			void InitRenderer()
			{
				InitVulkan();
			}

			void Render()
			{
				MainLoop();
			}

		private:
			void CreateInstance()
			{
				// APP INFO 
				VkApplicationInfo appInfo{};
				appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
				appInfo.pApplicationName = "Fuse2D";
				appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
				appInfo.pEngineName = "No Engine";
				appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
				appInfo.apiVersion = VK_API_VERSION_1_0;

				VkInstanceCreateInfo createInfo{};
				createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
				createInfo.pApplicationInfo = &appInfo;

				// EXTENSIONS
				uint32_t glfwExtensionCount = 0;
				const char** glfwExtensions;

				glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

				createInfo.enabledExtensionCount = glfwExtensionCount;
				createInfo.ppEnabledExtensionNames = glfwExtensions;

				std::vector<const char*> requiredExtensions;

				for (uint32_t i = 0; i < glfwExtensionCount; ++i)
				{
					requiredExtensions.emplace_back(glfwExtensions[i]);
				}

				uint32_t extensionCount = 0;
				vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
				std::vector<VkExtensionProperties> extensions(extensionCount);
				vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
				std::cout << "Available Extensions: \n";

				for (const auto& extension : extensions)
				{
					std::cout << "\t" << extension.extensionName << "\n";
				}

				// LAYERS
				CheckValidationLayerSupport();

				if (enableValidationLayers)
				{
					createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
					createInfo.ppEnabledLayerNames = validationLayers.data();
				}
				else
					createInfo.enabledLayerCount = 0;

				if (enableValidationLayers && !CheckValidationLayerSupport())
					throw std::runtime_error("Validation layers supported, but not available!");

				auto getExtensions = GetRequiredExtensions();
				createInfo.enabledExtensionCount = static_cast<uint32_t>(getExtensions.size());
				createInfo.ppEnabledExtensionNames = getExtensions.data();

				VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
				if (enableValidationLayers)
				{
					createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
					createInfo.ppEnabledLayerNames = validationLayers.data();

					PopulateDebugMessengerCreateInfo(debugCreateInfo);
					createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
				}
				else
				{
					createInfo.enabledLayerCount = 0;
					createInfo.pNext = nullptr;
				}

				if (vkCreateInstance(&createInfo, nullptr, &m_VKInstance) != VK_SUCCESS)
					throw std::runtime_error("Failed to create instance");
			}

			bool CheckValidationLayerSupport()
			{
				uint32_t layerCount;
				vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

				std::vector<VkLayerProperties> avaliableLayers(layerCount);
				vkEnumerateInstanceLayerProperties(&layerCount, avaliableLayers.data());

				for (const char* layerName : validationLayers)
				{
					bool layerFound = false;

					for (const auto& layerProperties : avaliableLayers)
					{
						if (strcmp(layerName, layerProperties.layerName) == 0)
						{
							layerFound = true;
							break;
						}
					}

					if (!layerFound)
						return false;
				}

				return true;
			}

			// DEBUG MESSENGER
			static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
				VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
				VkDebugUtilsMessageTypeFlagsEXT messageType,
				const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
				void* pUserData)
			{
				std::cerr << "Validation Layer: " << pCallbackData->pMessage << std::endl;
				return VK_FALSE;
			}

			void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
			{
				createInfo = {};

				createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
				createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT 
					| VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT 
					| VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
				createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT 
					| VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT 
					| VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

				createInfo.pfnUserCallback = debugCallback;
			}

			void SetupDebugMessenger()
			{
				if (!enableValidationLayers) return;

				VkDebugUtilsMessengerCreateInfoEXT createInfo;
				PopulateDebugMessengerCreateInfo(createInfo);

				if (CreateDebugUtilsMessengerEXT(m_VKInstance, &createInfo, nullptr, &m_DebugMessenger) != VK_SUCCESS)
					throw std::runtime_error("failed to setup a debug messenger");
			}

			VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
				const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
			{
				auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

				if (func != nullptr)
					return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
				else
					return VK_ERROR_EXTENSION_NOT_PRESENT;
			}

			void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
			{
				auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
				
				if (func != nullptr)
					func(instance, debugMessenger, pAllocator);
			}

			// SURFACE
			void CreateSurface()
			{
				if (glfwCreateWindowSurface(m_VKInstance, m_Window.GetWindowInstance(), nullptr, &m_Surface) != VK_SUCCESS) 
					throw std::runtime_error("failed to create window surface!");
			}

			// PHYSICAL DEVICES 
			void PickPhysicalDevice()
			{
				uint32_t deviceCount = 0;
				vkEnumeratePhysicalDevices(m_VKInstance, &deviceCount, nullptr);

				if (deviceCount == 0)
					throw std::runtime_error("Failed to find a GPU with Vulkan Support!");

				std::vector<VkPhysicalDevice> devices(deviceCount);
				vkEnumeratePhysicalDevices(m_VKInstance, &deviceCount, devices.data());

				for (const auto& device : devices)
				{
					if (IsDeviceSuitable(device))
					{
						m_PhysicalDevice = device;
						break;
					}
				}

				if (m_PhysicalDevice == VK_NULL_HANDLE)
					throw std::runtime_error("Failed to find a suitable GPU");
			}

			// Logical Device
			void CreateLogicalDevice()
			{
				QueueFamilyIndices indices = FindQueueFamilies(m_PhysicalDevice);

				std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
				std::set<uint32_t> uniqueQueueFamilies = { indices.m_GhraphicsFamily.value(), indices.m_PresentFamily.value() };

				float queuePriority = 1.0f;
				for (uint32_t queueFamily : uniqueQueueFamilies)
				{
					VkDeviceQueueCreateInfo queueCreateInfo {};
					queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
					queueCreateInfo.queueFamilyIndex = queueFamily;
					queueCreateInfo.queueCount = 1;
					queueCreateInfo.pQueuePriorities = &queuePriority;
					queueCreateInfos.push_back(queueCreateInfo);
				}

				VkPhysicalDeviceFeatures deviceFeatures {};
				deviceFeatures.samplerAnisotropy = VK_TRUE;

				VkDeviceCreateInfo createInfo {};
				createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
				createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
				createInfo.pQueueCreateInfos = queueCreateInfos.data();
				createInfo.pEnabledFeatures = &deviceFeatures;
				createInfo.ppEnabledExtensionNames = deviceExtensions.data();
				createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());

				if (enableValidationLayers)
				{
					createInfo.enabledLayerCount = static_cast<uint32_t> (validationLayers.size());
					createInfo.ppEnabledLayerNames = validationLayers.data();
				}
				else
				{
					createInfo.enabledLayerCount = 0;
				}

				if (vkCreateDevice(m_PhysicalDevice, &createInfo, nullptr, &m_Device) != VK_SUCCESS)
					throw std::runtime_error("Failed to create a logical device!");

				vkGetDeviceQueue(m_Device, indices.m_GhraphicsFamily.value(), 0, &m_GraphicsQueue);
				vkGetDeviceQueue(m_Device, indices.m_PresentFamily.value(), 0, &m_PresentQueue);
			}

			// EXTENSIONS
			std::vector<const char*> GetRequiredExtensions()
			{
				uint32_t glfwExtensionCount = 0;
				const char** glfwExtensions;

				glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

				std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

				if (enableValidationLayers)
					extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

				return extensions;
			}

			bool CheckDeviceExtensionSupport(VkPhysicalDevice device)
			{
				uint32_t extensionCount;

				vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

				std::vector<VkExtensionProperties> availableExtensions(extensionCount);
				vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

				std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

				for (const auto& extension : availableExtensions)
				{
					requiredExtensions.erase(extension.extensionName);
				}

				return requiredExtensions.empty();
			}

			// Queue Families 
			bool IsDeviceSuitable(VkPhysicalDevice device)
			{
				QueueFamilyIndices indices = FindQueueFamilies(device);

				bool extensionsSupported = CheckDeviceExtensionSupport(device);
				bool swapChainAdequate = false;

				if (extensionsSupported)
				{
					SwapchainSupportDetails swapchainSupport = QuerySwapchainSupport(device);
					swapChainAdequate = !swapchainSupport.m_SurfaceFormats.empty() && !swapchainSupport.m_PresentModes.empty();
				}

				VkPhysicalDeviceFeatures supportFeatures;
				vkGetPhysicalDeviceFeatures(device, &supportFeatures);

				return indices.IsComplete() && extensionsSupported && swapChainAdequate && supportFeatures.samplerAnisotropy; 
			}

			QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device)
			{
				QueueFamilyIndices indices;

				uint32_t queueFamilyCount = 0;
				vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

				std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
				vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

				int i = 0;
				for (const auto& queueFamily : queueFamilies)
				{
					if (indices.IsComplete())
						break;

					if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
						indices.m_GhraphicsFamily = i;

					VkBool32 presentSupport = false;
					vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_Surface, &presentSupport);

					if (presentSupport)
						indices.m_PresentFamily = i;

					i++;
				}

				return indices;
			}

			// SWAPCHAIN
			SwapchainSupportDetails QuerySwapchainSupport(VkPhysicalDevice device)
			{
				SwapchainSupportDetails details;

				vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, m_Surface, &details.m_Capabilities);

				uint32_t formatCount;
				vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_Surface, &formatCount, nullptr);

				if (formatCount != 0)
				{
					details.m_SurfaceFormats.resize(formatCount);
					vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_Surface, &formatCount, details.m_SurfaceFormats.data());
				}

				uint32_t presentModeCount;
				vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_Surface, &presentModeCount, nullptr);

				if (presentModeCount != 0)
				{
					details.m_PresentModes.resize(presentModeCount);
					vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_Surface, &presentModeCount, details.m_PresentModes.data());
				}

				return details;
			}

			VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
			{
				for (const auto& availableFormat : availableFormats)
				{
					if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLORSPACE_SRGB_NONLINEAR_KHR)
						return availableFormat;
				}

				return availableFormats[0];
			}

			VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
			{
				for (const auto& availablePresentMode : availablePresentModes)
				{
					if (availablePresentMode == vsyncEnabled)
						return availablePresentMode;
				}

				return VK_PRESENT_MODE_FIFO_KHR;
			}

			VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
			{
				if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
					return capabilities.currentExtent;
				else
				{
					int width;
					int height;

					glfwGetFramebufferSize(m_Window.GetWindowInstance(), &width, &height);

					VkExtent2D actualExtent =
					{
						static_cast<uint32_t>(width),
						static_cast<uint32_t>(height)
					};

					actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
					actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

					return actualExtent;
				}
			}

			void CreateSwapChain()
			{
				SwapchainSupportDetails swapchainSupport = QuerySwapchainSupport(m_PhysicalDevice);

				VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapchainSupport.m_SurfaceFormats);
				VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapchainSupport.m_PresentModes);
				VkExtent2D extent = ChooseSwapExtent(swapchainSupport.m_Capabilities);

				uint32_t imageCount = swapchainSupport.m_Capabilities.maxImageCount + 1;
					
				if (swapchainSupport.m_Capabilities.maxImageCount > 0 && imageCount > swapchainSupport.m_Capabilities.maxImageCount)
					imageCount = swapchainSupport.m_Capabilities.maxImageCount;

				VkSwapchainCreateInfoKHR createInfo {};
				createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
				createInfo.surface = m_Surface;

				createInfo.minImageCount = imageCount;
				createInfo.imageFormat = surfaceFormat.format;
				createInfo.imageColorSpace = surfaceFormat.colorSpace;
				createInfo.imageExtent = extent;
				createInfo.imageArrayLayers = 1;
				createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

				createInfo.preTransform = swapchainSupport.m_Capabilities.currentTransform;
				createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

				createInfo.presentMode = presentMode;
				createInfo.clipped = VK_TRUE;

				createInfo.oldSwapchain = VK_NULL_HANDLE;
				
				if (vkCreateSwapchainKHR(m_Device, &createInfo, nullptr, &m_SwapChain) != VK_SUCCESS)
					throw std::runtime_error("Failed to create a swapchain!");

				vkGetSwapchainImagesKHR(m_Device, m_SwapChain, &imageCount, nullptr);
				m_SwapchainImages.resize(imageCount);
				vkGetSwapchainImagesKHR(m_Device, m_SwapChain, &imageCount, m_SwapchainImages.data());

				m_SwapchainFormat = surfaceFormat.format;
				m_SwapchainExtent = extent;
			}

			void CreateImageViews()
			{
				m_SwapchainImageViews.resize(m_SwapchainImages.size());

				for (size_t i = 0; i < m_SwapchainImages.size(); ++i)
				{
					m_SwapchainImageViews[i] = CreateImageView(m_SwapchainImages[i], m_SwapchainFormat);
				}
			}

			// GRAPHICS PIPELINE
			void CreateGraphicsPipeline()
			{
				std::vector<VkDynamicState> dynamicStates =
				{
					VK_DYNAMIC_STATE_VIEWPORT,
					VK_DYNAMIC_STATE_SCISSOR
				};

				auto vertShaderCode = Fuse2D::ResourceManager::LoadShader("res/shaders/vert.spv");
				auto fragShaderCode = Fuse2D::ResourceManager::LoadShader("res/shaders/frag.spv");

				VkShaderModule vertShaderModule = CreateShaderModule(vertShaderCode);
				VkShaderModule fragShaderModule = CreateShaderModule(fragShaderCode);

				VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
				vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
				vertShaderStageInfo.module = vertShaderModule;
				vertShaderStageInfo.pName = "main";

				VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
				fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
				fragShaderStageInfo.module = fragShaderModule;
				fragShaderStageInfo.pName = "main";

				VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

				auto bindingDescription = Vertex::getBindingDescription();
				auto attributeDescription = Vertex::getAttributeDescriptions();

				VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
				vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
				vertexInputInfo.vertexBindingDescriptionCount = 1;
				vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescription.size());
				vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
				vertexInputInfo.pVertexAttributeDescriptions = attributeDescription.data();

				VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
				inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
				inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
				inputAssembly.primitiveRestartEnable = VK_FALSE;

				VkPipelineDynamicStateCreateInfo dynamicState{};
				dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
				dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
				dynamicState.pDynamicStates = dynamicStates.data();

				VkViewport viewport{};
				viewport.x = 0.0f;
				viewport.y = 0.0f;
				viewport.width = static_cast<float>(m_SwapchainExtent.width);
				viewport.height = static_cast<float>(m_SwapchainExtent.height);
				viewport.minDepth = 0.0f;
				viewport.maxDepth = 1.0f;
				vkCmdSetViewport(m_CommandBuffers[m_CurrentFrame], 0, 1, &viewport);

				VkRect2D scissor{};
				scissor.offset = { 0, 0 };
				scissor.extent = m_SwapchainExtent;
				vkCmdSetScissor(m_CommandBuffers[m_CurrentFrame], 0, 1, &scissor);

				VkPipelineViewportStateCreateInfo viewportState{};
				viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
				viewportState.viewportCount = 1;
				viewportState.pViewports = &viewport;
				viewportState.scissorCount = 1;
				viewportState.pScissors = &scissor;

				VkPipelineRasterizationStateCreateInfo rasterizer{};
				rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
				rasterizer.depthBiasClamp = VK_FALSE;
				rasterizer.rasterizerDiscardEnable = VK_FALSE;
				rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
				rasterizer.lineWidth = 1.0f;
				rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
				rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
				rasterizer.depthBiasEnable = VK_FALSE;
				rasterizer.depthBiasConstantFactor = 0.0f;
				rasterizer.depthBiasClamp = 0.0f;
				rasterizer.depthBiasSlopeFactor = 0.0f;

				VkPipelineMultisampleStateCreateInfo multisampling{};
				multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
				multisampling.sampleShadingEnable = VK_FALSE;
				multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
				multisampling.minSampleShading = 1.0f; 
				multisampling.pSampleMask = nullptr;
				multisampling.alphaToCoverageEnable = VK_FALSE; 
				multisampling.alphaToOneEnable = VK_FALSE;

				VkPipelineColorBlendAttachmentState colourBlendAttachment{};
				colourBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT
					| VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
				colourBlendAttachment.blendEnable = VK_TRUE;
				colourBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
				colourBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
				colourBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
				colourBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
				colourBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
				colourBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

				VkPipelineColorBlendStateCreateInfo colourBlending{};
				colourBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
				colourBlending.logicOpEnable = VK_FALSE;
				colourBlending.logicOp = VK_LOGIC_OP_COPY;
				colourBlending.attachmentCount = 1;
				colourBlending.pAttachments = &colourBlendAttachment;
				colourBlending.blendConstants[0] = 0.0f;
				colourBlending.blendConstants[1] = 0.0f;
				colourBlending.blendConstants[2] = 0.0f;
				colourBlending.blendConstants[3] = 0.0f;

				VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
				pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
				pipelineLayoutInfo.setLayoutCount = 1;
				pipelineLayoutInfo.pSetLayouts = &m_DescriptorSetLayout;
				pipelineLayoutInfo.pushConstantRangeCount = 0;
				pipelineLayoutInfo.pPushConstantRanges = nullptr;

				if (vkCreatePipelineLayout(m_Device, &pipelineLayoutInfo, nullptr, &m_PipelineLayout) != VK_SUCCESS)
					throw std::runtime_error("Failed to create Graphics Pipeline Layout!");

				VkGraphicsPipelineCreateInfo pipelineInfo {};
				pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
				pipelineInfo.stageCount = 2;
				pipelineInfo.pStages = shaderStages;
				pipelineInfo.pVertexInputState = &vertexInputInfo;
				pipelineInfo.pInputAssemblyState = &inputAssembly;
				pipelineInfo.pViewportState = &viewportState;
				pipelineInfo.pRasterizationState = &rasterizer;
				pipelineInfo.pMultisampleState = &multisampling;
				pipelineInfo.pDepthStencilState = nullptr;
				pipelineInfo.pColorBlendState = &colourBlending;
				pipelineInfo.pDynamicState = &dynamicState;
				pipelineInfo.layout = m_PipelineLayout;
				pipelineInfo.renderPass = m_RenderPass;
				pipelineInfo.subpass = 0;
				pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
				pipelineInfo.basePipelineIndex = -1;

				if (vkCreateGraphicsPipelines(m_Device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_GraphicsPipeline) != VK_SUCCESS)
					throw std::runtime_error("Failed to create a Graphics pipeline!");

				vkDestroyShaderModule(m_Device, vertShaderModule, nullptr);
				vkDestroyShaderModule(m_Device, fragShaderModule, nullptr);
			}
			
			// CREATE VERTEX BUFFER
			void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory)
			{
				VkBufferCreateInfo bufferInfo{};
				bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
				bufferInfo.size = size;
				bufferInfo.usage = usage;
				bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

				if (vkCreateBuffer(m_Device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS)
					throw std::runtime_error("Failed to create a vertex buffer!");

				VkMemoryRequirements memRequirements;
				vkGetBufferMemoryRequirements(m_Device, buffer, &memRequirements);

				VkMemoryAllocateInfo allocInfo{};
				allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
				allocInfo.allocationSize = memRequirements.size;
				allocInfo.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits, properties);

				if (vkAllocateMemory(m_Device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS)
					throw std::runtime_error("Failed to allocate Vertex Buffer Memory!");

				vkBindBufferMemory(m_Device, buffer, bufferMemory, 0);
			}
			
			void CreateVertexBuffer()
			{
				VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

				VkBuffer stagingBuffer;
				VkDeviceMemory stagingBufferMemory;
				CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT 
					| VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

				void* data;
				vkMapMemory(m_Device, stagingBufferMemory, 0, bufferSize, 0, &data);
					memcpy(data, vertices.data(), (size_t)bufferSize);
				vkUnmapMemory(m_Device, stagingBufferMemory);

				CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT
					| VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_VertexBuffer, m_VertexBufferMemory);

				CopyBuffer(stagingBuffer, m_VertexBuffer, bufferSize);

				vkDestroyBuffer(m_Device, stagingBuffer, nullptr);
				vkFreeMemory(m_Device, stagingBufferMemory, nullptr);
			}

			void CreateIndexBuffer()
			{
				VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

				VkBuffer stagingBuffer;
				VkDeviceMemory stagingBufferMemory;
				CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT 
					| VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

				void* data;
				vkMapMemory(m_Device, stagingBufferMemory, 0, bufferSize, 0, &data);
				memcpy(data, indices.data(), (size_t)bufferSize);
				vkUnmapMemory(m_Device, stagingBufferMemory);

				CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT 
					| VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_IndexBuffer, m_IndexBufferMemory);

				CopyBuffer(stagingBuffer, m_IndexBuffer, bufferSize);

				vkDestroyBuffer(m_Device, stagingBuffer, nullptr);
				vkFreeMemory(m_Device, stagingBufferMemory, nullptr);
			}

			void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
			{
				VkCommandBuffer commandBuffer = BeginSingleTimeCommands();

				VkBufferCopy copyRegion {};
				copyRegion.size = size;
				vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

				EndSingleTimeCommands(commandBuffer);
			}

			VkShaderModule CreateShaderModule(const std::vector<char>& shaderCode)
			{
				VkShaderModuleCreateInfo createInfo {};
				createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
				createInfo.codeSize = shaderCode.size();
				createInfo.pCode = reinterpret_cast<const uint32_t*>(shaderCode.data());
			
				VkShaderModule shaderModule;
				if (vkCreateShaderModule(m_Device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
					throw std::runtime_error("Failed to create Shader Module!");
			
				return shaderModule;
			}

			// RENDER PASSES
			void CreateRenderPass()
			{
				VkAttachmentDescription colourAttachment{};
				colourAttachment.format = m_SwapchainFormat;
				colourAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
				colourAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
				colourAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
				colourAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
				colourAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
				colourAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
				colourAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

				VkAttachmentReference colourAttachmentRef {};
				colourAttachmentRef.attachment = 0;
				colourAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

				VkSubpassDescription subpass {};
				subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
				subpass.colorAttachmentCount = 1;
				subpass.pColorAttachments = &colourAttachmentRef;

				VkSubpassDependency dependency{};
				dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
				dependency.dstSubpass = 0;
				dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				dependency.srcAccessMask = 0;
				dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

				VkRenderPassCreateInfo renderPassCreateInfo {};
				renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
				renderPassCreateInfo.attachmentCount = 1;
				renderPassCreateInfo.pAttachments = &colourAttachment;
				renderPassCreateInfo.subpassCount = 1;
				renderPassCreateInfo.pSubpasses = &subpass;
				renderPassCreateInfo.dependencyCount = 1;
				renderPassCreateInfo.pDependencies = &dependency;

				if (vkCreateRenderPass(m_Device, &renderPassCreateInfo, nullptr, &m_RenderPass) != VK_SUCCESS)
					throw std::runtime_error("Failed to create a Render Pass!");
			}

			// FRAMEBUFFERS
			void CreateFramebuffer()
			{
				m_SwapChainFramebuffers.resize(m_SwapchainImageViews.size());

				for (size_t i = 0; i < m_SwapchainImageViews.size(); ++i)
				{
					VkImageView attachments[] =
					{
						m_SwapchainImageViews[i]
					};

					VkFramebufferCreateInfo framebufferInfo {};
					framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
					framebufferInfo.renderPass = m_RenderPass;
					framebufferInfo.attachmentCount = 1;
					framebufferInfo.pAttachments = attachments;
					framebufferInfo.width = m_SwapchainExtent.width;
					framebufferInfo.height = m_SwapchainExtent.height;
					framebufferInfo.layers = 1;

					if (vkCreateFramebuffer(m_Device, &framebufferInfo, nullptr, &m_SwapChainFramebuffers[i]) != VK_SUCCESS)
						throw std::runtime_error("Failed to create Framebuffer!");
				}
			}

			// COMMAND POOL
			void CreateCommandPool()
			{
				QueueFamilyIndices queueFamilyIndices = FindQueueFamilies(m_PhysicalDevice);

				VkCommandPoolCreateInfo poolInfo{};
				poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
				poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
				poolInfo.queueFamilyIndex = queueFamilyIndices.m_GhraphicsFamily.value();

				if (vkCreateCommandPool(m_Device, &poolInfo, nullptr, &m_CommandPool) != VK_SUCCESS)
					throw std::runtime_error("Failed to create Command Pool!");
			}

			// CREATE COMMAND BUFFER
			void CreateCommandBuffers()
			{
				m_CommandBuffers.resize(MAX_FRAMES_IN_FLIGHT);

				VkCommandBufferAllocateInfo allocInfo{};
				allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
				allocInfo.commandPool = m_CommandPool;
				allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
				allocInfo.commandBufferCount = (uint32_t) m_CommandBuffers.size();

				if (vkAllocateCommandBuffers(m_Device, &allocInfo, m_CommandBuffers.data()) != VK_SUCCESS)
					throw std::runtime_error("Failed to allocate Command Buffer!");
			}

			// COMMAND BUFFER
			void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex)
			{
				VkCommandBufferBeginInfo beginInfo{};
				beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
				beginInfo.flags = 0;
				beginInfo.pInheritanceInfo = nullptr;

				if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS)
					throw std::runtime_error("Failed to begin recording Command Buffer!");

				VkRenderPassBeginInfo renderPassBeginInfo{};
				renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
				renderPassBeginInfo.renderPass = m_RenderPass;
				renderPassBeginInfo.framebuffer = m_SwapChainFramebuffers[imageIndex];
				renderPassBeginInfo.renderArea.offset = { 0, 0 };
				renderPassBeginInfo.renderArea.extent = m_SwapchainExtent;

				VkClearValue clearColour = { {{0, 100, 255, 255}} };
				renderPassBeginInfo.clearValueCount = 1;
				renderPassBeginInfo.pClearValues = &clearColour;

				vkCmdBeginRenderPass(commandBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
				vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_GraphicsPipeline);

				VkBuffer vertexBuffers[] = { m_VertexBuffer };
				VkBuffer indexBuffer = { m_IndexBuffer };
				VkDeviceSize offsets[] = { 0 };

				vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
				vkCmdBindIndexBuffer(commandBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT16);

				vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_PipelineLayout, 0, 1, &m_DescriptorSets[m_CurrentFrame], 0, nullptr);
				vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);
				vkCmdEndRenderPass(commandBuffer);

				if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS)
					throw std::runtime_error("Failed to record Command Buffer!");
			}

			// CREATE SYNC OBJECTS
			void CreateSyncObjects()
			{
				m_ImageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
				m_RenderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
				m_InFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

				VkSemaphoreCreateInfo semaphoreInfo {};
				semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

				VkFenceCreateInfo fenceInfo {};
				fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
				fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
				
				for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i)
				{
					if (vkCreateSemaphore(m_Device, &semaphoreInfo, nullptr, &m_ImageAvailableSemaphores[i]) != VK_SUCCESS ||
						vkCreateSemaphore(m_Device, &semaphoreInfo, nullptr, &m_RenderFinishedSemaphores[i]) != VK_SUCCESS ||
						vkCreateFence(m_Device, &fenceInfo, nullptr, &m_InFlightFences[i]) != VK_SUCCESS)
					{
						throw std::runtime_error("Failed to create semaphores!");
					}
				}
			}

			// Swapchains
			void RecreateSwapChain()
			{
				int width = 0, height = 0;
				glfwGetFramebufferSize(m_Window.GetWindowInstance(), &width, &height);

				while (width == 0 || height == 0)
				{
					glfwGetFramebufferSize(m_Window.GetWindowInstance(), &width, &height);
					glfwWaitEvents();
				}

				vkDeviceWaitIdle(m_Device);

				CleanUpSwapchain();

				CreateSwapChain();
				CreateImageViews();
				CreateFramebuffer();
			}

			// DESCRIPTOR LAYOUTS
			void CreateDescriptorSetLayout()
			{
				VkDescriptorSetLayoutBinding uboLayoutBinding {};
				uboLayoutBinding.binding = 0;
				uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
				uboLayoutBinding.descriptorCount = 1;
				uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
				uboLayoutBinding.pImmutableSamplers = nullptr;

				VkDescriptorSetLayoutBinding samplerLayoutBinding{};
				samplerLayoutBinding.binding = 1;
				samplerLayoutBinding.descriptorCount = 1;
				samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
				samplerLayoutBinding.pImmutableSamplers = nullptr;
				samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

				std::array<VkDescriptorSetLayoutBinding, 2> bindings = { uboLayoutBinding, samplerLayoutBinding };
				VkDescriptorSetLayoutCreateInfo layoutInfo{};
				layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
				layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
				layoutInfo.pBindings = bindings.data();

				if (vkCreateDescriptorSetLayout(m_Device, &layoutInfo, nullptr, &m_DescriptorSetLayout) != VK_SUCCESS)
					throw std::runtime_error("Failed to create descriptor set layout!");
			}

			void CreateDescriptorPool()
			{
				std::array<VkDescriptorPoolSize, 2> poolSizes{};
				poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
				poolSizes[0].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
				poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
				poolSizes[1].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
				
				VkDescriptorPoolCreateInfo poolInfo {};
				poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
				poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
				poolInfo.pPoolSizes = poolSizes.data();
				poolInfo.maxSets = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

				if (vkCreateDescriptorPool(m_Device, &poolInfo, nullptr, &m_DescriptorPool) != VK_SUCCESS)
					throw std::runtime_error("Failed to create descriptor pool!");
			}

			void CreateDescriptorSets()
			{
				std::vector<VkDescriptorSetLayout> layouts(MAX_FRAMES_IN_FLIGHT, m_DescriptorSetLayout);
				VkDescriptorSetAllocateInfo allocInfo {};
				allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
				allocInfo.descriptorPool = m_DescriptorPool;
				allocInfo.descriptorSetCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
				allocInfo.pSetLayouts = layouts.data();

				m_DescriptorSets.resize(MAX_FRAMES_IN_FLIGHT);
				if (vkAllocateDescriptorSets(m_Device, &allocInfo, m_DescriptorSets.data()) != VK_SUCCESS)
					throw std::runtime_error("Failed to allocate descriptor sets!");

				for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i)
				{
					VkDescriptorBufferInfo bufferInfo {};
					bufferInfo.buffer = m_UniformBuffers[i];
					bufferInfo.offset = 0;
					bufferInfo.range = sizeof(uniformBufferObject);

					VkDescriptorImageInfo imageInfo {};
					imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
					imageInfo.imageView = m_TextureImageView;
					imageInfo.sampler = m_TextureSampler;

					std::array<VkWriteDescriptorSet, 2> descriptorWrites{};
					descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
					descriptorWrites[0].dstSet = m_DescriptorSets[i];
					descriptorWrites[0].dstBinding = 0;
					descriptorWrites[0].dstArrayElement = 0;
					descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
					descriptorWrites[0].descriptorCount = 1;
					descriptorWrites[0].pBufferInfo = &bufferInfo;

					descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
					descriptorWrites[1].dstSet = m_DescriptorSets[i];
					descriptorWrites[1].dstBinding = 1;
					descriptorWrites[1].dstArrayElement = 0;
					descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
					descriptorWrites[1].descriptorCount = 1;
					descriptorWrites[1].pImageInfo = &imageInfo;

					vkUpdateDescriptorSets(m_Device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
				}
			}

			// UNIFORM BUFFERS
			void CreateUniformBuffers()
			{
				VkDeviceSize bufferSize = sizeof(uniformBufferObject);

				m_UniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);
				m_UniformBufferMemory.resize(MAX_FRAMES_IN_FLIGHT);
				m_UniformBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);

				for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i)
				{
					CreateBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
						| VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_UniformBuffers[i], m_UniformBufferMemory[i]);

					vkMapMemory(m_Device, m_UniformBufferMemory[i], 0, bufferSize, 0, &m_UniformBuffersMapped[i]);
				}
			}

			void UpdateUniformBuffer(uint32_t currentFrame)
			{
				static auto startTime = std::chrono::high_resolution_clock::now();

				auto currentTime = std::chrono::high_resolution_clock::now();
				float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

				uniformBufferObject ubo;
				ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
				ubo.view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				ubo.ortho = glm::perspective(glm::radians(90.0f), m_SwapchainExtent.width / (float)m_SwapchainExtent.height, 0.1f, 10.0f);
				ubo.ortho[1][1] *= -1;

				memcpy(m_UniformBuffersMapped[currentFrame], &ubo, sizeof(ubo));
			}

			// HELPER FUNCTIONS
			VkCommandBuffer BeginSingleTimeCommands()
			{
				VkCommandBufferAllocateInfo allocInfo {};
				allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
				allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
				allocInfo.commandPool = m_CommandPool;
				allocInfo.commandBufferCount = 1;

				VkCommandBuffer commandBuffer;
				vkAllocateCommandBuffers(m_Device, &allocInfo, &commandBuffer);

				VkCommandBufferBeginInfo beginInfo {};
				beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
				beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
				
				vkBeginCommandBuffer(commandBuffer, &beginInfo);
				return commandBuffer;
			}

			void EndSingleTimeCommands(VkCommandBuffer commandBuffer)
			{
				vkEndCommandBuffer(commandBuffer);

				VkSubmitInfo submitInfo {};
				submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
				submitInfo.commandBufferCount = 1;
				submitInfo.pCommandBuffers = &commandBuffer;

				vkQueueSubmit(m_GraphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
				vkQueueWaitIdle(m_GraphicsQueue);

				vkFreeCommandBuffers(m_Device, m_CommandPool, 1, &commandBuffer);
			}

			void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height)
			{
				VkCommandBuffer commandBuffer = BeginSingleTimeCommands();

				VkBufferImageCopy region {};
				region.bufferOffset = 0;
				region.bufferRowLength = 0;
				region.bufferImageHeight = 0;

				region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
				region.imageSubresource.mipLevel = 0;
				region.imageSubresource.baseArrayLayer = 0;
				region.imageSubresource.layerCount = 1;

				region.imageOffset = { 0, 0, 0 };
				region.imageExtent =
				{
					width,
					height,
					1
				};

				vkCmdCopyBufferToImage(
					commandBuffer,
					buffer,
					image,
					VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
					1,
					&region
				);

				EndSingleTimeCommands(commandBuffer);
			}

			VkImageView CreateImageView(VkImage image, VkFormat format)
			{
				VkImageViewCreateInfo viewInfo{};
				viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
				viewInfo.image = image;
				viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
				viewInfo.format = format;
				viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
				viewInfo.subresourceRange.baseMipLevel = 0;
				viewInfo.subresourceRange.levelCount = 1;
				viewInfo.subresourceRange.baseArrayLayer = 0;
				viewInfo.subresourceRange.layerCount = 1;

				VkImageView imageView;
				if (vkCreateImageView(m_Device, &viewInfo, nullptr, &imageView) != VK_SUCCESS)
					throw std::runtime_error("Failed to create Texture Image View!");

				return imageView;
			}

			// TEXTURES
			void CreateImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory)
			{
				VkImageCreateInfo imageInfo{};
				imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
				imageInfo.imageType = VK_IMAGE_TYPE_2D;
				imageInfo.extent.width = static_cast<uint32_t>(width);
				imageInfo.extent.height = static_cast<uint32_t>(height);
				imageInfo.extent.depth = 1;
				imageInfo.mipLevels = 1;
				imageInfo.arrayLayers = 1;
				imageInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
				imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
				imageInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
				imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
				imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
				imageInfo.flags = 0;

				if (vkCreateImage(m_Device, &imageInfo, nullptr, &m_TextureImage) != VK_SUCCESS)
					throw std::runtime_error("Failed to create Image!");

				VkMemoryRequirements memRequirements;
				vkGetImageMemoryRequirements(m_Device, image, &memRequirements);

				VkMemoryAllocateInfo allocInfo {};
				allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
				allocInfo.allocationSize = memRequirements.size;
				allocInfo.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits, properties);

				if (vkAllocateMemory(m_Device, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS)
					throw std::runtime_error("Failed to allocae image memory!");

				vkBindImageMemory(m_Device, image, imageMemory, 0);
			}

			void CreateTextureImage(std::string path)
			{
				int textureWidth;
				int textureHeight;
				int numOfChannels;

				stbi_uc* pixels = stbi_load(path.c_str(), &textureWidth, &textureHeight, &numOfChannels, STBI_rgb_alpha);
				VkDeviceSize imageSize = textureWidth * textureHeight * 4;

				if (!pixels)
					throw std::runtime_error("Failed to load texture image!");

				VkBuffer stagingBuffer;
				VkDeviceMemory stagingBufferMemory;

				CreateBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
					| VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

				void* data;
				vkMapMemory(m_Device, stagingBufferMemory, 0, imageSize, 0, &data);
				memcpy(data, pixels, static_cast<size_t>(imageSize));
				vkUnmapMemory(m_Device, stagingBufferMemory);

				CreateImage(textureWidth, textureHeight, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT
					| VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_TextureImage, m_TextureImageMemory);

				stbi_image_free(pixels);

				TransitionImageLayout(m_TextureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
					CopyBufferToImage(stagingBuffer, m_TextureImage, static_cast<uint32_t>(textureWidth), static_cast<uint32_t>(textureHeight));
				TransitionImageLayout(m_TextureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

				vkDestroyBuffer(m_Device, stagingBuffer, nullptr);
				vkFreeMemory(m_Device, stagingBufferMemory, nullptr);
			}

			void CreateTextureImageView()
			{
				m_TextureImageView = CreateImageView(m_TextureImage, VK_FORMAT_R8G8B8A8_SRGB);
			}

			void CreateTextureSampler()
			{
				VkPhysicalDeviceProperties properties {};
				vkGetPhysicalDeviceProperties(m_PhysicalDevice, &properties);

				VkSamplerCreateInfo samplerInfo {};
				samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
				samplerInfo.magFilter = VK_FILTER_LINEAR;
				samplerInfo.minFilter = VK_FILTER_LINEAR;
				samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
				samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
				samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
				samplerInfo.anisotropyEnable = VK_TRUE;
				samplerInfo.maxAnisotropy = properties.limits.maxSamplerAnisotropy;
				samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
				samplerInfo.unnormalizedCoordinates = VK_FALSE;
				samplerInfo.compareEnable = VK_FALSE;
				samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
				samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
				samplerInfo.mipLodBias = 0.0f;
				samplerInfo.minLod = 0.0f;
				samplerInfo.maxLod = 0.0f;

				if (vkCreateSampler(m_Device, &samplerInfo, nullptr, &m_TextureSampler) != VK_SUCCESS)
					throw std::runtime_error("Failed to create a Texture Sampler!");
			}
			
			void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout)
			{
				VkPipelineStageFlags sourceStage;
				VkPipelineStageFlags destinationStage;
				VkCommandBuffer commandBuffer = BeginSingleTimeCommands();

				VkImageMemoryBarrier barrier{};
				barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
				barrier.oldLayout = oldLayout;
				barrier.newLayout = newLayout;
				barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
				barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
				barrier.image = image;
				barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
				barrier.subresourceRange.baseMipLevel = 0;
				barrier.subresourceRange.levelCount = 1;
				barrier.subresourceRange.baseArrayLayer = 0;
				barrier.subresourceRange.layerCount = 1;
				barrier.srcAccessMask = 0;
				barrier.dstAccessMask = 0;

				if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) 
				{
					barrier.srcAccessMask = 0;
					barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

					sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
					destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
				}
				else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
				{
					barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
					barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

					sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
					destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
				}
				else 
					throw std::invalid_argument("unsupported layout transition!");

				vkCmdPipelineBarrier(
					commandBuffer,
					sourceStage, destinationStage,
					0,
					0, nullptr,
					0, nullptr,
					1, &barrier
				);

				EndSingleTimeCommands(commandBuffer);
			}

			// Draw Frame 
			void DrawFrame()
			{
				uint32_t imageIndex;
				m_CurrentFrame = 0;

				vkWaitForFences(m_Device, 1, &m_InFlightFences[m_CurrentFrame], VK_TRUE, UINT64_MAX);

				VkResult result = vkAcquireNextImageKHR(m_Device, m_SwapChain, UINT64_MAX, m_ImageAvailableSemaphores[m_CurrentFrame], VK_NULL_HANDLE, &imageIndex);

				if (result == VK_ERROR_OUT_OF_DATE_KHR)
				{
					RecreateSwapChain();
					return;
				}
				else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
				{
					throw std::runtime_error("Failed to aquire swap chain image!");
				}

				UpdateUniformBuffer(m_CurrentFrame);

				vkResetFences(m_Device, 1, &m_InFlightFences[m_CurrentFrame]);

				vkResetCommandBuffer(m_CommandBuffers[m_CurrentFrame], 0);
				RecordCommandBuffer(m_CommandBuffers[m_CurrentFrame], imageIndex);

				VkSubmitInfo submitInfo{};
				submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

				VkSemaphore waitSemaphores[] = { m_ImageAvailableSemaphores[m_CurrentFrame]};
				VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
				submitInfo.waitSemaphoreCount = 1;
				submitInfo.pWaitSemaphores = waitSemaphores;
				submitInfo.pWaitDstStageMask = waitStages;
				submitInfo.commandBufferCount = 1;
				submitInfo.pCommandBuffers = &m_CommandBuffers[m_CurrentFrame];

				VkSemaphore signalSemaphores[] = { m_RenderFinishedSemaphores[m_CurrentFrame]};
				submitInfo.signalSemaphoreCount = 1;
				submitInfo.pSignalSemaphores = signalSemaphores;

				if (vkQueueSubmit(m_GraphicsQueue, 1, &submitInfo, m_InFlightFences[m_CurrentFrame]) != VK_SUCCESS)
					throw std::runtime_error("Failed to submit draw to the Command Buffer!");

				VkPresentInfoKHR presentInfo {};
				presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
				presentInfo.waitSemaphoreCount = 1;
				presentInfo.pWaitSemaphores = signalSemaphores;

				VkSwapchainKHR swapchains[] = { m_SwapChain };
				presentInfo.swapchainCount = 1;
				presentInfo.pSwapchains = swapchains;
				presentInfo.pImageIndices = &imageIndex;
				presentInfo.pResults = nullptr;

				result = vkQueuePresentKHR(m_PresentQueue, &presentInfo);

				if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || m_FramebufferResized)
				{
					m_FramebufferResized = false;
					RecreateSwapChain();
				}
				else if (result != VK_SUCCESS)
					throw std::runtime_error("Failed to present a swapchain image!");

				m_CurrentFrame = (m_CurrentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
			}

			// MEMORY
			uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
			{
				VkPhysicalDeviceMemoryProperties memProperties;
				vkGetPhysicalDeviceMemoryProperties(m_PhysicalDevice, &memProperties);

				for (uint32_t i = 0; i < memProperties.memoryTypeCount; ++i)
				{
					if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties))
						return i;
				}

				throw std::runtime_error("Failed to find suitable memory type!");
			}

			// VulkanRenderer2D functions
			void InitVulkan()
			{
				if (!m_IsInitialised)
				{
					CreateInstance();
					SetupDebugMessenger();
					CreateSurface();
					PickPhysicalDevice();
					CreateLogicalDevice();
					CreateSwapChain();
					CreateImageViews();
					CreateRenderPass();
					CreateCommandPool();
					CreateTextureImage("res/Textures/MrBean.png");
					CreateTextureImageView();
					CreateTextureSampler();
					CreateVertexBuffer();
					CreateIndexBuffer();
					CreateCommandBuffers();
					CreateUniformBuffers();
					CreateDescriptorPool();
					CreateDescriptorSetLayout();
					CreateDescriptorSets();
					CreateGraphicsPipeline();
					CreateFramebuffer();
					CreateSyncObjects();

					std::cout << "Renderer Initialised!" << std::endl;

					m_IsInitialised = true;
				}
			}

			void MainLoop()
			{
				DrawFrame();
			}

			void CleanUpSwapchain()
			{
				for (size_t i = 0; i < m_SwapChainFramebuffers.size(); ++i)
				{
					vkDestroyFramebuffer(m_Device, m_SwapChainFramebuffers[i], nullptr);
				}

				for (size_t i = 0; i < m_SwapChainFramebuffers.size(); ++i)
				{
					vkDestroyImageView(m_Device, m_SwapchainImageViews[i], nullptr);
				}

				vkDestroySwapchainKHR(m_Device, m_SwapChain, nullptr);
			}

			void CleanUp()
			{
				CleanUpSwapchain();

				vkDestroySampler(m_Device, m_TextureSampler, nullptr);
				vkDestroyImageView(m_Device, m_TextureImageView, nullptr);

				vkDestroyImage(m_Device, m_TextureImage, nullptr);
				vkFreeMemory(m_Device, m_TextureImageMemory, nullptr);

				for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
					vkDestroyBuffer(m_Device, m_UniformBuffers[i], nullptr);
					vkFreeMemory(m_Device, m_UniformBufferMemory[i], nullptr);
				}
				vkDestroyDescriptorPool(m_Device, m_DescriptorPool, nullptr);
				vkDestroyDescriptorSetLayout(m_Device, m_DescriptorSetLayout, nullptr);

				vkDestroyBuffer(m_Device, m_VertexBuffer, nullptr);
				vkFreeMemory(m_Device, m_VertexBufferMemory, nullptr);
				
				vkDestroyBuffer(m_Device, m_IndexBuffer, nullptr);
				vkFreeMemory(m_Device, m_IndexBufferMemory, nullptr);

				vkDestroyPipeline(m_Device, m_GraphicsPipeline, nullptr);
				vkDestroyPipelineLayout(m_Device, m_PipelineLayout, nullptr);
				vkDestroyRenderPass(m_Device, m_RenderPass, nullptr);

				for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i)
				{
					vkDestroySemaphore(m_Device, m_RenderFinishedSemaphores[i], nullptr);
					vkDestroySemaphore(m_Device, m_ImageAvailableSemaphores[i], nullptr);
					vkDestroyFence(m_Device, m_InFlightFences[i], nullptr);
				}

				if (enableValidationLayers)
					DestroyDebugUtilsMessengerEXT(m_VKInstance, m_DebugMessenger, nullptr);

				vkDestroyCommandPool(m_Device, m_CommandPool, nullptr);
				vkDestroyDevice(m_Device, nullptr);

				vkDestroySurfaceKHR(m_VKInstance, m_Surface, nullptr);
				vkDestroyInstance(m_VKInstance, nullptr);
			}

		private:
			VkInstance m_VKInstance;
			VkDebugUtilsMessengerEXT m_DebugMessenger;
			VkSurfaceKHR m_Surface;
			VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
			VkDevice m_Device;
			VkQueue m_GraphicsQueue;
			VkQueue m_PresentQueue;

			VkSwapchainKHR m_SwapChain;
			VkFormat m_SwapchainFormat;
			VkExtent2D m_SwapchainExtent;
			VkRenderPass m_RenderPass;
			VkDescriptorSetLayout m_DescriptorSetLayout;
			VkDescriptorPool m_DescriptorPool;
			VkPipelineLayout m_PipelineLayout;
			VkPipeline m_GraphicsPipeline;

			VkCommandPool m_CommandPool;
			std::vector<VkCommandBuffer> m_CommandBuffers;

			std::vector<VkSemaphore> m_ImageAvailableSemaphores;
			std::vector<VkSemaphore> m_RenderFinishedSemaphores;
			std::vector<VkFence> m_InFlightFences;

			std::vector<VkImage> m_SwapchainImages;
			std::vector<VkImageView> m_SwapchainImageViews;
			std::vector<VkFramebuffer> m_SwapChainFramebuffers;

			std::vector<VkDescriptorSet> m_DescriptorSets;
			
			VkBuffer m_VertexBuffer;
			VkDeviceMemory m_VertexBufferMemory;

			VkBuffer m_IndexBuffer;
			VkDeviceMemory m_IndexBufferMemory;

			std::vector<VkBuffer> m_UniformBuffers;
			std::vector<VkDeviceMemory> m_UniformBufferMemory;
			std::vector<void*> m_UniformBuffersMapped;

			VkImage m_TextureImage;
			VkDeviceMemory m_TextureImageMemory;
			VkImageView m_TextureImageView;
			VkSampler m_TextureSampler;

			uint32_t m_CurrentFrame = 0;
			bool m_FramebufferResized = false;

		private:
			Fuse2D::Window m_Window;
			bool m_IsInitialised = false;
	};

	class VulkanRenderer2D
	{
		public:
			VulkanRenderer2D() {}
			VulkanRenderer2D(Fuse2D::Window& window)
			{
				m_TriangleApp = HelloTriangleApp(&window);
			}
			
		public:
			void Init() { m_TriangleApp.InitRenderer(); }
			void Render() { m_TriangleApp.Render(); }

		private:
			HelloTriangleApp m_TriangleApp;
	};
}