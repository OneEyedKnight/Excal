#include "debug.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>
#include <vector>
#include <iostream>

namespace Excal::Debug
{
std::vector<const char*> getValidationLayers()
{
  return { "VK_LAYER_KHRONOS_validation" };
}

bool checkValidationLayerSupport()
{
  auto availableLayers = vk::enumerateInstanceLayerProperties();

  // Check if all of the layers in validationLayers exist in availableLayers
  auto validationLayers = getValidationLayers();
  for (const char* layerName : validationLayers) {
    bool layerFound = false;

    for (const auto& layerProperties : availableLayers) {
      if (strcmp(layerName, layerProperties.layerName) == 0) {
        layerFound = true;
        break;
      }
    }

    if (!layerFound) {
      return false;
    }
  }

  return true;
}

VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
  VkDebugUtilsMessageSeverityFlagBitsEXT      messageSeverity,
  VkDebugUtilsMessageTypeFlagsEXT             messageType,
  const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
  void*                                       pUserData
) {
  std::cerr << std::endl << "validation layer: " << pCallbackData->pMessage << std::endl;

  return VK_FALSE;
}

VkDebugUtilsMessengerCreateInfoEXT getDebugMessengerCreateInfo()
{
  // Specify types of severities for callback to be called for
  vk::DebugUtilsMessageSeverityFlagsEXT severityFlags(
      vk::DebugUtilsMessageSeverityFlagBitsEXT::eError
    | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning
    | vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose
    | vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo
  );

  // Specify message types that callback is notified for
  vk::DebugUtilsMessageTypeFlagsEXT messageTypeFlags(
      vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation
    | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance
    //| vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral
  );

  return VkDebugUtilsMessengerCreateInfoEXT(
    vk::DebugUtilsMessengerCreateInfoEXT(
      {}, severityFlags, messageTypeFlags, &debugCallback
    )
  );
}
}
