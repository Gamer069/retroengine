#pragma once

namespace RetroEngine {
	enum class RenderAPI {
		None = 0,
		OpenGL = 1,
		DirectX = 2,
		Vulkan = 3,
	};
	class Renderer {
		public:
			inline static RenderAPI GetAPI() { return s_RenderAPI; }
		private:
			static RenderAPI s_RenderAPI;
	};
}