/*
  ==============================================================================

    DotComponent.cpp
    Created: 17 Oct 2020 2:25:47am
    Author:  Dan German

  ==============================================================================
*/

#include "DotComponent.h"
#include "ThemeManager.h"

DotComponent::DotComponent() { }
DotComponent::~DotComponent() { setName("DotComponent"); }

void DotComponent::paint(juce::Graphics& g) {
  g.setColour(ThemeManager::shared()->getCurrent().two);
  g.fillEllipse(getLocalBounds().toFloat());
}

void DotComponent::mouseMove(const MouseEvent& event) {
  Component::mouseMove(event);
}

void DotComponent::setColour(Colour colour) {
  this->colour = colour;
  repaint();
}