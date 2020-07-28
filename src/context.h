#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include <vector>

namespace Excal
{
class Context
{
// Type declarations and definitions
public:
  struct DebugContext {
    bool                               enableValidationLayers;
    bool                               validationLayerSupport;
    std::vector<const char*>           validationLayers;
    VkDebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo;
  };

  struct SurfaceContext {
    GLFWwindow* window;
    vk::SurfaceKHR surface;
  };

  struct DeviceContext {
    vk::Instance            instance;
    vk::PhysicalDevice      physicalDevice;
    vk::Device              device;
    vk::Queue               graphicsQueue;
    vk::Queue               presentQueue;
    vk::SampleCountFlagBits msaaSamples;
  };

public:
  Context();

  DebugContext   debug;
  SurfaceContext surface;
  DeviceContext  device;
};
}
