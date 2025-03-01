/*
  ==============================================================================

    UILayer.h
    Created: 27 Jun 2021 1:28:08am
    Author:  Dan German

  ==============================================================================
*/

#pragma once

#include "ModulatorsButton.h"
#include "BlocksButton.h"
#include "SideMenu.h"
#include "Modulation.h"
#include "PresetButtonComponent.h"
#include "KeyboardComponent.h"
#include "ValueAnimator.h"
#include "Module.h"
#include "ModulatorsListModel.h"
#include "ModulatorsSideMenu.h"
#include "ButtonGridPopup.h"
#include <juce_gui_basics/juce_gui_basics.h>
#include "SVGButton.h"
#include "SavePopup.h"

using Modulation = Model::Modulation;
using Module = Model::Module;

class UILayer: public juce::Component, ComponentMovementWatcher {
public:
  SideMenu matrix;
  ModulatorsSideMenu modulators;
  PresetButtonComponent presetButton;
  MidiKeyboardState keyboardState;
  KeyboardComponent keyboard;

  std::unique_ptr<SVGButton> settingsButton;
  std::unique_ptr<SVGButton> matrixButton;
  std::unique_ptr<SVGButton> saveButton;
  std::unique_ptr<SVGButton> newPresetButton;
  std::unique_ptr<SVGButton> themeButton;

  std::unique_ptr<ModulatorsButton> modulatorsButton;

  ModulationsListBoxModel modulationsListBoxModel;

  UILayer(Slider::Listener* listener);
  ~UILayer() override;

  void resized() override;
  void setModulations(Array<std::shared_ptr<Modulation>> modulationConnections);
  void setModulators(Array<std::shared_ptr<Module>> modulators);
  void componentMovedOrResized(bool wasMoved, bool wasResized) override {};
  void componentPeerChanged() override {};
  void componentVisibilityChanged() override {};
private:
  void addSVGButton(std::unique_ptr<SVGButton>& button, const char* rawData, size_t size);
  void resizePresetButton();
  void setupSideMenus();
  void setupKeyboard();
  void setupSettingsButton();
  void addModulatorsButton();
  void resizeModulatorsButton();
  void showModulatorsSideMenu();
  void resizeSettingsButton();
  void resizeSaveAndNewButtons();
  int edgeMargin = 16;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UILayer)
};
