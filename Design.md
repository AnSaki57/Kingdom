### Planning to be done here

### Things to include:
- Overall design and structure so far
- Bug fixes
- Things for later

## Structure

### Legend:
- Class
    - -> has a
    - <- is a
<br>

- Game
    - -> WorldMap
    - -> Player
    - -> TopCamera

- WorldMap
    - -> Chunk

- Chunk
    - -> Tile

- Tile
    - -> StationaryEntity
    - <- GrassTile
    - <- MudTile

- Entity
    - <- StationaryEntity
    - <- MobileEntry

- StationaryEntity
    - <- Tree

- MobileEntity
    - <- Player

## Design rationale