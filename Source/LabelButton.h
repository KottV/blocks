#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "Index.h"
#include "BaseButton.h"
#include "ThemeManager.h"

using namespace juce;

class LabelButton: public BaseButton, public ThemeListener {
public:
  LabelButton();
  ~LabelButton() override;

  DrawablePath content;

  Label text;
  Path p;
  float fontSize = 15.0f;
  float selectedFontSize = 16.5f;

  void setButtonColour(Colour colour) override {
    this->colour = colour;
    repaint();
  };

  void paint(Graphics& g) override {}; // basebutton's paint sets colour from theme... this override is an empty function aka a lame hack
  void selectedAnimation(float value, float progress) override;
  void deselectedAnimation(float value, float progress) override;
  void deselectedCompletion() override;
  void selectedCompletion() override;
  void themeChanged(Theme theme) override;

  void resized() override;

  Component* getContent() override { return &content; };
};
