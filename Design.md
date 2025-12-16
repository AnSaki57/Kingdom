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

## Future ideas
1. Resources, inventory system
2. Mining and harvesting, more stationaryEntities
3. Buildings
4. User profiles
5. Comprehensive debugging and error handling
6. Collisions
7. Weapons, enemies, and attacking
8. Music & sound fx

## Lines of code
- No comments:     ~580
- With comments:    787