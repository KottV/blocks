#pragma once
#include "BasePopup.h"
#include "LabelButton.h"
#include "PresetNameGenerator.h"

class SavePopup: public BasePopup {
public:
  LabelButton saveButton;
  TextEditor textEditor;

  SavePopup() {
    cornerRadius = 13.0f;

    addAndMakeVisible(saveButton);
    addAndMakeVisible(textEditor);

    saveButton.text.setText("save", dontSendNotification);
  }

  void setVisible(bool shouldBeVisible) override {
    BasePopup::setVisible(shouldBeVisible);
    if (shouldBeVisible) {
      textEditor.grabKeyboardFocus();
      textEditor.setText(PresetNameGenerator::generate(), dontSendNotification);
    }
  }

  ~SavePopup() override { }

  void resized() override {
    auto inset = 8.0f;
    auto buttonWidth = 37.0f;

    textEditor.setBounds(
      inset,
      inset,
      getWidth() - buttonWidth - inset * 3,
      getHeight() - inset * 2
    );

    saveButton.setBounds(
      textEditor.getRight(),
      textEditor.getY() - 2,
      getWidth() - textEditor.getRight(),
      textEditor.getHeight()
    );
  };

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SavePopup)
};