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
    - -> EntityManager
    - -> ResourceManager
    - -> FadeoutManager
    - -> TopCamera

#### Mapping subsystem
- WorldMap
    - -> Chunk

- Chunk
    - -> Tile

- Tile
    - <- GrassTile
    - <- MudTile
    - <- SandTile

#### Entity subsystem
- EntityManager
    - -> Entity

- Entity
    - <- StationaryEntity
    - <- MobileEntry

- StationaryEntity
    - <- Tree

- MobileEntity
    - -> ProgressBar
    - <- Player
    - <- Projectile
    - <- Enemy

- Player
    - -> Inventory

- Enemy

#### Resource subsystem
- ResourceManager
    - -> Resource

- Inventory
    - -> Resource

- Resource
    - <- Wood

#### Fadeout subsystem
- FadeoutManager
    - -> Fadeout

## Future ideas
1. ~Resources, inventory system~
2. Mining and harvesting, more stationaryEntities
3. Buildings
4. User profiles
5. Comprehensive debugging and error handling
6. Collisions
7. Weapons, enemies, and attacking
8. Music & sound fx
9. Better map generation (Perlin noise? Wave function collapse?)

## Lines of code
- No comments, no whitespaces:  1689 (using `cloc src/`)
- With comments/whitespaces:    2954 (using `sed -n '$=' src/* src/types/*`)