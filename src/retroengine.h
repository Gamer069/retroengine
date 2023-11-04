#pragma once

#include "app.h"
#include "logging.h"
#include "entrypoint.h"
#include "layer.h"
#include "inp.h"
#include "key.h"
#include "imgui/imgui_layer.h"
#include "render/renderer.h"
#include "render/render_utils.h"
#include "render/shader.h"
#include "render/array.h"
#include "render/cam/orthographic.h"
#include "util/time.h"
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#define BIND_FN(x) std::bind(&x, this, std::placeholders::_1)
