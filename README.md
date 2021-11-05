# Pokémon FireRed Speedchoice

This project is based on the disassembly of Pokémon FireRed and LeafGreen.

To set up the repository, see [INSTALL.md](INSTALL.md).

## Contacts

You can find us on [Discord](https://discord.gg/keizaron), in the #roms-and-mods channel. Be sure to read the rules on joining.

## Changelog
### 1.0.0a0
- Ported the speedchoice menu from [Emerald](https://github.com/ProjectRevoTPP/pokeemerald-speedchoice)
- Ported the Done Button from Emerald
- Ported stat counters for Done Button
- Ported B/W experience logic
- Ported X items buff logic
- Implemented "Early Surf"
- Implemented "Easy dex requirements"
- Implemented plotless logic
- Implemented badge requirement nerfs
- Ported fast egg hatch
- Ported nice menu order
- Ported max vision logic
- Ported spinners logic
- Ported new wild encounter slots
- Ported better early wilds
- Implemented better marts
- Ported instant text
- Removed the help messages at the start of the game
- Removed the tutorial messages in Rival 1
- Removed quest log on continue
- Implemented "Easy False Swipe"
- Implemented "Early Bike"
- Ported "Run Indoors"
- Skipped naming prompts at the start of the game because they're covered by the speedchoice menu
- Ported inigen from Emerald

### 1.0.0a1
- Fixed a bug where leveling up set your HP to 1
- Updates plotless item logic and declares offsets in inigen

### 1.0.0a2
- Updated HM badge requirement nerf to affect overworld use
- Updated handling for Rival 1 battle
- Speed up battles
- Safari zone step counters are now Inf

### 1.0.0a3
- Disabled the cutesy anim when using an item on a party Pokemon in the field

### 1.0.0a4
- Fix desynced intro anims
- Fix mon faint anim overlapping cry
- HP/EXP bar speedup
- Fix Rare Candy evos cancellable in Evo Every Level
- Allow Pokemon to evolve into later-gen targets pre-national dex

### 1.0.0a5
- Patch Unown generation loop

### 1.0.0a6
- Fix good early wilds
- Fix randomizer compatibility

### 1.0.0a7
- Minor tweaks to HP bar logic

### 1.0.0a8
- Finalize HP bar logic
- Minimum catch rate
- Disable map previews

### 1.0.0a9
- Fix graphical glitches
- Remove extra level-up anim
- Make all Altering Cave encounters accessible

### 1.0.0b1
- Put Moon Stone and Sun Stone in Celadon Dept Store 4F
- Fishing is guaranteed to hook a Pokemon if possible
- Add a shady salesman to Cerulean City that gives a guaranteed Rare Candy
- Replaced TM09 Bullet Seed with Sweet Scent (item ball in Mt Moon 1F)
- Divorced instant text and hold-to-mash
- Enabled switch button on fly map

### 1.0.0b2
- Fixed a bug in instant text introduced in the previous version
- Fixed alignment of speedchoice version string
- Fixed a bug that blocks progression onto Cycling Road

### 1.0.0b3
- Add Escape option to the start menu
- Added Plotless hook on Bill in Cinnabar
- Added option to nerf Lt. Surge's trash cans.

### 1.0.0b4
- Hell trash cans now reroll on save&quit
- Why trash cans
- Guaranteed Rock Smash encounters
- Fixed revocation of Rainbow Pass effectiveness after completing Lostelle quest
- Fixed Altering Cave exit warps
- Add Luxury Ball, Lax Incense, Sea Incense, and Heart Scale to Two Island Shop
- Add dex beep
- Revert TM09 to Bullet Seed, and set TM27 to Sweet Scent

### 1.0.0b5
- Fix issues with the Lift Key and Card Key not working properly in plotless
- Secondary fix for revocation of Rainbow Pass effectiveness after completing Lostelle quest
- Fix Surge trash cans settings HELL and WHY becoming NERF and KEEP, respectively

### 1.0.0rc1
- Print version on continue screen
- Add extra tag to copyright screen
- Add error screen if emulator is incorrectly configured
- Add instruction prefetch accuracy test
- Removed inaccessible encounter slots on Route 21 South
- Add encounter slots to penultimate floor of Mt Ember Ruby Path

### 1.0.0rc2
- Fix bug with Card Key unconditionally not working

### 1.0.0rc3
- Implement "use another repel"
- Random stories from the Vermilion Fan Club Chairman
- Fix Sweet Scent not usable in the overworld because it was mapped to Bullet Seed instead
- Don't give Tri Pass if you already have Rainbow Pass
- Old Man is a speedy boi
- Fix bug with max vision
- Add dev mode that gives you a level 100 Mewtwo right off the bat
- Fix full-plotless oversights
- Fix problems with Rainbow Pass check being performed incorrectly
- Fix message box persisting when declining additional repel use

### 1.0.0
- Fix forgot move message
- Document Surge WHY in tooltip
- Logic for E4 round 2 unlock in plotless
- Fix misplaced window in Pokedex covering up type icons
- Add Race Goal option
- Initial bag has Bicycle on top
- Correctly init the Two Island shop
- Early Saffron separate from Plotless
- Fix glitch rod by making there be two encounter slots per rod instead of two fishing slots total

### 1.0.1
- Hotfix Early Saffron

### 1.1.0
- Refactor Speedchoice-related code (devs: breaks API)
- Fix bug with Silph Scope door at Giovanni
- Remove options for and enables unconditionally: instant text, run everywhere, new wild encounters, better marts, nice menu order, fast egg hatch
- Implements Brock nerf

### 1.1.1
- Bundle RELEASE.txt

### 1.1.2
- Hold-to-mash is disabled in the speedchoice menu tooltips

## See also

Other disassembly and/or decompilation projects:
* [**Pokémon Red and Blue**](https://github.com/pret/pokered)
* [**Pokémon Gold and Silver (Space World '97 demo)**](https://github.com/pret/pokegold-spaceworld)
* [**Pokémon Yellow**](https://github.com/pret/pokeyellow)
* [**Pokémon Trading Card Game**](https://github.com/pret/poketcg)
* [**Pokémon Pinball**](https://github.com/pret/pokepinball)
* [**Pokémon Stadium**](https://github.com/pret/pokestadium)
* [**Pokémon Gold and Silver**](https://github.com/pret/pokegold)
* [**Pokémon Crystal**](https://github.com/pret/pokecrystal)
* [**Pokémon Ruby and Sapphire**](https://github.com/pret/pokeruby)
* [**Pokémon Pinball: Ruby & Sapphire**](https://github.com/pret/pokepinballrs)
* [**Pokémon Emerald**](https://github.com/pret/pokeemerald)
* [**Pokémon Mystery Dungeon: Red Rescue Team**](https://github.com/pret/pmd-red)
