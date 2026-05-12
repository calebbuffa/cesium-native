#pragma once

#include <Cesium3DTilesSelection/Library.h>
#include <Cesium3DTilesSelection/ViewUpdateResult.h>

#include <vector>

namespace Cesium3DTilesSelection {

class Tile;
class TilesetFrameState;
class TilesetExternals;
struct TilesetOptions;
class TileOcclusionRendererProxy;

/**
 * @brief Per-frame inputs for the tile selection algorithm.
 */
struct TileSelectionContext {
  /** @brief The tileset configuration options. */
  const TilesetOptions& options;
  /** @brief External interfaces (asset accessor, task processor, etc.). */
  const TilesetExternals& externals;
  /** @brief Scratch buffer reused across frames. Contents on entry are
   * unspecified. */
  std::vector<double>& scratchDistances;
  /** @brief Scratch buffer reused across frames. Contents on entry are
   * unspecified. */
  std::vector<const TileOcclusionRendererProxy*>& scratchOcclusionProxies;
};

/**
 * @brief Runs the tile selection / LOD traversal algorithm.
 *
 * Populates `result` with the tiles to render this frame. The view group in
 * `frameState` also receives load queue updates.
 *
 * @pre `frameState.viewGroup.startNewFrame()` must be called before this
 * function.
 * @post `frameState.viewGroup.finishFrame()` must be called after this
 * function.
 * @pre `frameState.fogDensities` must have the same size as
 * `frameState.frustums`.
 *
 * @param context Configuration, external dependencies, and scratch buffers.
 * @param frameState Per-frame view parameters and the view group to update.
 * @param rootTile Root of the tile hierarchy to traverse.
 * @param result Filled with the selected tiles and statistics for this frame.
 *
 * @private
 */
CESIUM3DTILESSELECTION_API void selectTiles(
    const TileSelectionContext& context,
    const TilesetFrameState& frameState,
    Tile& rootTile,
    ViewUpdateResult& result);

} // namespace Cesium3DTilesSelection
