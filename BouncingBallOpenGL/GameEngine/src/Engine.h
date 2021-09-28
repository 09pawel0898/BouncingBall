#pragma once

#include "Engine/Core/Application.h"
#include "Engine/Core/Window.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Events/WindowEvent.h"
#include "Engine/States/StateManager.h"
#include "Engine/Resources/ResourceManager.h"
#include "Engine/Graphics/Sprite.h"

#define BIND_EVENT_FN(x) std::bind(&x, this,std::placeholders::_1)