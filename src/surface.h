#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include "context.h"

namespace Excal
{
class Surface
{
private:
  GLFWwindow*    window;
  vk::SurfaceKHR surface;

  static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

  const uint32_t WIDTH  = 1440;
  const uint32_t HEIGHT = 900;

public:
  Surface();
  Excal::Context::SurfaceContext getContext();

  GLFWwindow*    initWindow();
  vk::SurfaceKHR createSurface(const vk::Instance& instance);
};
}
