#include "render_utils.h"
#include "opengl/opengl_render_api.h"

namespace RetroEngine {
	RenderAPI* RenderUtils::s_API  = new OpenGLRenderAPI;
}