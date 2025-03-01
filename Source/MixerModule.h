/*
  ==============================================================================

    MixerModule.h
    Created: 15 Jul 2021 7:25:01pm
    Author:  Dan German

  ==============================================================================
*/

#pragma once

#include "Block.h"
#include "ModelConstants.h"
#include "ModuleParameter.h"

namespace Model {
  struct MixerModule: public Block {
    enum Parameters { pGain, pPan };

    MixerModule(int moduleNumber): Block(Model::Types::mixer, moduleNumber) {
      category = Module::Category::effect;

      createFloatParameter({ .name = "gain", .defaultValue = 0.0f });
      createFloatParameter({ .name = "pan", .defaultValue = 0.0f, .range = { -1.0f, 1.0f, 0.0001f } });
    }

    ~MixerModule() {}
  };
}