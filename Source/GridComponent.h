#pragma once

#include "BlockComponent.h"
#include "PlusComponent.h"
#include "GraphicsTimer.h"
#include "DotComponent.h"
#include "Index.h"
#include "BlockPlaceholder.h"
#include "GridItemComponent.h"

class GridComponent: public Component, public GridItemComponent::Listener {
public:
  struct Config {
    int itemHeight;
    int itemWidth;
    int edgeSpacing;
    int spacing;
    int rows;
    int columns;
    bool enablePlaceholder;
  };

  struct Listener;
  Listener* listener;

  MouseListener* mouseListener = nullptr;
  Colour colour;
  PlusComponent addButton;
  std::optional<Index> previousPlaceholderIndex;
  Path path;
  int currentPlaceholderLength = 1;
  Array<Array<Point<int>>> positions;

  virtual void gridItemEndedDrag(GridItemComponent* item, const MouseEvent& event) override;
  void gridItemIsStretching(GridItemComponent* item, int offset) override;
  void gridItemStretchEnded(GridItemComponent* item, int offset) override;
  void gridItemClicked(GridItemComponent* item, const MouseEvent& event) override;
  void gridItemIsDragging(GridItemComponent* item, const MouseEvent& event) override;
  void gridItemStartedDrag(GridItemComponent* item, const MouseEvent& event) override;

  GridComponent(Config config);
  void paint(Graphics&) override;

  Rectangle<int> boundsForItem(GridItemComponent* item, bool resetBounds = false);
  Rectangle<int> getModuleBounds() const;
  virtual Index indexForPoint(Point<int> point) const;
  Point<int> pointForIndex(Index index) const;

  virtual void clear();
  void show();
  void hide();
  void resnapBlock(GridItemComponent* moduleComponent);
  void detachModule(Index index, bool remove = true);
  void setConfig(Config configuration);
  virtual void snapItem(GridItemComponent* item, Index index, bool resetBounds = false);
  virtual void setItemLength(GridItemComponent* moduleComponent, int length);
  virtual void addItem(GridItemComponent* item, Index index, bool resetBounds = false);
  virtual void hideAllItems(bool hidden, GridItemComponent* ignore = nullptr);
  inline void setItemHidden(Index index, bool hidden) { if (auto item = itemMatrix[index.row][index.column]) item->setHidden(hidden); }

  /// Checks if the slot is taken and if so returns the parent item
  GridItemComponent* isSlotTaken(Index index, GridItemComponent* candidate);
  GridItemComponent* isSlotTaken(Index index);
  GridItemComponent* getModuleComponent(Index index);
  GridComponent::Config getConfig() { return config; }

  bool isIndexValid(Index currentIndex, Index targetIndex, int length);
  bool containsItem(const GridItemComponent* item) { return items.contains(item); }
  int getNumberOfItems() { return items.size(); }
  OwnedArray<GridItemComponent>& getItems() { return items; }
  Config config;
protected:
  std::vector<std::vector<GridItemComponent*>> itemMatrix;
  OwnedArray<GridItemComponent> items;

  inline bool isIndexInside(Index index) { return !isIndexOutside(index); }
  inline bool isIndexOutside(Index index) { return index.row >= config.rows || index.row < 0 || index.column >= config.columns || index.column < 0; }
  virtual void itemHovered(GridItemComponent* item, bool valid, bool inside, int proposedLength, Index index) {};
  virtual void itemLandedOutside(GridItemComponent* item, Index index) {};

  void mouseMove(const MouseEvent& event) override;
  void mouseExit(const MouseEvent& event) override;
  void mouseUp(const MouseEvent& event) override;
private:
  Index previousIndexUnderMouse = { -1, -1 };
  float sineX = 0.0f;
  float defaultAlpha = 0.25f;

  void showAddButton(Index index);
  void handleItemLandedInside(GridItemComponent* item, Index index);
  Point<int> getItemPosition(GridItemComponent* item);

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GridComponent)
};

struct GridComponent::Listener {
  virtual void clickedOnGrid(GridComponent* grid, Index index) = 0;
  virtual void gridItemClicked(GridComponent* grid, GridItemComponent* item, const MouseEvent& event) = 0;
  virtual void gridItemRemoved(GridComponent* grid, GridItemComponent* item) = 0;
  virtual void gridItemRepositioned(GridComponent* grid, GridItemComponent* item, Index oldIndex) = 0;
  virtual void gridItemHovered(GridComponent* grid, GridItemComponent* item, Index oldIndex) = 0;
  virtual void gridItemLengthChanged(GridComponent* grid, GridItemComponent* item, int length) = 0;
  virtual void gridItemStartedDrag(GridComponent* grid, GridItemComponent* item, const MouseEvent& mouseEvent) = 0;
  virtual void gridItemEndedDrag(GridComponent* grid, GridItemComponent* item, const MouseEvent& mouseEvent) = 0;
};